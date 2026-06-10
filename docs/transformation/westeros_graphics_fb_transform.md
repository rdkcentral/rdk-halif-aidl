# Transforming Westeros onto IGraphicsFbProvider

## Purpose

This document describes how the Westeros compositor (and its successor) is
transformed to render through the Plane Control HAL's graphics frame buffer
interface, `IGraphicsFbProvider`, replacing the per-vendor Westeros GL
backends with a single, platform-agnostic implementation.

The HAL contract is vendor-agnostic and complete: it covers EGL display
setup, DMA-buf buffer allocation, and presentation. The compositor needs
exactly those three things, so all SoC-specific graphics code moves below
the HAL boundary and is implemented once per platform.

Related interface: [`planecontrol/current`](../../planecontrol/current/docs/plane_control.md).
Related issues: #603 (this work), #329 (PlaneControl controller audit),
issue #33 (Graphics allocation / Gralloc review), #62 (VSI Graphics specification).

---

## 1. The interface the compositor consumes

A graphics plane exposes a provider, obtained from `IPlaneControl`:

```aidl
@nullable IGraphicsFbProvider getGraphicsFbProvider(
    in int planeResourceIndex,
    in IGraphicsFbProviderListener graphicsFbProviderListener);
```

`IGraphicsFbProvider` gives the compositor all three things it needs:

```aidl
@VintfStability
interface IGraphicsFbProvider {
    // EGL setup — replaces vendor-specific native display initialisation
    long getNativeDisplayHandle();
    int  getEGLPlatformType();

    // Buffer lifecycle — replaces GBM / Nexus allocation
    GraphicsFbCapabilities getCapabilities();
    ParcelFileDescriptor   createGraphicsFb(in int width, in int height, out GraphicsFbInfo outInfo);
    void                   destroyGraphicsFb(in int graphicsFbId);

    // Presentation — replaces drmModeSetPlane / NEXUS_SurfaceClient
    boolean commitGraphicsFb(in int graphicsFbId);
}

@VintfStability
oneway interface IGraphicsFbProviderListener {
    void onGraphicsFbReleased(in int oldGraphicsFbId, in long elapsedRealtimeNanos);
}
```

The buffer metadata is split deliberately: per-frame geometry travels in
`GraphicsFbInfo`, while the pixel format and modifier — constant for a
given provider — travel in `GraphicsFbCapabilities`.

```aidl
@VintfStability
parcelable GraphicsFbInfo {
    int graphicsFbId;   // identifies the buffer
    int pixelWidth;     // EGL_WIDTH
    int pixelHeight;    // EGL_HEIGHT
    int stride;         // bytes per row  (EGL_DMA_BUF_PLANE0_PITCH_EXT)
    int offset;         // bytes to pixel data (EGL_DMA_BUF_PLANE0_OFFSET_EXT)
}

@VintfStability
parcelable GraphicsFbCapabilities {
    int  maxGraphicsFrameBuffers;
    int  maxGraphicsFbWidth;
    int  maxGraphicsFbHeight;
    int  format;        // opaque pass-through value, known to the client EGL implementation
    long modifier;      // opaque pass-through value, known to the client EGL implementation
}
```

Three properties of the contract drive the compositor code and are easy to
get wrong:

- **`format` and `modifier` are provider-level capabilities, not per-frame.**
  Read them once from `getCapabilities()`, not from `GraphicsFbInfo`. They are
  **opaque** values passed through the interface without interpretation by the
  HAL — "known to the client EGL implementation." On DRM-class platforms they
  are a DRM fourcc and a DRM modifier and map directly to the EGL import
  attributes below; the interface does not mandate that encoding.
- **The returned file descriptor may be shared across buffers.**
  `createGraphicsFb()` "can be called multiple times… The returned file
  descriptor can be the same for all created graphics frame buffers." Buffers
  are distinguished by `offset`, so the EGL import must key on `GraphicsFbInfo.offset`
  and must not assume one fd per buffer.
- **`getGraphicsFbProvider()` is `@nullable`.** A plane that is not of type
  `GRAPHICS` returns null; confirm the plane type via `IPlaneControl.getCapabilities()`
  first.

---

## 2. What EGL actually needs to import a buffer

The [`EGL_EXT_image_dma_buf_import`](https://registry.khronos.org/EGL/extensions/EXT/EGL_EXT_image_dma_buf_import.txt)
extension defines exactly the metadata required to import a DMA-buf into EGL
on Linux. Every field maps to something the provider hands back:

| EGL attribute | Source |
|---|---|
| `EGL_DMA_BUF_PLANE0_FD_EXT` | the `ParcelFileDescriptor` from `createGraphicsFb()` |
| `EGL_WIDTH` / `EGL_HEIGHT` | `GraphicsFbInfo.pixelWidth` / `pixelHeight` |
| `EGL_DMA_BUF_PLANE0_PITCH_EXT` | `GraphicsFbInfo.stride` |
| `EGL_DMA_BUF_PLANE0_OFFSET_EXT` | `GraphicsFbInfo.offset` |
| `EGL_LINUX_DRM_FOURCC_EXT` | `GraphicsFbCapabilities.format` |
| `EGL_DMA_BUF_PLANE0_MODIFIER_LO/HI_EXT` | `GraphicsFbCapabilities.modifier` |

None of these attributes are allocator-specific. They are DRM/EGL standards
and apply regardless of how the buffer was allocated underneath the HAL.

---

## 3. The problem today: a GL backend per vendor

Westeros currently requires a different GL backend per SoC family. Each one
re-implements EGL display init, buffer allocation, and presentation:

| Backend | Lines | Source |
|---|---|---|
| `westeros-gl-brcm` (Broadcom / Nexus) | 530+ | [rdkcentral/westeros-gl-brcm](https://github.com/rdkcentral/westeros-gl-brcm) |
| `westeros-gl-drm` (generic DRM / GBM) | 8,384 | [rdkcentral/westeros-gl-drm](https://github.com/rdkcentral/westeros-gl-drm) |
| `westeros-soc-mtk` (Mediatek) | 3,936 | [rdk-e/westeros-soc-mtk](https://github.com/rdk-e/westeros-soc-mtk) |
| `westeros-sink-soc-realtek` | vendor-specific | [rdk-e/westeros-sink-soc-realtek](https://github.com/rdk-e/westeros-sink-soc-realtek) |

Each backend handles the same three concerns differently:

1. **EGL display initialisation** — vendor-specific native display type.
2. **Buffer allocation** — GBM on DRM, Nexus on Broadcom.
3. **Buffer presentation** — `drmModeSetPlane` on DRM, `NEXUS_SurfaceClient` on Broadcom.

Every new SoC needs a new backend; every bug fix may need porting across all
of them. The architecture does not scale.

---

## 4. The transformation: one platform-agnostic Westeros

The provider supplies the EGL display, the renderable buffers, and the
presentation lifecycle, so one implementation works on every vendor. The
SoC differences (GBM vs Nexus allocation, DRM vs Nexus presentation) live
entirely inside the vendor HAL.

```cpp
// ONE Westeros GL backend — works on every vendor
void init(sp<IPlaneControl> planeControl, int planeIndex) {
    provider = planeControl->getGraphicsFbProvider(planeIndex, listener);
    // provider is @nullable: confirm the plane is GRAPHICS before calling.

    // 1. EGL setup — platform-agnostic, no vendor native-display code path
    EGLDisplay dpy = eglGetPlatformDisplay(
        provider->getEGLPlatformType(),
        (void*)provider->getNativeDisplayHandle(), nullptr);
    eglInitialize(dpy, nullptr, nullptr);
    EGLContext ctx = eglCreateContext(dpy, config, EGL_NO_CONTEXT, ctxAttrs);

    // 2. Format/modifier are provider-level capabilities — read once.
    GraphicsFbCapabilities caps = provider->getCapabilities();

    // 3. Allocate frame buffers (triple-buffered)
    for (int i = 0; i < 3; i++) {
        GraphicsFbInfo info;
        frames[i].pfd = provider->createGraphicsFb(1920, 1080, &info);
        frames[i].id  = info.graphicsFbId;

        // 4. Import into EGL — identical on every vendor. Note: fd may be shared
        //    across buffers; geometry is per-buffer, so key on info.offset.
        EGLAttrib attrs[] = {
            EGL_WIDTH,                          info.pixelWidth,
            EGL_HEIGHT,                         info.pixelHeight,
            EGL_LINUX_DRM_FOURCC_EXT,           caps.format,
            EGL_DMA_BUF_PLANE0_FD_EXT,          frames[i].pfd.get(),
            EGL_DMA_BUF_PLANE0_OFFSET_EXT,      info.offset,
            EGL_DMA_BUF_PLANE0_PITCH_EXT,       info.stride,
            EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT, (uint32_t)(caps.modifier),
            EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT, (uint32_t)(caps.modifier >> 32),
            EGL_NONE
        };
        frames[i].image = eglCreateImageKHR(dpy, EGL_NO_CONTEXT,
                                            EGL_LINUX_DMA_BUF_EXT, nullptr, attrs);

        // Back an FBO with the imported EGLImage
        glGenTextures(1, &frames[i].texture);
        glBindTexture(GL_TEXTURE_2D, frames[i].texture);
        glEGLImageTargetTexture2DOES(GL_TEXTURE_2D, frames[i].image);
        glGenFramebuffers(1, &frames[i].fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, frames[i].fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, frames[i].texture, 0);
        frames[i].available = true;
    }
}

void renderAndPresent() {
    Frame& f = nextAvailableFrame();
    glBindFramebuffer(GL_FRAMEBUFFER, f.fbo);
    renderScene();
    glFinish();
    provider->commitGraphicsFb(f.id);   // non-blocking; returns false on unknown id
    f.available = false;
}

// IGraphicsFbProviderListener callback
void onGraphicsFbReleased(int oldGraphicsFbId, long elapsedRealtimeNanos) {
    findFrame(oldGraphicsFbId).available = true;   // oldGraphicsFbId == -1 on first release
}
```

This replaces ~13,000 lines of vendor-specific GL backend code with one
implementation that talks only standard EGL/GL — no GBM, no Nexus, no
vendor `#include`.

---

## 5. Why a DMA-buf FD is the universal transport

A DMA-buf is a Linux kernel object (`struct dma_buf`) that wraps physical
memory as a shareable, reference-counted file descriptor. It is the export
wrapper, not the memory itself.

```
        Caller sees: DMA-buf file descriptor (standard Linux kernel object)
                                  │
                       Kernel: struct dma_buf
                       - reference counted across processes
                       - exportable as FD via Binder
                       - importable by GPU, display, video HW
                                  │ backed by
                ┌─────────────────┼─────────────────┐
            CMA pages          GEM heap        Nexus-managed
            (RTK / AML)        (DRM)            (Broadcom)
```

The physical memory may be CMA, a GEM heap, vendor carveout, or Nexus-managed
memory. Any kernel driver that manages physical memory can implement the
exporter callbacks (`struct dma_buf_ops`). This is why the interface names no
allocator: the DMA-buf FD is the universal transport, and the allocation
behind it is vendor-specific and hidden by the kernel.

### DRM platforms (Realtek, Amlogic, Mediatek)

These use the standard Linux DRM/GBM stack. The vendor HAL wraps it:

```c
// DRM vendor HAL — wraps kernel GBM allocation
ParcelFileDescriptor createGraphicsFb(int w, int h, GraphicsFbInfo* info) {
    struct gbm_bo* bo = gbm_bo_create(gbm, w, h,
        GBM_FORMAT_ARGB8888, GBM_BO_USE_SCANOUT | GBM_BO_USE_RENDERING);
    info->stride = gbm_bo_get_stride(bo);
    info->offset = gbm_bo_get_offset(bo, 0);
    // format/modifier are reported once via getCapabilities():
    //   gbm_bo_get_format(bo), gbm_bo_get_modifier(bo)
    return ParcelFileDescriptor(gbm_bo_get_fd(bo));
}
```

### Broadcom (Nexus) — no GBM, same DMA-buf result

Broadcom has no DRM/KMS or GBM. Allocation goes through the proprietary
Nexus userspace API, then exports a kernel DMA-buf FD:

```c
// Broadcom vendor HAL — Nexus allocation + kernel DMA-buf export
ParcelFileDescriptor createGraphicsFb(int w, int h, GraphicsFbInfo* info) {
    NEXUS_SurfaceCreateSettings settings;
    NEXUS_Surface_GetDefaultCreateSettings(&settings);
    settings.width = w; settings.height = h;
    settings.pixelFormat = NEXUS_PixelFormat_eA8_R8_G8_B8;
    NEXUS_SurfaceHandle surface = NEXUS_Surface_Create(&settings);
    int fd = nexus_surface_export_dmabuf(surface);   // kernel DMA-buf export
    info->stride = settings.pitch;
    info->offset = 0;
    return ParcelFileDescriptor(fd);
}
```

That this works on Broadcom is not speculative. Broadcom's own DME player
framework already exports Nexus surfaces as DMA-buf FDs and imports them into
EGL with exactly the metadata this interface carries
(`BSEAV/lib/dme/player/texturing/TextureData.cpp`, Broadcom refsw
`refsw_release_unified_URSR_26_*`):

```c
// TextureData.cpp — Broadcom already uses EGL_LINUX_DMA_BUF_EXT on Nexus surfaces
uint32_t fourcc; uint64_t modifier;
NexusToDrm(status.pixelFormat, &fourcc, &modifier);   // Nexus format → DRM fourcc/modifier
int fd;
NEXUS_Surface_CreateDescriptor_driver(surface, &fd);  // Nexus → DMA-buf FD export

EGLint attr[] = {
    EGL_WIDTH,                          (EGLint)status.width,
    EGL_HEIGHT,                         (EGLint)status.height,
    EGL_LINUX_DRM_FOURCC_EXT,           (EGLint)fourcc,
    EGL_DMA_BUF_PLANE0_FD_EXT,          fd,
    EGL_DMA_BUF_PLANE0_OFFSET_EXT,      (EGLint)properties.pixelMemoryOffset,
    EGL_DMA_BUF_PLANE0_PITCH_EXT,       (EGLint)status.pitch,
    EGL_DMA_BUF_PLANE0_MODIFIER_HI_EXT, (EGLint)(modifier >> 32),
    EGL_DMA_BUF_PLANE0_MODIFIER_LO_EXT, (EGLint)(modifier & 0xffffffff),
    EGL_NONE
};
eglImage = eglCreateImageKHR(eglGetCurrentDisplay(),
    EGL_NO_CONTEXT, EGL_LINUX_DMA_BUF_EXT, nullptr, attr);
```

`NexusToDrm()` maps Nexus pixel formats to DRM fourcc codes and modifiers
(including `DRM_FORMAT_MOD_BROADCOM_UIF` for tiled formats). The chain is pure
Nexus → kernel DMA-buf → EGL, with no GBM anywhere. The Broadcom graphics HAL
performs this same sequence internally and returns the FD as
`ParcelFileDescriptor` and the geometry as `GraphicsFbInfo`.

---

## 6. Why the HAL allocates, not the client

On DRM platforms the kernel already provides displayable buffer allocation
via GBM and [DMA-buf heaps](https://docs.kernel.org/userspace-api/dma-buf-heaps.html):
the driver knows which memory is scanout-capable and which formats/modifiers
the display planes support. A "client allocates" model (as in
[Wayland linux-dmabuf-v1](https://wayland.app/protocols/linux-dmabuf-v1))
works there because the kernel interface is standard.

It does not work on Broadcom: there is no standard DRM/KMS path, and allocation
goes through Nexus. A client-allocates model would force the middleware to know
about Nexus, breaking the abstraction. Allocating in the HAL keeps the vendor
interface difference below the boundary: the compositor calls
`createGraphicsFb()` and never learns which kernel path was used.

---

## 7. Android precedent

This mirrors Android's proven graphics buffer model:

| Android | RDK (this design) |
|---|---|
| `IAllocator` HAL (AIDL) | `IGraphicsFbProvider` (AIDL) |
| `HardwareBuffer` (FD + metadata) | `ParcelFileDescriptor` + `GraphicsFbInfo` |
| `eglGetNativeClientBufferANDROID()` → opaque import | `eglCreateImageKHR(EGL_LINUX_DMA_BUF_EXT)` → explicit metadata |
| `IComposerClient.presentDisplay()` | `commitGraphicsFb()` |
| `IComposerClient` display config | `getNativeDisplayHandle()` + `getEGLPlatformType()` |
| Vendor gralloc implementation | Vendor HAL: GBM on DRM, Nexus on Broadcom |

The architecture is identical — vendor-opaque allocation behind a standard
HAL, with the compositor never touching vendor code. The only difference is
the EGL import extension: Linux uses `EGL_EXT_image_dma_buf_import` with
explicit DRM metadata where Android uses an opaque `HardwareBuffer`.

---

## 8. What the transformation eliminates

| Component | Status | Replaced by |
|---|---|---|
| `westeros-gl-brcm` (530+ lines) | Eliminated | `IGraphicsFbProvider` vendor HAL |
| `westeros-gl-drm` (8,384 lines) | Eliminated | `IGraphicsFbProvider` vendor HAL |
| `westeros-soc-mtk` (3,936 lines) | Eliminated | `IGraphicsFbProvider` vendor HAL |
| Essos EGL abstraction | Eliminated when retired | `getNativeDisplayHandle()` / `getEGLPlatformType()` |
| Custom FD-transport header (`GraphicsDmaBufFrameFd.h`) | Eliminated | `ParcelFileDescriptor` (built-in AIDL) |
| `getNativeGraphicsWindowHandle()` | Eliminated | `createGraphicsFb()` returns a DMA-buf FD |
| `flipGraphicsBuffer()` | Eliminated | `commitGraphicsFb()` |

The compositor becomes a single, portable, vendor-agnostic implementation
that talks standard EGL/GL. All vendor complexity moves below the HAL,
implemented once per SoC and validated through VTS.

---

## 9. Reference implementation: `plane-control-poc`

The [`rdk-e/graphics-test-apps`](https://github.com/rdk-e/graphics-test-apps)
repository contains a working proof of concept (`plane-control-poc/`) that is
this design prototyped over a Unix socket instead of Binder. Its wire protocol
is `IGraphicsFbProvider` in all but name:

| `PlaneControllerProtocol.h` message | `IGraphicsFbProvider` |
|---|---|
| `CreateBufferRequest { width, height }` | `createGraphicsFb(width, height, outInfo)` |
| `CreateBufferResponse { buffer_id, width, height, stride, offset, format, fd }` | `GraphicsFbInfo` + `ParcelFileDescriptor` |
| `DestroyBufferRequest { buffer_id }` | `destroyGraphicsFb(graphicsFbId)` |
| `CommitBufferRequest { buffer_id }` | `commitGraphicsFb(graphicsFbId)` |
| `ReleaseBufferEvent { buffer_id }` | `onGraphicsFbReleased(oldGraphicsFbId, …)` |

It was tested on Amlogic (`apache-4k-mtc`); Realtek (`xione`) is in progress;
Broadcom is blocked pending URSR 25.3, which adds the EGL DMA-buf *target*
support the import path needs.

**What it validates.** The POC confirms the load-bearing parts of this design
on real hardware:

- **DMA-buf FD + metadata is a sufficient cross-process transport.** The server
  passes the FD over the socket via `SCM_RIGHTS` alongside `stride`/`offset`/
  `format`; under Binder this becomes `ParcelFileDescriptor` + `GraphicsFbInfo`.
- **The server is a thin GBM wrapper.** `drm-backend.cpp` allocates with
  `gbm_bo_create[_with_modifiers]()` and exports with `gbm_bo_get_fd()`,
  reading `gbm_bo_get_stride/offset/modifier()` — exactly the DRM vendor-HAL
  shape in §5, presenting through a DRM atomic commit (`notes.txt`).
- **The client import is standard EGL.** `OpenGLClient.cpp` imports the FD with
  `eglCreateImageKHR(EGL_LINUX_DMA_BUF_EXT)` using `EGL_LINUX_DRM_FOURCC_EXT` +
  `EGL_DMA_BUF_PLANE0_FD/OFFSET/PITCH_EXT`, then binds it to a texture/FBO —
  exactly §2 and §4.

**What the POC has not yet done — the work this design adds.** Bringing it onto
the merged interface means closing these gaps:

- **EGL display setup is still vendor-coupled.** The client opens
  `/dev/dri/card0`, calls `gbm_create_device()`, and hardcodes
  `eglGetPlatformDisplay(EGL_PLATFORM_GBM_KHR, gbm, …)`. That is the exact code
  path `getNativeDisplayHandle()` + `getEGLPlatformType()` exist to remove. Per
  this design the client must take both from the provider and never touch the
  DRM node or GBM — this is also what lets Broadcom, which has no `card0`/GBM,
  work through the same client.
- **No modifier is carried.** The protocol transports `format` only and assumes
  linear. The server already knows the modifier (`gbm_bo_get_modifier()`); it
  must be surfaced through `GraphicsFbCapabilities.modifier` and fed to
  `EGL_DMA_BUF_PLANE0_MODIFIER_LO/HI_EXT`, which tiled formats (Amlogic AFBC,
  `DRM_FORMAT_MOD_BROADCOM_UIF`) require.
- **`format` is per-buffer in the POC**, but is constant per provider — it
  belongs in `GraphicsFbCapabilities`, read once.
- **The transport is a raw socket**, to be replaced by the `IGraphicsFbProvider`
  Binder service.

The POC therefore de-risks the design and is the natural starting point for the
Amlogic vendor HAL; the transformation is to retarget its client onto the Binder
interface and drive EGL setup through the provider rather than the DRM node.

---

## Sources

### EGL / DRM
- [EGL_EXT_image_dma_buf_import](https://registry.khronos.org/EGL/extensions/EXT/EGL_EXT_image_dma_buf_import.txt)
- [EGL_EXT_image_dma_buf_import_modifiers](https://github.com/KhronosGroup/EGL-Registry/blob/main/extensions/EXT/EGL_EXT_image_dma_buf_import_modifiers.txt)
- [DRM format modifiers — Collabora](https://www.collabora.com/news-and-blog/blog/2017/02/09/notes-on-drm-format-modifiers/)

### Linux kernel
- [DMA-BUF driver API](https://docs.kernel.org/driver-api/dma-buf.html)
- [DMA-BUF heaps](https://docs.kernel.org/userspace-api/dma-buf-heaps.html)

### Broadcom refsw
- `refsw_release_unified_URSR_26_20260331-bme.tgz` — `BSEAV/lib/dme/player/texturing/TextureData.cpp`:
  `NEXUS_Surface_CreateDescriptor_driver()` DMA-buf export, `NexusToDrm()` format mapping,
  `eglCreateImageKHR(EGL_LINUX_DMA_BUF_EXT)` import.

### RDK vendor GL backends
- [westeros-gl-brcm](https://github.com/rdkcentral/westeros-gl-brcm) — Broadcom Nexus GL backend (no GBM)
- [westeros-gl-drm](https://github.com/rdkcentral/westeros-gl-drm) — DRM/GBM GL backend
- [westeros-soc-mtk](https://github.com/rdk-e/westeros-soc-mtk) — Mediatek GL backend
- [westeros](https://github.com/rdkcentral/westeros) — main compositor
- [essos](https://github.com/rdkcentral/essos) — EGL/input abstraction (to be retired)

### Android
- [AIDL for Hardware Composer HAL](https://source.android.com/docs/core/graphics/aidl-hwc)
- [BufferQueue and Gralloc](https://source.android.com/docs/core/graphics/arch-bq-gralloc)
