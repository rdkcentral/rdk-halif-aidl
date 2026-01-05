#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiosink/IAudioSink.h>
#include <com/rdk/hal/avclock/ClockMode.h>
#include <com/rdk/hal/avclock/ClockTime.h>
#include <com/rdk/hal/videosink/IVideoSink.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class IAVClockController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockController)
  static const int32_t VERSION = 1;
  const std::string HASH = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  static constexpr char* HASHVALUE = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status setAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* _aidl_return) = 0;
  virtual ::android::binder::Status setSupplementaryAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& supplementaryAudioSinkId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getSupplementaryAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* _aidl_return) = 0;
  virtual ::android::binder::Status setVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoSink(::com::rdk::hal::videosink::IVideoSink::Id* _aidl_return) = 0;
  virtual ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode clockMode, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* _aidl_return) = 0;
  virtual ::android::binder::Status notifyPCRSample(int64_t pcrTimeNs, int64_t sampleTimestampNs, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getCurrentClockTime(::com::rdk::hal::avclock::ClockTime* _aidl_return) = 0;
  virtual ::android::binder::Status setPlaybackRate(double rate, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getPlaybackRate(double* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockController

class IAVClockControllerDefault : public IAVClockController {
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
  ::android::binder::Status setAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& /*audioSinkId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSupplementaryAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& /*supplementaryAudioSinkId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSupplementaryAudioSink(::com::rdk::hal::audiosink::IAudioSink::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& /*videoSinkId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSink(::com::rdk::hal::videosink::IVideoSink::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode /*clockMode*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyPCRSample(int64_t /*pcrTimeNs*/, int64_t /*sampleTimestampNs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentClockTime(::com::rdk::hal::avclock::ClockTime* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPlaybackRate(double /*rate*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPlaybackRate(double* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockControllerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
