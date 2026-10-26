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
        /** Minimum value. */
        int minValue;
        /** Maximum value. */
        int maxValue;
        /** Spacing between allowed values, for regularly spaced controls. */
        @VintfStability
        parcelable StepValue {
            /** The step between consecutive allowed values. */
            int value;
        }
        /** The step value. Null if the allowed values are not regularly spaced. */
        @nullable StepValue stepValue;
    }

    /**
     * Per-dimming-mode level limits used when pqParameter ==
     * PQParameter.DIMMING_SETTINGS.
     */
    @VintfStability
    parcelable DimmingModeLevelCapability {
        /** The dimming mode. */
        DimmingMode dimmingMode;
        /** Number of levels supported for the mode, the length of supportedValues. */
        int numSupportedLevels;
        /** The levels supported for the mode. */
        DimmingLevel[] supportedValues;
    }

    /**
     * Wrapper for the list of per-mode dimming level capabilities.
     */
    @VintfStability
    parcelable DimmingModeLevelCapabilities {
        /** One entry for each supported dimming mode. */
        DimmingModeLevelCapability[] entries;
    }

    /**
     * Capabilities for grouped dimming settings.
     */
    @VintfStability
    parcelable DimmingSettingsCapabilities {
        /** The supported dimming levels for each dimming mode. */
        DimmingModeLevelCapabilities modeLevelCapabilities;
    }

    /**
     * Per-tone-mapping-mode level support used when pqParameter ==
     * PQParameter.TONE_MAPPING_SETTINGS.
     */
    @VintfStability
    parcelable ToneMappingModeLevelCapability {
        /** The tone-mapping mode. */
        ToneMappingMode toneMappingMode;
        /** Number of levels supported for the mode, the length of supportedValues. */
        int numSupportedLevels;
        /** The levels supported for the mode. */
        ToneMappingLevel[] supportedValues;
    }

    /**
     * Wrapper for the list of per-mode tone-mapping level capabilities.
     */
    @VintfStability
    parcelable ToneMappingModeLevelCapabilities {
        /** One entry for each supported tone-mapping mode. */
        ToneMappingModeLevelCapability[] entries;
    }

    /**
     * Capabilities for grouped tone-mapping settings.
     */
    @VintfStability
    parcelable ToneMappingSettingsCapabilities {
        /** The supported tone-mapping levels for each tone-mapping mode. */
        ToneMappingModeLevelCapabilities modeLevelCapabilities;
    }

    /**
     * Bounds used when pqParameter == PQParameter.DV_CALIBRATION.
     */
    @VintfStability
    parcelable DvCalibrationBounds {
        /** The minimum value of each field. */
        DolbyVisionCalibrationSettings minBound;
        /** The maximum value of each field. */
        DolbyVisionCalibrationSettings maxBound;
    }

    /**
     * Capability bounds used when pqParameter == PQParameter.TWO_POINT_WB.
     *
     * The supported colour temperatures are discrete strings and are listed in
     * SupportedValues. This structure only carries the allowed numeric ranges
     * for the RGB gain and offset fields.
     */
    @VintfStability
    parcelable TwoPointWBCapabilities {
        /** Bounds for the red gain. */
        IntBounds redGain;
        /** Bounds for the red offset. */
        IntBounds redOffset;
        /** Bounds for the green gain. */
        IntBounds greenGain;
        /** Bounds for the green offset. */
        IntBounds greenOffset;
        /** Bounds for the blue gain. */
        IntBounds blueGain;
        /** Bounds for the blue offset. */
        IntBounds blueOffset;
    }

    /**
     * Capability bounds used when pqParameter == PQParameter.MULTI_POINT_WB.
     *
     * The supported colour temperatures are discrete strings and are listed in
     * SupportedValues. This structure only carries the fixed min/max bounds for
     * the red, green, and blue channel values.
     */
    @VintfStability
    parcelable MultiPointWBCapabilities {
        /** Bounds for the red channel values. */
        IntBounds r;
        /** Bounds for the green channel values. */
        IntBounds g;
        /** Bounds for the blue channel values. */
        IntBounds b;
    }

    /**
     * Bounds used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS.
     */
    @VintfStability
    parcelable ColourManagementSettingsBounds {
        /** The minimum value of each field. */
        ColourManagementSettings minBound;
        /** The maximum value of each field. */
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
     * TwoPointWBCapabilities, MultiPointWBCapabilities, and
     * ColourManagementSettings do not use stepValue. For white balance, the
     * numeric field limits live in RangeBound while the discrete colour
     * temperature names live in SupportedValues. When the preset arrays are
     * omitted or empty, the structured min/max bounds define the full supported
     * numeric domain.
     */
    @VintfStability
    union RangeBound {
        /** Bounds for simple integer-backed PQ parameters. */
        IntBounds intBounds;
        /** Used when pqParameter == PQParameter.DIMMING_SETTINGS. */
        DimmingSettingsCapabilities dimmingSettingsCapabilities;
        /** Used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
        ToneMappingSettingsCapabilities toneMappingSettingsCapabilities;
        /** Used when pqParameter == PQParameter.DV_CALIBRATION. */
        DvCalibrationBounds dvCalibrationBounds;
        /** Used when pqParameter == PQParameter.TWO_POINT_WB. */
        TwoPointWBCapabilities twoPointWBCapabilities;
        /** Used when pqParameter == PQParameter.MULTI_POINT_WB. */
        MultiPointWBCapabilities multiPointWBCapabilities;
        /** Used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
        ColourManagementSettingsBounds colourManagementSettingsBounds;
    }

    /** The bounds for the PQ parameter. Null if the parameter uses supportedValues only. */
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
        @nullable @utf8InCpp String[] supportedStringValues;

        /**
         * Specific grouped dimming presets that are supported.
         */
        @nullable DimmingSettings[] supportedDimmingSettingsValues;

        /**
         * Specific Dolby Vision calibration presets that are supported.
         */
        @nullable DolbyVisionCalibrationSettings[] supportedDvCalibrationValues;

        /**
         * Specific 2-point white balance colour-temperature strings that are
         * supported.
         */
        @nullable @utf8InCpp String[] supportedTwoPointWBValues;

        /**
         * Specific multi-point white balance colour-temperature strings that
         * are supported.
         */
        @nullable @utf8InCpp String[] supportedMultiPointWBValues;

        /**
         * Specific grouped colour-management presets that are supported.
         */
        @nullable ColourManagementSettings[] supportedColourManagementSettingsValues;

        /**
         * Specific grouped tone-mapping presets that are supported.
         */
        @nullable ToneMappingSettings[] supportedToneMappingSettingsValues;
    }

    /** The discrete preset values for the PQ parameter. Null if it uses rangeBound only. */
    @nullable SupportedValues supportedValues;

    /**
     * Nested PQ parameter picture-mode capabilities definition.
     */
    @VintfStability
    parcelable PQParamPictureModeCapabilities {
        /** The picture mode. */
        @utf8InCpp String pictureMode;

        /**
         * Nested PQ parameter dynamic-range capabilities definition.
         */
        @VintfStability
        parcelable PQParamDynamicRangeCapabilities {
            /** The dynamic range. */
            DynamicRange dynamicRange;
            /** The AV sources for which the PQ parameter is supported in this picture mode and dynamic range. */
            PanelSource[] supportedAVSources;
        }

        /** The dynamic ranges, and their AV sources, supported for this picture mode. */
        PQParamDynamicRangeCapabilities[] pqParamDynamicRangeCapabilities;
    }

    /**
     * Array of PQ parameter capabilities for picture modes.
     */
    PQParamPictureModeCapabilities[] pqParamPictureModeCapabilities;
}
