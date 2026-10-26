#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortController.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortControllerListener.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPortListener.h>
#include <com/rdk/hal/audiomixer/OutputPortCapabilities.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <com/rdk/hal/audiomixer/State.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief    Audio Output Port HAL interface.
 * @details  Per-port interface returned by IAudioMixer.getAudioOutputPort().
 *           Provides read access (capabilities, state, property reads) plus
 *           open()/close() to acquire an exclusive IAudioOutputPortController
 *           for property writes.
 *
 *           Lifecycle:
 *             CLOSED → (open) → OPENING → READY → (close) → CLOSING → CLOSED
 *
 *           If the client holding the controller crashes, the HAL implicitly
 *           calls close() to release the port.
 *
 *           Read access (getCapabilities, getProperty, getState, listener
 *           registration) does not require ownership and is available in any
 *           state. Property writes are gated on holding the controller — see
 *           IAudioOutputPortController.setProperty().
 *
 *           DAP and audio capture are exposed only via the port
 *           controller (not the read-side handle): see
 *           IAudioOutputPortController.getDolbyMs12_2_6_Dap() and
 *           IAudioOutputPortController.getAudioCapture(). Write-capable
 *           sub-interface acquisition is gated on the same exclusive-
 *           ownership boundary used for property writes.
 */
class IAudioOutputPort : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPort)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief    Returns this port's static and property capabilities.
   *
   *           Capabilities are immutable for the lifetime of the port.
   *
   * @param[out] _aidl_return OutputPortCapabilities describing this port.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Gets the current lifecycle state of this output port.
   * @details  Output ports use a subset of the shared State enum:
   *           CLOSED, OPENING, READY, CLOSING. Output ports do NOT enter
   *           STARTING / STARTED / STOPPING / FLUSHING — those values
   *           apply to the mixer instance lifecycle. Audio routing and
   *           emission to the port are driven by the mixer's start/stop;
   *           the port itself only tracks ownership of write access.
   *
   *           The OutputPortProperty.STATE read-only property mirrors this
   *           value for clients accessing it via getProperty().
   *
   * @param[out] _aidl_return Current State (CLOSED, OPENING, READY, or CLOSING).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::audiomixer::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Gets a property value from this port.
   *
   *           Property reads do not require ownership; they are available
   *           in any state. Property writability and write-state gating are
   *           handled via IAudioOutputPortController.setProperty().
   *
   * @param[in] property  Property key (from OutputPortProperty enum).
   * @param[out] _aidl_return Property value.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the property is not
   *                     supported by this port.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, ::com::rdk::hal::PropertyValue* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Opens this output port for exclusive property control.
   *
   *           On success the port transitions from CLOSED through OPENING
   *           to READY. The returned IAudioOutputPortController is used to
   *           write properties (volume, mute, output format, etc.).
   *
   *           Only one controller may exist per port at a time. If the
   *           client holding the controller crashes, the HAL implicitly
   *           calls close().
   *
   *           A second open() call on a port already held by another client
   *           throws EX_ILLEGAL_STATE — null is returned only for internal
   *           failures (resource allocation, vendor-specific init errors).
   *
   * @param[in] listener  Listener for controller callbacks (state transitions).
   * @param[out] _aidl_return IAudioOutputPortController on success; null on internal/init
   *                          failure (port stays in CLOSED state).
   *
   * @see close(), IAudioOutputPortController
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the port is not in CLOSED
   *                     state (i.e. another client already holds the controller).
   * @retval ::android::binder::Status::EX_NULL_POINTER if listener is null.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortControllerListener>& listener, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Closes this output port and releases the controller.
   *
   *           The port must be in READY state. On success the controller is
   *           invalidated and another client may open() the port.
   *
   * @param[in] controller  The controller instance returned by open().
   * @param[out] _aidl_return true on successful close, false if the supplied controller is
   *                          not the instance returned by open().
   *
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the port is not in READY state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if controller is null.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>& controller, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an audio output port event listener.
   *
   * An `IAudioOutputPortListener` can only be registered once and will
   * fail on subsequent registration attempts with the same instance.
   * Listener registration does not require ownership of the controller —
   * observers can attach without holding the IAudioOutputPortController.
   *
   * @param[in] audioOutputPortEventListener Listener object for callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   * @see IAudioOutputPortListener
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters an audio output port event listener.
   *
   * @param[in] audioOutputPortEventListener Listener object for callbacks.
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
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& audioOutputPortEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPort

class IAudioOutputPortDefault : public IAudioOutputPort {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::OutputPortCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::audiomixer::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, ::com::rdk::hal::PropertyValue* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*audioOutputPortEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPortListener>& /*audioOutputPortEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
