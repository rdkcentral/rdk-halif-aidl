#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
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
 *  @brief     Event callbacks listener interface from AV Clock.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAVClockEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockEventListener)
  static const int32_t VERSION = 2010;
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
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockEventListener

class IAVClockEventListenerDefault : public IAVClockEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::avclock::State /*oldState*/, ::com::rdk::hal::avclock::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockEventListenerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
