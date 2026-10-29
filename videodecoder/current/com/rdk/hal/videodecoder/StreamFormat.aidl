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
package com.rdk.hal.videodecoder;

/**
 *  @brief     H.264/H.265 input stream format: how NAL units are delimited
 *             in the buffers passed to `decodeBufferWithMetadata()`.
 *
 *  @see BitstreamFormat
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum StreamFormat {
    /**
     * Annex B byte stream: each NAL unit is preceded by a start code
     * (`00 00 01` or `00 00 00 01`). Parameter sets are carried in-band.
     * GStreamer `stream-format=byte-stream`.
     * ITU-T H.264 Annex B, ITU-T H.265 Annex B.
     */
    BYTE_STREAM = 0,

    /**
     * Each NAL unit is preceded by its length, big-endian, in
     * `lengthSizeMinusOne + 1` bytes as given by the avcC/hvcC record
     * supplied as codec-specific data. GStreamer `stream-format=avc`,
     * `hvc1` or `hev1`.
     * ISO/IEC 14496-15.
     */
    LENGTH_PREFIXED = 1
}
