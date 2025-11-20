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
import com.rdk.hal.farfieldvoice.KeywordDetectInfo;

/**
 *  @brief     Callbacks listener interface from Far Field Voice controller.
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
oneway interface IFarFieldVoiceControllerListener {

    /**
	 * Callback when a keyword is detected on the "KEYWORD" channel.
     *
     * @param[in] keywordDetectInfo     Keyword detect information.
     */
    void onKeywordDetected(in KeywordDetectInfo keywordDetectInfo);

    /**
	 * Callback when an End of voice command is detected on the "KEYWORD" channel following the keyword.
     *
     * @param[in] sampleOffset      "KEYWORD" channel sample offset to the end of voice command.
     * @param[in] timedOut          Indicates if timed out detecting end of command.
     */
    void onEndOfCommand(in long sampleOffset, boolean timedOut);
}
