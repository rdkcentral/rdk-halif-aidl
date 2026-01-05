#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/IHDMIInput.h>
#include <com/rdk/hal/hdmiinput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class IHDMIInputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  static constexpr char* HASHVALUE = "82e8e5917a80b0598944ae1e7c36f1eba27fac32";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& hdmiInputId, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputManager

class IHDMIInputManagerDefault : public IHDMIInputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& /*hdmiInputId*/, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputManagerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
