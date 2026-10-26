#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmiinput/Capabilities.h>
#include <com/rdk/hal/hdmiinput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmiinput/HDCPStatus.h>
#include <com/rdk/hal/hdmiinput/HDMIVersion.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputController.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputControllerListener.h>
#include <com/rdk/hal/hdmiinput/IHDMIInputEventListener.h>
#include <com/rdk/hal/hdmiinput/Property.h>
#include <com/rdk/hal/hdmiinput/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDMI Input HAL interface for a single port.
 *  @see com.rdk.hal.hdmiinput.State - for state transitions
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IHDMIInput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInput)
  static const int32_t VERSION = 2000;
  const std::string HASH = "b40c57ae7d1bc106df72be13a813813713acbae8";
  static constexpr char* HASHVALUE = "b40c57ae7d1bc106df72be13a813813713acbae8";
  // @aidl-doc
  /** HDMI input resource ID type */
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmiinput.IHDMIInput.Id");
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
   * Gets the capabilities for this HDMI input port.
   *
   * This function can be called at any time and is not dependant on any HDMI input state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown or unavailable for this port.
   *
   *
   * @see Property
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::hdmiinput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current HDMI input state.
   *
   * @param[out] _aidl_return State enum value.
   *
   *
   * @see IHDMIInputEventListener.onStateChanged().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::hdmiinput::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current EDID set for the HDMI input port.
   *
   * If no EDID has been explicitly set via setEDID(), a default EDID is returned.
   * When multiple default EDID versions are supported (as listed in Capabilities.supportedVersions[]),
   * the latest supported default EDID version is returned.
   *
   * Spec Info : CTA 861 standards
   *
   * The EDID returned in `edid` is set for the HDMI input port.
   *
   * @param[out] edid     The EDID data.
   *
   * @param[out] _aidl_return boolean
   *   - true: The EDID was retrieved successfully.
   *   - false: Indicates an error condition (e.g., resource not available, invalid state, or parameter
   *     validation failure).
   * @see setEDID(), getDefaultEDID()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getEDID(::std::vector<uint8_t>* edid, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the default EDID for the HDMI input port for a given HDMI version.
   *
   * Spec Info : CTA 861 standards
   *
   * A default EDID is defined for each HDMIVersion listed as as supported in the
   * `Capabilities.supportedVersions[]`.
   *
   * The RDK middleware is expected to set an EDID based on the defined default
   * EDID for a port/version after feature modification.
   *
   * @param[in] version   The HDMI version to retrieve.
   * @param[out] edid     The EDID data.
   *
   * @param[out] _aidl_return boolean
   *   - true: The EDID was retrieved successfully.
   *   - false: The EDID was not available.
   * @see setEDID(), getCapabilities()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getDefaultEDID(::com::rdk::hal::hdmiinput::HDMIVersion version, ::std::vector<uint8_t>* edid, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current authenticated HDCP version which was negotiated with the HDMI source device (HDCP transmitter).
   *
   * If HDCP has not yet been authenticated then `HDCPProtocolVersion.UNDEFINED` is returned.
   *
   * @param[out] _aidl_return HDCPProtocolVersion
   *
   *
   * @see getHDCPStatus(), IHDMIInputControllerListener.onHDCPStatusChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmiinput::HDCPProtocolVersion* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the HDCP status.
   *
   * If HDCP is not in use, then `HDCPStatus.UNKNOWN` is returned.
   *
   * In case of persistent error (e.g., repeated authentication failure), client should close and re-open the session
   * to reset the state.
   *
   * @param[out] _aidl_return HDCPStatus
   *
   *
   * @see getHDCPCurrentVersion(), IHDMIInputControllerListener.onHDCPStatusChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmiinput::HDCPStatus* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the last received source product description (SPD) InfoFrame.
   *
   * For InfoFrame payload, starting with the InfoFrame type code. See HDMI Specification 2.0, Section 8.x for layout.
   *
   * @param[out] _aidl_return InfoFrame data byte array, or empty array if no InfoFrame has been received since last device connection
   *                     or start.
   *
   *
   * @see IHDMIInputControllerListener.onSPDInfoFrame()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getSPDInfoFrame(::std::vector<uint8_t>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the HDMI input port instance.
   *
   * If successful the HDMI input transitions to an `OPENING` state and then a `READY` state
   * which is notified to any registered `IHDMIInputEventListener` interfaces.
   *
   * Controller related callbacks are made through the `IHDMIInputControllerListener`
   * passed into the call.
   *
   * The `IHDMIInputControllerListener.onConnectionStateChanged()` callback is always fired during
   * the `OPENING` state to indicate the current connected/disconnected state.
   *
   * The returned `IHDMIInputController` interface is used to control the HDMI input port interface
   * including starting and stopping the port for display.
   *
   * The HAL holds the controller session for the lifetime of the owning client's
   * binder connection. On loss of that connection the HAL releases the session:
   * the port stops, the controller closes, and the resource returns to
   * `State::CLOSED`, where `open()` succeeds again.
   *
   * Once opened to a `READY` state the HDMI input port HPD line is unasserted and CEC remains inactive.
   *
   * @param[in] hdmiInputControllerListener    Listener object for controller callbacks.
   *
   * @param[out] _aidl_return IHDMIInputController, or null if the port cannot be opened (e.g. invalid state).
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see IHDMIInputController, close(), registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputControllerListener>& hdmiInputControllerListener, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the HDMI input.
   *
   * The HDMI input must be in a `READY` state before it can be closed.
   * If successful the HDMI input transitions to a `CLOSING` state and then a `CLOSED` state.
   * Then `onStateChanged(CLOSING, CLOSED)` will be notified on any registered event listener interfaces.
   *
   * The `hdmiInputController` parameter must be the same instance returned from the `open()` function
   * otherwise `false` is returned.
   *
   * @param[in] hdmiInputController     Instance of the IHDMIInputController.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or unrecognised parameter.
   * @pre The resource must be in State::READY.
   *
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>& hdmiInputController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a HDMI input event listener.
   *
   * Only one event listener may be registered per port at a time. Attempting to register a second listener will
   * return false.
   *
   * Registration delivers an initial `onStateChanged()` carrying the port's current
   * state in both `oldState` and `newState`. Before `open()` that state is `CLOSED`.
   *
   * @param[in] hdmiInputEventListener    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a HDMI input event listener.
   *
   * @param[in] hdmiInputEventListener    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInput

class IHDMIInputDefault : public IHDMIInput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmiinput::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::hdmiinput::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getEDID(::std::vector<uint8_t>* /*edid*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDefaultEDID(::com::rdk::hal::hdmiinput::HDMIVersion /*version*/, ::std::vector<uint8_t>* /*edid*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmiinput::HDCPProtocolVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmiinput::HDCPStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSPDInfoFrame(::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputControllerListener>& /*hdmiInputControllerListener*/, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>& /*hdmiInputController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& /*hdmiInputEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& /*hdmiInputEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
