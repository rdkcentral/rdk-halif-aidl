#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/ActiveOutputFormat.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
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
  static const int32_t VERSION = 4010;
  const std::string HASH = "7e609bf4bacdb53162390a921c00b7f375537296";
  static constexpr char* HASHVALUE = "7e609bf4bacdb53162390a921c00b7f375537296";
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
   *              <li><b>OUTPUT_FORMAT</b> — when the configured value is
   *                  written, and, as in 0.3.0.0, when what it resolves to
   *                  changes (e.g. AUTO after EDID/CEC re-negotiation), with
   *                  the resolved format as newValue. The resolved case is
   *                  kept for clients built against 0.3.0.0 and is
   *                  deprecated: read onActiveOutputFormatChanged(), which
   *                  carries format, channel layout and Atmos together.</li>
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
  // @aidl-doc
  /**
   * @brief     Called when the audio this port is emitting changes.
   * @details   Fires once per change, with every field of the new state:
   *            a codec change at the source, a reconnect to a sink with a
   *            different capability set, an OUTPUT_FORMAT write, or Atmos
   *            starting or stopping in the content. Fires with null when
   *            the port stops emitting (see
   *            IAudioOutputPort.getActiveOutputFormat()).
   *
   * @param[in] activeOutputFormat  The new active format, or null.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onActiveOutputFormatChanged(const ::std::optional<::com::rdk::hal::audiomixer::ActiveOutputFormat>& activeOutputFormat) = 0;
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
  ::android::binder::Status onActiveOutputFormatChanged(const ::std::optional<::com::rdk::hal::audiomixer::ActiveOutputFormat>& /*activeOutputFormat*/) override {
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
