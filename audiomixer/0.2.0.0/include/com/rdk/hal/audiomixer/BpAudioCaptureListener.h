#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioCaptureListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioCaptureListener : public ::android::BpInterface<IAudioCaptureListener> {
public:
  explicit BpAudioCaptureListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioCaptureListener() = default;
  ::android::binder::Status onDataAvailable(int64_t offsetBytes, int32_t lengthBytes, const ::com::rdk::hal::audiomixer::AudioCaptureData& metadata) override;
  ::android::binder::Status onStarted() override;
  ::android::binder::Status onStopped() override;
  ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError error, const ::android::String16& message) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioCaptureListener
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
