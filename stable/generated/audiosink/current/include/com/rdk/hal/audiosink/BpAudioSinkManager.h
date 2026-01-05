#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiosink/IAudioSinkManager.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BpAudioSinkManager : public ::android::BpInterface<IAudioSinkManager> {
public:
  explicit BpAudioSinkManager(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioSinkManager() = default;
  ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* _aidl_return) override;
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* _aidl_return) override;
  ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioSinkManager
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
