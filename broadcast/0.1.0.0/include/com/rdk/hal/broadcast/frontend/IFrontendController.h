#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/IFrontendController.h>
#include <com/rdk/hal/broadcast/frontend/SignalInfoProperty.h>
#include <com/rdk/hal/broadcast/frontend/SignalInfoValue.h>
#include <com/rdk/hal/broadcast/frontend/TuneParameters.h>
#include <com/rdk/hal/broadcast/frontend/TuneStatus.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class IFrontendController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FrontendController)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  class SignalInfoReturn : public ::android::Parcelable {
  public:
    enum class Readiness : int8_t {
      UNDEFINED = 0,
      UNSUPPORTED = 1,
      UNAVAILABLE = 2,
      UNSTABLE = 3,
      STABLE = 4,
    };
    ::com::rdk::hal::broadcast::frontend::SignalInfoValue value;
    ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness readiness = ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness(0);
    inline bool operator!=(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) != std::tie(rhs.value, rhs.readiness);
    }
    inline bool operator<(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) < std::tie(rhs.value, rhs.readiness);
    }
    inline bool operator<=(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) <= std::tie(rhs.value, rhs.readiness);
    }
    inline bool operator==(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) == std::tie(rhs.value, rhs.readiness);
    }
    inline bool operator>(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) > std::tie(rhs.value, rhs.readiness);
    }
    inline bool operator>=(const SignalInfoReturn& rhs) const {
      return std::tie(value, readiness) >= std::tie(rhs.value, rhs.readiness);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.IFrontendController.SignalInfoReturn");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "SignalInfoReturn{";
      os << "value: " << ::android::internal::ToString(value);
      os << ", readiness: " << ::android::internal::ToString(readiness);
      os << "}";
      return os.str();
    }
  };  // class SignalInfoReturn
  virtual ::android::binder::Status tune(const ::com::rdk::hal::broadcast::frontend::TuneParameters& tuneParams) = 0;
  virtual ::android::binder::Status stopTune() = 0;
  virtual ::android::binder::Status getTuneStatus(::com::rdk::hal::broadcast::frontend::TuneStatus* _aidl_return) = 0;
  virtual ::android::binder::Status getSignalInfo(const ::std::vector<::com::rdk::hal::broadcast::frontend::SignalInfoProperty>& properties, ::std::vector<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFrontendController

class IFrontendControllerDefault : public IFrontendController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status tune(const ::com::rdk::hal::broadcast::frontend::TuneParameters& /*tuneParams*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stopTune() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getTuneStatus(::com::rdk::hal::broadcast::frontend::TuneStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSignalInfo(const ::std::vector<::com::rdk::hal::broadcast::frontend::SignalInfoProperty>& /*properties*/, ::std::vector<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFrontendControllerDefault
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(IFrontendController::SignalInfoReturn::Readiness val) {
  switch(val) {
  case IFrontendController::SignalInfoReturn::Readiness::UNDEFINED:
    return "UNDEFINED";
  case IFrontendController::SignalInfoReturn::Readiness::UNSUPPORTED:
    return "UNSUPPORTED";
  case IFrontendController::SignalInfoReturn::Readiness::UNAVAILABLE:
    return "UNAVAILABLE";
  case IFrontendController::SignalInfoReturn::Readiness::UNSTABLE:
    return "UNSTABLE";
  case IFrontendController::SignalInfoReturn::Readiness::STABLE:
    return "STABLE";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness, 5> enum_values<::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness> = {
  ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness::UNSUPPORTED,
  ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness::UNAVAILABLE,
  ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness::UNSTABLE,
  ::com::rdk::hal::broadcast::frontend::IFrontendController::SignalInfoReturn::Readiness::STABLE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
