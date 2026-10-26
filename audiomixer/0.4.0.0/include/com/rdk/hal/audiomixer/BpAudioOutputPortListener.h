#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioOutputPortListener : public ::android::BpInterface<IAudioOutputPortListener> {
public:
  explicit BpAudioOutputPortListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioOutputPortListener() = default;
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& newValue) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioOutputPortListener
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
