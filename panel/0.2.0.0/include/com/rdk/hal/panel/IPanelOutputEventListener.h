#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/panel/State.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Display Panel Output Event Listener interface.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class IPanelOutputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutputEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  static constexpr char* HASHVALUE = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  // @aidl-doc
  /**
   * Callback when the video source being tracked for PQ settings changes.
   *
   * This occurs when video starts, stops or on a source change to the video.
   * When video stops then a `PanelSource` with type `UNKNOWN` is passed.
   *
   * @param[in] avSource      The new AV source.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoSourceChanged(const ::com::rdk::hal::panel::PanelSource& avSource) = 0;
  // @aidl-doc
  /**
   * Callback when the dynamic range being tracked for PQ settings changes.
   *
   * This occurs when video starts, stops or on a DynamicRange change in the video.
   * When video stops then `DynamicRange.UNKNOWN` is passed in the call.
   *
   * @param[in] dynamicRange      The new dynamic range.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDynamicRangeChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) = 0;
  // @aidl-doc
  /**
   * Callback when the video frame rate being tracked for PQ settings changes.
   *
   * This occurs when video starts, stops or on a frame rate change in the video.
   * When video stops then the frame rate 0/0 is passed in the call.
   *
   * @param[in] frameRateNumerator        The numerator of the frame rate.
   * @param[in] frameRateDenominator      The denominator of the frame rate.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoFrameRateChanged(int32_t frameRateNumerator, int32_t frameRateDenominator) = 0;
  // @aidl-doc
  /**
   * Callback when the video resolution being tracked for PQ settings changes.
   *
   * This occurs when video starts, stops or on a resolution change in the video.
   * When video stops then width and height 0,0 are passed in the call.
   *
   * @param[in] width     The video frame width.
   * @param[in] height    The video frame height.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoResolutionChanged(int32_t width, int32_t height) = 0;
  // @aidl-doc
  /**
   * Callback when the panel refresh rate changes.
   *
   * This occurs when `setRefreshRate()` sets a new refresh rate or if frame rate
   * matching is enabled and it adjusts the refresh rate to best match the video frame rate.
   *
   * @param[in] refreshRateHz     The new panel refresh rate.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onRefreshRateChanged(double refreshRateHz) = 0;
  // @aidl-doc
  /**
   * Callback when the panel output transitions to a new lifecycle state.
   *
   * Fired for all transitions driven by start(), stop(), and error
   * conditions. The panel output State enum covers STOPPED, STARTING,
   * STARTED, STOPPING, and ERROR.
   *
   * @param[in] oldState  The state being left.
   * @param[in] newState  The state being entered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::panel::State oldState, ::com::rdk::hal::panel::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutputEventListener

class IPanelOutputEventListenerDefault : public IPanelOutputEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onVideoSourceChanged(const ::com::rdk::hal::panel::PanelSource& /*avSource*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDynamicRangeChanged(::com::rdk::hal::videodecoder::DynamicRange /*dynamicRange*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoFrameRateChanged(int32_t /*frameRateNumerator*/, int32_t /*frameRateDenominator*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoResolutionChanged(int32_t /*width*/, int32_t /*height*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onRefreshRateChanged(double /*refreshRateHz*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::panel::State /*oldState*/, ::com::rdk::hal::panel::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputEventListenerDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
