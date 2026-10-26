/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
 *  @brief     Dolby Vision dual-layer presence flags.
 *
 *  Indicates whether a Dolby Vision Base Layer (BL) and/or Enhancement
 *  Layer (EL) are present in the bitstream, as signalled in the container.
 *  This lets the decoder configure the correct dual-stream DV decode mode
 *  before decoding begins.
 *
 *  A BL-only stream is a standard HEVC/AVC-compatible stream with Dolby
 *  Vision RPU metadata. A BL+EL stream carries an additional enhancement
 *  layer for full Dolby Vision quality.
 *
 *  Only applicable when the stream DynamicRange is DOLBY_VISION.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
parcelable DolbyVisionLayerFlags {

    /**
     * true if a Dolby Vision Base Layer is present.
     */
    boolean blPresent;

    /**
     * true if a Dolby Vision Enhancement Layer is present.
     */
    boolean elPresent;
}
