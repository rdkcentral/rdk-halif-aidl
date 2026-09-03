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

import com.rdk.hal.videocapture.FormatLayout;
import com.rdk.hal.videocapture.Source;
import com.rdk.hal.videodecoder.Codec;

/**
 *  @brief     Video capture capabilities definition for a capture resource.
 *
 *  Describes what frames this capture resource can deliver and how its buffer pool
 *  behaves. This is the whole of the capture declaration: a client reads it, selects
 *  from it through `IVideoCaptureController.setFormat()`, and the vendor layer configures whatever it needs
 *  to on the decoder to satisfy the selection.
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable Capabilities
{
    /**
     * Indicates the behaviour when every buffer in the pool is locked by the client and
     * the decoder has a new frame to write.
     *
     * When true, the decoder stalls until a buffer is released.
     * When false, the oldest Ready buffer is recycled and its frame is dropped.
     * Decode proceeds at full rate in both cases for as long as buffers are available.
     */
    boolean stallsWhenPoolExhausted;

    /**
     * The pixel format and memory layout pairs this capture resource can deliver.
     *
     * Paired, because a modifier is not valid with every format: most modifiers are
     * vendor-namespaced tiling or compression layouts that apply to particular
     * formats and bit depths. Declaring two independent lists would offer a client
     * the full cross-product, most of which a capture cannot deliver, and leave it to
     * find out at `start()`.
     *
     * A client selects one entry and passes it to
     * `IVideoCaptureController.setFormat()`.
     *
     * These are the pairs this product can deliver, and the whole of them. A client
     * that can handle none of them cannot capture from this resource.
     */
    FormatLayout[] supportedFormats;

    /**
     * The maximum frame width in pixels this capture resource can deliver.
     *
     * @see Property.WIDTH
     */
    int maxFrameWidth;

    /**
     * The maximum frame height in pixels this capture resource can deliver.
     *
     * @see Property.HEIGHT
     */
    int maxFrameHeight;

    /**
     * The video codecs whose decoded frames this capture can take.
     *
     * Capture is not required of every codec a platform can decode. A decoder opened
     * for a codec outside this list decodes and displays normally; what it cannot do is
     * feed a capture.
     *
     * @see com.rdk.hal.videodecoder.Codec
     */
    Codec[] supportedCodecs;

    /**
     * Whether this capture can deliver frames at a resolution other than the one the
     * bound source is decoding.
     *
     * When false, the capture's `Property.WIDTH` and `HEIGHT` must equal the resolution the
     * bound source decodes to, and `IVideoCaptureController.start()` fails with
     * `ErrorCode.RESOLUTION_MISMATCH` if they do not. Nothing is scaled: the
     * frames the client receives are the frames the decoder produced.
     *
     * Declaring false is what keeps the tested surface small - a capture that never
     * scales has no scaling quality to validate and no resolution permutations to
     * cover.
     *
     * @see Property.WIDTH, Property.HEIGHT, ErrorCode.RESOLUTION_MISMATCH
     */
    boolean resize;

    /**
     * How many capture sessions one source can carry at once on this resource.
     *
     * A source already carrying this many captures refuses a further bind with
     * `ErrorCode.SOURCE_UNAVAILABLE`. One is the common case; a product that can fan
     * one source out to several captures declares more.
     *
     * The limit is per source, not per capture resource: two sessions on different
     * sources do not count against each other.
     */
    int maxCapturesPerSource;

    /**
     * The pipeline sources this capture resource can take frames from, and the whole
     * of them.
     *
     * Every source a session may be opened against is listed here, by the same `Source`
     * union a client passes to `IVideoCapture.open()` - so what the capability lists is
     * exactly what `open()` accepts, and a client enumerates rather than discovering a
     * pairing by a failed bind.
     *
     * The declaration is centralised here rather than on each source's own
     * capabilities, because capture is a module in its own right: what can be captured
     * from is a property of the capture, and a source carries no capture vocabulary.
     *
     * A source absent from this list fails `open()` with
     * `ErrorCode.SOURCE_NOT_CAPTURABLE`.
     *
     * @see IVideoCapture.open(), Source, ErrorCode.SOURCE_NOT_CAPTURABLE
     */
    Source[] supportedSources;
}
