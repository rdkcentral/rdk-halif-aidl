#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/avclock/IAVClockController.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class BpAVClockController : public ::android::BpInterface<IAVClockController> {
public:
  explicit BpAVClockController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAVClockController() = default;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status setAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, bool* _aidl_return) override;
  ::android::binder::Status getAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* _aidl_return) override;
  ::android::binder::Status setSupplementaryAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& supplementaryAudioSinkId, bool* _aidl_return) override;
  ::android::binder::Status getSupplementaryAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* _aidl_return) override;
  ::android::binder::Status setVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, bool* _aidl_return) override;
  ::android::binder::Status getVideoSink(::com::rdk::hal::videosink::IVideoSink::Id* _aidl_return) override;
  ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode clockMode, bool* _aidl_return) override;
  ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* _aidl_return) override;
  ::android::binder::Status notifyPCRSample(int64_t pcrTimeNs, int64_t sampleTimestampNs, bool* _aidl_return) override;
  ::android::binder::Status getCurrentClockTime(::com::rdk::hal::avclock::ClockTime* _aidl_return) override;
  ::android::binder::Status setPlaybackRate(double rate, bool* _aidl_return) override;
  ::android::binder::Status getPlaybackRate(double* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAVClockController
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
