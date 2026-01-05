#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiosink/IAudioSink.h>
#include <com/rdk/hal/audiosink/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
class IAudioSinkManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "2c1b84b1b69a8f134c625cde43cdcc185d464a99";
  static constexpr char* HASHVALUE = "2c1b84b1b69a8f134c625cde43cdcc185d464a99";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkManager

class IAudioSinkManagerDefault : public IAudioSinkManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& /*audioSinkId*/, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkManagerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
