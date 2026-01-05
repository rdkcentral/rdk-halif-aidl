#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videosink/IVideoSink.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class IVideoSinkManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  static constexpr char* HASHVALUE = "4dc98af4f8977cf8c6c7e7f353161287f0b7b106";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkManager

class IVideoSinkManagerDefault : public IVideoSinkManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& /*videoSinkId*/, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkManagerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
