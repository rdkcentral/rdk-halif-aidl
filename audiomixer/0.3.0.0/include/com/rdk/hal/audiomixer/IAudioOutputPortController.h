#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/IAudioCapture.h>
#include <com/rdk/hal/audiomixer/IAudioCaptureListener.h>
#include <com/rdk/hal/audiomixer/IDolbyMs12_2_6_Dap.h>
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
  virtual ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& audioCaptureListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* _aidl_return) = 0;
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
  ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& /*audioCaptureListener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* /*_aidl_return*/) override {
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
