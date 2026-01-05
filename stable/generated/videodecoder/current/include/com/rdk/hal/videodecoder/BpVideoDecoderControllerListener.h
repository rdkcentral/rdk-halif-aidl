#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderControllerListener.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class BpVideoDecoderControllerListener : public ::android::BpInterface<IVideoDecoderControllerListener> {
public:
  explicit BpVideoDecoderControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoDecoderControllerListener() = default;
  ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& metadata) override;
  ::android::binder::Status onUserDataOutput(int64_t nsPresentationTime, const ::std::vector<uint8_t>& userData) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoDecoderControllerListener
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
