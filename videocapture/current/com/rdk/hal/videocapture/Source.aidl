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
 *  @brief     The kinds of pipeline stage a capture session can bind to.
 *
 *  A capture takes frames from one stage of the pipeline. This enum names the
 *  stages a capture can bind to; `Capabilities.supportedSources` declares
 *  which of them a given product offers, and
 *  `IVideoCaptureManager.getSupportedSources()` the union across the product's
 *  captures.
 *
 *  A session names its source by calling the matching attach method with the
 *  resource's own ID - `IVideoCapture.openWithDecoder()` for `VIDEO_DECODER`,
 *  `IVideoCapture.openWithSink()` for `VIDEO_SINK`. This enum declares what a
 *  product can do; it does not itself select an instance, which is why it has no
 *  unbound value.
 *
 *  This is not the AV input. What flows through the bound stage is decided by
 *  the input feed as it always was, and a capture neither selects nor changes it.
 *  These values say where frames are taken from, not what they contain.
 *
 *  @author    Gerald Weatherup
 */
@VintfStability
@Backing(type="int")
enum Source {

    /**
     * Frames as the video decoder produces them, before any presentation
     * processing. No clock is applied: nothing is dropped for being late and
     * nothing held for being early. Bound through
     * `IVideoCapture.openWithDecoder()`.
     */
    VIDEO_DECODER = 1,

    /**
     * Frames at the video sink, after presentation processing has been applied
     * and at the point the sink presents them. A capture bound here follows the
     * same timing the presentation path does, because the sink is where the AV
     * clock's synchronisation has already been applied. Bound through
     * `IVideoCapture.openWithSink()`.
     */
    VIDEO_SINK = 2,
}
