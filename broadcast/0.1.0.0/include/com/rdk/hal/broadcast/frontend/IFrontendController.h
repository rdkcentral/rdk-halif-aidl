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
// @aidl-doc
/**
 * @brief Frontend controller interface.
 *
 * This interface gives exclusive access to a frontend's resources, allowing *one* client to tune the frontend and query
 * its status. Only one controller will be given out per frontend at a time, guaranteeing the client uninterrupted
 * access to the frontend.
 *
 * The client might choose to internally share the frontend controller with other components, in which case it's the
 * client's responsibility to ensure that the internal usage is synchronized.
 *
 * The service side is thread-safe: concurrent calls on this interface are permitted and are serialised internally, so a
 * client sharing the controller across threads risks interleaved ordering but never a corrupted service state. Calls
 * may block for the duration of the underlying hardware operation.
 *
 * This interface deliberately provides no listener or callback interface. Tune status and signal information are
 * observed by polling getTuneStatus() and getSignalInfo(); the client chooses its own polling interval. Nothing is
 * pushed from the service, so a client that stops polling simply stops observing.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IFrontendController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FrontendController)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /** Return type for @ref IFrontendController::getSignalInfo. */
  class SignalInfoReturn : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** Possible readiness values. */
    enum class Readiness : int32_t {
      // @aidl-doc
      /** Clean value when default initialized. */
      UNDEFINED = 0,
      // @aidl-doc
      /** The requested info is not available for this frontend or tune type. */
      UNSUPPORTED = 1,
      // @aidl-doc
      /** The info is generally supported but currently not available. */
      UNAVAILABLE = 2,
      // @aidl-doc
      /** The returned reading has to be considered unstable. */
      UNSTABLE = 3,
      // @aidl-doc
      /** A reliable reading. */
      STABLE = 4,
    };
    // @aidl-doc
    /** The requested value. */
    ::com::rdk::hal::broadcast::frontend::SignalInfoValue value;
    // @aidl-doc
    /** The quality of the reading. */
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
  // @aidl-doc
  /**
   * @brief Tune with the given parameters.
   *
   * Asynchronous: returns as soon as the request has been accepted, not when lock is achieved. The frontend enters
   * TUNING and the client polls getTuneStatus() until it reports LOCKED or NO_SIGNAL.
   *
   * Retuning is allowed. Calling tune() while a tune is already in progress, or while locked, is legal and
   * supersedes the previous request: the frontend abandons it and begins tuning to the new parameters. The client
   * does not need to call stopTune() first.
   *
   * @param[in] tuneParams The carrier-specific parameters to tune with.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION The given parameters are for a carrier type that
   *                                                             is not supported by this frontend.
   */
  virtual ::android::binder::Status tune(const ::com::rdk::hal::broadcast::frontend::TuneParameters& tuneParams) = 0;
  // @aidl-doc
  /**
   * @brief Cancels any ongoing tune and sets the tuner into unlocked state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status stopTune() = 0;
  // @aidl-doc
  /**
   * @brief Gets the current frontend tune status.
   *
   * This is the only means of observing tune progress: there is no completion callback, so a client waiting for a
   * tune to finish polls this method until it reports LOCKED or NO_SIGNAL. Loss of lock after a successful tune is
   * likewise only visible by continued polling.
   *
   * @param[out] _aidl_return Current tune status (e.g. IDLE, TUNING, NO_SIGNAL, LOCKED).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getTuneStatus(::com::rdk::hal::broadcast::frontend::TuneStatus* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get frontend signal information.
   *
   * @param[in] properties A list of information types that shall be returned. Note that this has to be a subset of
   *                       the information types returned in the Capabilities set for this frontend.
   *
   * @param[out] _aidl_return The list of the requested information values, in the same order as the requested properties.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
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
    return std::to_string(static_cast<int32_t>(val));
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
