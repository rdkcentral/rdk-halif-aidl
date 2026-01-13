#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/State.h>
#include <com/rdk/hal/avclock/Capabilities.h>
#include <com/rdk/hal/avclock/IAVClockController.h>
#include <com/rdk/hal/avclock/IAVClockControllerListener.h>
#include <com/rdk/hal/avclock/IAVClockEventListener.h>
#include <com/rdk/hal/avclock/Property.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
class IAVClock : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClock)
  static const int32_t VERSION = 1;
  const std::string HASH = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  static constexpr char* HASHVALUE = "01c503f66097c7c8de4f50e3d8f23792d09d8291";
  class Id : public ::android::Parcelable {
  public:
    int32_t value = 0;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avclock.IAVClock.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::avclock::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getState(::com::rdk::hal::State* _aidl_return) = 0;
  virtual ::android::binder::Status getProperty(::com::rdk::hal::avclock::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  virtual ::android::binder::Status setProperty(::com::rdk::hal::avclock::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::avclock::IAVClockControllerListener>& avClockControllerListener, ::android::sp<::com::rdk::hal::avclock::IAVClockController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::avclock::IAVClockController>& avClockController, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& avClockEventListener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& avClockEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClock

class IAVClockDefault : public IAVClock {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::avclock::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::avclock::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::avclock::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::avclock::IAVClockControllerListener>& /*avClockControllerListener*/, ::android::sp<::com::rdk::hal::avclock::IAVClockController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::avclock::IAVClockController>& /*avClockController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& /*avClockEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& /*avClockEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
