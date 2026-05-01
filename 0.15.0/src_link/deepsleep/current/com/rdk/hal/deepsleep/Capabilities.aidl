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
package com.rdk.hal.deepsleep;
import com.rdk.hal.deepsleep.WakeUpTrigger;
 
/** 
 *  @brief     Deep sleep capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
parcelable Capabilities
{
    /** 
     * Array of wake up triggers supported by the deep sleep service. 
     */
    WakeUpTrigger[] supportedTriggers;

    /**
     * Array of preconfigured wake up triggers which are always armed by the platform.
     *
     * These triggers are platform-defined and cannot be disabled by the client.
     * They are implicitly added to the set of active triggers when entering deep sleep.
     * This is a subset of the supportedTriggers[].
     */
    WakeUpTrigger[] preconfiguredTriggers;
}
