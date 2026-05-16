#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/sensor/motion/Capabilities.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorController.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorControllerListener.h>
#include <com/rdk/hal/sensor/motion/IMotionSensorEventListener.h>
#include <com/rdk/hal/sensor/motion/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
class IMotionSensor : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(MotionSensor)
  static const int32_t VERSION = 1;
  const std::string HASH = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
  static constexpr char* HASHVALUE = "fe60d3f4495ff4af10cfa3bdd049282660d60367";
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.sensor.motion.IMotionSensor.Id");
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
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* _aidl_return) = 0;
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& listener, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& controller, bool* _aidl_return) = 0;
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) = 0;
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& motionSensorEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMotionSensor

class IMotionSensorDefault : public IMotionSensor {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::sensor::motion::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::sensor::motion::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& /*motionSensorEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensorEventListener>& /*motionSensorEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMotionSensorDefault
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
