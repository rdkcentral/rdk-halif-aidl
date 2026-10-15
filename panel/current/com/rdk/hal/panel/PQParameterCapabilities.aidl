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
import com.rdk.hal.panel.DimmingLevel;
import com.rdk.hal.panel.DimmingMode;
import com.rdk.hal.panel.DimmingSettings;
import com.rdk.hal.panel.DolbyVisionCalibrationSettings;
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PanelSource;
import com.rdk.hal.panel.SDRGamma;
import com.rdk.hal.panel.ToneMappingLevel;
import com.rdk.hal.panel.ToneMappingMode;
import com.rdk.hal.panel.ToneMappingSettings;
import com.rdk.hal.panel.TwoPointWB;
import com.rdk.hal.panel.WhiteBalanceMultiPointSettings;
import com.rdk.hal.videodecoder.DynamicRange;

/**
 * @brief Panel PQ parameter capabilities.
 */
@VintfStability
parcelable PQParameterCapabilities {
    /**
     * The PQ parameter being referenced in these capabilities.
     */
    PQParameter pqParameter;

    /**
     * Whether this PQ parameter is supported on the platform.
     * If unsupported, all other fields in this parcelable should be ignored.
     */
    boolean isSupported;

    /**
     * Whether this PQ parameter globally affects the composite image,
     * including the graphics plane and all video planes, or is limited to
     * video.
     */
    boolean isGlobal;

    /**
     * Scalar integer minimum/maximum bounds used by simple integer-backed PQ
     * parameters.
     */
    @VintfStability
    parcelable IntBounds {
        int minValue;
        int maxValue;
        @VintfStability
        parcelable StepValue {
            int value;
        }
        @nullable StepValue stepValue;
    }

    /**
    * Per-dimming-mode level limits used when pqParameter ==
    * PQParameter.DIMMING_SETTINGS.
     */
    @VintfStability
    parcelable DimmingModeLevelCapability {
        DimmingMode dimmingMode;
        int numSupportedLevels;
        DimmingLevel[] supportedValues;
    }

    /**
     * Wrapper for the list of per-mode dimming level capabilities.
     */
    @VintfStability
    parcelable DimmingModeLevelCapabilities {
        DimmingModeLevelCapability[] entries;
    }

    /**
     * Capabilities for grouped dimming settings.
     */
    @VintfStability
    parcelable DimmingSettingsCapabilities {
        DimmingModeLevelCapabilities modeLevelCapabilities;
    }

    /**
    * Per-tone-mapping-mode level support used when pqParameter ==
    * PQParameter.TONE_MAPPING_SETTINGS.
     */
    @VintfStability
    parcelable ToneMappingModeLevelCapability {
        ToneMappingMode toneMappingMode;
        int numSupportedLevels;
        ToneMappingLevel[] supportedValues;
    }

    /**
     * Wrapper for the list of per-mode tone-mapping level capabilities.
     */
    @VintfStability
    parcelable ToneMappingModeLevelCapabilities {
        ToneMappingModeLevelCapability[] entries;
    }

    /**
     * Capabilities for grouped tone-mapping settings.
     */
    @VintfStability
    parcelable ToneMappingSettingsCapabilities {
        ToneMappingModeLevelCapabilities modeLevelCapabilities;
    }

    /**
     * Bounds used when pqParameter == PQParameter.DV_CALIBRATION.
     */
    @VintfStability
    parcelable DvCalibrationBounds {
        DolbyVisionCalibrationSettings minBound;
        DolbyVisionCalibrationSettings maxBound;
    }

    /**
     * Bounds used when pqParameter == PQParameter.TWO_POINT_WB.
     */
    @VintfStability
    parcelable TwoPointWBBounds {
        TwoPointWB minBound;
        TwoPointWB maxBound;
    }

    /**
     * Bounds used when pqParameter == PQParameter.MULTI_POINT_WB.
     */
    @VintfStability
    parcelable MultiPointWBBounds {
        WhiteBalanceMultiPointSettings minBound;
        WhiteBalanceMultiPointSettings maxBound;
    }

    /**
     * Bounds used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS.
     */
    @VintfStability
    parcelable ColourManagementSettingsBounds {
        ColourManagementSettings minBound;
        ColourManagementSettings maxBound;
    }

    /**
     * Bounds information for the PQ parameter.
     *
     * Only one bounds shape is valid for a given PQ parameter, so the active
     * variant identifies how the parameter's legal range is described.
     * Integer-backed parameters may also carry an optional step value so large
     * numeric domains can be represented compactly without enumerating every
     * allowed value.
     * Structured parcelables such as DolbyVisionCalibrationSettings,
     * TwoPointWB, WhiteBalanceMultiPointSettings, and
     * ColourManagementSettings do not use stepValue; they are represented
     * either by their own min/max bounds in RangeBound or by explicit preset
     * arrays in SupportedValues. When the preset arrays are omitted or empty,
     * the structured min/max bounds define the full supported domain.
     */
    @VintfStability
    union RangeBound {
        IntBounds intBounds;
        DimmingSettingsCapabilities dimmingSettingsCapabilities;
        ToneMappingSettingsCapabilities toneMappingSettingsCapabilities;
        DvCalibrationBounds dvCalibrationBounds;
        TwoPointWBBounds twoPointWBBounds;
        MultiPointWBBounds multiPointWBBounds;
        ColourManagementSettingsBounds colourManagementSettingsBounds;
    }
    @nullable RangeBound rangeBound;

    /**
     * Discrete supported values for the PQ parameter.
     *
     * Only one supported-values shape is valid for a given PQ parameter, so the
     * active variant identifies how explicit preset values are conveyed.
     * This is intended for finite preset lists rather than large numeric
     * domains. These arrays are nullable; implementations may omit them or use
     * an empty array when no explicit presets are advertised. When a structured
     * capability uses min/max bounds instead of explicit presets, the bounds
     * describe the full supported domain.
     */
    @VintfStability
    union SupportedValues {
        /**
         * Specific integer values supported for simple integer-backed PQ
         * parameters.
         * Empty array means every integer allowed by `rangeBound.intBounds` is
         * valid.
         */
        @nullable int[] supportedIntValues;

        /**
         * Supported SDR gamma values used when pqParameter ==
         * PQParameter.SDR_GAMMA.
         */
        @nullable SDRGamma[] supportedSdrGammaValues;

        /**
         * Supported string values used when pqParameter ==
         * PQParameter.COLOR_TEMPERATURE.
         */
        @nullable String[] supportedStringValues;

        /**
         * Specific grouped dimming presets that are supported.
         */
        @nullable DimmingSettings[] supportedDimmingSettingsValues;

        /**
         * Specific Dolby Vision calibration presets that are supported.
         */
        @nullable DolbyVisionCalibrationSettings[] supportedDvCalibrationValues;

        /**
         * Specific 2-point white balance presets that are supported.
         */
        @nullable TwoPointWB[] supportedTwoPointWBValues;

        /**
         * Specific multi-point white balance presets that are supported.
         */
        @nullable WhiteBalanceMultiPointSettings[] supportedMultiPointWBValues;

        /**
         * Specific grouped colour-management presets that are supported.
         */
        @nullable ColourManagementSettings[] supportedColourManagementSettingsValues;

        /**
         * Specific grouped tone-mapping presets that are supported.
         */
        @nullable ToneMappingSettings[] supportedToneMappingSettingsValues;

    }
    @nullable SupportedValues supportedValues;

    /**
     * Nested PQ parameter picture-mode capabilities definition.
     */
    @VintfStability
    parcelable PQParamPictureModeCapabilities {
        String pictureMode;

        /**
         * Nested PQ parameter dynamic-range capabilities definition.
         */
        @VintfStability
        parcelable PQParamDynamicRangeCapabilities {
            DynamicRange dynamicRange;
            PanelSource[] supportedAVSources;
        }

        PQParamDynamicRangeCapabilities[] pqParamDynamicRangeCapabilities;
    }

    /**
     * Array of PQ parameter capabilities for picture modes.
     */
    PQParamPictureModeCapabilities[] pqParamPictureModeCapabilities;
}
