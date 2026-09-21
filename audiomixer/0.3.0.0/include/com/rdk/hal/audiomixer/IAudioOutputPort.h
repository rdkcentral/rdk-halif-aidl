#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortController.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortControllerListener.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortListener.h>
#include <com/rdk/hal/audiomixer/OutputPortCapabilities.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <com/rdk/hal/audiomixer/State.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioOutputPort : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPort)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ff12e597d51955e239d709062d17dd73b32ddb56";
  static constexpr char* HASHVALUE = "ff12e597d51955e239d709062d17dd73b32ddb56";
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getState(::com::rdk::hal::audiomixer::State* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, ::com::rdk::hal::PropertyValue* _aidl_return) = 0;
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortControllerListener>& listener, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>& controller, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) = 0;
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
  ::android::binder::Status getState(::com::rdk::hal::audiomixer::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, ::com::rdk::hal::PropertyValue* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*audioOutputPortEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*audioOutputPortEventListener*/, bool* /*_aidl_return*/) override {
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
