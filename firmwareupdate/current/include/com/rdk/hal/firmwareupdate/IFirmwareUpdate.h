#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/firmwareupdate/IFirmwareUpdateListener.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
class IFirmwareUpdate : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FirmwareUpdate)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status updateFirmwareFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& listener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFirmwareUpdate

class IFirmwareUpdateDefault : public IFirmwareUpdate {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status updateFirmwareFromFile(const ::std::string& /*filename*/, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFirmwareUpdateDefault
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
