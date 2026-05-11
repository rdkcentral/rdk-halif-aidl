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

import com.rdk.hal.audiomixer.OutputPortProperty;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Listener interface for audio output port events.
 * Provides callbacks for changes in port connection state, supported formats,
 *            output format changes, state transitions, and feature support (e.g., Dolby Atmos).
 *            Registered by clients interested in monitoring real-time output port events.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @copyright Copyright 2024 RDK Management
 */
@VintfStability
oneway interface IAudioOutputPortListener {

    /**
     * @brief     Called when a dynamic property value changes.
     * @param[in] property   The OutputPortProperty that changed.
     * @param[in] newValue   The new PropertyValue.
     */
    void onPropertyChanged(in OutputPortProperty property, in PropertyValue newValue);
}
