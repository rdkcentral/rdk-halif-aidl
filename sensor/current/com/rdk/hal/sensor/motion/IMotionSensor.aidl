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
 * @details
 * The motion sensor can operate in a mode that reports either "motion" events
 * or "no-motion" events after an inactivity window. Sensitivity is optional:
 * if unsupported, both minSensitivity and maxSensitivity are 0.
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.State;
import com.rdk.hal.sensor.motion.Capabilities;
import com.rdk.hal.sensor.motion.IMotionSensorEventListener;
import com.rdk.hal.sensor.motion.OperationalMode;
import com.rdk.hal.sensor.motion.TimeWindow;

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
     * @return Capabilities describing this sensor.
     */
    Capabilities getCapabilities();

    /**
     * @brief Start the motion sensor.
     *
     * @param operationalMode Operational mode (MOTION or NO_MOTION).
     * @param noMotionSeconds After the sensor becomes active, the contiguous number
     *        of seconds without motion before a NO_MOTION event is reported. Use 0 for none.
     * @param activeStartSeconds Delay in seconds before the sensor becomes active after start().
     *        Use 0 for immediate activation.
     * @param activeStopSeconds Duration in seconds after which the sensor becomes inactive.
     *        Use 0 for no automatic stop.
     *
     * @details On success, the state transitions STOPPED → STARTING → STARTED.
     *          If initialization fails, the state becomes ERROR.
     *
     * @retval true Sensor accepted the start request.
     * @retval false Sensor could not be started (e.g. invalid hw state).
     */
    boolean start(in OperationalMode operationalMode,
                  in int noMotionSeconds,
                  in int activeStartSeconds,
                  in int activeStopSeconds);

    /**
     * @brief Stop the motion sensor.
     * @details On success, the state transitions STARTED → STOPPING → STOPPED.
     * @retval true Sensor accepted the stop request.
     * @retval false Sensor could not be stopped.
     */
    boolean stop();

    /**
     * @brief Get the current lifecycle state of the sensor.
     * @return State Current state (e.g. STARTED, STOPPED, ERROR).
     */
    State getState();

    /**
     * @brief Get the operational mode configured at start().
     * @return OperationalMode Current mode (MOTION or NO_MOTION).
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is STOPPED or ERROR.
     */
    OperationalMode getOperationalMode();

    /**
     * @brief Get the current sensitivity value.
     * @return int Current sensitivity level.
     */
    int getSensitivity();

    /**
     * @brief Set the sensitivity level.
     *
     * @param sensitivity Desired level. Must be within
     *        {@link Capabilities#minSensitivity}..{@link Capabilities#maxSensitivity}.
     * @retval true Sensitivity was set.
     * @retval false Sensitivity out of range or unsupported.
     * @exception binder::Status EX_ILLEGAL_STATE if the sensor is not STOPPED.
     */
    boolean setSensitivity(in int sensitivity);

    /**
     * @brief Enable or disable autonomous motion detection during deep sleep.
     *
     * @param enabled True to enable, false to disable.
     * @returns success flag.
     * @retval true Mode updated (or already at requested value).
     * @retval false Operation not supported (see Capabilities.supportsDeepSleepAutonomy).
     * @exception binder::Status EX_ILLEGAL_STATE if the sensor is not STOPPED.
     *
     * @details
     * When enabled and supported by the platform, the sensor may wake the system
     * from deep sleep based on motion activity without full SoC resume.
     *
     * Since this wake source could be hardware independent of the CPU, the sensor enabling has no effect on DeepSleep of the CPU.
     * The DeepSleep module must be configured independently to support the CPU wakeup.
     */
    boolean setAutonomousDuringDeepSleep(in boolean enabled);

    /**
     * @brief Query whether autonomous deep-sleep mode is enabled.
     * @return boolean True if enabled, false otherwise (or unsupported).
     */
    boolean isAutonomousDuringDeepSleepEnabled();

    /**
     * @brief Register an event listener. A listener may only be registered once.
     * @param motionSensorEventListener Listener to receive motion events.
     * @retval true Listener registered.
     * @retval false Listener already registered.
     */
    boolean registerEventListener(in IMotionSensorEventListener motionSensorEventListener);

    /**
     * @brief Unregister a previously registered listener.
     * @param motionSensorEventListener Listener to remove.
     * @retval true Listener unregistered.
     * @retval false Listener not found.
     */
    boolean unregisterEventListener(in IMotionSensorEventListener motionSensorEventListener);

    /**
     * @brief Set daily time windows when the sensor should actively monitor.
     *
     * @param windows Array of time windows. Motion events outside these windows
     *        are suppressed. Empty array or windows with both values set to 0
     *        enables 24-hour monitoring. Windows may overlap; the union of all
     *        windows defines the active periods.
     * @retval true Time windows configured successfully.
     * @retval false Invalid window ranges or sensor state prevents configuration.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if any window has invalid
     *            time values (outside 0-86399 range).
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not STOPPED.
     *
     * @details
     * Windows wrapping across midnight are supported (endTime < startTime).
     * Changes take effect on next start() call. Calling this method replaces
     * any previously configured windows.
     */
    boolean setActiveWindows(in TimeWindow[] windows);

    /**
     * @brief Get the currently configured active time windows.
     *
     * @return TimeWindow[] Array of active windows. Empty if 24-hour monitoring
     *         is configured or no windows have been set.
     */
    TimeWindow[] getActiveWindows();

    /**
     * @brief Clear all active time windows, enabling 24-hour monitoring.
     *
     * @retval true Windows cleared successfully.
     * @retval false Unable to clear (e.g., sensor not in valid state).
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not STOPPED.
     *
     * @details Equivalent to calling setActiveWindows() with an empty array.
     */
    boolean clearActiveWindows();
}
