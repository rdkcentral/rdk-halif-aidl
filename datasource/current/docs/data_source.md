# Data Source

The **Data Source HAL** defines a common typed buffer descriptor and a single consumer contract for reading data from a source in the media pipeline.

- A **data source** presents data — a byte stream or a sequence of framed buffers — that a consumer reads through one `acquire` / `release` lifecycle.
- A **buffer descriptor** is a typed reference to shared memory: a mappable segment, a dma-buf, or a secure-opaque handle, addressed by one or more planes.
- The **memory type** and **delivery mode** are negotiated between producer and consumer, so the same consumer reads a dma-buf on a target platform and a mappable segment on a reference host without change.
- A source classifies its origin with `AVSource` (IP, tuner, system, HDMI, composite).

## References

!!! info References
    |||
    |-|-|
    |**Interface Definition**|[datasource/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/develop/datasource/current)|
    |**Interface Version**|`current`|
    | **API Documentation** | *TBD - Doxygen* |
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|
    |**VTS Tests**| TBC |
    |**Reference Implementation - vComponent**|**TBD**|
    |**RFC / rationale**|[Issue #668](https://github.com/rdkcentral/rdk-halif-aidl/issues/668)|

## Related Pages

!!! tip "Related Pages"
    - [AV Buffer](../avbuffer/av_buffer.md)
    - [Video Decoder](../videodecoder/video_decoder.md)
    - [Plane Control](../planecontrol/plane_control.md)
    - [Broadcast](../broadcast/broadcast.md)

## Implementation Requirements

|#|Requirement|Comments|
|-|-----------|--------|
|**HAL.DSRC.1**|A data source shall expose a single consume lifecycle: `configure()` → `start()` → (`acquire()` / `release()`)\* → `stop()`.||
|**HAL.DSRC.2**|`configure()` shall negotiate the memory type from the consumer's accepted mask and the delivery mode, and fix both for the session.|Consumer declares a bitmask of accepted `MemoryType`.|
|**HAL.DSRC.3**|A buffer descriptor shall carry its backings as a list — `fds` for `MAPPABLE` / `DMABUF`, or `handles` for `SECURE_OPAQUE` — and each plane shall reference one backing by index plus an offset within it.||
|**HAL.DSRC.4**|`SECURE_OPAQUE` buffers cannot be mapped into an unprivileged process and shall meet secure video / audio path requirements.|Resolvable only by a trusted entity. Mirrors `HAL.AVBUF.7`.|
|**HAL.DSRC.5**|In `STREAM` mode, `acquire(size)` shall return a region of up to `size` bytes; `release(descriptor, size)` may release a prefix, advancing the read position by that amount.|Partial release supports progressive assembly.|
|**HAL.DSRC.6**|In `FRAMED` mode, `acquire()` shall return one complete, self-describing buffer (planes + meta); `release()` shall return the whole slot for reuse.||
|**HAL.DSRC.7**|A source shall signal readiness through `IDataSourceListener.onDataAvailable()`; implementations may coalesce notifications.||
|**HAL.DSRC.8**|`abortAcquire()` shall unblock a thread waiting in `acquire()` and shall have no effect when no call is blocked.||
|**HAL.DSRC.9**|The backing file descriptor(s) shall be exchanged at negotiation; the steady-state `acquire` / `release` loop shall not require a per-buffer file-descriptor transfer.|Enables an off-binder frame loop over a shared index.|
|**HAL.DSRC.10**|A source shall report its origin via `getSource()` using `AVSource`.||
|**HAL.DSRC.11**|Both backing layouts shall be representable: a single shared backing with offset-addressed planes (single fd, many offsets), and one backing per plane at offset 0 (many fds, zero offset). Where offsets cannot distinguish slots, `id` carries the release identity.|Broadcom NEXUS exports a per-surface fd per slot; other SoCs export one ring fd.|
|**HAL.DSRC.12**|A source shall report the memory accounting of its buffer pool via `getMemoryStats()`: total allocated backing bytes, the mapped subset, and the pool / acquired buffer counts. `mappedBytes` shall be 0 for a `SECURE_OPAQUE` session.|Each consumer holds its own `IDataSource`, so the figures are attributable to one consumer — pipeline memory usage is visible and a leak is traceable to its owner.|

## Interface Definition

|Interface Definition File|Description|
|-------------------------|-----------|
|`IDataSource.aidl`|The consumer contract: configure, start, acquire, release, stop.|
|`IDataSourceListener.aidl`|Data-ready, end-of-stream and error callbacks.|
|`BufferDescriptor.aidl`|Typed reference to shared memory: memory type + backing list (`fds` / `handles`) + planes + id + meta.|
|`MemoryType.aidl`|Backing and access discriminator: `MAPPABLE`, `DMABUF`, `SECURE_OPAQUE`.|
|`Plane.aidl`|One addressable region: `{backingIndex, offset, stride, size}`.|
|`BufferMeta.aidl`|Optional per-buffer PTS / format / dimensions / flags.|
|`DeliveryMode.aidl`|`STREAM` (byte-window) or `FRAMED` (whole-buffer).|
|`MemoryStats.aidl`|Buffer-pool accounting: allocated / mapped bytes + pool / acquired counts.|

## The Buffer Descriptor

A `BufferDescriptor` is the single container that expresses every buffer-bearing payload in the pipeline. It decomposes a buffer along three axes:

| Axis | Values | Field |
|---|---|---|
| **Backing / access** | `MAPPABLE` · `DMABUF` · `SECURE_OPAQUE` | `MemoryType memoryType` |
| **Backings** | one shared, or one per plane | `ParcelFileDescriptor[] fds` / `long[] handles` |
| **Shape** | single blob · N planes | `Plane[] planes` (each `{backingIndex, offset, stride, size}`) |
| **Identity** | acquire id / ring slot | `long id` |

### Per-platform buffer layout

A buffer carries a *list* of backings, and each plane references one by `backingIndex` plus an `offset`. This is the same abstraction Android's `native_handle` (multiple fds) and PipeWire's `spa_data[]` (one fd per data) use, and it represents both layouts SoCs actually produce with no special case in consumer code:

| Layout | `fds` / `handles` | Planes | Seen on |
|---|---|---|---|
| **Single fd, many offsets** | one shared entry | each plane `backingIndex = 0`, distinct `offset` | one ring dma-buf — most SoCs |
| **Many fds, zero offset** | one entry per plane / slot | each plane its own `backingIndex`, `offset = 0` | per-surface dma-buf — Broadcom NEXUS |

For NV12 with a single shared ring fd: `fds = [ringFd]`, planes `= [{0, yOffset, yStride, ySize}, {0, uvOffset, uvStride, uvSize}]`. For a per-surface SoC: `fds = [yFd, uvFd]`, planes `= [{0, 0, yStride, ySize}, {1, 0, uvStride, uvSize}]`. Because per-surface offsets are all 0 and cannot distinguish slots, `id` carries the release identity.

Optional `BufferMeta` carries presentation timing, pixel format, dimensions and flags for framed, self-describing buffers; it is absent for an undifferentiated byte stream, where the consumer derives structure from the negotiated format.

## Negotiation

`configure()` takes a bitmask of the memory types the consumer can accept and the requested delivery mode. The source intersects the mask with what it can produce and returns the selected `MemoryType`, fixed for the session. The same consumer code therefore runs against a dma-buf on a target platform and a mappable segment on a reference host, because `MemoryType` abstracts the backing.

## Delivery Modes

- **`STREAM`** — byte-window delivery over a contiguous backing. `acquire(size)` returns a region of up to `size` bytes at the current read position; `release()` may release a prefix, advancing the read position. Buffers carry no meta.
- **`FRAMED`** — whole-buffer delivery from a set of slots. `acquire()` returns one complete buffer (planes + meta); `release()` returns that slot for reuse.

## Consolidating Existing Surfaces

Each existing buffer-bearing surface is a binding of this interface:

| Surface | Delivery mode | Memory type | Shape |
|---|---|---|---|
| `IRingBufferSource` | `STREAM` | `MAPPABLE` | one plane, moving offset |
| `IAVBuffer` (consume) | `FRAMED` | `SECURE_OPAQUE` / `MAPPABLE` | one blob, handle |
| `IGraphicsFbProvider` | `FRAMED` | `DMABUF` | one plane + stride |
| `ICapture` | `FRAMED` | `DMABUF` | NV12 planes + `meta.pts` |

### Wrapping the Ring Buffer

`IRingBuffer` is the `STREAM` binding. Its consumer-side requirements map directly:

| `IRingBuffer` requirement | Data Source equivalent |
|---|---|
| `getFileDescriptor()` — one shared, mmap-able fd | `BufferDescriptor.fd` with `MemoryType.MAPPABLE`, exchanged at `configure()` |
| `acquire(size)` → `{id, offset, size}` | `acquire(size)` → `BufferDescriptor` (single plane at `offset`, `size`) |
| `release(id, size)`, partial release of a prefix | `release(descriptor, size)` with `size` ≤ acquired (`HAL.DSRC.5`) |
| offset-addressed read/write into mapped memory | `Plane.offset` into the mapped backing |
| `setBlocking(true/false)` | blocking vs non-blocking `acquire()` fixed at `configure()` |
| `abortAcquire()` | `abortAcquire()` (`HAL.DSRC.8`) |
| `onDataAvailable(size)` / `onSpaceAvailable(size)` | `IDataSourceListener.onDataAvailable(available)` |
| error codes (`PRODUCER_DISCONNECTED`, …) | `IDataSourceListener.onError(code, message)` |
| DMA-backed backing behind the fd (custom driver) | `MemoryType.DMABUF` on the same descriptor, negotiated |
| "no out-of-band sync besides the interface" | backing + wakeup exchanged at `configure()`; steady loop off binder (`HAL.DSRC.9`) |

The ring's byte-granular `acquire` / partial-`release` — its distinguishing feature — is the `STREAM` delivery mode. The one thing the ring leaves as prose (a DMA-backed backing reachable through the fd) becomes an explicit, negotiated `MemoryType`, so a consumer knows whether it may mmap the region or must import it.

## Initialization

The vendor layer provides the systemd unit that starts a data-source service and registers its interface with the [Service Manager](../vsi/service_manager/current/service_manager.md).

## Relationship to AVSource

`common/current/com/rdk/hal/AVSource.aidl` classifies where a stream originates. `IDataSource.getSource()` returns an `AVSource` so a consumer can identify the origin of what it reads. `AVSource` names the origin; `IDataSource` is the contract for reading from it.
