#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/avclock/ClockTime.h>
#include <com/rdk/hal/avclock/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
// @aidl-doc
/**
 *  @brief     Controller callbacks listener interface from AV Clock.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAVClockControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  static constexpr char* HASHVALUE = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  // @aidl-doc
  /**
   * Callback when the AV Clock has transitioned to a new state.
   *
   * @param[in] oldState	            The state transitioned from.
   * @param[in] newState              The new state transitioned to.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::avclock::State oldState, ::com::rdk::hal::avclock::State newState) = 0;
  // @aidl-doc
  /**
   * Callback delivered when the AV Clock transitions from `STARTED`-but-unprimed
   * to primed — the first valid clock value is now available. Fires exactly
   * once per started session, ordered after the configured `ClockMode`'s
   * priming event arrives:
   *
   * - `ClockMode::PCR`          → after the first `notifyPCRSample()` call
   * - `ClockMode::AUDIO_MASTER` → after the first audio frame PTS from the linked audio sink
   * - `ClockMode::VIDEO_MASTER` → after the first video frame PTS from the linked video sink
   * - `ClockMode::AUTO`         → after whichever of the above arrives first
   *
   * Until this callback fires, `IAVClockController.getCurrentClockTime()`
   * returns `null`. After it fires, `getCurrentClockTime()` returns valid
   * times for the remainder of the started session. The unprimed → primed
   * transition is one-way per session; re-priming requires `stop()` + `start()`.
   *
   * @param[in] currentClockTime  The first valid clock value, so clients do
   *                              not need to immediately call `getCurrentClockTime()`
   *                              after the callback.
   *
   * @see IAVClockController.getCurrentClockTime()
   * @see IAVClockController.notifyPCRSample()
   * @see ClockMode
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onPrimed(const ::com::rdk::hal::avclock::ClockTime& currentClockTime) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockControllerListener

class IAVClockControllerListenerDefault : public IAVClockControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::avclock::State /*oldState*/, ::com::rdk::hal::avclock::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onPrimed(const ::com::rdk::hal::avclock::ClockTime& /*currentClockTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockControllerListenerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
