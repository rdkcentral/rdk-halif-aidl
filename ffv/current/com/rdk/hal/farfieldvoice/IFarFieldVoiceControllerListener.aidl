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
 *  @brief     Callbacks listener interface from Far Field Voice controller.
 *
 *  Passed to IFarFieldVoice.open() by the controlling client. Reports keyword detection
 *  and the end of the voice command on the Keyword Audio channel.
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
oneway interface IFarFieldVoiceControllerListener {

    /**
     * Invoked when a keyword (wake word) is detected on the Keyword Audio channel.
     */
    void onKeywordDetected();

    /**
     * Invoked when the end of a spoken command is detected on the Keyword Audio channel,
     * immediately following the wake word/keyword.
     *
     * @param[in] sampleOffset      The sample offset, relative to the Keyword Audio channel, marking the
     *                              end of the detected voice command. 0 is the first sample written to the
     *                              pipe after the channel was opened.
     * @param[in] timedOut          True if the end of command was not detected within the expected
     *                              timeframe (detection timed out); false if it was detected.
     */
    void onEndOfCommand(in long sampleOffset, in boolean timedOut);
}
