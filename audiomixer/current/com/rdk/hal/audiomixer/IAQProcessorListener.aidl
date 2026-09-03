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

import com.rdk.hal.PropertyValue;

/**
 * @file      IAQProcessorListener.aidl
 * @brief     Observer callback interface for an AQ (Audio Quality) processor.
 *
 *            Registered against IAQProcessor via registerListener() and
 *            unregisterListener(). Listener registration is independent of
 *            write ownership: a settings UI, diagnostics tool, certification
 *            suite, or firmware migration service can observe parameter
 *            and sound-mode changes without holding the
 *            IAQProcessorController.
 *
 *            Multiple listeners may be registered concurrently. Callbacks are
 *            @c oneway — the HAL does not block on listener delivery.
 *            Listeners must not perform long-running work in the callback;
 *            offload to a worker thread.
 *
 * @see       IAQProcessor.registerListener()
 * @see       IAQProcessor.unregisterListener()
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
@VintfStability
oneway interface IAQProcessorListener {

    /**
     * @brief     Fired when a single AQ parameter value changes.
     *
     *            The change source may be:
     *              - A direct write via IAQProcessorController.setAQParameter().
     *              - A batch write via IAQProcessorController.setAQParameters()
     *                (the listener sees one onParameterChanged() call per
     *                parameter in the batch).
     *              - A sound-mode activation via setAQSoundMode() that
     *                touched this parameter (the listener also sees a
     *                separate onSoundModeChanged() call).
     *              - A resetToDefault() call that touched this parameter.
     *              - A global parameter propagating from another port's
     *                IAQProcessorController (AQParameterMetadata.isGlobal).
     *
     *            Listeners on every port that exposes the same global
     *            parameter receive the callback when one port writes it.
     *
     * @param[in] name      Canonical parameter name (matches the entries
     *                      from IAQProcessor.getSupportedParameters()).
     * @param[in] value     New PropertyValue. The active union field
     *                      matches the AQParameterMetadata.type for this name.
     */
    void onParameterChanged(in @utf8InCpp String name, in PropertyValue value);

    /**
     * @brief     Fired when the active sound mode changes.
     *
     *            The change source may be a direct call to
     *            IAQProcessorController.setAQSoundMode() or a platform-
     *            initiated change (e.g. content-adaptive switch). The
     *            listener will additionally see one onParameterChanged()
     *            call for every parameter the new mode touched.
     *
     * @param[in] soundMode  New active sound mode; one of the strings
     *                       returned by IAQProcessor.getAQSoundModes().
     */
    void onSoundModeChanged(in @utf8InCpp String soundMode);

    /**
     * @brief     Fired when the underlying AQ processor instance is replaced.
     *
     *            Vendor stacks may hot-swap the processor (e.g. a firmware
     *            update replaces MS12 v1.4 with v2.6, or the platform
     *            re-loads the processor after a fault recovery). The
     *            previously cached supported-parameter set, sound-mode
     *            list, and version string may all be stale.
     *
     *            Contract: the vendor HAL MUST fire this callback only
     *            AFTER the new processor is fully queryable and
     *            consistent — i.e. getName(), getVersion(),
     *            getSupportedParameters(), getAQSoundModes(), and
     *            getAQParameter() all return the new instance's data
     *            before any listener sees this callback. Clients can
     *            therefore call those query methods inside the callback
     *            without racing the swap.
     *
     *            On receipt, clients should:
     *              - Discard any cached AQParameterMetadata.
     *              - Re-query getSupportedParameters().
     *              - Re-query getName() / getVersion() to detect a
     *                processor-family or version change.
     *              - Re-apply any client-side persisted parameter overrides.
     */
    void onProcessorReset();
}
