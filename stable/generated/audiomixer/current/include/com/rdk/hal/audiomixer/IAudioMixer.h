#pragma once

#include <array>
#include <binder/Enums.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/Capabilities.h>
#include <com/rdk/hal/audiomixer/IAudioMixerController.h>
#include <com/rdk/hal/audiomixer/IAudioMixerEventListener.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPort.h>
#include <com/rdk/hal/audiomixer/InputRouting.h>
#include <com/rdk/hal/audiomixer/Property.h>
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
class IAudioMixer : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixer)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  enum class Id : int32_t {
    MIXER_SYSTEM = 0,
    MIX1 = 1,
    MIX2 = 2,
    MIX3 = 3,
    MIX4 = 4,
    MIX5 = 5,
  };
  virtual ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioOutputPort(int32_t id, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* _aidl_return) = 0;
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property property, ::com::rdk::hal::PropertyValue* _aidl_return) = 0;
  virtual ::android::binder::Status open(bool secure, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& audioMixerController, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) = 0;
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& listener) = 0;
  virtual ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* _aidl_return) = 0;
  virtual ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixer

class IAudioMixerDefault : public IAudioMixer {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioOutputPort(int32_t /*id*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property /*property*/, ::com::rdk::hal::PropertyValue* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(bool /*secure*/, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*audioMixerEventListener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& /*audioMixerController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(IAudioMixer::Id val) {
  switch(val) {
  case IAudioMixer::Id::MIXER_SYSTEM:
    return "MIXER_SYSTEM";
  case IAudioMixer::Id::MIX1:
    return "MIX1";
  case IAudioMixer::Id::MIX2:
    return "MIX2";
  case IAudioMixer::Id::MIX3:
    return "MIX3";
  case IAudioMixer::Id::MIX4:
    return "MIX4";
  case IAudioMixer::Id::MIX5:
    return "MIX5";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::IAudioMixer::Id, 6> enum_values<::com::rdk::hal::audiomixer::IAudioMixer::Id> = {
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIXER_SYSTEM,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX1,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX2,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX3,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX4,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX5,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
