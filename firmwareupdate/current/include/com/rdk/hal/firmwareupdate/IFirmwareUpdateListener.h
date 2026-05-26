#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/firmwareupdate/FirmwareUpdateResult.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
class IFirmwareUpdateListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FirmwareUpdateListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status onProgress(int32_t percentComplete) = 0;
  virtual ::android::binder::Status onCompleted(::com::rdk::hal::firmwareupdate::FirmwareUpdateResult result, const ::std::string& report) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFirmwareUpdateListener

class IFirmwareUpdateListenerDefault : public IFirmwareUpdateListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onProgress(int32_t /*percentComplete*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onCompleted(::com::rdk::hal::firmwareupdate::FirmwareUpdateResult /*result*/, const ::std::string& /*report*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFirmwareUpdateListenerDefault
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
