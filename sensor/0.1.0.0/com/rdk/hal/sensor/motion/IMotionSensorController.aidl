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

/**
 * @file IMotionSensorController.aidl
 * @brief Exclusive controller interface for a motion sensor instance.
 *
 * Returned by {@link IMotionSensor#open(IMotionSensorControllerListener)}.
 * Provides lifecycle control (start/stop), configuration, and diagnostic
 * queries. Only one controller may exist per sensor at a time.
 *
 * If the client that opened this controller crashes, stop() and close()
 * are implicitly called by the HAL to release the sensor.
 *
 * @author Gerald Weatherup
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.LastEventInfo;
import com.rdk.hal.sensor.motion.StartConfig;
import com.rdk.hal.sensor.motion.TimeWindow;

@VintfStability
interface IMotionSensorController {

    /**
     * @brief Start the motion sensor.
     *
     * On success, the state transitions STOPPED → STARTING → STARTED.
     * IMotionSensorControllerListener.onStateChanged() fires for each transition.
     * If hardware initialisation fails, the state transitions to ERROR
     * (observable via onStateChanged()) and this call fails with
     * EX_SERVICE_SPECIFIC. Use IMotionSensor.close() to release the sensor
     * from ERROR; close() accepts STOPPED or ERROR.
     *
     * @param config Start configuration (mode, timing parameters).
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if StartConfig contains
     *            invalid values (e.g. noMotionSeconds outside 0–86400 range).
     * @exception binder::Status EX_SERVICE_SPECIFIC if hardware initialisation
     *            fails. The state transitions to ERROR before the exception
     *            is raised.
     *
     * Aligned with the repo-wide controller convention (`void start()` +
     * binder exceptions for failure, lifecycle observable via state change
     * listener) — same shape as compositeinput, hdmiinput, audiosink, etc.
     */
    void start(in StartConfig config);

    /**
     * @brief Stop the motion sensor.
     *
     * On success, the state transitions STARTED → STOPPING → STOPPED.
     * IMotionSensorControllerListener.onStateChanged() fires for each transition.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STARTED state.
     *
     * Aligned with the repo-wide controller convention (`void stop()` +
     * binder exception for failure).
     */
    void stop();

    /**
     * @brief Retrieve the configuration passed to start().
     *
     * @returns The StartConfig used for the current session.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is in STOPPED or ERROR state.
     */
    StartConfig getStartConfig();

    /**
     * @brief Retrieve diagnostic info about the most recent event.
     *
     * Returns the mode and timestamp of the last onEvent() delivered to
     * listeners. Returns null if no event has been delivered since start().
     *
     * @returns LastEventInfo, or null if no event has occurred.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is in STOPPED or ERROR state.
     */
    @nullable LastEventInfo getLastEventInfo();

    /**
     * @brief Get the current sensitivity value.
     *
     * @returns Current sensitivity level (within Capabilities.minSensitivity..maxSensitivity).
     */
    int getSensitivity();

    /**
     * @brief Set the sensitivity level.
     *
     * @param sensitivity Desired level. Must be within
     *        {@link Capabilities#minSensitivity}..{@link Capabilities#maxSensitivity}.
     *
     * @returns Success flag.
     * @retval true  Sensitivity was set.
     * @retval false Sensitivity out of range or unsupported.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     */
    boolean setSensitivity(in int sensitivity);

    /**
     * @brief Enable or disable autonomous motion detection during deep sleep.
     *
     * When enabled and supported by the platform, the sensor may wake the system
     * from deep sleep based on motion activity without full SoC resume.
     *
     * The deep sleep module must be configured independently to support the
     * CPU wake-up reasons — enabling sensor autonomy alone does not affect
     * CPU deep sleep behaviour.
     *
     * @param enabled True to enable, false to disable.
     *
     * @returns Success flag.
     * @retval true  Mode updated (or already at requested value).
     * @retval false Not supported (see Capabilities.supportsDeepSleepAutonomy).
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     */
    boolean setAutonomousDuringDeepSleep(in boolean enabled);

    /**
     * @brief Query whether autonomous deep-sleep mode is enabled.
     *
     * @returns True if enabled, false otherwise (or unsupported).
     */
    boolean isAutonomousDuringDeepSleepEnabled();

    /**
     * @brief Set daily time windows when the sensor should actively monitor.
     *
     * Windows wrapping across midnight are supported (endTime < startTime).
     * Changes take effect on next start() call. Calling this method replaces
     * any previously configured windows.
     *
     * @param windows Array of time windows. Motion events outside these windows
     *        are suppressed. Empty array or windows with both values set to 0
     *        enables 24-hour monitoring. Windows may overlap; the union of all
     *        windows defines the active periods.
     *
     * @returns Success flag.
     * @retval true  Windows configured successfully.
     * @retval false Invalid window ranges or sensor state prevents configuration.
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT if any window has invalid
     *            time values (outside 0–86399 range).
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     */
    boolean setActiveWindows(in TimeWindow[] windows);

    /**
     * @brief Get the currently configured active time windows.
     *
     * @returns Array of active windows. Empty if 24-hour monitoring is configured
     *          or no windows have been set.
     */
    TimeWindow[] getActiveWindows();

    /**
     * @brief Clear all active time windows, enabling 24-hour monitoring.
     *
     * Equivalent to calling setActiveWindows() with an empty array.
     *
     * @returns Success flag.
     * @retval true  Windows cleared successfully.
     * @retval false Unable to clear (e.g., sensor not in valid state).
     *
     * @exception binder::Status EX_ILLEGAL_STATE if sensor is not in STOPPED state.
     */
    boolean clearActiveWindows();
}
