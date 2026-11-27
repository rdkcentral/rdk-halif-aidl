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

import com.rdk.hal.panel.ColourManagementSettings;
import com.rdk.hal.panel.DimmingSettings;
import com.rdk.hal.panel.DolbyVisionCalibrationSettings;
import com.rdk.hal.panel.SDRGamma;
import com.rdk.hal.panel.ToneMappingSettings;
import com.rdk.hal.panel.TwoPointWB;
import com.rdk.hal.panel.WhiteBalanceMultiPointSettings;

/**
 * @brief Value union for a PQ parameter configuration.
 */
@VintfStability
union PQParameterValue {
    /**
     * Integer value used by all PQ parameters except SDR_GAMMA, COLOR_TEMPERATURE, DIMMING_SETTINGS, DV_CALIBRATION,
     * TWO_POINT_WB, MULTI_POINT_WB, COLOUR_MANAGEMENT_SETTINGS, and TONE_MAPPING_SETTINGS.
     */
    int intValue;
    /** SDR gamma value used when pqParameter == PQParameter.SDR_GAMMA. */
    SDRGamma sdrGamma;
    /** String value used when pqParameter == PQParameter.COLOR_TEMPERATURE. */
    @utf8InCpp String stringValue;
    /** Grouped dimming settings used when pqParameter == PQParameter.DIMMING_SETTINGS. */
    DimmingSettings dimmingSettings;
    /** Dolby Vision calibration settings used when pqParameter == PQParameter.DV_CALIBRATION. */
    DolbyVisionCalibrationSettings dvCalibrationSettings;
    /**
     * Aggregate 2-point white balance settings used when pqParameter == PQParameter.TWO_POINT_WB; the array contains
     * the full bundle for the resolved selector context.
     */
    TwoPointWB[] twoPointWBSettings;
    /**
     * Aggregate multi-point white balance settings used when pqParameter == PQParameter.MULTI_POINT_WB; the array
     * contains the full bundle for the resolved selector context.
     */
    WhiteBalanceMultiPointSettings[] multiPointWBSettings;
    /** Grouped colour-management settings used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
    ColourManagementSettings colourManagementSettings;
    /** Grouped tone-mapping settings used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
    ToneMappingSettings toneMappingSettings;
}
