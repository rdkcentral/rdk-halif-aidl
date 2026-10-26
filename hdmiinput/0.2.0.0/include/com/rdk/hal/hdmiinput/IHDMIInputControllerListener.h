#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmiinput/HDCPStatus.h>
#include <com/rdk/hal/hdmiinput/SignalState.h>
#include <com/rdk/hal/hdmiinput/VIC.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     Controller callbacks listener interface from HDMI input.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IHDMIInputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputControllerListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "b40c57ae7d1bc106df72be13a813813713acbae8";
  static constexpr char* HASHVALUE = "b40c57ae7d1bc106df72be13a813813713acbae8";
  // @aidl-doc
  /**
   * Device connection state event notification.
   *
   * Debouncing is performed by the HAL, ensuring a stable state before firing the event.
   * The event always fires to reflect the current state during the `OPENING` state transition,
   * and during a hot plug of an HDMI source device.
   *
   * @param[in] connectionState `true` if the device is connected, `false` otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onConnectionStateChanged(bool connectionState) = 0;
  // @aidl-doc
  /**
   * Always fires to reflect the current signal state during the `STARTING` state transition.
   *
   * @param[in] signalState   The signal state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState signalState) = 0;
  // @aidl-doc
  /**
   * Video ID code change notification.
   *
   * Fires to reflect a change in the video ID code from the HDMI source device,
   * and on every entry to `SignalState.LOCKED` after `start()` carrying the
   * current VIC.
   *
   * @param[in] vic       The VIC code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVIChanged(::com::rdk::hal::hdmiinput::VIC vic) = 0;
  // @aidl-doc
  /**
   * Variable refresh rate change notification.
   *
   * Fires to reflect a change in the VRR/FVA signalling from the source device
   * decoded from the received Video Timing Extended Metadata (VTEM), and on every
   * entry to `SignalState.LOCKED` after `start()` carrying the current VRR
   * signalling state.
   *
   * When the VTEM is no longer received (EM timeout condition) then this
   * callback fires with vrrActive=false, M_CONST=false, fastVActive=false, frameRate=0.0.
   *
   * The `frameRate` could vary on a frame by frame basis, but this callback shall not
   * fire at more than 2Hz.
   *
   * VRR is active when vrrActive=true. QMS is indicated by M_CONST=true. FVA is indicated by fastVActive=true. See
   * HDMI 2.1 Specification for definitions.
   *
   * @param[in] vrrActive     When true, VRR is active.
   * @param[in] M_CONST       When true, M_CONST VRR is active.
   * @param[in] fastVActive   When true, FVA is active.
   * @param[in] frameRate     The latest frame rate calculated while VRR is active.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVRRChanged(bool vrrActive, bool M_CONST, bool fastVActive, double frameRate) = 0;
  // @aidl-doc
  /**
   * Auxilliary Video Information (AVI) InfoFrame event.
   *
   * Spec Info : CTA 861 standards
   *
   * The event fires on first received InfoFrame after the HDMI input port is in
   * in a STARTED state, after a device connection or if the InfoFrame changes.
   *
   * @param[in] data  InfoFrame payload, starting with the InfoFrame type code. See HDMI Specification 2.0,
   * Section 8.x for layout.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * Audio InfoFrame event.
   *
   * Spec Info : CTA 861 standards
   *
   * The event fires on first received InfoFrame after the HDMI input port is in
   * in a STARTED state, after a device connection or if the InfoFrame changes.
   *
   * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * Source Product Description (SPD) InfoFrame event.
   *
   * Spec Info : CTA 861 standards
   *
   * The event fires on first received InfoFrame after the HDMI input port is in
   * in a STARTED state, after a device connection or if the InfoFrame changes.
   *
   * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * Dynamic Range and Mastering (DRM) InfoFrame event.
   *
   * Spec Info : CTA 861 standards
   *
   * The event fires on first received InfoFrame after the HDMI input port is in
   * in a STARTED state, after a device connection or if the InfoFrame changes.
   *
   * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * Vendor Specific InfoFrame (VSIF) event.
   *
   * Spec Info : CTA 861 standards
   *
   * The event fires on first received InfoFrame after the HDMI input port is in
   * in a STARTED state, after a device connection or if the InfoFrame changes.
   *
   * VSIF are unique only when the OUI is included in the data matching.
   * e.g. Dolby VSIF and HF-VSIF are delivered as separate InfoFrames.
   *
   * @param[in] data  Array of data bytes holding the InfoFrame, starting with InfoFrame type code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& data) = 0;
  // @aidl-doc
  /**
   * HDCP status change event with protocol version information.
   *
   * @param[in] hdcpStatus            The HDCP status.
   * @param[in] hdcpProtocolVersion   The HDCP protocol version.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion hdcpProtocolVersion) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputControllerListener

class IHDMIInputControllerListenerDefault : public IHDMIInputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onConnectionStateChanged(bool /*connectionState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSignalStateChanged(::com::rdk::hal::hdmiinput::SignalState /*signalState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVIChanged(::com::rdk::hal::hdmiinput::VIC /*vic*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVRRChanged(bool /*vrrActive*/, bool /*M_CONST*/, bool /*fastVActive*/, double /*frameRate*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAVIInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onSPDInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDRMInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVendorSpecificInfoFrame(const ::std::vector<uint8_t>& /*data*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onHDCPStatusChanged(::com::rdk::hal::hdmiinput::HDCPStatus /*hdcpStatus*/, ::com::rdk::hal::hdmiinput::HDCPProtocolVersion /*hdcpProtocolVersion*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputControllerListenerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
