#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
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
 *  @brief     HDMI Input Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IHDMIInputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputController)
  static const int32_t VERSION = 2000;
  const std::string HASH = "b40c57ae7d1bc106df72be13a813813713acbae8";
  static constexpr char* HASHVALUE = "b40c57ae7d1bc106df72be13a813813713acbae8";
  // @aidl-doc
  /**
   * Gets the current connection state for a device attached to the HDMI input port.
   *
   * @param[out] _aidl_return boolean
   *   - true: A device is connected.
   *   - false: No device is connected.
   * @see IHDMIInputControllerListener.onConnectionStateChanged()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getConnectionState(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts the HDMI input.
   *
   * When started, video from the HDMI input port can be mapped to a video plane and the
   * associated audio can be mixed into the system audio path.
   *
   * The HDMI input must be in a `READY` state before it can be started.
   * If successful, the HDMI input transitions to a `STARTING` state and then to a `STARTED` state.
   *
   * During the `STARTING` state, the `IHDMIInputControllerListener.onSignalStateChanged()`
   * callback is always fired at least once to indicate the current HDMI signal state
   * (e.g. no signal, unstable, locked).
   *
   * When the HDMI input is in the `STARTED` state and a valid sink configuration is present,
   * the HPD line for the corresponding HDMI input port is asserted towards the source.
   *
   * @pre The resource must be in State::READY.
   *
   * @see stop(), IHDMIInput.open(), PlatformCapabilities.maximumConcurrentStartedPorts
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   *              Thrown if the resource is not in State::READY, or if starting this port would
   *              exceed the platform's maximumConcurrentStartedPorts limit as defined in
   *              PlatformCapabilities.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the HDMI input.
   *
   * The HDMI input must be in the `STARTED` state before it can be stopped.
   * If successful, the HDMI input transitions to a `STOPPING` state and then to a `READY` state.
   *
   * During the `STOPPING` state, the `IHDMIInputControllerListener.onSignalStateChanged()`
   * callback may be fired to indicate signal changes as the port is being stopped.
   *
   * @pre The resource must be in the `STARTED` state.
   *
   * @see start(), IHDMIInput.close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the `STARTED` state.
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Sets the EDID for the HDMI input port.
   *
   * The EDID defined in `edid` is set for the HDMI input port.
   * This function can only be called when the interface is open and in the `READY` state.
   *
   * The RDK middleware is responsible for providing an EDID that only reflects the
   * known capabilities of this HDMI input port.
   *
   * @param[in] edid  EDID data as a byte array. Must be valid and standards-compliant (typically 128 or 256 bytes).
   *
   * @param[out] _aidl_return boolean
   *   - true: The EDID was set successfully.
   *   - false: Indicates an error condition (e.g., resource not available, invalid state, or parameter
   *     validation failure).
   * @see getEDID(), getCapabilities()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   *              Thrown if the resource is not in State::READY
   */
  virtual ::android::binder::Status setEDID(const ::std::vector<uint8_t>& edid, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputController

class IHDMIInputControllerDefault : public IHDMIInputController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getConnectionState(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setEDID(const ::std::vector<uint8_t>& /*edid*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputControllerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
