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
 *  @brief     H.264/H.265 input buffer alignment: how much of the stream
 *             one buffer passed to `decodeBufferWithMetadata()` holds.
 *
 *  @see BitstreamFormat
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type = "int")
enum Alignment {
    /**
     * One buffer holds exactly one complete access unit: all the NAL units
     * of one coded picture, usually several. GStreamer `alignment=au`.
     */
    AU = 0,

    /**
     * One buffer holds exactly one complete NAL unit.
     * GStreamer `alignment=nal`.
     */
    NAL = 1
}
