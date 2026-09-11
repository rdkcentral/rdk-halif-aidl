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

import com.rdk.hal.audiomixer.AQParameterKV;
import com.rdk.hal.PropertyValue;

/**
 * @file      IAQProcessorController.aidl
 * @brief     Exclusive write interface for an AQ (Audio Quality) processor.
 *
 *            Returned from IAQProcessor.open(). Only one writer may hold the
 *            controller per IAQProcessor instance at a time. If the holding
 *            client crashes, the HAL detects the binder death and implicitly
 *            releases the controller — equivalent to calling
 *            IAQProcessor.close(controller). Parameter STATE is preserved
 *            across the implicit close; the next client that opens the
 *            processor sees the values the previous client left behind.
 *
 *            Read access (getAQParameter, getAQParameters,
 *            getSupportedParameters, getAQSoundMode, getAQSoundModes,
 *            getName, getVersion, getProcessorType) remains on IAQProcessor
 *            and does not require ownership. Observers register and
 *            unregister listeners directly on IAQProcessor regardless of
 *            who holds the controller.
 *
 *            Validation contract:
 *              - The PropertyValue union field carried by @c value MUST
 *                match the PropertyType declared for @c name in
 *                AQParameterMetadata. A mismatch causes
 *                EX_ILLEGAL_ARGUMENT to be thrown.
 *              - The active union field MUST fall within
 *                [AQParameterMetadata.min, AQParameterMetadata.max] when
 *                both bounds are present. An out-of-range value causes
 *                the setter to return @c false WITHOUT throwing.
 *              - Writing a parameter where AQParameterMetadata.readOnly
 *                is true returns @c false.
 *              - Writing a name not returned by
 *                IAQProcessor.getSupportedParameters() throws
 *                EX_ILLEGAL_ARGUMENT.
 *
 * @see       IAQProcessor.open()
 * @see       IAQProcessor.close()
 * @see       AQParameterMetadata
 * @see       AQParameterKV
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
interface IAQProcessorController {

    /**
     * @brief     Sets a single AQ parameter on this processor.
     *
     *            When AQParameterMetadata.isGlobal is true for @c name,
     *            the write propagates to every output port whose
     *            IAQProcessor exposes the same parameter name. Listeners
     *            on each affected port see onParameterChanged().
     *
     * @param[in] name      Canonical parameter name (must appear in
     *                      IAQProcessor.getSupportedParameters()).
     * @param[in] value     PropertyValue carrying the new value; active
     *                      union field must match the parameter's
     *                      AQParameterMetadata.type.
     *
     * @returns   @c true on successful write; @c false if the value is
     *            outside the declared [min, max] range or the parameter
     *            is read-only.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if @c name is not a
     *            supported parameter or @c value's active union field
     *            does not match the declared PropertyType.
     */
    boolean setAQParameter(in @utf8InCpp String name, in PropertyValue value);

    /**
     * @brief     Sets a batch of AQ parameters atomically.
     *
     *            Atomicity: the implementation MUST validate every entry in
     *            @c parameters BEFORE applying any of them. If any entry
     *            would fail (unknown name, type mismatch, out-of-range, or
     *            read-only), NO parameter in the batch is applied and the
     *            method returns @c false (range/read-only) or throws
     *            EX_ILLEGAL_ARGUMENT (unknown name or type mismatch). On
     *            success every entry is applied as a single transaction
     *            visible to observers; partial application is not
     *            permitted.
     *
     *            Listeners receive one onParameterChanged() callback per
     *            entry that changed value. Entries whose value already
     *            matches the current setting may be skipped from
     *            notification (vendor choice).
     *
     *            Per-entry validation rules are identical to setAQParameter().
     *            Global parameters (AQParameterMetadata.isGlobal) propagate
     *            across ports as part of the same atomic transaction.
     *
     * @param[in] parameters  Batch of name/value pairs to apply.
     *
     * @returns   @c true on successful atomic apply; @c false if any entry
     *            fails range / read-only validation.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if any @c name is not
     *            a supported parameter or any value's active union field
     *            does not match the declared PropertyType.
     */
    boolean setAQParameters(in AQParameterKV[] parameters);

    /**
     * @brief     Activates a sound-mode preset.
     *
     *            The vendor stack applies the platform-defined values for
     *            every parameter listed under @c soundMode in the HFP.
     *            Listeners see one onSoundModeChanged() callback followed
     *            by one onParameterChanged() callback per parameter the
     *            mode touched.
     *
     * @param[in] soundMode  Sound mode to activate; must appear in
     *                       IAQProcessor.getAQSoundModes().
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if @c soundMode is not
     *            a supported sound mode for this processor.
     */
    void setAQSoundMode(in @utf8InCpp String soundMode);

    /**
     * @brief     Resets one or all parameters to their factory defaults.
     *
     *            When @c name is non-null, the single named parameter is
     *            reset to its AQParameterMetadata.defaultValue. When @c name
     *            is null, every parameter on this processor with a
     *            non-null defaultValue is reset.
     *
     *            Parameters whose AQParameterMetadata.defaultValue is null
     *            are left untouched.
     *
     *            Listeners receive one onParameterChanged() callback per
     *            parameter whose value changed. The active sound mode is
     *            NOT changed by this call.
     *
     * @param[in] name  Parameter to reset; null to reset every parameter
     *                  that has a declared default.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if @c name is non-null
     *            and not a supported parameter.
     */
    void resetToDefault(in @nullable @utf8InCpp String name);
}
