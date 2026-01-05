#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiosink/IAudioSinkController.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BpAudioSinkController : public ::android::BpInterface<IAudioSinkController> {
public:
  explicit BpAudioSinkController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioSinkController() = default;
  ::android::binder::Status setAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, bool* _aidl_return) override;
  ::android::binder::Status getAudioDecoder(::com::rdk::hal::audiodecoder::IAudioDecoder::Id* _aidl_return) override;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status queueAudioFrame(int64_t nsPresentationTime, int64_t bufferHandle, const ::com::rdk::hal::audiodecoder::FrameMetadata& metadata, bool* _aidl_return) override;
  ::android::binder::Status flush() override;
  ::android::binder::Status getVolume(::com::rdk::hal::audiosink::Volume* _aidl_return) override;
  ::android::binder::Status setVolume(const ::com::rdk::hal::audiosink::Volume& volume, bool* _aidl_return) override;
  ::android::binder::Status setVolumeRamp(double targetVolume, int32_t overMs, ::com::rdk::hal::audiosink::VolumeRamp volumeRamp, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioSinkController
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
