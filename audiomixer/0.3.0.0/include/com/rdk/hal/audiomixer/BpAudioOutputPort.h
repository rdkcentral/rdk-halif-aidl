#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPort.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class BpAudioOutputPort : public ::android::BpInterface<IAudioOutputPort> {
public:
  explicit BpAudioOutputPort(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioOutputPort() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::audiomixer::State* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, ::com::rdk::hal::PropertyValue* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortControllerListener>& listener, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>& controller, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioOutputPort
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
