#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/boot/BootReason.h>
#include <com/rdk/hal/boot/Capabilities.h>
#include <com/rdk/hal/boot/PowerSource.h>
#include <com/rdk/hal/boot/ResetType.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace boot {
class IBoot : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Boot)
  static const int32_t VERSION = 1;
  const std::string HASH = "80e31b1e4037b6988846f183be9c68c2f7427a3f";
  static constexpr char* HASHVALUE = "80e31b1e4037b6988846f183be9c68c2f7427a3f";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::boot::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getBootReason(::com::rdk::hal::boot::BootReason* _aidl_return) = 0;
  virtual ::android::binder::Status setBootReason(::com::rdk::hal::boot::BootReason reason, const ::android::String16& reasonString) = 0;
  virtual ::android::binder::Status reboot(::com::rdk::hal::boot::ResetType resetType, const ::android::String16& reasonString) = 0;
  virtual ::android::binder::Status getPowerSource(::com::rdk::hal::boot::PowerSource* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBoot

class IBootDefault : public IBoot {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::boot::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getBootReason(::com::rdk::hal::boot::BootReason* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setBootReason(::com::rdk::hal::boot::BootReason /*reason*/, const ::android::String16& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status reboot(::com::rdk::hal::boot::ResetType /*resetType*/, const ::android::String16& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPowerSource(::com::rdk::hal::boot::PowerSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBootDefault
}  // namespace boot
}  // namespace hal
}  // namespace rdk
}  // namespace com
