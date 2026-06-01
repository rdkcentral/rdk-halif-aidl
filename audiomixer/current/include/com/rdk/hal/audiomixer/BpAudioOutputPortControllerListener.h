#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioOutputPortControllerListener : public ::android::BpInterface<IAudioOutputPortControllerListener> {
public:
  explicit BpAudioOutputPortControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioOutputPortControllerListener() = default;
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioOutputPortControllerListener
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
