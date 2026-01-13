#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/flash/IFlashListener.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
class IFlash : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Flash)
  static const int32_t VERSION = 1;
  const std::string HASH = "ac43ccbd6a0c0ee9e7cff2cfdde25a77122dd8ae";
  static constexpr char* HASHVALUE = "ac43ccbd6a0c0ee9e7cff2cfdde25a77122dd8ae";
  virtual ::android::binder::Status flashImageFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::flash::IFlashListener>& listener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFlash

class IFlashDefault : public IFlash {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status flashImageFromFile(const ::std::string& /*filename*/, const ::android::sp<::com::rdk::hal::flash::IFlashListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFlashDefault
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
