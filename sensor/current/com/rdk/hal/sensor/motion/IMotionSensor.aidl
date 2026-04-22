/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
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

/**
 * @file IMotionSensor.aidl
 * @brief Instance interface for a motion sensor (PIR, radar, etc.).
 *
 * The motion sensor can operate in a mode that reports either "motion" events
 * or "no-motion" events after an inactivity window. Sensitivity is optional:
 * if unsupported, both minSensitivity and maxSensitivity are 0.
 *
 * Lifecycle ownership:
 * The sensor uses a controller pattern. A single middleware component
 * (e.g., a power management service) calls open() to acquire an exclusive
 * IMotionSensorController for lifecycle and configuration control. Other
 * components register as event listeners via registerEventListener() to
 * observe motion/no-motion events without needing ownership.
 *
 * If the client that opened the controller crashes, stop() and close()
 * are implicitly called by the HAL to release the sensor.
 *
 * Timing controls vs active windows:
 * StartConfig.activeStartSeconds/activeStopSeconds and active windows
 * (configured via IMotionSensorController.setActiveWindows()) are
 * independent, layered mechanisms:
 *   - Timing controls govern the sensor hardware lifecycle — whether
 *     the sensor is active at all.
 *   - Active windows govern event suppression — whether detected events
 *     are delivered to listeners.
 *
 * Timing controls take precedence. Callers are responsible for ensuring
 * sensible combinations.
 *
 * @author Gerald Weatherup
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.State;
import com.rdk.hal.sensor.motion.Capabilities;
import com.rdk.hal.sensor.motion.IMotionSensorController;
import com.rdk.hal.sensor.motion.IMotionSensorControllerListener;
import com.rdk.hal.sensor.motion.IMotionSensorEventListener;

@VintfStability
interface IMotionSensor {

    /**
     * @brief Motion sensor resource identifier type.
     */
    @VintfStability parcelable Id {
        /**
         * @brief Undefined/invalid ID value.
         */
        const int UNDEFINED = -1;

        /**
         * @brief The concrete resource identifier value.
         */
        int value;
    }

    /**
     * @brief Returns immutable capabilities for this sensor.
     *
     * Can be called at any time, regardless of sensor state.
     *
     * @returns Immutable capabilities describing this sensor instance.
     */
    Capabilities getCapabilities();

    /**
     * @brief Get the current lifecycle state of the sensor.
     *
     * @returns Current state (e.g. STARTED, STOPPED, ERROR).
     */
    State getState();

    /**
     * @brief Open this sensor for exclusive control.
     *
     * On success the sensor is ready for configuration and start().
     * The returned IMotionSensorController provides lifecycle control,
     * configuration, and diagnostic queries.
     *
     * Only one controller may exist at a time. If the owning client
     * crashes, the HAL implicitly calls stop() and close() to release
     * the sensor.
     *
     * @param listener Listener for controller callbacks (state changes,
     *                 active window transitions).
     *
     * @returns IMotionSensorController, or null if the sensor cannot be opened.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is already open.
     * @exception binder::Status EX_NULL_POINTER if listener is null.
     *
     * @see close(), IMotionSensorController
     */
    @nullable IMotionSensorController open(in IMotionSensorControllerListener listener);

    /**
     * @brief Close this sensor and release the controller.
     *
     * The sensor must be in STOPPED state. On success the controller
     * is invalidated and another client may open() the sensor.
     *
     * @param controller The IMotionSensorController instance returned by open().
     *
     * @returns Success flag.
     * @retval true  Successfully closed.
     * @retval false The supplied controller is not the instance returned by open().
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     * @exception binder::Status EX_NULL_POINTER if controller is null.
     *
     * @see open()
     */
    boolean close(in IMotionSensorController controller);

    /**
     * @brief Register an event listener.
     *
     * Multiple listeners may be registered. Event listeners receive
     * motion/no-motion detection events via onEvent(). Registration does
     * not require the sensor to be open.
     *
     * @param motionSensorEventListener Listener to receive motion events.
     *
     * @returns Success flag.
     * @retval true  Listener registered.
     * @retval false Listener already registered.
     */
    boolean registerEventListener(in IMotionSensorEventListener motionSensorEventListener);

    /**
     * @brief Unregister a previously registered listener.
     *
     * @param motionSensorEventListener Listener to remove.
     *
     * @returns Success flag.
     * @retval true  Listener unregistered.
     * @retval false Listener not found.
     */
    boolean unregisterEventListener(in IMotionSensorEventListener motionSensorEventListener);
}
