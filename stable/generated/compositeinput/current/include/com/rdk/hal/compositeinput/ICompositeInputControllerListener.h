#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/SignalStatus.h>
#include <com/rdk/hal/compositeinput/VideoResolution.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class ICompositeInputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputControllerListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  static constexpr char* HASHVALUE = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  virtual ::android::binder::Status onConnectionChanged(bool connected) = 0;
  virtual ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus signalStatus) = 0;
  virtual ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& resolution) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputControllerListener

class ICompositeInputControllerListenerDefault : public ICompositeInputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onConnectionChanged(bool /*connected*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus /*signalStatus*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& /*resolution*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputControllerListenerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
