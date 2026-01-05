#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/videodecoder/FrameMetadata.h>
#include <com/rdk/hal/videodecoder/IVideoDecoder.h>
#include <com/rdk/hal/videosink/Property.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class IVideoSinkController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkController)
  static const int32_t VERSION = 1;
  const std::string HASH = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  static constexpr char* HASHVALUE = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  virtual ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* _aidl_return) = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status queueVideoFrame(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::com::rdk::hal::videodecoder::FrameMetadata& metadata, bool* _aidl_return) = 0;
  virtual ::android::binder::Status flush(bool holdLastFrame) = 0;
  virtual ::android::binder::Status discardFramesUntil(int64_t nsPresentationTime) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkController

class IVideoSinkControllerDefault : public IVideoSinkController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& /*videoDecoderId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status queueVideoFrame(int64_t /*nsPresentationTime*/, int64_t /*frameBufferHandle*/, const ::com::rdk::hal::videodecoder::FrameMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*holdLastFrame*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status discardFramesUntil(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkControllerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
