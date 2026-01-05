#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmicec/SendMessageStatus.h>
#include <com/rdk/hal/hdmicec/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
class IHdmiCecEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiCecEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "5790bea2dfbdfc34cbbe010cecda4694d0bd432d";
  static constexpr char* HASHVALUE = "5790bea2dfbdfc34cbbe010cecda4694d0bd432d";
  virtual ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& message) = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State oldState, ::com::rdk::hal::hdmicec::State newState) = 0;
  virtual ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus status) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHdmiCecEventListener

class IHdmiCecEventListenerDefault : public IHdmiCecEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State /*oldState*/, ::com::rdk::hal::hdmicec::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& /*message*/, ::com::rdk::hal::hdmicec::SendMessageStatus /*status*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHdmiCecEventListenerDefault
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
