#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortController.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioOutputPortController : public ::android::BpInterface<IAudioOutputPortController> {
public:
  explicit BpAudioOutputPortController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioOutputPortController() = default;
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) override;
  ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* _aidl_return) override;
  ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& audioCaptureListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioOutputPortController
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
