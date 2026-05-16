#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/IAudioMixer.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioMixerManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id id, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerManager

class IAudioMixerManagerDefault : public IAudioMixerManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id /*id*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerManagerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
