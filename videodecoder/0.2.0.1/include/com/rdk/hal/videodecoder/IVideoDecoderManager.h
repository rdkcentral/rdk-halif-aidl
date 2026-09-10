#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/IVideoDecoder.h>
#include <com/rdk/hal/videodecoder/OperationalMode.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class IVideoDecoderManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderManager)
  static const int32_t VERSION = 2001;
  const std::string HASH = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  static constexpr char* HASHVALUE = "52acdb59af5cdef53d7da0c5a3acf3d37c0b8c7c";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getVideoDecoderIds(::std::vector<::com::rdk::hal::videodecoder::IVideoDecoder::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getSupportedOperationalModes(::std::vector<::com::rdk::hal::videodecoder::OperationalMode>* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoder>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderManager

class IVideoDecoderManagerDefault : public IVideoDecoderManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVideoDecoderIds(::std::vector<::com::rdk::hal::videodecoder::IVideoDecoder::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSupportedOperationalModes(::std::vector<::com::rdk::hal::videodecoder::OperationalMode>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& /*videoDecoderId*/, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoder>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderManagerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
