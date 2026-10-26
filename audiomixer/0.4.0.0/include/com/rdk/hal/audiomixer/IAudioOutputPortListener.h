#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief     Listener interface for audio output port events.
 * Provides callbacks for changes in port connection state, supported formats,
 *            output format changes, state transitions, and feature support (e.g., Dolby Atmos).
 *            Registered by clients interested in monitoring real-time output port events.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
class IAudioOutputPortListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPortListener)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief     Called when a dynamic property value changes.
   * @details   Fires for any property whose value changes after the listener
   *            was registered. Common change sources:
   *            <ul>
   *              <li><b>CONNECTION_STATE</b> — physical hot-plug / hot-unplug
   *                  events (HDMI cable insert/remove, ARC/eARC negotiation,
   *                  Bluetooth A2DP connect/disconnect). The HAL fires this
   *                  callback whenever the underlying connection transitions
   *                  between any two ConnectionState values
   *                  (UNKNOWN / DISCONNECTED / CONNECTED / PENDING / FAULT).
   *                  Clients should not poll CONNECTION_STATE — register a
   *                  listener instead.</li>
   *              <li><b>OUTPUT_FORMAT</b> — when the active format changes
   *                  (e.g. AUTO mode resolves to a different codec after
   *                  EDID/CEC re-negotiation).</li>
   *              <li><b>VOLUME / MUTE</b> — when changed by another component
   *                  (e.g. system audio service adjusting per-port master).</li>
   *              <li><b>SUPPORTED_AUDIO_FORMATS / DOLBY_ATMOS_SUPPORT</b> —
   *                  when the connected sink's capability set changes
   *                  (e.g. different AVR plugged in, eARC handshake completes).</li>
   *            </ul>
   *
   *            On disconnect (CONNECTION_STATE → DISCONNECTED) any in-flight
   *            audio routed to this port is silently dropped. The port
   *            remains open from the controller's perspective; the HAL does
   *            not implicitly close it. Middleware should decide whether to
   *            re-route to another port, pause playback, or wait for re-plug.
   *
   * @param[in] property   The OutputPortProperty that changed.
   * @param[in] newValue   The new PropertyValue.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& newValue) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPortListener

class IAudioOutputPortListenerDefault : public IAudioOutputPortListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onPropertyChanged(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*newValue*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
