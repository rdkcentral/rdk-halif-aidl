#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/videodecoder/CSDVideoFormat.h>
#include <com/rdk/hal/videodecoder/Colorimetry.h>
#include <com/rdk/hal/videodecoder/ContentLightLevel.h>
#include <com/rdk/hal/videodecoder/InputBufferMetadata.h>
#include <com/rdk/hal/videodecoder/MasteringDisplayInfo.h>
#include <com/rdk/hal/videodecoder/Property.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class IVideoDecoderController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderController)
  static const int32_t VERSION = 1;
  const std::string HASH = "afc6bd3166231467a3288c4956b6b4322e039c38";
  static constexpr char* HASHVALUE = "afc6bd3166231467a3288c4956b6b4322e039c38";
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::videodecoder::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status decodeBufferWithMetadata(int64_t bufferHandle, const ::com::rdk::hal::videodecoder::InputBufferMetadata& metadata, bool* _aidl_return) = 0;
  virtual ::android::binder::Status flush(bool reset) = 0;
  virtual ::android::binder::Status signalDiscontinuity() = 0;
  virtual ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::videodecoder::CSDVideoFormat csdVideoFormat, const ::std::vector<uint8_t>& codecData, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setMasteringDisplayInfo(const ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo>& info) = 0;
  virtual ::android::binder::Status setContentLightLevel(const ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel>& info) = 0;
  virtual ::android::binder::Status setColorimetry(::com::rdk::hal::videodecoder::Colorimetry colorimetry) = 0;
  virtual ::android::binder::Status setStreamResolution(int32_t width, int32_t height) = 0;
  virtual ::android::binder::Status setFrameRate(int32_t numerator, int32_t denominator) = 0;
  virtual ::android::binder::Status setDolbyVisionLayerFlags(bool blPresent, bool elPresent) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderController

class IVideoDecoderControllerDefault : public IVideoDecoderController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::videodecoder::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decodeBufferWithMetadata(int64_t /*bufferHandle*/, const ::com::rdk::hal::videodecoder::InputBufferMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*reset*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalDiscontinuity() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::videodecoder::CSDVideoFormat /*csdVideoFormat*/, const ::std::vector<uint8_t>& /*codecData*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMasteringDisplayInfo(const ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo>& /*info*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setContentLightLevel(const ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel>& /*info*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setColorimetry(::com::rdk::hal::videodecoder::Colorimetry /*colorimetry*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setStreamResolution(int32_t /*width*/, int32_t /*height*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFrameRate(int32_t /*numerator*/, int32_t /*denominator*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDolbyVisionLayerFlags(bool /*blPresent*/, bool /*elPresent*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderControllerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
