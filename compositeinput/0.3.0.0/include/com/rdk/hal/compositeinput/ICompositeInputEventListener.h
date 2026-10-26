#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Event listener interface for composite input port observation.
 *
 * Provides asynchronous lifecycle and property callbacks for a composite
 * input port. Callbacks are delivered via oneway binder calls and do not
 * block the HAL service.
 *
 * This is the multi-client observation channel: any client (UI, diagnostics,
 * telemetry, system monitors) may register an event listener without needing
 * to own the controller. Real-time A/V signal events (connection, signal
 * status, video mode) are delivered on ICompositeInputControllerListener
 * instead, exclusively to the controller owner.
 *
 * Multiple listeners may be registered on the same port via
 * ICompositeInputPort.registerEventListener(). Register the listener before
 * calling open() if you need to observe the CLOSED → OPENING → READY
 * transitions.
 */
class ICompositeInputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputEventListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  static constexpr char* HASHVALUE = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  // @aidl-doc
  /**
   * Callback when the port has transitioned to a new state.
   *
   * Fired for all transitions driven by open(), close(), start(), and
   * stop() on any registered event listener.
   *
   * @param[in] oldState  The state that the port has transitioned from.
   * @param[in] newState  The new state that the port has transitioned to.
   *
   * @see State, ICompositeInputPort.getState()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::compositeinput::State oldState, ::com::rdk::hal::compositeinput::State newState) = 0;
  // @aidl-doc
  /**
   * Callback for property value changes.
   *
   * Fired when any runtime property or telemetry metric on this port
   * changes. Listeners receive the same PortProperty keys they would read
   * via ICompositeInputPort.getProperty(). Update frequency is
   * implementation-defined; typically bursty for status changes and
   * periodic (1–10 s) for metric counters during active monitoring.
   *
   * @param[in] property  The property key whose value changed.
   * @param[in] value     The new property value.
   *
   * @see PortProperty, ICompositeInputPort.getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onPropertyChanged(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputEventListener

class ICompositeInputEventListenerDefault : public ICompositeInputEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::compositeinput::State /*oldState*/, ::com::rdk::hal::compositeinput::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::compositeinput::PortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputEventListenerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
