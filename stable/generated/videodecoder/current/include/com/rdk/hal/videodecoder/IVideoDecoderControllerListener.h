#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/FrameMetadata.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class IVideoDecoderControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderControllerListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "afc6bd3166231467a3288c4956b6b4322e039c38";
  static constexpr char* HASHVALUE = "afc6bd3166231467a3288c4956b6b4322e039c38";
  virtual ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameAVBufferHandle, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& metadata) = 0;
  virtual ::android::binder::Status onUserDataOutput(int64_t nsPresentationTime, const ::std::vector<uint8_t>& userData) = 0;
  virtual ::android::binder::Status onDecodeBufferAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderControllerListener

class IVideoDecoderControllerListenerDefault : public IVideoDecoderControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFrameOutput(int64_t /*nsPresentationTime*/, int64_t /*frameAVBufferHandle*/, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onUserDataOutput(int64_t /*nsPresentationTime*/, const ::std::vector<uint8_t>& /*userData*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDecodeBufferAvailable() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderControllerListenerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
