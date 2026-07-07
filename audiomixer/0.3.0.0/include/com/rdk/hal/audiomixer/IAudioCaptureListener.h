#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioCaptureData.h>
#include <com/rdk/hal/audiomixer/AudioCaptureError.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioCaptureListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioCaptureListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ff12e597d51955e239d709062d17dd73b32ddb56";
  static constexpr char* HASHVALUE = "ff12e597d51955e239d709062d17dd73b32ddb56";
  virtual ::android::binder::Status onDataAvailable(int64_t offsetBytes, int32_t lengthBytes, const ::com::rdk::hal::audiomixer::AudioCaptureData& metadata) = 0;
  virtual ::android::binder::Status onStarted() = 0;
  virtual ::android::binder::Status onStopped() = 0;
  virtual ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError error, const ::android::String16& message) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioCaptureListener

class IAudioCaptureListenerDefault : public IAudioCaptureListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDataAvailable(int64_t /*offsetBytes*/, int32_t /*lengthBytes*/, const ::com::rdk::hal::audiomixer::AudioCaptureData& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStarted() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStopped() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError /*error*/, const ::android::String16& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioCaptureListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
