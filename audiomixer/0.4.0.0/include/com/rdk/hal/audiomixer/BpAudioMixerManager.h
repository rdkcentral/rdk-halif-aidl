#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioMixerManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioMixerManager : public ::android::BpInterface<IAudioMixerManager> {
public:
  explicit BpAudioMixerManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioMixerManager() = default;
  ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* _aidl_return) override;
  ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id id, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioMixerManager
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
