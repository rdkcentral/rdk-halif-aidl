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
 *  @brief     Far Field Voice channel status.
 *  @author    Philip Stick
 */

@VintfStability
parcelable ChannelStatus
{
    /**
     * Indicates if the channel has been opened.
     */
    boolean channelIsOpen;

    /**
     * Total number of samples lost due to buffer overflow.
     *
     * This is for information only and useful to log at the end of a session.
     * Non zero values may indicate inadequate CPU time or buffer space.
     */
    long samplesLost;
}
