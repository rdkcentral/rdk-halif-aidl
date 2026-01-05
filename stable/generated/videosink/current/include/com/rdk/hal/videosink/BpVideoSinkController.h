#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/videosink/IVideoSinkController.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class BpVideoSinkController : public ::android::BpInterface<IVideoSinkController> {
public:
  explicit BpVideoSinkController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpVideoSinkController() = default;
  ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, bool* _aidl_return) override;
  ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* _aidl_return) override;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status queueVideoFrame(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::com::rdk::hal::videodecoder::FrameMetadata& metadata, bool* _aidl_return) override;
  ::android::binder::Status flush(bool holdLastFrame) override;
  ::android::binder::Status discardFramesUntil(int64_t nsPresentationTime) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpVideoSinkController
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
