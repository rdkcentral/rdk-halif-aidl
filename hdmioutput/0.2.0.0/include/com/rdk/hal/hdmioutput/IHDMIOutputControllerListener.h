#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmioutput/HDCPStatus.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     Controller callbacks listener interface from HDMI output.
 *
 *  Receives controller-side notifications from the HDMI output subsystem regarding
 *  hotplug events, EDID acquisition, HDCP authentication, and frame rate transitions.
 *
 *  These events are generated from the HDMI controller and are always delivered
 *  on a one-way, async interface. The receiving client must respond in a non-blocking way.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class IHDMIOutputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputControllerListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  static constexpr char* HASHVALUE = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  // @aidl-doc
  /**
   * Device hotplug state changed event.
   *
   * This event reflects a change in the HDMI Hot Plug Detect (HPD) line state.
   *
   * - **ALWAYS** fired during the `OPENING` transition (CLOSED → READY), even if the
   *   HPD state has not changed, to communicate the initial sink connection state.
   * - **Only on actual HPD changes** during `READY`, `STARTING`, `STARTED`, and `STOPPING` states
   *   (i.e., when cable is physically connected/disconnected or sink is powered on/off).
   * - Debouncing is handled internally by the HAL; the state reported here is stable.
   *
   * @param[in] state  True if the HPD line is asserted (sink connected), false otherwise.
   *
   * @see IHDMIOutput.open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onHotPlugDetectStateChanged(bool state) = 0;
  // @aidl-doc
  /**
   * Frame rate changed event.
   *
   * Triggered after a new frame rate has been applied to the HDMI output.
   * This indicates that video mode configuration has completed and that
   * any display timing changes are now live.
   *
   * Must be fired only after AVMUTE is cleared — i.e., when content can be visible.
   * This is especially important for native frame rate matching in OTT applications.
   *
   * This callback is paired with client-facing logic such as `videoOutputStatusChanged`.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFrameRateChanged() = 0;
  // @aidl-doc
  /**
   * HDCP status change event.
   *
   * Notifies clients about changes to the HDCP authentication state or negotiated version.
   * May be triggered due to cable changes, EDID updates, power cycling, or key revocation.
   *
   * This callback is expected to cover all transitions: from unauthenticated to authenticated,
   * failure cases, or changes in protocol version (e.g., 1.x vs 2.x).
   *
   * @param[in] hdcpStatus           Current HDCP status of the output link.
   * @param[in] hdcpProtocolVersion  Protocol version negotiated with the sink.
   *
   * @see getHDCPStatus()
   * @see getHDCPCurrentVersion()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion hdcpProtocolVersion) = 0;
  // @aidl-doc
  /**
   * E-EDID read event.
   *
   * Fired when the full Extended EDID (E-EDID) block has been successfully retrieved
   * from the connected HDMI sink.
   *
   * - This event is guaranteed to fire after `onHotPlugDetectStateChanged(true)`
   *   if a valid and powered sink is detected.
   * - This provides full EDID blocks, not just the base 128-byte block.
   * - EDID may be used to extract sink capabilities, such as supported video formats,
   *   audio formats, HDR support, and vendor-specific extensions.
   *
   * @param[in] edid  Byte array representing the full E-EDID data as read from the sink.
   *
   * @pre HDMI output must be in `READY` or `STARTED` state.
   *
   * @see IHDMIOutput.open()
   * @see CTA-861 specification
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEDID(const ::std::vector<uint8_t>& edid) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputControllerListener

class IHDMIOutputControllerListenerDefault : public IHDMIOutputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onHotPlugDetectStateChanged(bool /*state*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFrameRateChanged() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus /*hdcpStatus*/, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion /*hdcpProtocolVersion*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEDID(const ::std::vector<uint8_t>& /*edid*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputControllerListenerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
