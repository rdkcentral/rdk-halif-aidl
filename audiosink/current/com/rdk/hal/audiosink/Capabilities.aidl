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
package com.rdk.hal.audiosink;
import com.rdk.hal.audiosink.ContentType;
import com.rdk.hal.audiosink.ErrorCode;
import com.rdk.hal.audiosink.metrics.Episode;
import com.rdk.hal.audiosink.metrics.Metric;

/**
 *  @brief     Audio Sink capabilities parcelable definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Capabilities {
    /**
     * Indicates if this audio sink instance can work in secure audio path (SAP) mode.
     * @see Property.SECURE_AUDIO
     */
    boolean supportsSecure;

    /**
     * List of content types supported by this audio sink instance.
     * Clients should check this before calling `open()` with a given `ContentType`.
     * @see IAudioSink.open()
     */
    ContentType[] supportedContentTypes;

    /**
     * The metrics this resource instance serves through getMetrics(), as
     * listed under supportedMetrics in the HAL Feature Profile. getMetric()
     * throws EX_UNSUPPORTED_OPERATION for any other member.
     */
    Metric[] supportedMetrics;

    /**
     * The episodes this resource instance raises through
     * onMetricEpisodeStarted() and onMetricEpisodeResolved(), as listed under
     * supportedEpisodes in the HAL Feature Profile. No other member is raised.
     */
    Episode[] supportedEpisodes;

    /**
     * The error codes this resource instance raises through onRenderError(),
     * as listed under supportedErrorCodes in the HAL Feature Profile. No
     * other code is raised.
     */
    ErrorCode[] supportedErrorCodes;
}
