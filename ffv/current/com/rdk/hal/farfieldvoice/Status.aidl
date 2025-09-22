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
import com.rdk.hal.farfieldvoice.PowerMode;
import com.rdk.hal.farfieldvoice.KeywordDetectInfo;

/**
 *  @brief     Far Field Voice service status.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
parcelable Status
{
    /**
     * Build version of this Far Field Voice code instance.
     *
     * This is for information only and useful to log when the Far Field
     * Voice service is opened.
     */
    @utf8InCpp String codeBuildVersion;

    /**
     * Current power mode.
     */
    PowerMode powerMode;

    /**
     * Indicates if the Keyword channel has been opened.
     */
    boolean keywordChannelOpen;

    /**
     * Indicates if the Continual channel has been opened.
     */
    boolean continualChannelOpen;

    /**
     * Indicates if the Microphone channels has been opened.
     */
    boolean microphoneChannelsOpen;

    /**
     * Indicates if a keyword was detected on the Keyword channel.
     */
    boolean keywordDetected;

    /**
     * Keyword detect information (applicable only if keywordDetected is true).
     */
    KeywordDetectInfo keywordDetectInfo;

    /**
     * Indicates if privacy state is active.
     */
    boolean privacyStateActive;

    /**
     * Total number of keyword channel samples lost due to buffer overflow.
     *
     * This is for information only and useful to log at the end of a session.
     * Non zero values may indicate inadequate CPU time or buffer space and
     * be a reason for poor voice quality and false negative keyword detects.
     */
    long keywordChannelSamplesLost;

    /**
     * Total number of continual channel samples lost due to buffer overflow.
     *
     * This is for information only and useful to log at the end of a session.
     * Non zero values may indicate inadequate CPU time or buffer space and
     * be a reason for poor voice quality.
     */
    long continualChannelSamplesLost;

    /**
     * Total number of microphone channels samples lost due to buffer overflow.
     *
     * This is for information only and useful to log at the end of a session.
     * Non zero values may indicate inadequate CPU time or buffer space and
     * be a reason for erroneous microphone data.
     */
    long microphoneChannelsSamplesLost;

    /**
     * Vendor specific error code to indicate an error condition. A value of
     * zero indicates no error.
     *
     * This is for information only and useful to log if an error condition occurs.
     */
    long vendorErrorCode;
}
