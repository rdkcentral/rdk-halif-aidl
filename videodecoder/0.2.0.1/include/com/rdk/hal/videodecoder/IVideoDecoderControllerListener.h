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
  static const int32_t VERSION = 2001;
  const std::string HASH = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  static constexpr char* HASHVALUE = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  virtual ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameAVBufferHandle, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& metadata) = 0;
  virtual ::android::binder::Status onEndOfStream() = 0;
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
  ::android::binder::Status onEndOfStream() override {
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
