#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioMixerEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioMixerEventListener : public ::android::BpInterface<IAudioMixerEventListener> {
public:
  explicit BpAudioMixerEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioMixerEventListener() = default;
  ::android::binder::Status onInputCodecChanged(int32_t audioMixerInputIndex, ::com::rdk::hal::audiodecoder::Codec codec, ::com::rdk::hal::audiomixer::ContentType contentType) override;
  ::android::binder::Status onError(int32_t errorCode, const ::android::String16& message) override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioMixerEventListener
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
