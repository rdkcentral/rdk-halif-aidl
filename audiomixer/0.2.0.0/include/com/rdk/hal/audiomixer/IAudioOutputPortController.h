#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioOutputPortController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPortController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPortController

class IAudioOutputPortControllerDefault : public IAudioOutputPortController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortControllerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
