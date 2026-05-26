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
package com.rdk.hal.compositeinput;

import com.rdk.hal.compositeinput.PortProperty;
import com.rdk.hal.compositeinput.PropertyKVPair;
import com.rdk.hal.PropertyValue;

/**
 * @brief     Composite Input Controller HAL interface.
 *
 *            Returned by ICompositeInputPort.open(). Provides exclusive write
 *            control over a composite input port: lifecycle (start/stop),
 *            property mutation, and metrics reset. All state-mutating operations
 *            are gated on the port being in the correct State.
 *
 *            If the client that opened this controller crashes, stop() and
 *            close() are implicitly called to perform cleanup.
 *
 * @author    Gerald Weatherup
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified:
 * - Success: returns EX_NONE; all output parameters are valid.
 * - Failure: returns a service-specific exception; output parameters are undefined.
 */
@VintfStability
interface ICompositeInputController {

    /**
     * Starts the composite input port.
     *
     * The port must be in READY state. On success it transitions through
     * STARTING to STARTED. During STARTING, onSignalStatusChanged() is always
     * fired at least once on the ICompositeInputControllerListener to indicate
     * the current signal state.
     *
     * Only one port may be in STARTED state at a time unless the platform
     * declares maximumConcurrentStartedPorts > 1 in PlatformCapabilities.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if not in READY state, or if
     *            starting this port would exceed maximumConcurrentStartedPorts.
     *
     * @see stop(), ICompositeInputPort.open(), PlatformCapabilities.maximumConcurrentStartedPorts
     */
    void start();

    /**
     * Stops the composite input port.
     *
     * The port must be in STARTED state. On success it transitions through
     * STOPPING to READY state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if not in STARTED state.
     *
     * @see start(), ICompositeInputPort.close()
     */
    void stop();

    /**
     * Sets a property value for this port.
     *
     * The key must be one of the PortProperty enum values declared by the
     * platform in its HFP under ports[].supportedProperties. Read-only keys
     * (PropertyMetadata.readOnly == true) throw EX_UNSUPPORTED_OPERATION.
     *
     * @param[in] property   Property key (from PortProperty enum).
     * @param[in] value      Property value; union field must match PropertyMetadata.type.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if property is unknown or
     *            value type does not match.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if property is read-only.
     *
     * @see ICompositeInputPort.getProperty(), setPropertyMulti()
     */
    void setProperty(in PortProperty property, in PropertyValue value);

    /**
     * Sets multiple property values atomically.
     *
     * All entries are validated before any are applied. If any entry is invalid
     * the entire call fails and no properties are changed.
     *
     * @param[in] properties  Array of PropertyKVPair with keys and values to set.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if any entry is invalid or
     *            contains a type mismatch.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if any property is read-only.
     *
     * @see setProperty(), ICompositeInputPort.getPropertyMulti()
     */
    void setPropertyMulti(in PropertyKVPair[] properties);

    /**
     * Resets telemetry metric counters for this port.
     *
     * Clears all accumulated METRIC_* values on this port back to their initial
     * state, and updates METRIC_LAST_RESET_TIMESTAMP to the current wall-clock time.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if port is not in STARTED state.
     *
     * @see PortProperty, ICompositeInputPort.getProperty()
     */
    void resetMetrics();
}
