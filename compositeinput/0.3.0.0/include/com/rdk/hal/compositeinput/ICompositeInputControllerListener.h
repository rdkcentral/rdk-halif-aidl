#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/SignalStatus.h>
#include <com/rdk/hal/compositeinput/VideoResolution.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief     Controller callback listener interface for composite input.
 *
 *            Passed into ICompositeInputPort.open(). Delivers real-time A/V
 *            signal events to the exclusive controller owner: connection
 *            detection, signal status, and video mode changes.
 *
 *            State transition events (onStateChanged) are delivered on
 *            ICompositeInputEventListener instead — any observer (including
 *            the controller owner) may register an event listener to observe
 *            port lifecycle without needing exclusive ownership.
 *
 *            All callbacks are oneway (non-blocking, fire-and-forget).
 *
 * @author    Gerald Weatherup
 */
class ICompositeInputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  static constexpr char* HASHVALUE = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  // @aidl-doc
  /**
   * Called when the port connection state changes.
   *
   * Fired by hardware detection of cable presence. Indicates physical
   * connection only, not signal validity.
   *
   * Always fires at least once during the OPENING transition to report
   * the current connected/disconnected state before READY is reached.
   *
   * @param[in] connected  True if a cable is now connected, false if disconnected.
   *
   * @see ICompositeInputPort.getStatus()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onConnectionChanged(bool connected) = 0;
  // @aidl-doc
  /**
   * Called when the composite input signal status changes.
   *
   * Fired for transitions between signal states
   * (e.g. NO_SIGNAL → UNSTABLE → STABLE).
   *
   * Always fires at least once during the STARTING transition to report
   * the current signal state before STARTED is reached.
   *
   * @param[in] signalStatus  The new signal status.
   *
   * @see SignalStatus, ICompositeInputPort.getStatus()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus signalStatus) = 0;
  // @aidl-doc
  /**
   * Called when the detected video mode changes.
   *
   * Fired when the digitized resolution, format, or frame rate changes —
   * typically after initial signal stabilization or when the source device
   * switches video modes.
   *
   * @param[in] resolution  The newly detected video resolution and format.
   *
   * @see VideoResolution, ICompositeInputPort.getStatus()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& resolution) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputControllerListener

class ICompositeInputControllerListenerDefault : public ICompositeInputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onConnectionChanged(bool /*connected*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSignalStatusChanged(::com::rdk::hal::compositeinput::SignalStatus /*signalStatus*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoModeChanged(const ::com::rdk::hal::compositeinput::VideoResolution& /*resolution*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputControllerListenerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
