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
import com.rdk.hal.compositeinput.VideoScaling;
import com.rdk.hal.compositeinput.Property;
import com.rdk.hal.compositeinput.PortMetrics;
import com.rdk.hal.compositeinput.IPortEventListener;
import com.rdk.hal.compositeinput.IPortTelemetryListener;
import com.rdk.hal.PropertyValue;

/**
 * @brief Composite Input Port interface.
 * 
 * Provides control and monitoring for an individual composite video input port.
 * Each port can be independently controlled, configured, and monitored.
 * 
 * @author Gerald Weatherup
 */
@VintfStability
interface ICompositeInputPort
{
    /**
     * @brief Gets the port ID.
     * 
     * @returns Port ID for this port instance (0 to maxPorts-1).
     */
    int getId();
    
    /**
     * @brief Gets the capabilities of this specific port.
     * 
     * Returns port-specific capabilities which may differ from
     * platform capabilities if ports have different features.
     * 
     * @returns PortCapabilities parcelable.
     */
    PortCapabilities getCapabilities();
    
    /**
     * @brief Gets the current status of this port.
     * 
     * Returns current connection state, signal status, video mode,
     * and other runtime state information.
     * 
     * @returns PortStatus parcelable with current port state.
     * @exception EX_ILLEGAL_STATE if service is not ready.
     */
    PortStatus getStatus();
    
    /**
     * @brief Sets this port as active or inactive.
     * 
     * Activates or deactivates video presentation from this port.
     * Only one port can be active for presentation at a time.
     * 
     * @param[in] active True to activate, false to deactivate.
     * @exception EX_ILLEGAL_STATE if port cannot be activated (e.g., no signal).
     */
    void setActive(in boolean active);
    
    /**
     * @brief Scales and positions the video from this port.
     * 
     * Applies scaling and positioning to the video output.
     * The scaling rectangle must be within the display resolution bounds.
     * 
     * @param[in] scaling Video scaling parameters (mode and rectangle).
     * @exception EX_ILLEGAL_ARGUMENT if scaling parameters are invalid.
     * @exception EX_ILLEGAL_STATE if port is not active.
     * @exception EX_UNSUPPORTED_OPERATION if scaling mode not supported.
     */
    void scaleVideo(in VideoScaling scaling);
    
    /**
     * @brief Gets a property value for this port.
     * 
     * Retrieves runtime property values such as signal strength,
     * detected video standard, or audio presence.
     * 
     * @param[in] property The property to query.
     * @returns PropertyValue for the requested property, or null if not supported.
     * @exception EX_ILLEGAL_ARGUMENT if property is invalid.
     */
    @nullable PropertyValue getProperty(in Property property);
    
    /**
     * @brief Sets a property value for this port.
     * 
     * Configures port-specific settings. Not all properties are writable.
     * 
     * @param[in] property The property to set.
     * @param[in] value The value to set.
     * @exception EX_ILLEGAL_ARGUMENT if property or value is invalid.
     * @exception EX_UNSUPPORTED_OPERATION if property is read-only.
     */
    void setProperty(in Property property, in PropertyValue value);
    
    /**
     * @brief Gets telemetry metrics for this port.
     * 
     * Returns statistical information about port operation,
     * such as signal lock times and drop counts.
     * 
     * @returns PortMetrics parcelable with telemetry data.
     * @exception EX_UNSUPPORTED_OPERATION if metrics not supported.
     */
    PortMetrics getMetrics();
    
    /**
     * @brief Resets telemetry metrics for this port.
     * 
     * Clears accumulated metrics counters.
     * 
     * @exception EX_UNSUPPORTED_OPERATION if metrics not supported.
     */
    void resetMetrics();
    
    /**
     * @brief Registers an event listener for this port.
     * 
     * Registers callbacks for connection, signal status, and video mode events.
     * Multiple listeners can be registered.
     * 
     * @param[in] listener The event listener to register.
     * @exception EX_ILLEGAL_ARGUMENT if listener is null.
     */
    void registerEventListener(in IPortEventListener listener);
    
    /**
     * @brief Unregisters a previously registered event listener.
     * 
     * @param[in] listener The event listener to unregister.
     * @exception EX_ILLEGAL_ARGUMENT if listener is null or not registered.
     */
    void unregisterEventListener(in IPortEventListener listener);
    
    /**
     * @brief Registers a telemetry listener for this port.
     * 
     * Registers callbacks for signal quality changes and metrics updates.
     * 
     * @param[in] listener The telemetry listener to register.
     * @exception EX_ILLEGAL_ARGUMENT if listener is null.
     * @exception EX_UNSUPPORTED_OPERATION if metrics not supported.
     */
    void registerTelemetryListener(in IPortTelemetryListener listener);
    
    /**
     * @brief Unregisters a previously registered telemetry listener.
     * 
     * @param[in] listener The telemetry listener to unregister.
     * @exception EX_ILLEGAL_ARGUMENT if listener is null or not registered.
     */
    void unregisterTelemetryListener(in IPortTelemetryListener listener);
}
