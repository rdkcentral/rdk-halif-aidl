#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/InputRouting.h>
#include <com/rdk/hal/audiomixer/Property.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioMixerController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerController)
  static const int32_t VERSION = 1;
  const std::string HASH = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  static constexpr char* HASHVALUE = "9266a29b99c47e0e905d8c8e048328c3ee871b61";
  virtual ::android::binder::Status setInputRouting(const ::std::vector<::com::rdk::hal::audiomixer::InputRouting>& routing, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status flush(bool reset) = 0;
  virtual ::android::binder::Status signalDiscontinuity() = 0;
  virtual ::android::binder::Status signalEOS() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerController

class IAudioMixerControllerDefault : public IAudioMixerController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setInputRouting(const ::std::vector<::com::rdk::hal::audiomixer::InputRouting>& /*routing*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*reset*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalDiscontinuity() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalEOS() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerControllerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
