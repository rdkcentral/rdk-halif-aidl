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

import com.rdk.hal.PropertyType;
import com.rdk.hal.PropertyValue;

/**
 * @file      AQParameterMetadata.aidl
 * @brief     Per-AQ-parameter metadata describing type, range, units, and
 *            on/off/default sentinels for a single tunable parameter.
 *
 *            Returned in bulk from IAQProcessor.getSupportedParameters(). The
 *            entries are populated by the vendor HAL from the platform HFP
 *            (hfp-audiomixer.yaml -> aqProcessors[].parameters[]) and form the
 *            runtime-discoverable contract for tuning a given processor
 *            instance.
 *
 *            The shape mirrors the HFP YAML 1:1: the @c name field carries the
 *            canonical spelling from the HFP entry, @c type identifies which
 *            PropertyValue union field carries the value, and the optional
 *            @c min / @c max / @c offValue / @c onValue / @c defaultValue
 *            carry platform-specific sentinels distinct from each other
 *            (resolves the "platform-specific ON or OFF value separate from
 *            the reset value" requirement called out in the audiomixer
 *            workstream).
 *
 *            Validation contract — IAQProcessorController.setAQParameter()
 *            and setAQParameters() validate caller-supplied values against
 *            this metadata. A value whose PropertyValue union field does not
 *            match @c type is rejected with EX_ILLEGAL_ARGUMENT. A value
 *            whose field matches but falls outside [min, max] returns
 *            @c false from the setter without throwing.
 *
 * @see       IAQProcessor.getSupportedParameters()
 * @see       AQParameterKV
 * @see       IAQProcessorController.setAQParameter()
 * @see       IAQProcessorController.setAQParameters()
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
parcelable AQParameterMetadata {

    /**
     * @brief Canonical parameter name from the platform HFP.
     *
     *          Matches @c hfp-audiomixer.yaml -> @c aqProcessors[].parameters[].name
     *          for this processor instance. Names are case-sensitive and
     *          should follow the spellings listed in AQParameter.aidl when
     *          one applies. New, vendor-specific parameters may be added by
     *          HFP without changing any AIDL.
     */
    @utf8InCpp String name;

    /**
     * @brief Data type of the parameter value.
     *
     *          Identifies which field of the common PropertyValue.Value
     *          union carries this parameter's value across the binder.
     *          Callers must populate the matching union field when writing
     *          and read the matching union field when reading.
     */
    PropertyType type;

    /**
     * @brief True if this parameter is read-only.
     *
     *          A read-only parameter may be observed via
     *          IAQProcessor.getAQParameter() but cannot be written via
     *          IAQProcessorController.setAQParameter(); attempting to write
     *          returns @c false.
     */
    boolean readOnly;

    /**
     * @brief Optional human-readable unit string (e.g. "dB", "ms", "%", "Hz").
     *
     *          For UI and logging only; not interpreted by the HAL. May be
     *          null when the parameter is dimensionless (e.g. an enum-like
     *          INTEGER selector or a BOOLEAN toggle).
     */
    @nullable @utf8InCpp String unit;

    /**
     * @brief Lower bound of the value range (inclusive).
     *
     *          Used by IAQProcessorController.setAQParameter() for range
     *          validation. The PropertyValue.Value field carrying the bound
     *          MUST match the @c type field above. May be null for
     *          BOOLEAN-typed parameters or enum-like INTEGERs where a
     *          dense numeric range is not meaningful.
     */
    @nullable PropertyValue min;

    /**
     * @brief Upper bound of the value range (inclusive).
     *
     *          Same semantics and constraints as @c min.
     */
    @nullable PropertyValue max;

    /**
     * @brief Optional platform-specific OFF sentinel value.
     *
     *          When present, writing this value disables the effect on this
     *          processor instance. Distinct from @c defaultValue (factory
     *          reset value) — many platforms use a non-zero off sentinel
     *          (e.g. -1 in an integer range whose useful values start at 0).
     */
    @nullable PropertyValue offValue;

    /**
     * @brief Optional platform-specific ON sentinel value.
     *
     *          When present, writing this value enables the effect on this
     *          processor instance with a vendor-recommended "on" setting.
     *          May differ from @c defaultValue when the platform ships in
     *          OFF-by-default state.
     */
    @nullable PropertyValue onValue;

    /**
     * @brief Factory-reset value for this parameter.
     *
     *          Restored by IAQProcessorController.resetToDefault(name) and
     *          by resetToDefault(null) for every parameter. May be null
     *          when the platform does not declare a default for this
     *          parameter; in that case resetToDefault() leaves the
     *          parameter untouched.
     */
    @nullable PropertyValue defaultValue;

    /**
     * @brief True when the parameter applies globally across all output
     *        ports rather than to a single port.
     *
     *          When @c isGlobal is true, writing the parameter on one port's
     *          IAQProcessorController instance propagates the change to
     *          every port whose IAQProcessor exposes the same parameter
     *          name. Per-port observers will see onParameterChanged() fire.
     *          When @c isGlobal is false, the parameter is scoped to the
     *          port that produced the IAQProcessor.
     */
    boolean isGlobal;

    /**
     * @brief Names of the sound-mode presets that include this parameter.
     *
     *          Each entry matches one of the strings returned by
     *          IAQProcessor.getAQSoundModes(). Activating a sound mode via
     *          IAQProcessorController.setAQSoundMode() applies the
     *          platform-defined values for every parameter listed under
     *          that mode. Empty when the parameter is not bundled into
     *          any preset.
     */
    @utf8InCpp String[] includedInSoundMode;

    /**
     * @brief Human-readable description of the parameter.
     *
     *          Free-form vendor text intended for diagnostics, log messages,
     *          and tuning-UI labels. Not interpreted by the HAL.
     */
    @utf8InCpp String description;
}
