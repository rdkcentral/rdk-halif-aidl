#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmioutput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmioutput/HDCPStatus.h>
#include <com/rdk/hal/hdmioutput/Property.h>
#include <com/rdk/hal/hdmioutput/PropertyKVPair.h>
#include <com/rdk/hal/hdmioutput/SPDInfoFrame.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI Output Controller HAL interface.
 *
 *  Provides lifecycle management and low-level control of HDMI signal generation.
 *  This interface is used after a successful `open()` to configure output parameters,
 *  initiate/stop signalling, and query HDCP state and InfoFrames.
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
class IHDMIOutputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputController)
  static const int32_t VERSION = 2000;
  const std::string HASH = "1ca5bda96fbbe2b88aac65291c41d4b17179a64b";
  static constexpr char* HASHVALUE = "1ca5bda96fbbe2b88aac65291c41d4b17179a64b";
  // @aidl-doc
  /**
   * Starts the HDMI output signal.
   *
   * This operation initiates signal transmission to the connected HDMI sink.
   * The output transitions from `READY` → `STARTING` → `STARTED`. In this state,
   * the port actively drives the HDMI signal, including video, audio, and InfoFrames.
   *
   * The `onHotPlugDetectStateChanged()` callback fires during this transition only
   * if the HPD line state changes (e.g., cable disconnect/reconnect during start).
   *
   * If `start()` is called when not in `READY`, an `EX_ILLEGAL_STATE` exception is thrown.
   *
   * @pre Must be in State::READY
   *
   * @see stop(), IHDMIOutput.open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE HDMI output is not in READY state.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the HDMI output signal.
   *
   * The output transitions from `STARTED` → `STOPPING` → `READY`. Video/audio output
   * is disabled, and downstream sinks receive an inactive signal. This allows the client
   * to reconfigure properties before restarting output.
   *
   * If `stop()` is called outside of the `STARTED` state, an `EX_ILLEGAL_STATE` is raised.
   *
   * @pre Must be in State::STARTED
   *
   * @see start(), IHDMIOutput.close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE HDMI output is not in STARTED state.
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Queries the current Hot Plug Detect (HPD) line state.
   *
   * This reflects whether a valid sink device is physically connected to the HDMI output.
   * HPD deassertion typically indicates cable disconnect or sink power loss.
   *
   * @param[out] _aidl_return boolean
   *   - true: HPD is asserted — sink is connected and powered.
   *   - false: HPD is deasserted — no active sink detected.
   * @see IHDMIOutputControllerListener.onHotPlugDetectStateChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHotPlugDetectState(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets a property on the HDMI output.
   *
   * Properties can be set in `READY` state (applied when `start()` is called) or
   * dynamically in `STARTED` state (applied immediately to the active signal).
   *
   * When applied in `STARTED` state, most properties update InfoFrames without disruption.
   * Properties requiring video mode changes (e.g., VIC) will assert/deassert AVMUTE
   * per HDMI specification, causing a brief display interruption.
   *
   * @param[in] property        Property key (@see Property).
   * @param[in] propertyValue   New value to apply.
   *
   * @param[out] _aidl_return boolean
   *   - true: Property accepted and applied or queued.
   *   - false: Invalid property key or value.
   * @pre Output must be in State::READY or State::STARTED.
   *
   * @see setPropertyMulti(), getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets multiple properties on the HDMI output.
   *
   * Same semantics as `setProperty()`, but applies a batch of key-value pairs.
   * Invalid keys or values result in the full operation failing (fail-fast).
   *
   * @param[in] propertyKVList  Array of property key-value pairs.
   *
   * @param[out] _aidl_return boolean
   *   - true: All properties were valid and applied.
   *   - false: At least one invalid property in the array.
   * @see setProperty(), getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& propertyKVList, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Retrieves the currently authenticated HDCP protocol version.
   *
   * This returns the actively negotiated and running HDCP version on the HDMI link.
   * This may differ from the sink's advertised capabilities (from EDID) due to:
   * - HDCP repeaters in the signal chain forcing version downgrade
   * - Authentication failures requiring fallback to lower version
   * - Content that does not require HDCP protection
   *
   * @param[out] _aidl_return HDCPProtocolVersion enum value.
   *   - HDCPProtocolVersion.UNDEFINED: No active HDCP session (unprotected content or authentication inactive).
   * @see getHDCPStatus(), getHDCPReceiverVersion(), onEDID()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Retrieves the HDCP protocol version reported by the sink.
   *
   * This returns the maximum HDCP version advertised by the connected sink device
   * as read from the sink's EDID or HDCP capability registers. This represents what
   * the sink is capable of, not what is currently active on the link.
   *
   * This may differ from `getHDCPCurrentVersion()` if HDCP repeaters, authentication
   * failures, or content requirements result in a lower version being negotiated.
   *
   * @param[out] _aidl_return HDCPProtocolVersion enum value.
   *   - HDCPProtocolVersion.UNDEFINED: Sink capabilities not yet known (HPD deasserted or EDID not read).
   * @see getHDCPStatus(), getHDCPCurrentVersion(), onEDID()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current HDCP status of the HDMI link.
   *
   * Indicates whether HDCP authentication has occurred and whether it succeeded.
   * Use this in combination with `getHDCPCurrentVersion()` to understand the full
   * HDCP authentication state.
   *
   * @param[out] _aidl_return HDCPStatus enum value indicating authentication state.
   *   - HDCPStatus.UNKNOWN: No sink present or HDCP state not yet determined.
   * @see getHDCPCurrentVersion(), getHDCPReceiverVersion(), onHDCPStatusChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the Source Product Description (SPD) InfoFrame payload.
   *
   * The InfoFrame is inserted into HDMI signalling when the output is active.
   * Passing null disables the SPD InfoFrame.
   *
   * The default behavior is to not transmit SPD unless explicitly configured.
   *
   * @param[in] spdInfoFrame    SPD metadata or null to disable.
   *
   * @pre Output must be in State::READY or State::STARTED.
   *
   * @see getSPDInfoFrame()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& spdInfoFrame) = 0;
  // @aidl-doc
  /**
   * Gets the current Source Product Description (SPD) InfoFrame payload.
   *
   * If SPD has not been set, returns null.
   *
   * @param[out] _aidl_return SPDInfoFrame
   *   - null: No SPD InfoFrame is currently configured.
   * @pre Output must be in State::READY or State::STARTED.
   *
   * @see setSPDInfoFrame()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputController

class IHDMIOutputControllerDefault : public IHDMIOutputController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHotPlugDetectState(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& /*spdInfoFrame*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputControllerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
