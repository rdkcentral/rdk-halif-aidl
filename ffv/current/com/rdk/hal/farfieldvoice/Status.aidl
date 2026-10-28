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
import com.rdk.hal.farfieldvoice.ListeningMode;

/**
 *  @brief     Far Field Voice service status.
 *
 *  Returned by IFarFieldVoice.getStatus(). Unlike Capabilities, these values change at run time.
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
parcelable Status
{

    /**
     * Current listening mode.
     */
    ListeningMode listeningMode;

    /**
     * Indicates if a keyword was detected on the Keyword Audio channel since it was opened.
     *
     * Set when IFarFieldVoiceControllerListener.onKeywordDetected() is sent. Cleared when the
     * Keyword Audio channel is opened or closed, so true always refers to the current session.
     */
    boolean keywordDetected;

    /**
     * Indicates if privacy state is active.
     */
    boolean privacyStateActive;
}
