#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioMixerController.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioMixerController : public ::android::BpInterface<IAudioMixerController> {
public:
  explicit BpAudioMixerController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioMixerController() = default;
  ::android::binder::Status setInputRouting(const ::std::vector<::com::rdk::hal::audiomixer::InputRouting>& routing, bool* _aidl_return) override;
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status flush(bool reset) override;
  ::android::binder::Status signalDiscontinuity() override;
  ::android::binder::Status signalEOS() override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioMixerController
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
