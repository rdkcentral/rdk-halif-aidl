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
 *  @brief     Far Field Voice listening mode definitions.
 *
 *  A listening mode states what the Far Field Voice module is listening for and which
 *  audio channels it can serve. It describes the module's own behaviour; it is not a
 *  system power state. The system decides when to change mode and sets it through
 *  IFarFieldVoiceController.setListeningMode().
 *
 *  Not every platform supports every mode. The modes a platform supports are listed in
 *  Capabilities.supportedListeningModes and in the HAL Feature Profile.
 *
 *  @author    Philip Stick
 *  @author    Gary Skrabutenas
 */

@VintfStability
@Backing(type="int")

enum ListeningMode
{
    /**
     * Listening mode never set, or a listening mode change is in progress (not ready).
     */
    NONE = 0,

    /**
     * Full far field audio capture and processing.
     *
     * Keyword detection runs and every audio channel type listed in
     * Capabilities.channelTypes can be opened.
     */
    ACTIVE_LISTEN = 1,

    /**
     * Keyword detection only.
     *
     * The module listens for the keyword with reduced processing, so that a keyword
     * can be detected while the rest of the platform is in a low power state. Only the
     * Keyword channel type can be opened.
     */
    KEYWORD_ALERT = 2,

    /**
     * No audio capture or processing.
     *
     * Keyword detection does not run and no audio channel can be opened.
     */
    POWERED_OFF = 3,
}
