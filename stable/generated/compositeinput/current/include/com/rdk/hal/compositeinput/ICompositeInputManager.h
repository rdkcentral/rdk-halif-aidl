#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/ICompositeInputPort.h>
#include <com/rdk/hal/compositeinput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
class ICompositeInputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  static constexpr char* HASHVALUE = "bbad93fa82be1d9624c46072ad235ac4ae274556";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getPortIds(::std::vector<int32_t>* _aidl_return) = 0;
  virtual ::android::binder::Status getPort(int32_t portId, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputManager

class ICompositeInputManagerDefault : public ICompositeInputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPortIds(::std::vector<int32_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPort(int32_t /*portId*/, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputManagerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
