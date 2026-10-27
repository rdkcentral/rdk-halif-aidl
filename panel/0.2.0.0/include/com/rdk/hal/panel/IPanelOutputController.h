#pragma once
// @aidl-doc
/**
 * @file IPanelOutputController.h
 * @brief Exclusive controller interface for a panel output instance.
 *
 * Returned by {@link IPanelOutput#open(IPanelOutputControllerListener)}.
 * Provides lifecycle control and all exclusive panel output control APIs.
 * Only one controller may exist per panel output at a time.
 *
 * If the client that opened this controller crashes, the HAL releases the
 * controller ownership but retains the current panel state and the latest
 * stored configuration. A later client can reopen the panel and use
 * getState() to discover whether the panel is still STOPPED, STARTING,
 * STARTED, STOPPING, or in ERROR. The enabled/disabled state is retained
 * separately from lifecycle state.
 */

#include <array>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/ErrorCode.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PQParameterCapabilities.h>
#include <com/rdk/hal/panel/PQParameterConfiguration.h>
#include <com/rdk/hal/panel/PQParameterSelector.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/panel/PictureModeConfiguration.h>
#include <com/rdk/hal/panel/State.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class IPanelOutputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutputController)
  static const int32_t VERSION = 2000;
  const std::string HASH = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  static constexpr char* HASHVALUE = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  // @aidl-doc
  /**
   * @brief Start the panel output controller.
   *
   * This method can only be called in State.STOPPED.
   *
   * This method returns true on success and false on failure.
   * Calling start() when the controller is not in STOPPED is invalid and is
   * rejected with EX_ILLEGAL_STATE.
   *
   * On success, the controller transitions STOPPED -> STARTING -> STARTED
   * and the PQ pipeline becomes ready for configuration and video flow. A
   * panel may still be disabled while the controller is STARTED.
   * IPanelOutputEventListener.onStateChanged() fires for each transition.
   * If hardware initialization fails, the state transitions to ERROR
   * (observable via onStateChanged()) and this call returns false. Use
   * IPanelOutput.close() to release the panel output from ERROR; close()
   * accepts STOPPED or ERROR.
   *
   * @param[out] _aidl_return boolean
   *   - true: The panel output was started successfully.
   *   - false: Hardware initialization failed after a valid start request.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STOPPED state.
   */
  virtual ::android::binder::Status start(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the current lifecycle state of the panel output.
   *
   * This method can be called in any state.
   *
   * @param[out] _aidl_return Current State value.
   *
   * @see IPanelOutputEventListener.onStateChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::panel::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Stop the panel output controller.
   *
   * This method can only be called in State.STARTED. On success, it
   * transitions STARTED -> STOPPING -> STOPPED. A runtime or hardware
   * failure returns false and transitions the controller to ERROR.
   * IPanelOutputEventListener.onStateChanged() fires for each transition.
   *
   * This is the explicit lifecycle shutdown path. It is distinct from
   * setEnabled(false), which only suppresses panel output and may keep the
   * controller STARTED for light-sleep or standby operation.
   *
   * @param[out] _aidl_return boolean
   *   - true: The panel output was stopped successfully.
   *   - false: The HAL accepted the request but could not complete the stop because of a runtime or hardware
   *     failure.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   */
  virtual ::android::binder::Status stop(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the panel enabled state.
   *
   * This method can only be called in State.STARTED.
   *
   * When enabled the panel shall display the graphics/video composited display image.
   * When disabled the panel shall suppress visible output while keeping the
   * controller STARTED. On a backlight-driven panel this usually means
   * turning the backlight off. On an OLED panel this may mean using a
   * vendor-specific method to suppress pixel output at the final stage of the
   * video path without disturbing the rest of the video or audio flow.
   *
   * If the panel is already in the target state, then this function has no effect and
   * must not generate any artifacts on the panel display.
   *
   * On boot or resume, the panel may already be enabled or disabled depending
   * on platform power-management policy. Middleware should query getState()
   * first to determine lifecycle state, then call getEnabled() to determine
   * whether setEnabled() is needed.
   *
   * @param[in] enabled The new enable state for the panel.
   *
   * @see getEnabled()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setEnabled(bool enabled) = 0;
  // @aidl-doc
  /**
   * Gets the panel enabled state.
   *
   * This method can only be called in State.STARTED.
   *
   * The enabled state is orthogonal to lifecycle state: the controller may
   * be STARTED while the panel is disabled for light sleep or standby.
   *
   * @param[out] _aidl_return boolean
   *   - true: The panel is enabled.
   *   - false: The panel is disabled.
   * @see setEnabled()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getEnabled(bool* _aidl_return) = 0;
  // @aidl-doc
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
   * @param[out] _aidl_return boolean
   *   - true: The picture modes were successfully set.
   *   - false: The request was valid but one or more picture mode configurations could not be applied.
   * @see getPictureModes()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid or empty configuration list.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   */
  virtual ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& configurations, bool* _aidl_return) = 0;
  // @aidl-doc
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
   * - Passing an empty `requestedConfigurations` array throws EX_ILLEGAL_ARGUMENT.
   * - If any entry contains invalid criteria, the call throws EX_ILLEGAL_ARGUMENT and no output values are populated.
   * - If the criteria are valid but no picture mode can be resolved for one or more entries, the call returns false.
   *
   * @param[in] requestedConfigurations   Non-empty list of query criteria (dynamicRange/source/pictureMode optional).
   * @param[out] returnedConfigurations   Populated picture mode results matching input ordering.
   *
   * @param[out] _aidl_return boolean
   *   - true: All picture modes were successfully returned.
   *   - false: The criteria were valid but no picture mode could be returned for one or more entries.
   * @see setPictureModes()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* returnedConfigurations, bool* _aidl_return) = 0;
  // @aidl-doc
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
   * @param[out] _aidl_return boolean
   *   - true: All default picture modes were successfully returned.
   *   - false: The criteria were valid but no default picture mode could be returned for one or more entries.
   * @see setPictureModes(), getPictureModes()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* defaultConfigurations, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the picture quality parameters.
   *
   * This method can only be called when the panel output state is STARTED.
   *
   * When calibration mode is enabled (see `enableCalibrationMode()`), the HAL captures a
   * snapshot of the latest stored values for the active picture-mode, source,
   * dynamic-range, and colour-temperature permutation before forcing the
   * non-calibration PQ pipeline into a neutral state.
   *
   * While calibration mode remains enabled:
   * - `TWO_POINT_WB`, `MULTI_POINT_WB`, and `DV_CALIBRATION` requests for the active
   *   permutation are applied immediately so a factory or tuning tool can measure the effect
   *   on screen.
   * - Other PQ parameter writes, including `SDR_GAMMA`, are persisted but not applied until
   *   calibration mode is disabled.
   * - All writes remain keyed to their own picture-mode, source, dynamic-range, and
   *   colour-temperature permutation.
   *
   * When calibration mode is disabled, the active permutation exits neutral mode and resumes
   * using the latest stored values for that permutation. This includes the stored 2-point
   * white-balance, multi-point white-balance, and Dolby Vision calibration values associated
   * with the active picture-mode, source, dynamic-range, and colour-temperature permutation.
   * Deferred non-calibration writes also become active at that point. Repeated
   * enable/disable requests with the current calibration state are rejected and do not
   * refresh the snapshot.
   *
   * @param[in] configurations    Array of PQParameterConfiguration values.
   *
   * @param[out] _aidl_return ErrorCode
   *   - ErrorCode.SUCCESS: The PQ parameters were set.
   *   - ErrorCode.INVALID_ARGUMENT: One or more parameter configurations were invalid.
   *   - ErrorCode.NOT_SUPPORTED: One or more PQ parameters are unsupported.
   *   - ErrorCode.HARDWARE_FAILURE: The HAL could not apply the request.
   * @see getPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), enableCalibrationMode(),
   *     PQParameterConfiguration
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The configuration list is empty or contains invalid
   * selectors or value variants.
   */
  virtual ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& configurations, ::com::rdk::hal::panel::ErrorCode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current picture quality (PQ) parameter values.
   *
   * This method can only be called in State.STARTED.
   *
   * Input `requestedConfigurations` specifies one or more PQ parameter selectors to query. Each element's:
   * - `pqParameter` must be valid.
   * - `pictureMode` and `source` must be concrete values.
   * - `dynamicRange` must be a valid selector value for the requested parameter.
   *
   * The selector identifies the PQ parameter and its runtime context only.
   * The selector does not expand across picture modes or AV sources.
   * White-balance parameters are returned as aggregate bundles for the
   * resolved context; no additional white-balance selector keys are required
   * or defined on `PQParameterSelector`.
   * For aggregate PQ parameters, the returned `value` payload contains the
   * entire parameter set for the resolved selector context:
   * - `COLOUR_MANAGEMENT_SETTINGS` returns one grouped CMS payload.
   * - `TWO_POINT_WB` returns one array containing all 2-point WB entries for the resolved context.
   * - `MULTI_POINT_WB` returns one array containing all multi-point WB entries for the resolved context.
   * - `DV_CALIBRATION` returns one Dolby Vision calibration payload.
   *
   * Output `returnedConfigurations` mirrors ordering and criteria and populates the `value` field.
   * Clients shall interpret each returned entry together with the selector context that produced it.
   *
   * Errors:
   * - Empty input list throws EX_ILLEGAL_ARGUMENT.
   * - Any invalid `pqParameter` or malformed selector throws EX_ILLEGAL_ARGUMENT with no output populated.
   * - If every selector is valid but one or more entries cannot be resolved for the requested
   *   criteria, the call returns false.
   *
   * @param[in] requestedConfigurations   Non-empty list of PQ parameter query selectors.
   * @param[out] returnedConfigurations   Populated PQ parameter values (value field set).
   *
   * @param[out] _aidl_return boolean
   *   - true: All PQ parameter values were successfully returned.
   *   - false: The selectors were valid but one or more values could not be returned.
   * @see setPQParameters(), getDefaultPQParameters(), getPQParameterCapabilities(), PQParameterSelector,
   *     PQParameterConfiguration
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* returnedConfigurations, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the default picture quality (PQ) parameter values.
   *
   * This method can only be called in State.STARTED.
   *
   * Semantics are identical to `getPQParameters()` except the returned `value` reflects factory/default settings.
   * As with `getPQParameters()`, the input selector provides the PQ
   * parameter and runtime context, while aggregate parameters return their
   * full stored payload in the `value` union variant.
   * White-balance defaults are returned as the full 2-point or multi-point
   * bundle for the resolved context.
   *
   * @param[in] requestedConfigurations   Non-empty list of PQ parameter query selectors.
   * @param[out] defaultConfigurations    Populated default PQ parameter values.
   *
   * @param[out] _aidl_return boolean
   *   - true: All default PQ parameters were successfully returned.
   *   - false: The selectors were valid but one or more default values could not be returned.
   * @see setPQParameters(), getPQParameters(), getPQParameterCapabilities(), PQParameterSelector,
   *     PQParameterConfiguration
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid criteria or empty input list.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& requestedConfigurations, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* defaultConfigurations, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the platform capabilities for a PQ parameter.
   *
   * This method can only be called in State.STARTED.
   *
   * The returned PQParameterCapabilities confirms whether the parameter is supported by the platform and its minimum
   * and maximum allowed values. It also contains a list of picture modes, dynamic ranges and AV sources that are
   * supported by the PQ parameter.
   *
   * @param[in] pqParameter PQParameter
   *
   * @param[out] _aidl_return PQParameterCapabilities
   *
   * @see getPQParameters(), setPQParameters(), getDefaultPQParameters(), PQParameterCapabilities
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter pqParameter, ::com::rdk::hal::panel::PQParameterCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the panel refresh rate.
   *
   * This method can only be called in State.STARTED.
   *
   * The `refreshRateHz` value must be listed in Capabilities.supportedRefreshRatesHz[].
   *
   * @param[in] refreshRateHz   The refresh rate in Hz.
   * @param[out] _aidl_return boolean
   *   - true: The refresh rate was set.
   *   - false: Unsupported refresh rate.
   * @see getRefreshRate()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setRefreshRate(double refreshRateHz, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current panel refresh rate.
   *
   * This method can only be called in State.STARTED.
   *
   * @param[out] _aidl_return double   Refresh rate in Hz.
   *
   * @see setRefreshRate()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getRefreshRate(double* _aidl_return) = 0;
  // @aidl-doc
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
   * @param[out] _aidl_return boolean
   *   - true: The new frame rate matching state was set.
   *   - false: The new frame rate matching state was not set.
   * @see getFrameRateMatching()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setFrameRateMatching(bool enabled, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the frame rate matching enabled state.
   *
   * This method can only be called in State.STARTED.
   *
   * @param[out] _aidl_return boolean
   *   - true: Frame rate matching is enabled.
   *   - false: Frame rate matching is disabled.
   * @see setFrameRateMatching()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getFrameRateMatching(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the AV source override used to apply PQ settings, for example AUTO, IP, HDMI, composite, or DTV.
   *
   * This method can only be called in State.STARTED.
   *
   * When set to a PanelSource with type AUTO the video source is determined by the video playback subsystem.
   * Any other value overrides the video source and any other sources being used in the video playback
   * subsystem are ignored.
   *
   * Typically a PanelSource with type AUTO is used (and is the default), but override values may be used when
   * multi-video display is in operation and the PQ settings corresponding to one of the sources need to be applied.
   *
   * @param[in] source A PanelSource value.
   *
   * @see getVideoSourceOverride(), PanelSource
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setVideoSourceOverride(const ::com::rdk::hal::panel::PanelSource& source) = 0;
  // @aidl-doc
  /**
   * Gets the AV source override used to apply PQ settings.
   *
   * This method can only be called in State.STARTED.
   *
   * This returns the value previously set by a call to setVideoSourceOverride()
   * or the default is a PanelSource with type AUTO.
   *
   * @param[out] _aidl_return PanelSource
   *
   * @see setVideoSourceOverride(), PanelSource
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::panel::PanelSource* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current video source used to apply PQ settings.
   *
   * This method can only be called in State.STARTED.
   *
   * The returned value has type UNKNOWN if no video is playing.
   *
   * @param[out] _aidl_return PanelSource     The AV source.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getVideoSource(::com::rdk::hal::panel::PanelSource* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current dynamic range used to apply PQ settings.
   *
   * This method can only be called in State.STARTED.
   *
   * The returned value is DynamicRange.UNKNOWN if no video is playing.
   *
   * @param[out] _aidl_return The current dynamic range.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getDynamicRange(::com::rdk::hal::videodecoder::DynamicRange* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current video frame rate used to apply PQ settings.
   *
   * This method can only be called in State.STARTED.
   *
   * The returned array is { 0, 0 } if no video is playing.
   *
   * @param[out] _aidl_return int[2]   Where [0] is the numerator of the frame rate
   *                                  and [1] is the denominator of the frame rate.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current video resolution used to apply PQ settings.
   *
   * This method can only be called in State.STARTED.
   *
   * The returned array is { 0, 0 } if no video is playing.
   *
   * @param[out] _aidl_return int[2]   Where [0] is the video width
   *                                  and [1] is the video height.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Enables or disables calibration mode for the PQ pipeline.
   *
   * This method can only be called in State.STARTED.
   *
   * When enabled, all PQ processing blocks (e.g. brightness, contrast, sharpness, saturation, hue,
   * dimming, noise reduction, CMS, etc.) are set to a neutral or disabled state to allow accurate
   * measurement of the panel output without interference from PQ processing.
   * The white balance (WB) and gamma blocks are also set to a neutral or disabled state.
   * This does not make `SDR_GAMMA` a live calibration write; `SDR_GAMMA` remains deferred until
   * calibration mode is disabled, like other non-calibration PQ properties.
   *
   * When disabled, the active permutation exits neutral mode and resumes using the latest stored
   * values for that permutation. This includes the stored 2-point white-balance,
   * multi-point white-balance, and Dolby Vision calibration values associated with the active
   * picture-mode, source, dynamic-range, and colour-temperature permutation. Deferred
   * non-calibration writes also become active at that point.
   *
   * Calibration mode is disabled by default.
   *
   * Enabling calibration captures a snapshot for the active picture-mode, source, dynamic-range,
   * and colour-temperature permutation. Repeated calls with the current state are rejected and do
   * not refresh that snapshot.
   *
   * @param[in] enabled   The new calibration mode state.
   *                      true to enable calibration mode, false to leave neutral mode and use the
   *                      latest stored values for the active permutation.
   *                      If the requested state matches the current calibration mode state, the
   *                      call is rejected and returns false. The snapshot is not refreshed.
   *
   * @param[out] _aidl_return boolean
   *   - true: The calibration mode state was successfully set.
   *   - false: The calibration mode state could not be set, or it is already in the requested state.
   * @see getCalibrationMode(), setPQParameters()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The panel output is not in STARTED state.
   */
  virtual ::android::binder::Status enableCalibrationMode(bool enabled, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current calibration mode state.
   *
   * This method can only be called in State.STARTED.
   *
   * @param[out] _aidl_return boolean
   *   - true: Calibration mode is enabled.
   *   - false: Calibration mode is disabled.
   * @see enableCalibrationMode()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCalibrationMode(bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutputController

class IPanelOutputControllerDefault : public IPanelOutputController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::panel::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*configurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* /*returnedConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDefaultPictureModes(const ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PictureModeConfiguration>* /*defaultConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>& /*configurations*/, ::com::rdk::hal::panel::ErrorCode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* /*returnedConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDefaultPQParameters(const ::std::vector<::com::rdk::hal::panel::PQParameterSelector>& /*requestedConfigurations*/, ::std::vector<::com::rdk::hal::panel::PQParameterConfiguration>* /*defaultConfigurations*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPQParameterCapabilities(::com::rdk::hal::panel::PQParameter /*pqParameter*/, ::com::rdk::hal::panel::PQParameterCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setRefreshRate(double /*refreshRateHz*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getRefreshRate(double* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFrameRateMatching(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrameRateMatching(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoSourceOverride(const ::com::rdk::hal::panel::PanelSource& /*source*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSourceOverride(::com::rdk::hal::panel::PanelSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSource(::com::rdk::hal::panel::PanelSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDynamicRange(::com::rdk::hal::videodecoder::DynamicRange* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoFrameRate(std::array<int32_t, 2>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoResolution(std::array<int32_t, 2>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status enableCalibrationMode(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCalibrationMode(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputControllerDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
