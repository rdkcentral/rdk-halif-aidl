/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
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
package com.rdk.hal.deepsleep;
import com.rdk.hal.deepsleep.Capabilities;
import com.rdk.hal.deepsleep.WakeUpTrigger;
import com.rdk.hal.deepsleep.KeyCode;

/** 
 *  @brief     Deep Sleep HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IDeepSleep
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "DeepSleep";

    /**
     * Gets the capabilities of the deep sleep service.
     *
     * @returns Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Places the device into deep sleep which is configured to wake on a set of trigger types.
     *
     * The function will block until it resumes from standby and then returns the triggers that occured to wake up the device.
     * Upon return, the system clock has been adjusted to closely represent the actual elapsed time spent in deep sleep.
     *
     * The `preconfiguredTriggers[]` reported in the `Capabilities` are always enabled as trigger sources.
     * If they are not explicitly specified in the `triggersToWakeUpon[]` array then they are implicitly added.
     *
     * @param[in] triggersToWakeUpon    Array of wake up trigger events to wake upon after entering deep sleep.
     * @param[out] wokeUpByTriggers     Array of wake up trigger events that occurred when waking the device from deep sleep.
     * @param[out] keyCode              If one of the `wokeUpByTriggers[]` is an RCU based trigger, then keyCode contains the Linux key code.  
     *                                  `null` if not applicable.
     *
     * @returns boolean - true on success or false if any of the triggers are not supported on the device.
     * @retval true - the deep sleep was successful and woke up on one of the explicit or implicit triggers.
     * @retval false - deep sleep could not be entered.
     * 
     * @see setWakeUpTimer()
     */
    boolean enterDeepSleep(in WakeUpTrigger[] triggersToWakeUpon, out WakeUpTrigger[] wokeUpByTriggers, out @nullable KeyCode keyCode);

    /**
     * Sets the timer period to wake the device from deep sleep.
     *
     * The timer starts when `enterDeepSleep()` is called and `WakeUpTrigger.TIMER` is listed in the `triggersToWakeUpon[]` array.
     * The timer must support at least 7 days.
     *
     * The platform is expected to wake the device within ±/- 5 seconds of the programmed period.
     * The actual wake time could be adjusted for clock drift and resume latency where applicable.
     *
     * @param[in] seconds   The timer period in seconds which must be > 0.
     *
     * @returns boolean
     * @retval true - if the wake up timer period was valid.
     * @retval false - the period was invalid.
     *
     * @pre The WakeUpTrigger.TIMER must be listed in the Capabilities.supportedTriggers array.
     * 
     * @see getWakeUpTimer(), enterDeepSleep()
     */
    boolean setWakeUpTimer(in int seconds);

    /**
     * Gets the timer period set by `setWakeUpTimer()`.
     *
     * If no timer period was previously set, then -1 is returned.
     *
     * @returns int     The period of the wake up timer in seconds.
     *
     * @pre The WakeUpTrigger.TIMER must be listed in the Capabilities.supportedTriggers array.
     * 
     * @see setWakeUpTimer()
     */
    int getWakeUpTimer();
}
