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
import com.rdk.hal.panel.Capabilities;
import com.rdk.hal.panel.IFactoryPanel;
import com.rdk.hal.panel.PictureModeConfiguration;
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PQParameterConfiguration;
import com.rdk.hal.panel.PQParameterCapabilities;
import com.rdk.hal.panel.WhiteBalance2PointSettings;
import com.rdk.hal.panel.WhiteBalanceMultiPointSettings;
import com.rdk.hal.videodecoder.DynamicRange;
import com.rdk.hal.AVSource;

/** 
 *  @brief     Display Panel Output Control HAL interface.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */

@VintfStability
interface IPanelOutput
{
	/** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "PanelOutput";

    /**
     * Gets the capabilities of the panel service.
     * 
     * This function can be called at any time and the returned value is not allowed to change between calls.
     *
     * @return Capabilities parcelable.
     */
    Capabilities getCapabilities();

    /**
     * Gets the factory interface for the panel.
     *
     * @return IFactoryPanel or null on error.
     */
    @nullable IFactoryPanel getFactoryInterface();

  	/**
	 * Sets the panel enabled state.
	 * 
	 * When enabled the panel shall display the graphics/video composited display image.
	 * When disabled the panel shall be off where it will not show any image and will disable any backlight.
     * 
	 * If the panel if already in the target state, then this function has no effect and
	 * must not generate any artifacts on the panel display.
     * 
     * On boot, the panel may be left in an enabled or disabled state by the bootloader.
     * 
	 * @param[in] enabled	The new enable state for the panel.
	 *
	 * @see getEnabled()
	 */
    void setEnabled(in boolean enabled);

  	/**
	 * Gets the panel enabled state.
	 * 
	 * @return boolean
	 * @retval true				The panel is enabled.
	 * @retval false			The panel is disabled.
	 * 
	 * @see setEnabled()
	 */ 
 	boolean getEnabled();
	
	/**
     * Sets one or more picture modes for the panel.
     * 
     * Each `PictureModeConfiguration` element in the `configurations` array links together
     * a picture mode, dynamic range video format and AV source.
     *
     * @param[in] configurations    Array of PictureModeConfiguration values.
     * 
     * @return boolean
     * @retval true				The picture modes were successfully set.
     * @retval false			One or more picture mode configurations were invalid and could not be set.
     *
     * @see getPictureModes()
     */
	boolean setPictureModes(in PictureModeConfiguration[] configurations);

    /**
     * Gets one or more picture modes of the panel for a given AV source and dynamic range video format.
     * 
     * @param[in,out] configurations  Array of PictureModeConfiguration, filled with `pictureMode` values if successful.
     * 
     * @return boolean
     * @retval true				The picture modes were successfully return.
     * @retval false			One or more picture mode configurations were invalid and could not be returned.
     *
     * @see setPictureModes()
     */
    boolean getPictureModes(inout PictureModeConfiguration[] configurations);

    /**
     * Gets one or more picture mode defaults for a given AV source and dynamic range video format.
     *
     * @param[in,out] configurations  Array of PictureModeConfiguration, filled with `pictureMode` values if successful.
     *
     * @return boolean
     * @retval true				The picture modes were successfully return.
     * @retval false			One or more picture mode configurations were invalid and could not be returned.
     *
     * @see setPictureModes()
     */
    boolean getDefaultPictureModes(inout PictureModeConfiguration[] configurations);

    /**
     * Sets the picture quality parameters.
     *
     * @param[in] configurations    Array of PQParameterConfiguration values.
     *
     * @return boolean
     * @retval true     The PQ parameters were set.
     * @retval false    One or more invalid parameter configurations.
     * 
     * @see getPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), PQParameterConfiguration
     */
    boolean setPQParameters(in PQParameterConfiguration[] configurations);

    /**
     * Gets the current picture quality parameters.
     *
     * @param[inout] configurations     Array of PQParameterConfiguration values.
     *
     * @return boolean
     * @retval true     The PQ parameters were returned.
     * @retval false    One or more invalid parameter configuration requested.
     *
     * @see setPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), PQParameterConfiguration
     */
    boolean getPQParameters(inout PQParameterConfiguration[] configurations);

    /**
     * Gets the default picture quality parameters.
     *
     * @param[inout] configurations     Array of PQParameterConfiguration values.
     * 
     * @return boolean
     * @retval true     The default PQ parameter values were returned.
     * @retval false    One or more invalid parameter configuration requested.
     *
     * @see setPQParameters(), getPQParameters(), getPQParameterCapabilities(), PQParameterConfiguration
     */
    boolean getDefaultPQParameters(inout PQParameterConfiguration[] configurations);

	/**
	 * Gets the platform capabilities for a PQ parameter.
	 * 
	 * The returned PQCapabilities confirms whether the parameter is supported by the platform and its minimum and maximum allowed values.
	 * It also contains a list of picture modes, video formats and AV sources that are supported by the PQ parameter.
	 * 
	 * @param[in] pqParameter	PQParameter
	 * 
	 * @return PQCapabilities
	 * 
	 * @see getPQParameters(), setPQParameters(), getDefaultPQParameters(), PQCapabilities
	 */
    PQParameterCapabilities getPQParameterCapabilities(in PQParameter pqParameter);

    /**
     * Sets the panel refresh rate.
     * 
     * The `refreshRateHz` value must be listed in Capabilities.supportedRefreshRatesHz[].
     *
     * @param[in] refreshRateHz   The refresh rate in Hz.
     * 
     * @return boolean
     * @retval true     The refresh rate was set.
     * @retval false    Unsupported refresh rate.
     * 
     * @see getRefreshRate()
     */
    boolean setRefreshRate(in double refreshRateHz);      

    /**
     * Gets the current panel refresh rate.
     *
     * @return double   Refresh rate in Hz.
     *
     * @see setRefreshRate()
     */
	double getRefreshRate();

	/**
	 * Enables or disables frame rate matching (FRM).
     * 
     * When enabled, the panel refresh rate is synchronized with the video frame rate.
     * The refresh rate may be a multiple of the video frame rate or a close match.
     * 
     * If no video is playing then the default refresh rate is followed.
     * 
     * Frame rate matching is enabled by default if supported.
     * The `Capabilities.frameRateMatchingSupported` value is true if FRM is supported.
	 *
	 * @param[in] enabled   The new frame rate matching state.
     * 
	 * @return boolean
     * @retval true     The new frame rate matching state was set.
     * @retval false    The new frame rate matching state was not set.
     * 
     * @see getFrameRateMatching()
	 */
    boolean setFrameRateMatching(in boolean enabled);

    /**
     * Gets the frame rate matching enabled state.
     *
     * @return boolean
     * @retval true     Frame rate matching is enabled.
     * @retval false    Frame rate matching is disabled.
     * 
     * @see setFrameRateMatching()
     */
    boolean getFrameRateMatching();

    /**
	 * Sets the AV source override used to applying PQ settings.  e.g. AUTO, IP, HDMI, composite, DTV.
	 * 
	 * When set to AVSource.AUTO the video source is determined from the video playback subsystem.
	 * Any other value overrides the video source and any other sources being used in the video playback
	 * subsystem are ignored.
     * 
	 * Typically AVSource.AUTO is used (and is the default), but override values may be used when 
	 * multi-video display is in operation and the PQ settings corresponding to one of the sources need to be applied.
	 * 
	 * @param[in] source	An AVSource enum value.
	 * 
	 * @see getVideoSourceOverride(), AVSource
	 */ 
  	void setVideoSourceOverride(in AVSource source);
  	
  	/**
	 * Gets the AV source override used to applying PQ settings.
     * 
	 * This returns the value previously set by a call to setVideoSourceOverride()
	 * or the default is AUTO.
	 * 
	 * @return AVSource
	 * 
	 * @see setVideoSourceOverride(), AVSource
	 */ 
	AVSource getVideoSourceOverride();

    /**
     * Gets the current video source used to apply PQ settings.
     * 
     * The returned value is AVSource.UNKNOWN if no video is playing.
     *
     * @return AVSource     The AV source.
     */
    AVSource getVideoSource();

    /**
     * Gets the current dynamic range video format used to apply PQ settings.
     * 
     * The returned value is DynamicRange.UNKNOWN if no video is playing.
     *
     * @return DynamicRange     The current video format.
     */
    DynamicRange getVideoFormat();

    /**
     * Gets the current video frame rate used to apply PQ settings.
     * 
     * The returned array is { 0, 0 } if no video is playing.
     *
     * @return int[2]   Where [0] is the numerator of the frame rate
     *                  and [1] is the denominator of the frame rate.
     */
	int[2] getVideoFrameRate();

    /**
     * Gets the current video resolution used to apply PQ settings.
     *
     * The returned array is { 0, 0 } if no video is playing.
     *
     * @return int[2]   Where [0] is the video width
     *                  and [1] is the video height.
     */
	int[2] getVideoResolution();

    /**
     * Sets the 2-point white balance settings for a given color temperature.
     *
     * @param[in] colorTemperature  The color temperature to set.
     * @param[in] whiteBalance      The white balance settings.
     * 
     * @return boolean
     * @retval true     The 2-point white balance was set for the color temperature.
     * @retval false    One or more parameters are invalid.
     */
    boolean set2PointWhiteBalance(in int colorTemperature, in WhiteBalance2PointSettings whiteBalance);

    /**
     * Gets the 2-point white balance settings for a given color temperature.
     *
     * @param[in] colorTemperature  The color temperature to set.
     * 
     * @return WhiteBalance2PointSettings
     */
    WhiteBalance2PointSettings get2PointWhiteBalance(in int colorTemperature);

    /**
     * Sets the multi-point white balance settings for a given color temperature.
     *
     * @param[in] colorTemperature  The color temperature to set.
     * @param[in] whiteBalance      The white balance settings.
     *
     * @return boolean
     * @retval true     The multi-point white balance was set for the color temperature.
     * @retval false    One or more parameters are invalid.
     */
    boolean setMultiPointWhiteBalance(in int colorTemperature, in WhiteBalanceMultiPointSettings whiteBalance);

    /**
     * Gets the multi-point white balance settings for a given color temperature.
     *
     * @param[in] colorTemperature  The color temperature to set.
     *
     * @return WhiteBalanceMultiPointSettings
     */
    WhiteBalanceMultiPointSettings getMultiPointWhiteBalance(in int colorTemperature);

	/**
	 * Starts a display fade up or down operation.
     * 
	 * Fades the display linearly between two different luminance levels over a given duration.
	 * The function call returns immediately after starting the fade which runs asynchronously.
     * 
     * Luminance control depends on the display panel technology and may pertain to LED backlight or
     * overal pixel intensity.
     * 
     * The start and end luminance values are expressed as percentages of the normal luminance level
     * set by a combination of the picture mode, user setting or ambient light sensor algorithm if active.
     * 
     * A new call to `fadeDisplay()` can be made before the last fade has completed where it will
     * stop the operation and leave the luminance at its interrupted level before starting the
     * new fade operation.
     * 
     * `fadeDisplay(-1, 0, 500)` will fade the display from its current luminance level to black over 500ms.
     * `fadeDisplay(0, 100, 2000)` will fade the display from black to 100% of the normal luminance level over 2 seconds.
     * `fadeDisplay(-1, 100, 0)` will immediately jump to 100% of the normal luminance level.
	 *
	 * @param[in] start         Percentage of the current luminance value from where the fade starts.
     *                          A `start` value in the range 0-100% will first set the luminance fade to that level before the fade starts.
     *                          A `start` value of -1 is used to start at the current luminance fade level.
	 * @param[in] end           Percentage of current luminance value when fade ends. Valid range is 0-100%.
	 * @param[in] durationMs    Time duration for the fade to reach the end value. Valid range is 0-10000 ms.
     *                          When a `durationMs` of 0 is specified, the end fade luminance value is immediately set.
     * 
     * @return boolean
     * @retval true     The fade operation was started.
     * @retval false    The fade operation was not started because one or more parameters are invalid.
	 */ 
	boolean fadeDisplay(in int start, in int end, in int durationMs);

}
