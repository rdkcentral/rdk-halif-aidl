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
package com.rdk.hal.audiomixer;

import com.rdk.hal.audiomixer.IAudioCapture;
import com.rdk.hal.audiomixer.IAudioCaptureListener;
import com.rdk.hal.audiomixer.IAudioOutputPortListener;
import com.rdk.hal.audiomixer.IDolbyMs12_2_6_Dap;
import com.rdk.hal.audiomixer.OutputPortCapabilities;
import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.PropertyValue;

/**
 * @brief    Audio Output Port HAL interface, property-based design.
 * All dynamic/query/settable configuration is via get/setProperty,
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
     * @returns             True if set, false if not supported/invalid.
     */
    boolean setProperty(in OutputPortProperty property, in PropertyValue value);

    /**
     * @brief    Gets a property value from this port.
     * @param[in] property  Property key.
     * @returns             Property value.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if not supported.
     */
    PropertyValue getProperty(in OutputPortProperty property);

    /**
     * @brief    Registers a listener for port events (optional, as before).
     */
    void registerListener(in IAudioOutputPortListener listener);

    /**
     * @brief    Un-registers a previously registered listener.
     */
    void unregisterListener(in IAudioOutputPortListener listener);

    /**
     * @brief Creates a Dolby MS12 2.6 DAP command interface for this port.
     * 
     * If DOLBY_MS12_2_6 is reported as a supported AQProcessor in supportedAQProcessors then this function will return an interface to allow its control.
     *
     * @returns IDolbyMs12_2_6_Dap interface
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if Dolby MS12 v2.6 DAP is not supported.
     *
     * @see com.rdk.hal.audiomixer.OutputPortCapabilities.supportedAQProcessors
     */
    IDolbyMs12_2_6_Dap getDolbyMs12_2_6_Dap();


    /**
     * @brief Creates an audio capture interface for this port.
     * 
     * @param[in] audioCaptureListener a Listener for capture callbacks.
     * 
     * If supportsAudioCapture is true then this function will return an interface to allow its control.
     *
     * @returns IAudioCapture interface
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if audio capture from this port is not supported.
     * @exception binder::Status EX_NULL_POINTER if audioCaptureListener is null.
     *
     * @see com.rdk.hal.audiomixer.OutputPortCapabilities.supportsAudioCapture
     */
    IAudioCapture getAudioCapture(in IAudioCaptureListener audioCaptureListener );
}
