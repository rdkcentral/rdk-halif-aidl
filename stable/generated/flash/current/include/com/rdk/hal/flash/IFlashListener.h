#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/flash/FlashImageResult.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class IFlashListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FlashListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "78378d5495bc2fb3472b4f1413ef3a50ef9fbe22";
  static constexpr char* HASHVALUE = "78378d5495bc2fb3472b4f1413ef3a50ef9fbe22";
  virtual ::android::binder::Status onProgress(int32_t percentComplete) = 0;
  virtual ::android::binder::Status onCompleted(::com::rdk::hal::flash::FlashImageResult result, const ::std::string& report) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFlashListener

class IFlashListenerDefault : public IFlashListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onProgress(int32_t /*percentComplete*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onCompleted(::com::rdk::hal::flash::FlashImageResult /*result*/, const ::std::string& /*report*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFlashListenerDefault
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
