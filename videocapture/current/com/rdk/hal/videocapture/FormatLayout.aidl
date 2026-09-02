/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.videocapture;

/**
 *  @brief     A pixel format and a memory layout that are valid together.
 *
 *  A pair, because a modifier is valid with particular formats: most are
 *  vendor-namespaced tiling or compression layouts that apply to specific formats
 *  and bit depths. A client selects one entry of
 *  `Capabilities.supportedFormats` and passes it to
 *  `IVideoCaptureController.setFormat()`.
 *
 *  Both values are defined by the Linux kernel in `include/uapi/drm/drm_fourcc.h`
 *  and are carried as integers rather than enums: the kernel owns those
 *  namespaces, and new formats and layouts arrive with new kernel versions. They
 *  pass through this interface to the client's EGL implementation without
 *  interpretation.
 *
 *  @see Capabilities.supportedFormats
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable FormatLayout
{
    /** DRM FOURCC pixel format, e.g. `DRM_FORMAT_NV12` (0x3231564E). */
    int fourcc;

    /**
     * DRM format modifier valid with `fourcc`, e.g. `DRM_FORMAT_MOD_LINEAR` (0).
     *
     * A modifier is 64 bits composed as `(vendor << 56) | value`: the top 8 bits
     * are a registered vendor namespace and the rest means whatever that vendor
     * says. `DRM_FORMAT_MOD_LINEAR` (0) is the one vendor-neutral layout, and the
     * only one a client that must touch the pixels can rely on.
     */
    long modifier;
}
