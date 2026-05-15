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
class IAudioOutputPortListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPortListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  virtual ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& newValue) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPortListener

class IAudioOutputPortListenerDefault : public IAudioOutputPortListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*newValue*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
