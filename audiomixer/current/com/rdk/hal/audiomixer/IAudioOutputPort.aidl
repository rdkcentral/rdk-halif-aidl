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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 * Copyright 2024 RDK Management
 * Licensed under the Apache License, Version 2.0 (the "License");
 * http://www.apache.org/licenses/LICENSE-2.0
 */
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.OutputPortCapabilities;
import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.audiomixer.IAudioOutputPortListener;

/**
 * @brief    Audio Output Port HAL interface, property-based design.
 * @details  All dynamic/query/settable configuration is via get/setProperty,
 *           with supported properties enumerated in OutputPortCapabilities.
 */
@VintfStability
interface IAudioOutputPort {

    /**
     * @brief    Returns this port's static and property capabilities.
     */
    OutputPortCapabilities getCapabilities();

    /**
     * @brief    Sets a property value for this port.
     * @param[in] property  Property key (from OutputPortProperty).
     * @param[in] value     Property value.
     * @return              True if set, false if not supported/invalid.
     */
    boolean setProperty(in OutputPortProperty property, in PropertyValue value);

    /**
     * @brief    Gets a property value from this port.
     * @param[in] property  Property key.
     * @return              Property value.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if not supported.
     */
    PropertyValue getProperty(in OutputPortProperty property);

    /**
     * @brief    Registers a listener for port events (optional, as before).
     */
    void registerListener(in IAudioOutputPortListener listener);

    /**
     * @brief    Unregisters a previously registered listener.
     */
    void unregisterListener(in IAudioOutputPortListener listener);
}
