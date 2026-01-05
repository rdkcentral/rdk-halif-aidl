#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BpAudioDecoderControllerListener : public ::android::BpInterface<IAudioDecoderControllerListener> {
public:
  explicit BpAudioDecoderControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioDecoderControllerListener() = default;
  ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& metadata) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioDecoderControllerListener
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
