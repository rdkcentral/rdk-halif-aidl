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

/**
 * @brief    One addressable region within a data-source buffer.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * A plane is addressed by a (backing, offset) pair: `backingIndex` selects one of
 * the descriptor's backings and `offset` is the byte position within it. This one
 * shape expresses both platform layouts:
 *
 *   - one shared backing, planes at different offsets (single fd, many offsets);
 *   - one backing per plane, each at offset 0 (many fds, zero offset).
 *
 * A byte-blob payload uses a single plane. Planar video uses one plane per plane
 * (e.g. NV12 = Y, then interleaved UV).
 *
 * Prior art: Android gralloc PlaneLayout, PipeWire spa_data + spa_chunk,
 * GStreamer GstVideoMeta.
 */
@VintfStability
parcelable Plane {
    /**
     * Index of the backing this plane lives in: into BufferDescriptor.fds for
     * MAPPABLE / DMABUF, or into BufferDescriptor.handles for SECURE_OPAQUE.
     */
    int backingIndex;

    /** Byte offset of this plane within its backing. 0 when each plane has its own backing. */
    long offset;

    /** Row stride in bytes. 0 for non-image / byte-stream payloads. */
    int stride;

    /** Number of valid bytes in this plane. */
    long size;
}
