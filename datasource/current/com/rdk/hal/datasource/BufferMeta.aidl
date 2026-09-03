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
 * @brief    Optional per-buffer metadata carried in-band with a data-source buffer.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * Present when the source produces framed, self-describing buffers (video
 * frames, timed audio). Absent for an undifferentiated byte stream, where the
 * consumer derives structure from the negotiated format. Keeping timing and
 * format with the buffer makes a frame atomic, rather than split across a
 * separate metadata call.
 *
 * Prior art: PipeWire spa_meta_header, Android gralloc metadata + Dataspace.
 */
@VintfStability
parcelable BufferMeta {
    /** Presentation timestamp in nanoseconds. Long.MIN_VALUE when not present. */
    long presentationTimeNs;

    /** Decode timestamp in nanoseconds. Long.MIN_VALUE when not present. */
    long decodeTimeNs;

    /** DRM FOURCC of the pixel format, or 0 for non-image / unspecified. */
    int fourcc;

    /** Visible width in pixels, or 0 when not applicable. */
    int width;

    /** Visible height in pixels, or 0 when not applicable. */
    int height;

    /**
     * Bitmask of buffer flags.
     *
     * FLAG_KEYFRAME      (1 << 0) - random-access point.
     * FLAG_DISCONTINUITY (1 << 1) - a gap precedes this buffer.
     * FLAG_CORRUPTED     (1 << 2) - payload is known to be damaged.
     * FLAG_END_OF_STREAM (1 << 3) - last buffer of the stream.
     */
    int flags;
}
