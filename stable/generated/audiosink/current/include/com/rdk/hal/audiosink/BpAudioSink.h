#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiosink/IAudioSink.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class BpAudioSink : public ::android::BpInterface<IAudioSink> {
public:
  explicit BpAudioSink(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioSink() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiosink::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::audiosink::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status setProperty(::com::rdk::hal::audiosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::State* _aidl_return) override;
  ::android::binder::Status open(::com::rdk::hal::audiosink::ContentType contentType, const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkControllerListener>& audioSinkControllerListener, ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>& audioSinkController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioSink
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
