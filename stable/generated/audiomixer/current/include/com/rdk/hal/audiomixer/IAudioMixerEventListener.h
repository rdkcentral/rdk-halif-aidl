#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/ContentType.h>
#include <com/rdk/hal/audiomixer/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioMixerEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  virtual ::android::binder::Status onInputCodecChanged(int32_t audioMixerInputIndex, ::com::rdk::hal::audiodecoder::Codec codec, ::com::rdk::hal::audiomixer::ContentType contentType) = 0;
  virtual ::android::binder::Status onError(int32_t errorCode, const ::android::String16& message) = 0;
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerEventListener

class IAudioMixerEventListenerDefault : public IAudioMixerEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onInputCodecChanged(int32_t /*audioMixerInputIndex*/, ::com::rdk::hal::audiodecoder::Codec /*codec*/, ::com::rdk::hal::audiomixer::ContentType /*contentType*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(int32_t /*errorCode*/, const ::android::String16& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State /*oldState*/, ::com::rdk::hal::audiomixer::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerEventListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
