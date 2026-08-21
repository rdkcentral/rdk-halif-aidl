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
package com.rdk.hal.capture;

/**
 *  @brief     The point in the pipeline a capture session binds to.
 *
 *  A capture takes frames from one stage of the pipeline. This enum names the
 *  stages a capture can bind to; `CaptureCapabilities.supportedSources` declares
 *  which of them a given product offers.
 *
 *  This is not the AV input. What flows through the bound stage is decided by
 *  the input feed as it always was, and a capture neither selects nor changes it.
 *  These values say where frames are taken from, not what they contain.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum CaptureSource {

    /** No source bound. */
    NONE = 0,

    /**
     * Frames as the video decoder produces them, before any presentation
     * processing. What decode-to-texture wants: the decoded frame itself.
     */
    VIDEO_DECODER = 1,

    /**
     * Frames at the video sink, after presentation processing has been applied.
     * What the sink is about to present.
     */
    VIDEO_SINK = 2,

    /**
     * Frames at the point the AV clock releases them for presentation, so the
     * capture follows the same timing the presentation path does.
     */
    AV_CLOCK = 3,
}
