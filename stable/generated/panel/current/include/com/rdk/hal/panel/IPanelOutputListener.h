#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class IPanelOutputListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutputListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  static constexpr char* HASHVALUE = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  virtual ::android::binder::Status onPictureModeChanged(const ::android::String16& pictureMode) = 0;
  virtual ::android::binder::Status onVideoSourceChanged(::com::rdk::hal::AVSource avSource) = 0;
  virtual ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::videodecoder::DynamicRange dynamicRange) = 0;
  virtual ::android::binder::Status onVideoFrameRateChanged(int32_t frameRateNumerator, int32_t frameRateDenominator) = 0;
  virtual ::android::binder::Status onVideoResolutionChanged(int32_t width, int32_t height) = 0;
  virtual ::android::binder::Status onRefreshRateChanged(double refreshRateHz) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutputListener

class IPanelOutputListenerDefault : public IPanelOutputListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onPictureModeChanged(const ::android::String16& /*pictureMode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoSourceChanged(::com::rdk::hal::AVSource /*avSource*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoFormatChanged(::com::rdk::hal::videodecoder::DynamicRange /*dynamicRange*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoFrameRateChanged(int32_t /*frameRateNumerator*/, int32_t /*frameRateDenominator*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoResolutionChanged(int32_t /*width*/, int32_t /*height*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onRefreshRateChanged(double /*refreshRateHz*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputListenerDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
