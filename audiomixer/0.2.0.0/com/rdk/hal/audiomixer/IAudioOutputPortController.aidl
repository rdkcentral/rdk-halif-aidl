/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.PropertyValue;

/**
 * @brief    Audio Output Port Controller HAL interface.
 * @details  Exclusive write controller returned by IAudioOutputPort.open().
 *           Hosts mutating operations on the output port (property writes for
 *           volume, mute, output format, transcode format, AQ processor, etc.).
 *
 *           Only one client may hold the controller at a time. If the holding
 *           client crashes, the HAL detects the binder death and releases
 *           the port internally — equivalent to calling
 *           IAudioOutputPort.close(controller) on the orphaned controller —
 *           so a subsequent open() from another client succeeds.
 *
 *           Read access (getProperty, getCapabilities) remains on
 *           IAudioOutputPort and does not require ownership.
 *
 * @author   Gerald Weatherup
 */
@VintfStability
interface IAudioOutputPortController {

    /**
     * @brief    Sets a property value for the controlled output port.
     *
     *           The property must be writable in the current port state. Property
     *           writability is documented per-key in OutputPortProperty.aidl
     *           (e.g., VOLUME is writable in READY/STARTED, TRANSCODE_FORMAT is
     *           writable only in READY).
     *
     * @param[in] property  Property key (from OutputPortProperty enum).
     * @param[in] value     Property value; union field must match the property type.
     *
     * @returns  true on successful write, false if the property is not supported
     *           by this port or the value is rejected.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property is unknown or
     *            value type does not match.
     * @exception binder::Status EX_ILLEGAL_STATE if the port is not in a state
     *            that permits writing this property.
     *
     * @see IAudioOutputPort.getProperty()
     */
    boolean setProperty(in OutputPortProperty property, in PropertyValue value);
}
