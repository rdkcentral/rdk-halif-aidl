#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoder.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
class BpAudioDecoder : public ::android::BpInterface<IAudioDecoder> {
public:
  explicit BpAudioDecoder(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAudioDecoder() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiodecoder::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::audiodecoder::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::audiodecoder::State* _aidl_return) override;
  ::android::binder::Status open(::com::rdk::hal::audiodecoder::Codec codec, bool secure, const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderControllerListener>& audioDecoderControllerListener, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>& audioDecoderController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAudioDecoder
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
