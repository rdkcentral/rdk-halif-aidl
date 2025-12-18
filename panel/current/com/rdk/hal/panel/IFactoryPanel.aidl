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
package com.rdk.hal.panel;
import com.rdk.hal.panel.PanelType;
import com.rdk.hal.panel.WhiteBalance2PointSettings;

/** 
 *  @brief      Display Panel Factory interface.
 *              The functionality covers writing configuration settings to factory persistent storage
 *              and to execute test modes needed by the Factory Test Application.
 *  @authors    Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IFactoryPanel
{
    /**
     * Enum to describe how to save factory settings.
     */
    enum SaveTo
    {
        /** Saves the settings to update the display values only. */
        DISPLAY = 1,

        /** Saves the settings to update the flash values only. */
        FLASH = 2,

        /** Saves the settings to update the display and flash values. */
        DISPLAY_AND_FLASH = DISPLAY | FLASH
    }

    /**
     * Sets the panel ID in the factory area persistent storage.
     * 
     * @param[in] panelId       The unique panel identifier.
     * 
     * @return boolean
     * @retval true     The configuration data was successfully written.
     * @retval false    Write error or invalid parameter.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     */
    boolean setFactoryPanelConfiguration(in int panelId); 

    /**
     * Gets the panel ID from the factory area persistent storage.
     * 
     * @return int      The panelId
     */
    int getFactoryPanelConfiguration(); 

    /**
     * Sets the white balance calibration for a color temperature preset in the factory area persistent storage.
     * 
     * @param[in] colorTemperature  Color temperature index.
     * @param[in] whiteBalance      2-point white balance settings.
     * @param[in] saveTo            Where to save the factory settings to.
     *
     * @return boolean
     * @retval true     The calibration data was successfully written.
     * @retval false    Write error or invalid parameter.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     * 
     * @see getFactoryWhiteBalanceCalibration()
     */
    boolean setFactoryWhiteBalanceCalibration(in int colorTemperature, in WhiteBalance2PointSettings whiteBalance, in SaveTo saveTo);

    /**
     * Gets the 2-point white balance calibration for a color temperature from the display saved settings.
     *
     * @param[in] colorTemperature      Index of the color temperature preset.
     *
     * @return WhiteBalance2PointSettings
     * 
     * @see setFactoryWhiteBalanceCalibration()
     */
    WhiteBalance2PointSettings getFactoryWhiteBalanceCalibration(in int colorTemperature);

    /**
     * Sets the RGB gamma table for a color temperature preset in the factory area persistent storage.
     *
     * TODO: define what the valid range is - or provide an API for it.
     *
     * @param[in] colorTemperature  Color temperature index.
     * @param[in] red               Array of red gamma values.
     * @param[in] green             Array of green gamma values.
     * @param[in] blue              Array of blue gamma values.
     * @param[in] saveTo            Where to save the factory settings to.
     *
     * @return boolean
     * @retval true     The calibration data was successfully written.
     * @retval false    Write error or invalid parameter.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     *
     * @see getFactoryGammaTable()
     */
    boolean setFactoryGammaTable(in int colorTemperature, in int[] red, in int[] green, in int[] blue, in SaveTo saveTo);

    /**
     * Gets the RGB gamma table for a color temperature preset from display saved settings.
     *
     * @param[in] colorTemperature  Color temperature index.
     * @param[out] red              Array which receives the red gamma values.
     * @param[out] green            Array which receives the green gamma values.
     * @param[out] blue             Array which receives the blue gamma values.
     *
     * @return boolean
     * @retval true     The calibration data was successfully written.
     * @retval false    Write error or invalid parameter.
     *
     * @see setFactoryGammaTable()
     */
    void getFactoryGammaTable(in int colorTemperature, out int[] red, out int[] green, out int[] blue);

    /**
     * Sets the peak brightness.
     *
     * @param[in] dimmingLevel      Dimming level.  Same value used in `PQParameter.DIMMING_LEVEL`.
     * @param[in] nits              The peak brightness level in nits.
     *
     * @return boolean
     * @retval true     The peak brightness data was successfully written.
     * @retval false        Write error or invalid parameter.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     *
     * @see getFactoryPeakBrightness()
     */
    boolean setFactoryPeakBrightness(in int dimmingLevel, in int nits);

    /**
     * Gets the peak brightness.
     *
     * @param[in] dimmingLevel      Dimming level.  Same value used in `PQParameter.DIMMING_LEVEL`.
     *
     * @return int      The peak brightness level in nits.
     *
     * @see setFactoryPeakBrightness()
     */
    int getFactoryPeakBrightness(in int dimmingLevel);

    /**
     * Defines a local dimming zone coordinate and illumination level.
     */
    parcelable LocalDimmingZone
    {
        /**
         * X coordinate of the zone.
         * Must be 0 <= x < PQParameter.LOCAL_DIMMING_ZONES_X.
         */
        int x;

        /**
         * Y coordinate of the zone.
         * Must be 0 <= y < PQParameter.LOCAL_DIMMING_ZONES_Y.
         */
        int y;

        /**
         * Illumination level of the zone.
         * Normalised to 0..32767, where 0 is off and 32767 is full brightness.
         */
        int level;
    }

    /**
     * Illuminates an array of local dimming zones for a given time.
     * 
     * After the time expires then normal local dimming operation is resumed.
     * A new call to `setFactoryLocalDimming()` before the duration has expired will replace the existing pattern
     * with the new pattern and restart the duration timer.
     *
     * @param[in] zones         Each element is the coordinate and illumination level for a zone. 
     *                          Any zones not listed shall be set off.
     * @param[in] durationMs    The duration to hold the illumination pattern in milliseconds.
     * 
     * @return boolean
     * @retval true     The illumination pattern was presented and the duration timer started.
     * @retval false    Invalid parameter(s) or hardware fault.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     */
    boolean setFactoryLocalDimming(in LocalDimmingZone[] zones, in int durationMs);

    /**
     * Runs a local dimming test mode for a given time.
     *
     * After the time expires then normal local dimming operation is resumed.
     * A new call to `setFactoryLocalDimmingTestMode()` before the duration has expired will replace the existing
     * test mode with the new one and restart the duration timer.
     *
     * @param[in] mode          The test mode.
     * @param[in] durationMs    The duration to hold the illumination pattern in milliseconds.
     *
     * @return boolean
     * @retval true     The test mode was run and the duration timer started.
     * @retval false    Invalid parameter(s) or hardware fault.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     */
    boolean setFactoryLocalDimmingTestMode(in int mode, in int durationMs);

    /**
     * Enables or disables the local dimming pixel compensation.
     *
     * @param[in] enabled   The enabled state.
     *
     * @return boolean
     * @retval true     The setting was successfully changed.
     * @retval false    Driver or hardware error.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     * 
     * @see getFactoryLocalDimmingPixelCompensation()
     */
    boolean setFactoryLocalDimmingPixelCompensation(in boolean enabled);

    /**
     * Gets the state of the local dimming pixel compensation.
     *
     * @return boolean
     * @retval true     Local dimming pixel compensation is enabled.
     * @retval false    Local dimming pixel compensation is disabled.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IFactoryPanel}} for exception handling behavior).
     * 
     * @see setFactoryLocalDimmingPixelCompensation()
     */
    boolean getFactoryLocalDimmingPixelCompensation();
 
    /** 
     * Gets the backlight health status.
     * 
     * TODO: How is this used - needs description.  What is the return value indicating???
     * 
     * @return int   The status value is 0 for OK or >=1 for an LED fault.
     */
    int getFactoryBacklightHealth();
}
