#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortListener.h>
#include <com/rdk/hal/audiomixer/OutputPortCapabilities.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioOutputPort : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPort)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, ::com::rdk::hal::PropertyValue* _aidl_return) = 0;
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& listener) = 0;
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& listener) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPort

class IAudioOutputPortDefault : public IAudioOutputPort {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, ::com::rdk::hal::PropertyValue* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
