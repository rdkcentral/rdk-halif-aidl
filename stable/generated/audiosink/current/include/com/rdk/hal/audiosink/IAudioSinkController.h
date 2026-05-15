#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/FrameMetadata.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoder.h>
#include <com/rdk/hal/audiosink/Volume.h>
#include <com/rdk/hal/audiosink/VolumeRamp.h>
#include <com/rdk/hal/avclock/IAVClock.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class IAudioSinkController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkController)
  static const int32_t VERSION = 1;
  const std::string HASH = "d0dbeab60f70e3979cffc360ef24d7b283503a32";
  static constexpr char* HASHVALUE = "d0dbeab60f70e3979cffc360ef24d7b283503a32";
  virtual ::android::binder::Status setAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioDecoder(::com::rdk::hal::audiodecoder::IAudioDecoder::Id* _aidl_return) = 0;
  virtual ::android::binder::Status attachClock(const ::com::rdk::hal::avclock::IAVClock::Id& clockId) = 0;
  virtual ::android::binder::Status detachClock() = 0;
  virtual ::android::binder::Status getClock(::com::rdk::hal::avclock::IAVClock::Id* _aidl_return) = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status queueAudioFrame(int64_t nsPresentationTime, int64_t bufferHandle, const ::com::rdk::hal::audiodecoder::FrameMetadata& metadata, bool* _aidl_return) = 0;
  virtual ::android::binder::Status flush() = 0;
  virtual ::android::binder::Status getVolume(::com::rdk::hal::audiosink::Volume* _aidl_return) = 0;
  virtual ::android::binder::Status setVolume(const ::com::rdk::hal::audiosink::Volume& volume, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setVolumeRamp(double targetVolume, int32_t overMs, ::com::rdk::hal::audiosink::VolumeRamp volumeRamp, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkController

class IAudioSinkControllerDefault : public IAudioSinkController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& /*audioDecoderId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioDecoder(::com::rdk::hal::audiodecoder::IAudioDecoder::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status attachClock(const ::com::rdk::hal::avclock::IAVClock::Id& /*clockId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status detachClock() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getClock(::com::rdk::hal::avclock::IAVClock::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status queueAudioFrame(int64_t /*nsPresentationTime*/, int64_t /*bufferHandle*/, const ::com::rdk::hal::audiodecoder::FrameMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVolume(::com::rdk::hal::audiosink::Volume* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolume(const ::com::rdk::hal::audiosink::Volume& /*volume*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolumeRamp(double /*targetVolume*/, int32_t /*overMs*/, ::com::rdk::hal::audiosink::VolumeRamp /*volumeRamp*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkControllerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
