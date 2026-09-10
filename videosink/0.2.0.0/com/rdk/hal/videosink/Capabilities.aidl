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
package com.rdk.hal.videosink;

/**
 *  @brief     Video Sink capabilities parcelable definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 *
 *  Per-instance, immutable Video Sink capabilities, populated by the SoC
 *  vendor from the HAL Feature Profile (`hfp-videosink.yaml`). The values
 *  returned by `IVideoSink.getCapabilities()` must not change between calls
 *  for the lifetime of the Video Sink instance.
 */
@VintfStability
parcelable Capabilities
{
    /**
     * Indicates whether this Video Sink instance can synchronise frame
     * presentation against an AV Clock. When `false`, the sink presents
     * frames as soon as they are decoded (best-effort display).
     * Mirrors `IVideoSink[i].supportsAVSync` in the HFP.
     */
    boolean supportsAVSync;

    /**
     * Vendor-characterised latency, in nanoseconds, between the moment a
     * frame is committed for display and the moment it is actually scanned
     * out on the display. Used by AV-sync logic to compensate for sink
     * pipeline delay. Mirrors `IVideoSink[i].vsyncDisplayLatencyNs` in the
     * HFP.
     */
    long vsyncDisplayLatencyNs;

    /**
     * Indicates whether this Video Sink instance can hold and continue to
     * display the most recent frame after the upstream source stops
     * delivering frames (for example on `stop()` or underflow), rather than
     * blanking the output. Mirrors `IVideoSink[i].supportsHoldLastFrame`
     * in the HFP.
     */
    boolean supportsHoldLastFrame;

    /**
     * Indicates whether this Video Sink instance is able to operate in
     * Secure Video Path (SVP) mode and consume buffers carrying protected
     * content. Mirrors `IVideoSink[i].supportsSecure` in the HFP.
     */
    boolean supportsSecure;
}
