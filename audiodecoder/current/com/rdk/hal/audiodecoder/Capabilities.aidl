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
package com.rdk.hal.audiodecoder;
import com.rdk.hal.audiodecoder.Codec;
import com.rdk.hal.audiodecoder.metrics.Episode;
import com.rdk.hal.audiodecoder.metrics.Metric;

/**
 *  @brief     Audio decoder resource definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Capabilities {
    /**
     * Array of Codec enum values supported by this audio decoder instance.
     */
    Codec[] supportedCodecs;

    /**
     * Indicates if this decoder instance can work in secure audio path (SAP) mode.
     * @see Property.SECURE_AUDIO
     */
    boolean supportsSecure;

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
}
