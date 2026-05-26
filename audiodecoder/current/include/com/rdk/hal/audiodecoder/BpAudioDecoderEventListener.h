#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BpAudioDecoderEventListener : public ::android::BpInterface<IAudioDecoderEventListener> {
public:
  explicit BpAudioDecoderEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioDecoderEventListener() = default;
  ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode errorCode, int32_t vendorErrorCode) override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State oldState, ::com::rdk::hal::audiodecoder::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioDecoderEventListener
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
