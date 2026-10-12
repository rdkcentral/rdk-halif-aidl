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
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.panel;

import com.rdk.hal.panel.PanelSource;
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PQParameterConfiguration;
import com.rdk.hal.videodecoder.DynamicRange;

@VintfStability
oneway interface IPanelOutputControllerListener {
    /**
     * Callback when the picture mode changes.
     * 
     * This can occur on an AVSource or DynamicRange change in the video
     * or occurs after a call to setPictureMode().
     * 
     * @param[in] pictureMode   The new picture mode.
     */
    void onPictureModeChanged(in String pictureMode);

    /**
     * Callback when a PQ picture property value changes.
     *
     * @param[in] pictureMode             The picture mode for which the change applies.
     * @param[in] avSource                The AV source for which the change applies.
     * @param[in] dynamicRange            The dynamic range for which the change applies.
     * @param[in] pictureProperty         The PQ picture property that changed.
     * @param[in] picturePropertyValue    The changed value variant.
     */
    void onPQParameterChanged(in String pictureMode, in PanelSource avSource, in DynamicRange dynamicRange, in PQParameter pictureProperty, in PQParameterConfiguration.Value picturePropertyValue);
}
