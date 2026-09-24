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
 *  Describes what frames this capture resource delivers. This is the whole of the
 *  capture declaration: a client reads it and configures nothing, and the vendor layer
 *  arranges whatever the bound source needs in order to deliver what is declared.
 *
 *  @author    Peter Stieglitz
 *  @author    Gerald Weatherup
 */

@VintfStability
parcelable Capabilities
{
    /**
     * The pixel format and memory layout every frame of this capture is delivered in.
     *
     * One pair per capture, chosen by the product: the vendor's most efficient layout
     * that the product's GPU imports through `EGL_EXT_image_dma_buf_import` - with
     * `EGL_EXT_image_dma_buf_import_modifiers` for a layout other than
     * `DRM_FORMAT_MOD_LINEAR` - as an external texture, which the GPU samples as
     * RGB(A). The frame stays in its decoded colour encoding; conversion to RGB happens
     * in that sampling, not in the capture.
     */
    FormatLayout format;

    /**
     * The maximum frame width in pixels this capture resource can deliver.
     *
     * The pool is sized for `maxFrameWidth` x `maxFrameHeight`, and every buffer is that
     * size. A frame occupies the top-left `VideoFrameView.visibleWidth` x
     * `visibleHeight` of its buffer, so a stream changing resolution within the maximum
     * needs no new pool. A source decoding beyond it fails with
     * `ErrorCode.RESOLUTION_MISMATCH`.
     */
    int maxFrameWidth;

    /**
     * The maximum frame height in pixels this capture resource can deliver.
     *
     * @see maxFrameWidth
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
