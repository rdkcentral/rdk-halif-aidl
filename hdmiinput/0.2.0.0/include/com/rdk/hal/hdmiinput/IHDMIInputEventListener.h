#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     Event callbacks listener interface from HDMI input.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IHDMIInputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "c5b7dd577bd1ea4008ddd8019c1923942a4924a7";
  static constexpr char* HASHVALUE = "c5b7dd577bd1ea4008ddd8019c1923942a4924a7";
  // @aidl-doc
  /**
   * Callback when the HDMI input has transitioned to a new state.
   *
   * @param[in] oldState      The state that the port has transitioned from.
   * @param[in] newState      The new state that the port has transitioned to.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::hdmiinput::State oldState, ::com::rdk::hal::hdmiinput::State newState) = 0;
  // @aidl-doc
  /**
   * EDID change notification.
   *
   * Fires when the EDID for the HDMI input port is changed via setEDID().
   *
   * @param[in] edid  The new EDID data as a byte array.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEDIDChange(const ::std::vector<uint8_t>& edid) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputEventListener

class IHDMIInputEventListenerDefault : public IHDMIInputEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmiinput::State /*oldState*/, ::com::rdk::hal::hdmiinput::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEDIDChange(const ::std::vector<uint8_t>& /*edid*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputEventListenerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
