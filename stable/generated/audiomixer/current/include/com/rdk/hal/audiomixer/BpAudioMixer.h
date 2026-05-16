#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioMixer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioMixer : public ::android::BpInterface<IAudioMixer> {
public:
  explicit BpAudioMixer(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioMixer() = default;
  ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* _aidl_return) override;
  ::android::binder::Status getAudioOutputPort(int32_t id, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* _aidl_return) override;
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property property, ::com::rdk::hal::PropertyValue* _aidl_return) override;
  ::android::binder::Status open(bool secure, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& audioMixerController, bool* _aidl_return) override;
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) override;
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) override;
  ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* _aidl_return) override;
  ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioMixer
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
