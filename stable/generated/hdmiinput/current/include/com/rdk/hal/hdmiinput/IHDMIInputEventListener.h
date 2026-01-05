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
class IHDMIInputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  static constexpr char* HASHVALUE = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::hdmiinput::State oldState, ::com::rdk::hal::hdmiinput::State newState) = 0;
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
