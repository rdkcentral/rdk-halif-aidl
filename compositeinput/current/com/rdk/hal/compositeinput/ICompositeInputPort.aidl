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

import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.PortCapabilities;
import com.rdk.hal.compositeinput.PortStatus;
import com.rdk.hal.compositeinput.PropertyKVPair;
import com.rdk.hal.compositeinput.PortMetrics;
import com.rdk.hal.compositeinput.IPortEventListener;
import com.rdk.hal.compositeinput.IPortTelemetryListener;
import com.rdk.hal.PropertyValue;

/**
 * @brief Composite Input Port interface.
 *
 * Provides control and monitoring for an individual composite video input port.
 * Each port can be independently controlled, configured, and monitored.
 */
@VintfStability
interface ICompositeInputPort
{
    /**
     * Gets the port ID.
     *
     * Returns the unique identifier for this port instance. This ID matches
     * the ID used in ICompositeInputManager.getPort().
     *
     * @returns Port ID for this port instance (0 to maxPorts-1).
     */
    int getId();

    /**
     * Gets the capabilities of this specific port.
     *
     * Returns port-specific capabilities which may differ from platform
     * capabilities if ports have different features. This can be called
     * at any time and returns a constant value.
     *
     * @returns PortCapabilities parcelable containing port-specific capabilities.
     *
     * @see PortCapabilities, ICompositeInputManager.getPlatformCapabilities()
     */
    PortCapabilities getCapabilities();

    /**
     * Gets the current status of this port.
     *
     * Returns current connection state, signal status, detected video mode,
     * and other runtime state information. This should be polled or used in
     * conjunction with event listeners for real-time updates.
     *
     * @returns PortStatus parcelable with current port state.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if service is not ready.
     *
     * @see PortStatus, IPortEventListener
     */
    PortStatus getStatus();

    /**
     * Sets this port as active or inactive.
     *
     * Activates or deactivates video presentation from this port. When activated,
     * the port's video signal is displayed. Only one port can be active for
     * presentation at a time; activating a port deactivates any currently active port.
     *
     * @param[in] active     True to activate this port, false to deactivate.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if port cannot be activated (e.g., no stable signal).
     * @pre Port should have a stable signal (SignalStatus.STABLE) to activate successfully.
     * @post If successful, this port becomes the active video source.
     *
     * @see getStatus(), SignalStatus
     */
    void setActive(in boolean active);

    /**
     * Gets a property value for this port by string key.
     *
     * Retrieves runtime property values such as signal strength, detected video
     * standard, or audio presence. Property keys are defined in the HFP YAML and
     * discoverable via getCapabilities().supportedProperties.
     *
     * Clients should check the port's supportedProperties array before calling
     * this method to ensure the property is available on this port.
     *
     * @param[in] propertyKey     Property key string (e.g., "SIGNAL_STRENGTH", "VIDEO_STANDARD").
     * @returns PropertyValue for the requested property, or null if not supported.
     *
     * @retval PropertyValue      Valid property value (check appropriate union field based on property type).
     * @retval null               Property key is unknown or not supported by this port.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if propertyKey is null or empty.
     *
     * @see PropertyValue, getCapabilities(), setProperty(), getPropertyMulti()
     */
    @nullable PropertyValue getProperty(in @utf8InCpp String propertyKey);

    /**
     * Sets a property value for this port by string key.
     *
     * Configures port-specific settings. Not all properties are writable; most
     * properties are read-only status values. Property keys and writability are
     * defined in the HFP YAML and discoverable via PropertyMetadata.
     *
     * @param[in] propertyKey     Property key string to set.
     * @param[in] value          The value to set (use appropriate PropertyValue union field).
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if propertyKey or value is invalid or type mismatch.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if property is read-only or not supported by this port.
     *
     * @see PropertyValue, getProperty(), setPropertyMulti()
     */
    void setProperty(in @utf8InCpp String propertyKey, in PropertyValue value);

    /**
     * Gets multiple property values in a single call.
     *
     * Efficient batch retrieval of multiple properties. Reduces IPC overhead
     * when querying multiple properties simultaneously. Unsupported properties
     * will have null values in the returned array.
     *
     * @param[in] propertyKeys     Array of property key strings to retrieve.
     * @returns Array of PropertyKVPair with keys and values populated.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if propertyKeys is null or empty.
     * @post Returned array length matches input array length.
     *
     * @see PropertyKVPair, getProperty(), setPropertyMulti()
     */
    PropertyKVPair[] getPropertyMulti(in @utf8InCpp String[] propertyKeys);

    /**
     * Sets multiple property values in a single call.
     *
     * Efficient batch setting of multiple properties. All properties are validated
     * before any are applied, ensuring atomic operation (all succeed or all fail).
     *
     * @param[in] properties     Array of PropertyKVPair with keys and values to set.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if properties is null, empty, or contains invalid entries.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if any property is read-only or not supported.
     * @pre All properties in the array must be valid and writable.
     * @post Either all properties are updated successfully, or none are (atomic operation).
     *
     * @see PropertyKVPair, setProperty(), getPropertyMulti()
     */
    void setPropertyMulti(in PropertyKVPair[] properties);

    /**
     * Gets telemetry metrics for this port.
     *
     * Returns statistical information about port operation, including signal
     * lock times, drop counts, and uptime. Metrics availability depends on
     * port capabilities (PortCapabilities.metricsSupported).
     *
     * @returns PortMetrics parcelable with telemetry data.
     *
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if metrics are not supported by this port.
     * @pre Port must support metrics (PortCapabilities.metricsSupported == true).
     *
     * @see PortMetrics, resetMetrics(), getCapabilities()
     */
    PortMetrics getMetrics();

    /**
     * Resets telemetry metrics for this port.
     *
     * Clears accumulated metrics counters and restarts telemetry collection.
     * Useful for measuring performance over a specific time period.
     *
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if metrics are not supported by this port.
     * @pre Port must support metrics (PortCapabilities.metricsSupported == true).
     * @post All metric counters are reset to zero, lastResetTimestampMs is updated to current time.
     *
     * @see getMetrics()
     */
    void resetMetrics();

    /**
     * Registers an event listener for this port.
     *
     * Registers callbacks for connection, signal status, and video mode events.
     * Multiple listeners can be registered. Callbacks are delivered asynchronously
     * via oneway binder calls.
     *
     * @param[in] listener     The event listener to register.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null.
     * @post listener receives event callbacks for this port.
     *
     * @see IPortEventListener, unregisterEventListener()
     */
    void registerEventListener(in IPortEventListener listener);

    /**
     * Unregisters a previously registered event listener.
     *
     * Removes a listener from receiving event callbacks. After unregistration,
     * no further callbacks will be delivered to this listener.
     *
     * @param[in] listener     The event listener to unregister.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null or was not previously registered.
     * @post listener no longer receives event callbacks.
     *
     * @see IPortEventListener, registerEventListener()
     */
    void unregisterEventListener(in IPortEventListener listener);

    /**
     * Registers a telemetry listener for this port.
     *
     * Registers callbacks for signal quality changes and metrics updates.
     * Requires port metrics support (PortCapabilities.metricsSupported).
     *
     * @param[in] listener     The telemetry listener to register.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null.
     * @exception binder::Status EX_UNSUPPORTED_OPERATION if metrics are not supported by this port.
     * @pre Port must support metrics (PortCapabilities.metricsSupported == true).
     * @post listener receives telemetry callbacks for this port.
     *
     * @see IPortTelemetryListener, unregisterTelemetryListener(), getCapabilities()
     */
    void registerTelemetryListener(in IPortTelemetryListener listener);

    /**
     * Unregisters a previously registered telemetry listener.
     *
     * Removes a telemetry listener from receiving callbacks. After unregistration,
     * no further telemetry callbacks will be delivered to this listener.
     *
     * @param[in] listener     The telemetry listener to unregister.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if listener is null or was not previously registered.
     * @post listener no longer receives telemetry callbacks.
     *
     * @see IPortTelemetryListener, registerTelemetryListener()
     */
    void unregisterTelemetryListener(in IPortTelemetryListener listener);
}
