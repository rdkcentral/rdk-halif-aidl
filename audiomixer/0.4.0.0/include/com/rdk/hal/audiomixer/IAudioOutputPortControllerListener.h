#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief    Audio Output Port Controller callback listener.
 * @details  Passed into IAudioOutputPort.open(). Delivers lifecycle state
 *           transitions to the exclusive controller owner. All callbacks are
 *           oneway (non-blocking, fire-and-forget).
 *
 *           Property change events (volume changes, format changes, etc.) are
 *           delivered separately on IAudioOutputPortListener to any registered
 *           observer.
 *
 * @author   Gerald Weatherup
 */
class IAudioOutputPortControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPortControllerListener)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief    Called when the output port transitions to a new lifecycle state.
   *
   *           Fired for all transitions driven by open() and close()
   *           (e.g., CLOSED → OPENING → READY, READY → CLOSING → CLOSED).
   *
   * @param[in] oldState  The state being left.
   * @param[in] newState  The state being entered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPortControllerListener

class IAudioOutputPortControllerListenerDefault : public IAudioOutputPortControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State /*oldState*/, ::com::rdk::hal::audiomixer::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortControllerListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
