#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/ICompositeInputController.h>
#include <com/rdk/hal/compositeinput/ICompositeInputControllerListener.h>
#include <com/rdk/hal/compositeinput/ICompositeInputEventListener.h>
#include <com/rdk/hal/compositeinput/Port.h>
#include <com/rdk/hal/compositeinput/PortCapabilities.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PortStatus.h>
#include <com/rdk/hal/compositeinput/PropertyKVPair.h>
#include <com/rdk/hal/compositeinput/State.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief     Composite Input Port HAL interface.
 *
 *            Provides control and monitoring for a single composite video input port.
 *            State lifecycle is managed via open() / close() on this interface and
 *            start() / stop() on the ICompositeInputController returned by open().
 *
 *            State transitions:
 *              CLOSED → (open) → OPENING → READY → (start) → STARTING → STARTED
 *              STARTED → (stop) → STOPPING → READY → (close) → CLOSING → CLOSED
 *
 *            If the client that opened the controller crashes, stop() and close()
 *            are implicitly called to perform cleanup.
 *
 *            Runtime state and telemetry metrics are both exposed as read-only
 *            PortProperty keys read via getProperty() / getPropertyMulti(). There
 *            is no separate metrics parcelable.
 *
 * @note Video scaling, positioning and aspect-ratio control are intentionally
 *       not exposed on this interface. Composite input video, once presented
 *       via ICompositeInputController.start(), is scaled and positioned by the display pipeline
 *       through the planecontrol HAL (package com.rdk.hal.planecontrol, see
 *       IPlaneControl and its Property enum: X, Y, WIDTH, HEIGHT, ASPECT_RATIO,
 *       OVERSCAN). Clients migrating from the legacy dsCompositeInScaleVideo()
 *       API should configure the video plane via IPlaneControl rather than
 *       looking for an equivalent method on this interface.
 *
 * @author    Gerald Weatherup
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified:
 * - Success: returns EX_NONE; all output parameters are valid.
 * - Failure: returns a service-specific exception; output parameters are undefined.
 */
class ICompositeInputPort : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputPort)
  static const int32_t VERSION = 3000;
  const std::string HASH = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  static constexpr char* HASHVALUE = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  // @aidl-doc
  /**
   * Gets the port ID.
   *
   * @param[out] _aidl_return Port ID for this port instance (0 to maxPorts-1).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getId(int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets port metadata.
   *
   * Returns constant human-readable metadata. Value does not change between calls.
   *
   * @param[out] _aidl_return Port parcelable containing port metadata.
   * @see Port
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the capabilities of this specific port.
   *
   * Returns constant port-specific capabilities. Value does not change between calls.
   *
   * @param[out] _aidl_return PortCapabilities parcelable.
   * @see PortCapabilities, ICompositeInputManager.getPlatformCapabilities()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current state of this port.
   *
   * @param[out] _aidl_return State enum value.
   * @see ICompositeInputEventListener.onStateChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current status of this port.
   *
   * Returns a polled snapshot of connection state, signal status, and detected
   * video mode. For async updates, register an ICompositeInputControllerListener
   * via open() (signal events) and/or an ICompositeInputEventListener via
   * registerEventListener() (lifecycle and property events).
   *
   * @param[out] _aidl_return PortStatus parcelable with current port state.
   * @see PortStatus, ICompositeInputControllerListener, ICompositeInputEventListener
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property value for this port.
   *
   * PortProperty keys identify both runtime status (e.g. SIGNAL_STRENGTH) and
   * telemetry metrics (e.g. METRIC_SIGNAL_DROPS). Supported keys are declared
   * by the platform in hfp-compositeinput.yaml under ports[].supportedProperties
   * and discoverable via PortCapabilities.supportedProperties.
   *
   * @param[in] property  Property key (from PortProperty enum).
   * @param[out] _aidl_return PropertyValue, or null if the property is unknown or unavailable.
   *
   * @see PortProperty, getPropertyMulti(), ICompositeInputController.setProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if property is not a valid enum value.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets multiple property values in a single call.
   *
   * Efficient batch read. If any property in the array is unknown,
   * EX_ILLEGAL_ARGUMENT is thrown and no values are returned.
   *
   * @param[in] properties  Array of PortProperty enum values to retrieve.
   * @param[out] _aidl_return Array of PropertyKVPair with keys and values populated;
   *                          same length and order as the input array.
   *
   * @see PropertyKVPair, getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if properties is empty or
   *                     contains an unknown PortProperty value.
   */
  virtual ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& properties, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens this composite input port for runtime control.
   *
   * On success the port transitions from CLOSED through OPENING to READY.
   * onStateChanged() is fired for each transition on any registered
   * ICompositeInputEventListener — register via registerEventListener()
   * before calling open() if you need to observe these transitions.
   *
   * ICompositeInputControllerListener.onConnectionChanged() always fires at
   * least once during the OPENING transition to report the current
   * connected/disconnected state before READY is reached.
   *
   * onSignalStatusChanged() is not fired during OPENING — it is guaranteed
   * during the STARTING transition (driven by ICompositeInputController.start())
   * to report the current signal state before STARTED is reached.
   *
   * The returned ICompositeInputController is used to start/stop the port
   * and mutate properties. If the client that opened the controller crashes,
   * stop() and close() are implicitly called.
   *
   * @param[in] listener  Listener for controller callbacks (connection,
   *                      signal status, video mode).
   * @param[out] _aidl_return ICompositeInputController, or null on failure.
   *
   * @see close(), ICompositeInputController, registerEventListener(), State
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if port is not in CLOSED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if listener is null.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& listener, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes this composite input port.
   *
   * The port must be in READY state. On success it transitions through
   * CLOSING to CLOSED. ICompositeInputEventListener.onStateChanged() is
   * fired for each transition on any registered event listener.
   *
   * @param[in] controller  The ICompositeInputController instance returned by open().
   * @param[out] _aidl_return Success flag indicating whether the port was closed.
   *   - true: Successfully closed.
   *   - false: The supplied controller is not the instance returned by open().
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if port is not in READY state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if controller is null.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& controller, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an event listener for this port.
   *
   * Multiple listeners may be registered. Callbacks are delivered asynchronously
   * via oneway binder calls. Registration does not require the port to be open.
   *
   * Event listeners receive state transition and property change notifications.
   * Real-time A/V signal events (connection, signal status, video mode) are
   * delivered exclusively to the ICompositeInputControllerListener passed into
   * open() — register an event listener before calling open() to observe the
   * CLOSED → OPENING → READY transitions.
   *
   * @param[in] listener  The event listener to register.
   *
   * @see ICompositeInputEventListener, unregisterEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if listener is null.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) = 0;
  // @aidl-doc
  /**
   * Unregisters a previously registered event listener.
   *
   * @param[in] listener  The event listener to unregister.
   *
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if listener is null or not registered.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& listener) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputPort

class ICompositeInputPortDefault : public ICompositeInputPort {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPortInfo(::com::rdk::hal::compositeinput::Port* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::compositeinput::PortCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::compositeinput::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getStatus(::com::rdk::hal::compositeinput::PortStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::compositeinput::PortProperty /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PortProperty>& /*properties*/, ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputEventListener>& /*listener*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputPortDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
