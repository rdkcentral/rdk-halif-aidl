#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videosink/IVideoSink.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BpVideoSink : public ::android::BpInterface<IVideoSink> {
public:
  explicit BpVideoSink(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoSink() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::videosink::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::videosink::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::State* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkControllerListener>& videoSinkControllerListener, ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>& videoSinkController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& videoSinkEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& videoSinkEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoSink
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
