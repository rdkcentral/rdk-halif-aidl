/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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
package com.rdk.hal.farfieldvoice;

/**
 *  @brief     Far Field Voice service keyword detect information.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
parcelable KeywordDetectInfo
{
    /**
     * Keyword channel sample offset to the beginning of the keyword.
     */
    long beginSampleOffset;

    /**
     * Keyword channel sample offset to the end of the keyword.
     */
    long endSampleOffset;

    /**
     * Keyword detect sensitivity (keyword detector vendor specific units).
     */
    float detectSensitivity;

    /**
     * Keyword detect low trigger level threshold (keyword detector vendor specific units).
     */
    float lowDetectThreshold;

    /**
     * Keyword detect high trigger level threshold (keyword detector vendor specific units).
     */
    float highDetectThreshold;

    /**
     * Keyword detect triggered by high level threshold (highDetectThreshold).
     */
    boolean highThresholdTriggered;

    /**
     * Keyword detect confidence score (keyword detector vendor specific units).
     */
    float confidenceScore;

    /**
     * Signal to noise ratio during the keyword utterance (units of dB).
     */
    float keywordSnrDb;

    /**
     * Keyword direction of arrival (units of degrees).
     */
    int directionOfArrivalDegrees;

    /**
     * Dynamic gain applied to audio (units of dB).
     */
    float dynamicGainDb;

    /**
     * Name of keyword detector vendor.
     */
    @utf8InCpp String keywordDetectVendorName;

    /**
     * Name of component where keyword was detected.
     */
    @utf8InCpp String keywordDetectComponentName;
}
