#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/deviceinfo/Capabilities.h>
#include <com/rdk/hal/deviceinfo/Property.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
class IDeviceInfo : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeviceInfo)
  static const int32_t VERSION = 1;
  const std::string HASH = "84c73c5985435fb8c64996af32180b6f44241115";
  static constexpr char* HASHVALUE = "84c73c5985435fb8c64996af32180b6f44241115";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(const ::android::String16& propertyKey, ::std::optional<::com::rdk::hal::deviceinfo::Property>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDeviceInfo

class IDeviceInfoDefault : public IDeviceInfo {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(const ::android::String16& /*propertyKey*/, ::std::optional<::com::rdk::hal::deviceinfo::Property>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDeviceInfoDefault
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
