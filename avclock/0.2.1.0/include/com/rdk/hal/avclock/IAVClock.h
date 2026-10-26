#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/avclock/Capabilities.h>
#include <com/rdk/hal/avclock/IAVClockController.h>
#include <com/rdk/hal/avclock/IAVClockControllerListener.h>
#include <com/rdk/hal/avclock/IAVClockEventListener.h>
#include <com/rdk/hal/avclock/Property.h>
#include <com/rdk/hal/avclock/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
// @aidl-doc
/**
 *  @brief     AV Clock HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IAVClock : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClock)
  static const int32_t VERSION = 2010;
  const std::string HASH = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  static constexpr char* HASHVALUE = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  // @aidl-doc
  /** AV Clock resource ID type */
  class Id : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The actual resource ID */
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

    // @aidl-doc
    /** The undefined ID value. */
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
  // @aidl-doc
  /** Used to indicate that a clock value is invalid and should not be used * */
  enum : int64_t { UNDEFINED_TIME = -1L };
  // @aidl-doc
  /**
   * Gets the capabilities for this AV Clock.
   *
   * This function can be called at any time and is not dependant on any AV Clock state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::avclock::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current AV Clock state.
   *
   * @param[out] _aidl_return State enum value.
   *
   * @see IAVClockEventListener.onStateChanged(),  IAVClockControllerListener.onStateChanged().
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::avclock::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property.
   *
   * Read-only property accessor. Stays on `IAVClock` (not the controller)
   * so callers can discover identity properties such as `RESOURCE_ID`
   * before opening the clock — read access does not mutate state and
   * does not require holding the single-writer controller handle.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue holding the current value, or null if the
   *                          property key is not supported by this AV Clock instance.
   *
   * @see IAVClockController.setProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::avclock::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the AV Clock.
   *
   * While the AV Clock is in the `OPENING` state, these defaults are set on the AV Clock:
   *  - Mode is set to `ClockMode::AUTO`
   *  - Playback rate is set to 1.0
   *
   * Sink association is owned by the sinks, not the AV Clock: clients call
   * `attachClock()` / `detachClock()` / `getClock()` on the audio and video
   * sink controllers (`IAudioSinkController`, `IVideoSinkController`),
   * passing this clock's `IAVClock.Id`. The AV Clock holds no sink state.
   *
   * If successful the AV Clock transitions to the `OPENING` state and then to the `READY` state.
   * If an internal error occurs, the AV Clock transitions to the `OPENING` state and then back to the `CLOSED` state
   * with a null interface returned.
   *
   * If the client that opened the `IAVClockController` crashes,
   * then the `IAVClockController` has `stop()` and `close()` implicitly called to perform clean up.
   *
   * @param[in] avClockControllerListener		    Listener object for controller callbacks.
   *
   * @param[out] _aidl_return IAVClockController interface or null on internal error.
   *
   * @pre AV Clock is in State::CLOSED state.
   *
   * @see close(), IAVClockController
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::avclock::IAVClockControllerListener>& avClockControllerListener, ::android::sp<::com::rdk::hal::avclock::IAVClockController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the AV Clock.
   *
   * The AV Clock must be in a `READY` state before it can be closed.
   * If successful the AV Clock transitions to the `CLOSING` state and then to the `CLOSED` state.
   * `onStateChanged(CLOSING, CLOSED)` will be the last notification received on the `IAVClockControllerListener`.
   *
   * @param[in] avClockController     Instance of IAVClockController.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or unrecognised parameter.
   * @pre AV Clock has been successfully opened and is in the State::READY state.
   *
   * @see open(), IAVClockController
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If instance is not in OPENED State.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::avclock::IAVClockController>& avClockController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an AV Clock event listener.
   *
   * An `IAVClockEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] avClockEventListener	    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::avclock::IAVClockEventListener>& avClockEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters an AV Clock event listener.
   *
   * @param[in] avClockEventListener	    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
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
  ::android::binder::Status getState(::com::rdk::hal::avclock::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::avclock::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
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
