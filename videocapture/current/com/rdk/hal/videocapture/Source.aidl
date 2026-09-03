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

import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.videosink.IVideoSink;

/**
 *  @brief     The pipeline stage a capture session takes its frames from.
 *
 *  A capture is an output in its own right, and what it names is a source rather than
 *  a resource it belongs to. The two arms are the two stages that hold decoded frames,
 *  and which one a session names decides what the frames mean:
 *
 *  - `videoSinkId` - the frames the sink would be presenting, under whatever
 *    presentation mode that sink is running.
 *  - `videoDecoderId` - the frames the decoder has produced, in the order it produced
 *    them.
 *
 *  A capture declares which sources it serves in `Capabilities.supportedSources`, and
 *  the union is the same type in both places: what a client may pass to
 *  `IVideoCapture.open()` is exactly what the capability lists.
 *
 *  A further stage arrives as a further arm. AIDL has no method overloading, so a
 *  second `open()` could never be added - a union keeps `open()` one method for the
 *  life of the interface and makes a new source additive.
 *
 *  @author    Gerald Weatherup
 */

@VintfStability
union Source
{
    /** A video sink, by its own ID, as the frame source. */
    IVideoSink.Id videoSinkId;

    /** A video decoder, by its own ID, as the frame source. */
    IVideoDecoder.Id videoDecoderId;
}
