#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderEventListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class BpVideoDecoderEventListener : public ::android::BpInterface<IVideoDecoderEventListener> {
public:
  explicit BpVideoDecoderEventListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoDecoderEventListener() = default;
  ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode errorCode, int32_t vendorErrorCode) override;
  ::android::binder::Status onStateChanged(::com::rdk::hal::State oldState, ::com::rdk::hal::State newState) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoDecoderEventListener
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
