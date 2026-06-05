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
import com.rdk.hal.audiomixer.AQParameterMetadata;
import com.rdk.hal.audiomixer.AQProcessor;
import com.rdk.hal.audiomixer.IAQProcessorController;
import com.rdk.hal.audiomixer.IAQProcessorListener;
import com.rdk.hal.PropertyValue;

/**
 * @file      IAQProcessor.aidl
 * @brief     AQ (Audio Quality) processor HAL interface.
 *
 * @details   Per-port handle returned by IAudioOutputPort.getAQProcessor().
 *            Provides read access to the parameter set and current values,
 *            multi-client observation via registerListener(), and an
 *            exclusive write controller via open() / close().
 *
 *            Source of truth — the parameter inventory and metadata
 *            returned by getSupportedParameters() is populated by the
 *            vendor HAL from the platform HFP
 *            (hfp-audiomixer.yaml -> aqProcessors[].parameters[]). Names
 *            returned correspond to the @c parameters[].name field declared
 *            in that HFP entry. The AQParameter.aidl enum is a docs-only
 *            spelling reference and is not consulted at runtime.
 *
 *            Open / close ownership model — only one writer may hold the
 *            IAQProcessorController per processor instance at a time. A
 *            second open() call while another client holds the controller
 *            throws EX_ILLEGAL_STATE; null is returned only for internal
 *            init failures.
 *
 *            Crash recovery — if the client holding the controller crashes,
 *            the HAL detects the binder death and implicitly closes the
 *            controller. Parameter STATE survives the implicit close: the
 *            next client to open() sees the values the previous client left
 *            behind. Observers registered against this interface persist
 *            across writer churn.
 *
 *            Processor type vs version — getProcessorType() returns the
 *            AQProcessor enum value identifying the family (DOLBY_MS12_2_6,
 *            DTS_ULTRA, etc.) for downstream clients that branch on type.
 *            getVersion() returns the vendor version string for the loaded
 *            processor instance (e.g. "2.6.1", "1.4.3") so different
 *            instances of the same family are distinguishable. getName()
 *            returns a free-form human-readable label for diagnostics.
 *
 * @see       IAudioOutputPort.getAQProcessor()
 * @see       IAQProcessorController
 * @see       IAQProcessorListener
 * @see       AQParameterMetadata
 * @see       AQParameterKV
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
interface IAQProcessor {

    /**
     * @brief     Returns a free-form human-readable identifier for this
     *            processor instance.
     *
     * @details   Intended for diagnostics, log lines, and tuning UI
     *            headings. Format is vendor-defined and may combine the
     *            processor family and version (e.g. "Dolby MS12-X v2.6.1").
     *            Downstream clients that branch on processor identity
     *            MUST use getProcessorType() and getVersion() instead of
     *            parsing this string.
     *
     * @returns   Vendor-defined identifier; never null but may be empty
     *            when the vendor does not expose a label.
     */
    @utf8InCpp String getName();

    /**
     * @brief     Returns the processor family enum.
     *
     * @details   Identifies the processor family for clients that need to
     *            branch on it (e.g. apply MS12-specific telemetry
     *            different from DTS-specific telemetry). Split from
     *            getName() so type matching does not depend on parsing a
     *            free-form string.
     *
     * @returns   AQProcessor enum value for this instance.
     *
     * @see       AQProcessor
     */
    AQProcessor getProcessorType();

    /**
     * @brief     Returns the vendor version string for this processor.
     *
     * @details   Distinguishes multiple instances of the same processor
     *            family running on the same platform — e.g. an MS12 v1.4.3
     *            instance routed to SPDIF and an MS12 v2.6.1 instance
     *            routed to HDMI. The version string MUST match the
     *            @c aqProcessors[].version field declared in
     *            hfp-audiomixer.yaml for this processor instance.
     *
     *            Recommended formatting is a dotted semver-like string
     *            (e.g. "2.6.1"); vendor-defined otherwise. Never null but
     *            may be empty when the vendor does not version this
     *            processor family.
     *
     * @returns   Vendor version string.
     */
    @utf8InCpp String getVersion();

    /**
     * @brief     Returns the full set of supported AQ parameters with
     *            their metadata.
     *
     * @details   The names in the returned array correspond to the
     *            @c parameters[].name field declared in hfp-audiomixer.yaml
     *            under this processor's entry. The list is stable for the
     *            lifetime of the underlying processor instance — clients
     *            that cache it MUST refresh on IAQProcessorListener.
     *            onProcessorReset().
     *
     * @returns   Array of AQParameterMetadata describing every tunable
     *            parameter on this processor. Empty when the vendor
     *            declares no tunable parameters.
     *
     * @see       AQParameterMetadata
     * @see       IAQProcessorListener.onProcessorReset()
     */
    AQParameterMetadata[] getSupportedParameters();

    /**
     * @brief     Reads the current value of a single AQ parameter.
     *
     * @param[in] name  Canonical parameter name (must appear in
     *                  getSupportedParameters()).
     *
     * @returns   Current PropertyValue; active union field matches the
     *            parameter's AQParameterMetadata.type.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if @c name is not a
     *            supported parameter.
     */
    PropertyValue getAQParameter(in @utf8InCpp String name);

    /**
     * @brief     Reads a coherent snapshot of multiple AQ parameter values.
     *
     * @details   The vendor HAL MUST return values sampled from a single
     *            consistent instant — callers can compare cross-parameter
     *            invariants without racing partial updates.
     *
     * @param[in] names  Canonical parameter names to read; each MUST appear
     *                   in getSupportedParameters().
     *
     * @returns   Array of AQParameterKV in the same order as @c names.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if any @c name is not
     *            a supported parameter.
     */
    AQParameterKV[] getAQParameters(in @utf8InCpp String[] names);

    /**
     * @brief     Returns the list of supported sound-mode preset names.
     *
     * @details   Sound modes are platform-defined bundles of parameter
     *            values (e.g. "MOVIE", "MUSIC", "NEWS"). The membership of
     *            each mode is recorded in AQParameterMetadata.
     *            includedInSoundMode. Empty when the vendor declares no
     *            sound-mode presets.
     *
     * @returns   Array of sound-mode names.
     */
    @utf8InCpp String[] getAQSoundModes();

    /**
     * @brief     Returns the currently active sound-mode name.
     *
     * @details   Empty when no sound mode is active (i.e. parameters are
     *            being driven individually rather than via a preset).
     *
     * @returns   Active sound-mode name; one of the strings in
     *            getAQSoundModes(), or empty.
     */
    @utf8InCpp String getAQSoundMode();

    /**
     * @brief     Registers a listener for AQ processor events.
     *
     * @details   Multiple listeners may be registered. Registration does
     *            NOT require write ownership of the controller — a
     *            settings UI, diagnostics tool, or firmware migration
     *            service can observe state changes while another client
     *            owns the writer.
     *
     * @param[in] listener  Listener for AQ processor callbacks.
     *
     * @exception binder::Status EX_NULL_POINTER if @c listener is null.
     *
     * @see       IAQProcessorListener
     */
    void registerListener(in IAQProcessorListener listener);

    /**
     * @brief     Unregisters a previously registered listener.
     *
     * @param[in] listener  Listener previously passed to registerListener().
     */
    void unregisterListener(in IAQProcessorListener listener);

    /**
     * @brief     Opens exclusive write control over this AQ processor.
     *
     * @details   Returns an IAQProcessorController for parameter and
     *            sound-mode writes. Only one controller may exist per
     *            processor instance at a time. If the client holding the
     *            controller crashes, the HAL detects the binder death and
     *            implicitly closes the controller; parameter state is
     *            preserved across the implicit close.
     *
     *            A second open() while another client holds the controller
     *            throws EX_ILLEGAL_STATE. Null is returned only for
     *            internal init failures.
     *
     * @returns   IAQProcessorController on success; null on internal
     *            failure (no other client holds the controller).
     *
     * @exception binder::Status EX_ILLEGAL_STATE if another client already
     *            holds the controller.
     *
     * @see       close()
     * @see       IAQProcessorController
     */
    @nullable IAQProcessorController open();

    /**
     * @brief     Closes the exclusive write controller.
     *
     * @param[in] controller  The controller instance returned by open().
     *
     * @returns   @c true on successful close; @c false if the supplied
     *            controller is unknown or already closed.
     *
     * @exception binder::Status EX_NULL_POINTER if @c controller is null.
     *
     * @see       open()
     */
    boolean close(in IAQProcessorController controller);
}
