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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
package com.rdk.hal.datasource;

import com.rdk.hal.datasource.MemoryType;
import com.rdk.hal.datasource.Plane;
import com.rdk.hal.datasource.BufferMeta;

/**
 * @brief    A typed reference to shared memory produced by a data source.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * The single container that expresses every buffer-bearing payload in the media
 * pipeline: a ring slice (MAPPABLE, one plane), an AVBuffer frame (SECURE_OPAQUE,
 * handle), a graphics framebuffer (DMABUF, one plane + stride) and a capture slot
 * (DMABUF, planar + pts).
 *
 * A buffer has one or more backings, and each plane references a backing by index
 * plus an offset within it. This carries both platform layouts with one shape:
 *
 *   - single shared backing, offset-addressed planes — `fds`/`handles` has one
 *     entry; planes differ by `offset` (single fd, many offsets);
 *   - one backing per plane/slot — `fds`/`handles` has one entry per plane, each
 *     plane at `offset` 0 (many fds, zero offset, e.g. Broadcom NEXUS surfaces).
 *
 * The backing lists are exchanged when the source is configured; on a stable-
 * backing source they do not change per buffer, so the steady frame loop carries
 * only plane offsets and the id.
 *
 * Prior art: Android AHardwareBuffer / graphics.common HardwareBuffer (a
 * native_handle carrying multiple fds), PipeWire spa_buffer (n_datas, each with
 * its own fd), GStreamer GstBuffer (multiple GstMemory).
 */
@VintfStability
parcelable BufferDescriptor {
    /** How the backings are stored and accessed. */
    MemoryType memoryType;

    /**
     * Backing file descriptors for MAPPABLE and DMABUF. One entry for a shared,
     * offset-addressed backing; one entry per plane/slot for the per-fd layout.
     * Empty for SECURE_OPAQUE. Planes select an entry via Plane.backingIndex.
     */
    ParcelFileDescriptor[] fds;

    /**
     * Opaque backing tokens for SECURE_OPAQUE, resolvable only by a trusted
     * entity. Same one-shared-or-one-per-plane rule as `fds`. Empty for
     * MAPPABLE / DMABUF. Callers compare for equality only.
     */
    long[] handles;

    /** One plane for a byte blob; one per plane for planar formats. */
    Plane[] planes;

    /**
     * Identity for release correlation (acquire id / ring slot). Required where
     * per-backing offsets are all 0 and cannot distinguish slots. 0 = none.
     */
    long id;

    /** Present for framed, self-describing buffers; absent for a raw byte stream. */
    @nullable BufferMeta meta;
}
