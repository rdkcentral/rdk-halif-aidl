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
 * @file IPanelOutputController.aidl
 * @brief Exclusive controller interface for a panel output instance.
 *
 * Returned by {@link IPanelOutput#open(IPanelOutputControllerListener)}.
 * Provides lifecycle control and all exclusive panel output control APIs.
 * Only one controller may exist per panel output at a time.
 *
 * If the client that opened this controller crashes, stop() and close()
 * are implicitly called by the HAL to release the panel output.
 */
package com.rdk.hal.panel;

import com.rdk.hal.panel.ErrorCode;
import com.rdk.hal.panel.PanelSource;
import com.rdk.hal.panel.PQParameter;
import com.rdk.hal.panel.PQParameterCapabilities;
import com.rdk.hal.panel.PQParameterConfiguration;
import com.rdk.hal.panel.PictureModeConfiguration;
import com.rdk.hal.panel.State;
import com.rdk.hal.videodecoder.DynamicRange;

@VintfStability
interface IPanelOutputController {

    /**
     * @brief Start the panel output controller.
     *
      * This method can only be called in State.STOPPED.
      *
      * This method returns true on success and false on failure.
      * Calling start() twice without a successful stop() between the two calls
      * is invalid and returns false.
      *
     * On success, the state transitions STOPPED -> STARTING -> STARTED.
      * IPanelOutputEventListener.onStateChanged() fires for each
      * transition. If hardware initialization fails, the state transitions
      * to ERROR (observable via onStateChanged()) and this call returns false.
      * Use IPanelOutput.close() to release the panel
     * output from ERROR; close() accepts STOPPED or ERROR.
     *
      * @returns boolean
      * @retval true The panel output was started successfully.
      * @retval false The panel output was not in STOPPED state or hardware initialization failed.
     */
    boolean start();

      /**
       * @brief Gets the current lifecycle state of the panel output.
       *
        * This method can be called in any state.
        *
       * @returns Current State value.
       *
       * @see IPanelOutputEventListener.onStateChanged()
       */
      State getState();
    
    /**
     * @brief Stop the panel output controller.
     *
      * This method can only be called in any state other than State.STOPPED
      * or State.STOPPING.
     * Calling stop() twice without a successful start() between the two calls
      * is invalid and returns false.
     *
     * On success, the state transitions STARTED -> STOPPING -> STOPPED.
    * IPanelOutputEventListener.onStateChanged() fires for each
     * transition.
     *
      * @returns boolean
      * @retval true The panel output was stopped successfully.
      * @retval false The panel output was not in a state where stop() could succeed.
     */
    boolean stop();

  	/**
	 * Sets the panel enabled state.
	 * 
       * This method can only be called in State.STARTED.
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
       * This method can only be called in State.STARTED.
     * 
	 * @returns boolean
	 * @retval true				The panel is enabled.
	 * @retval false			The panel is disabled.
     *
	 * 
	 * @see setEnabled()
	 */ 
 	boolean getEnabled();
	
	/**
     * Sets one or more picture modes for the panel.
     * 
   * This method can only be called in State.STARTED.
   * 
     * Each `PictureModeConfiguration` element in the `configurations` array links together
     * a picture mode, dynamic range and AV source.
     *
     * @param[in] configurations    Array of PictureModeConfiguration values.
     * 
     * @returns boolean
     * @retval true				The picture modes were successfully set.
     * @retval false			One or more picture mode configurations were invalid and could not be set.
     *
     *
     * @see getPictureModes()
     */
	boolean setPictureModes(in PictureModeConfiguration[] configurations);

    /**
     * Gets one or more picture modes of the panel for a given AV source and dynamic range.
     *
      * This method can only be called in State.STARTED.
     *
     * Input `requestedConfigurations` contains one or more entries where the `dynamicRange` and `source`
     * fields specify the query criteria. The `pictureMode` field may be ignored on input.
     *
     * Output `returnedConfigurations` contains one element per input element (same ordering). For each element:
     * - The `dynamicRange` and `source` fields echo the requested values.
     * - The `pictureMode` field is populated on success.
     *
     * Error handling:
     * - Passing an empty `requestedConfigurations` array returns false.
     * - If any entry contains invalid criteria, the call returns false and no output values are populated.
     *
     * @param[in] requestedConfigurations   Non-empty list of query criteria (dynamicRange/source/pictureMode optional).
     * @param[out] returnedConfigurations   Populated picture mode results matching input ordering.
     *
     * @returns boolean
     * @retval true     All picture modes were successfully returned.
     * @retval false    One or more picture mode configurations were invalid and could not be returned or Invalid criteria or empty input list.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     *
     * @see setPictureModes()
     */
    boolean getPictureModes(in PictureModeConfiguration[] requestedConfigurations, out PictureModeConfiguration[] returnedConfigurations);

    /**
     * Gets one or more default picture modes for a given AV source and dynamic range.
     *
      * This method can only be called in State.STARTED.
     *
     * Input `requestedConfigurations` defines the query criteria (dynamicRange/source). `pictureMode` is ignored.
     * Output `defaultConfigurations` echoes criteria and populates the default `pictureMode` value.
     * Failure semantics mirror `getPictureModes()`.
     *
     * @param[in] requestedConfigurations   Non-empty list of query criteria.
     * @param[out] defaultConfigurations     Populated default picture modes.
     *
     * @returns boolean
     * @retval true     All default picture modes were successfully returned.
     * @retval false    One or more picture mode configurations were invalid and could not be returned or Invalid criteria or empty input list.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     *
     * @see setPictureModes(), getPictureModes()
     */
    boolean getDefaultPictureModes(in PictureModeConfiguration[] requestedConfigurations, out PictureModeConfiguration[] defaultConfigurations);
    /**
     * Sets the picture quality parameters.
     *
   * This method can only be called when the panel output state is STARTED.
     * 
     * When calibration mode is enabled (see `enableCalibrationMode()`), the supplied PQ parameter
     * values are persisted but not applied to the PQ pipeline, so that calibration measurements are
   * not disturbed. The panel is kept in a neutral PQ state while calibration is active.
   * The persisted values are applied when calibration mode is subsequently disabled for the
   * active picture-mode, source, dynamic-range, and colour-temperature permutation.
     *
     * @param[in] configurations    Array of PQParameterConfiguration values.
     *
   * @returns ErrorCode
   * @retval ErrorCode.SUCCESS           The PQ parameters were set.
   * @retval ErrorCode.INVALID_ARGUMENT  One or more parameter configurations were invalid.
   * @retval ErrorCode.NOT_SUPPORTED     One or more PQ parameters are unsupported.
   * @retval ErrorCode.HARDWARE_FAILURE  The HAL could not apply the request.
     *
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE The panel output is not in STARTED state.
     * 
     * @see getPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), enableCalibrationMode(), PQParameterConfiguration
     */
  ErrorCode setPQParameters(in PQParameterConfiguration[] configurations);

    /**
     * Gets the current picture quality (PQ) parameter values.
     *
      * This method can only be called in State.STARTED.
     *
     * Input `requestedConfigurations` specifies one or more PQ parameters to query. Each element's:
     * - `pqParameter` must be valid.
     * - `pictureMode`, `source`, and `dynamicRange` may be concrete values or wildcards per their definitions.
    * - `value` field is ignored on input for pure query operations; only the selector fields are used.
     *
     * Output `returnedConfigurations` mirrors ordering and criteria and populates the `value` field.
     *
     * Errors:
     * - Empty input list returns false.
     * - Any invalid `pqParameter` or unsupported criteria returns false with no output populated.
     *
     * @param[in] requestedConfigurations   Non-empty list of PQ parameter query criteria.
     * @param[out] returnedConfigurations   Populated PQ parameter values (value field set).
     *
     * @returns boolean
     * @retval true     All PQ parameter values were successfully returned.
     * @retval false    Invalid criteria or empty input list.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     *
     * @see setPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), PQParameterConfiguration
     */
    boolean getPQParameters(in PQParameterConfiguration[] requestedConfigurations, out PQParameterConfiguration[] returnedConfigurations);

    /**
     * Gets the default picture quality (PQ) parameter values.
     *
      * This method can only be called in State.STARTED.
     *
     * Semantics are identical to `getPQParameters()` except the returned `value` reflects factory/default settings.
     *
     * @param[in] requestedConfigurations   Non-empty list of PQ parameter query criteria.
     * @param[out] defaultConfigurations    Populated default PQ parameter values.
     *
     * @returns boolean
     * @retval true     All default PQ parameters were successfully returned.
     * @retval false    Invalid criteria or empty input list.
     *
     * @exception binder::Status::Exception::EX_NONE             Success.
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
     * @exception binder::Status::Exception::EX_NULL_POINTER     Null out-parameter.
     *
     *
     * @see setPQParameters(), getPQParameters(), getPQParameterCapabilities(), PQParameterConfiguration
     */
    boolean getDefaultPQParameters(in PQParameterConfiguration[] requestedConfigurations, out PQParameterConfiguration[] defaultConfigurations);

	/**
	 * Gets the platform capabilities for a PQ parameter.
	 * 
     * This method can only be called in State.STARTED.
     * 
	 * The returned PQParameterCapabilities confirms whether the parameter is supported by the platform and its minimum and maximum allowed values.
	 * It also contains a list of picture modes, dynamic ranges and AV sources that are supported by the PQ parameter.
	 * 
	 * @param[in] pqParameter	PQParameter
	 * 
	 * @returns PQParameterCapabilities
	 * 
	 * @see getPQParameters(), setPQParameters(), getDefaultPQParameters(), PQParameterCapabilities
	 */
    PQParameterCapabilities getPQParameterCapabilities(in PQParameter pqParameter);

    /**
     * Sets the panel refresh rate.
     * 
      * This method can only be called in State.STARTED.
     * 
     * The `refreshRateHz` value must be listed in Capabilities.supportedRefreshRatesHz[].
     *
     * @param[in] refreshRateHz   The refresh rate in Hz.
     * 
     * @returns boolean
     * @retval true     The refresh rate was set.
     * @retval false    Unsupported refresh rate.
     *
     * 
     * @see getRefreshRate()
     */
    boolean setRefreshRate(in double refreshRateHz);      

    /**
     * Gets the current panel refresh rate.
     *
      * This method can only be called in State.STARTED.
     *
     * @returns double   Refresh rate in Hz.
     *
     * @see setRefreshRate()
     */
	double getRefreshRate();

	/**
	 * Enables or disables frame rate matching (FRM).
     * 
  * This method can only be called in State.STARTED.
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
	 * @returns boolean
     * @retval true     The new frame rate matching state was set.
     * @retval false    The new frame rate matching state was not set.
     *
     * 
	 * @see getFrameRateMatching()
	 */
    boolean setFrameRateMatching(in boolean enabled);

    /**
     * Gets the frame rate matching enabled state.
     *
      * This method can only be called in State.STARTED.
     *
     * @returns boolean
     * @retval true     Frame rate matching is enabled.
     * @retval false    Frame rate matching is disabled.
     *
     * 
     * @see setFrameRateMatching()
     */
    boolean getFrameRateMatching();

    /**
	 * Sets the AV source override used to applying PQ settings.  e.g. AUTO, IP, HDMI, composite, DTV.
	 * 
    * This method can only be called in State.STARTED.
     * 
   * When set to a PanelSource with type AUTO the video source is determined from the video playback subsystem.
	 * Any other value overrides the video source and any other sources being used in the video playback
	 * subsystem are ignored.
     * 
   * Typically a PanelSource with type AUTO is used (and is the default), but override values may be used when 
	 * multi-video display is in operation and the PQ settings corresponding to one of the sources need to be applied.
	 * 
   * @param[in] source	A PanelSource value.
	 * 
   * @see getVideoSourceOverride(), PanelSource
	 */ 
  void setVideoSourceOverride(in PanelSource source);
  	
  	/**
	 * Gets the AV source override used to applying PQ settings.
     * 
     * This method can only be called in State.STARTED.
     * 
	 * This returns the value previously set by a call to setVideoSourceOverride()
   * or the default is a PanelSource with type AUTO.
	 * 
   * @returns PanelSource
	 * 
   * @see setVideoSourceOverride(), PanelSource
	 */ 
  PanelSource getVideoSourceOverride();

    /**
     * Gets the current video source used to apply PQ settings.
     * 
      * This method can only be called in State.STARTED.
     * 
  	 * The returned value has type UNKNOWN if no video is playing.
     *
  	 * @returns PanelSource     The AV source.
     */
      PanelSource getVideoSource();

    /**
     * Gets the current dynamic range used to apply PQ settings.
     * 
      * This method can only be called in State.STARTED.
     * 
     * The returned value is DynamicRange.UNKNOWN if no video is playing.
     *
     * @returns The current dynamic range.
     */
    DynamicRange getDynamicRange();

    /**
     * Gets the current video frame rate used to apply PQ settings.
     * 
      * This method can only be called in State.STARTED.
     * 
     * The returned array is { 0, 0 } if no video is playing.
     *
     * @returns int[2]   Where [0] is the numerator of the frame rate
     *                  and [1] is the denominator of the frame rate.
     */
	int[2] getVideoFrameRate();

    /**
     * Gets the current video resolution used to apply PQ settings.
     *
      * This method can only be called in State.STARTED.
     *
     * The returned array is { 0, 0 } if no video is playing.
     *
     * @returns int[2]   Where [0] is the video width
     *                  and [1] is the video height.
     */
	int[2] getVideoResolution();

	/**
	 * Enables or disables calibration mode for the PQ pipeline.
     * 
  * This method can only be called in State.STARTED.
     * 
     * When enabled, all PQ processing blocks (e.g. brightness, contrast, sharpness, saturation, hue,
     * dimming, noise reduction, CMS, etc.) are set to a neutral or disabled state to allow accurate
     * measurement of the panel output without interference from PQ processing.
     * The white balance (WB) and gamma blocks are also set to a neutral or disabled state.
     * 
     * When disabled, all PQ blocks, the WB block and the gamma block are restored to a state based
     * on the latest PQ parameter values at that stage. This includes any values set by
     * `setPQParameters()` while calibration mode was enabled, which are persisted but not applied
     * until calibration mode is disabled.
     * 
     * Calibration mode is disabled by default.
	 *
	 * @param[in] enabled   The new calibration mode state.
     *                      true to enable calibration mode, false to restore the previous state.
     *                      If the requested state matches the current calibration mode state, the
     *                      call is rejected and returns false. The snapshot is not refreshed.
     * 
	 * @returns boolean
     * @retval true     The calibration mode state was successfully set.
     * @retval false    The calibration mode state could not be set, or it is already in the requested state.
     *
     * 
	 * @see getCalibrationMode(), setPQParameters()
	 */
    boolean enableCalibrationMode(in boolean enabled);

    /**
     * Gets the current calibration mode state.
     *
      * This method can only be called in State.STARTED.
     *
     * @returns boolean
     * @retval true     Calibration mode is enabled.
     * @retval false    Calibration mode is disabled.
     *
     * 
     * @see enableCalibrationMode()
     */
    boolean getCalibrationMode();

}
