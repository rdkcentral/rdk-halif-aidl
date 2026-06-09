#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/bootreason/BootCause.h>
#include <com/rdk/hal/bootreason/Capabilities.h>
#include <com/rdk/hal/bootreason/PowerSource.h>
#include <com/rdk/hal/bootreason/ResetType.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
class IBootReason : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BootReason)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* _aidl_return) = 0;
  virtual ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause cause, const ::android::String16& reasonString) = 0;
  virtual ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType resetType, const ::android::String16& reasonString) = 0;
  virtual ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBootReason

class IBootReasonDefault : public IBootReason {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause /*cause*/, const ::android::String16& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType /*resetType*/, const ::android::String16& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBootReasonDefault
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
