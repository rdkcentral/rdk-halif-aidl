#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmioutput/Capabilities.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputController.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputControllerListener.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputEventListener.h>
#include <com/rdk/hal/hdmioutput/Property.h>
#include <com/rdk/hal/hdmioutput/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI Output HAL interface.
 *
 *  This interface manages HDMI output resources, including capability queries,
 *  state transitions, and client lifecycle for output control.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 *
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IHDMIOutput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutput)
  static const int32_t VERSION = 2000;
  const std::string HASH = "1ca5bda96fbbe2b88aac65291c41d4b17179a64b";
  static constexpr char* HASHVALUE = "1ca5bda96fbbe2b88aac65291c41d4b17179a64b";
  // @aidl-doc
  /** HDMI Output resource ID type */
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.IHDMIOutput.Id");
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
  /**
   * Gets the capabilities for this HDMI output.
   *
   * This function can be called at any time and is not dependent on HDMI output state.
   * The returned value is constant and must not change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property value.
   *
   * @param[in] property     The key of a property from the Property enum.
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown.
   *
   *
   * @see setProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::hdmioutput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current HDMI output state.
   *
   * @param[out] _aidl_return State enum value.
   *
   *
   * @see IHDMIOutputEventListener.onStateChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::hdmioutput::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the HDMI output port instance.
   *
   * The output transitions to `OPENING` and then to `READY` on success.
   * Callbacks are delivered to the supplied controller listener.
   *
   * The `onHotPlugDetectStateChanged()` callback always fires during the `OPENING` state.
   *
   * If the client process dies (detected via Binder death notification), the HAL
   * implementation automatically calls `stop()` and `close()` to release resources.
   *
   * @param[in] hdmiOutputControllerListener  Listener for controller callbacks.
   * @param[out] _aidl_return IHDMIOutputController or null if input is invalid.
   *
   * @pre Must be in State::CLOSED.
   *
   * @see IHDMIOutputController, close(), registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputControllerListener>& hdmiOutputControllerListener, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the HDMI output.
   *
   * Transitions from `READY` to `CLOSING` to `CLOSED`, notifying listeners via
   * `onStateChanged(CLOSING, CLOSED)`.
   *
   * The supplied controller instance must match the one returned by `open()`.
   *
   * @param[in] hdmiOutputController  Instance from open().
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or mismatched instance.
   * @pre Must be in State::READY.
   *
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>& hdmiOutputController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a HDMI output event listener.
   *
   * Only one listener can be registered at a time.
   *
   * @param[in] hdmiOutputEventListener  Listener object.
   * @param[out] _aidl_return boolean
   *   - true: Listener registered.
   *   - false: Already registered.
   * @see unregisterEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a HDMI output event listener.
   *
   * @param[in] hdmiOutputEventListener  Listener object.
   * @param[out] _aidl_return boolean
   *   - true: Listener unregistered.
   *   - false: Listener not found.
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& hdmiOutputEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutput

class IHDMIOutputDefault : public IHDMIOutput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmioutput::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::hdmioutput::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputControllerListener>& /*hdmiOutputControllerListener*/, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputController>& /*hdmiOutputController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& /*hdmiOutputEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutputEventListener>& /*hdmiOutputEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
