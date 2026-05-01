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
 * @file IMotionSensorControllerListener.aidl
 * @brief Controller callback listener for motion sensor lifecycle and
 *        active window transitions.
 *
 * Passed into {@link IMotionSensor#open(IMotionSensorControllerListener)}.
 * Delivered exclusively to the controller owner. All callbacks are oneway
 * (non-blocking, fire-and-forget).
 *
 * Motion/no-motion detection events are delivered separately on
 * {@link IMotionSensorEventListener} to any registered observer.
 *
 * @author Gerald Weatherup
 */
package com.rdk.hal.sensor.motion;

import com.rdk.hal.sensor.motion.State;

@VintfStability
oneway interface IMotionSensorControllerListener {

    /**
     * @brief Called when the sensor transitions to a new lifecycle state.
     *
     * Fired for all transitions driven by start(), stop(), and error
     * conditions. The motion sensor State enum covers STOPPED, STARTING,
     * STARTED, STOPPING, ERROR — controller acquisition (IMotionSensor.open)
     * and release (IMotionSensor.close) do not produce dedicated state
     * values; they bracket the STOPPED period during which the controller
     * exists.
     *
     * @param[in] oldState  The state being left.
     * @param[in] newState  The state being entered.
     */
    void onStateChanged(in State oldState, in State newState);

    /**
     * @brief Called when the sensor enters an active monitoring period.
     *
     * Fires when the current time enters the union of all configured active
     * windows. If windows overlap, this callback fires once on the first
     * entry — not per-window. Motion events may be delivered while inside
     * the active period.
     *
     * Only fires when active windows have been configured via
     * IMotionSensorController.setActiveWindows() with a non-empty array.
     * Not fired when 24-hour monitoring is in effect, whether that is
     * because no windows have been set or because setActiveWindows() was
     * called with an empty array.
     */
    void onActiveWindowEntered();

    /**
     * @brief Called when the sensor exits all active monitoring windows.
     *
     * Fires when the current time leaves the union of all configured active
     * windows. Motion events are suppressed while outside active windows.
     *
     * Only fires when active windows have been configured via
     * IMotionSensorController.setActiveWindows() with a non-empty array.
     * Not fired in 24-hour monitoring mode (no windows / empty array).
     */
    void onActiveWindowExited();
}
