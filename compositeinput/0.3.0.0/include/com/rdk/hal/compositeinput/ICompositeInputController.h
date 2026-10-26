#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/compositeinput/PortProperty.h>
#include <com/rdk/hal/compositeinput/PropertyKVPair.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief     Composite Input Controller HAL interface.
 *
 *            Returned by ICompositeInputPort.open(). Provides exclusive write
 *            control over a composite input port: lifecycle (start/stop),
 *            property mutation, and metrics reset. All state-mutating operations
 *            are gated on the port being in the correct State.
 *
 *            If the client that opened this controller crashes, stop() and
 *            close() are implicitly called to perform cleanup.
 *
 * @author    Gerald Weatherup
 *
 * <h3>Exception Handling</h3>
 * Unless otherwise specified:
 * - Success: returns EX_NONE; all output parameters are valid.
 * - Failure: returns a service-specific exception; output parameters are undefined.
 */
class ICompositeInputController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputController)
  static const int32_t VERSION = 3000;
  const std::string HASH = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  static constexpr char* HASHVALUE = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  // @aidl-doc
  /**
   * Starts the composite input port.
   *
   * The port must be in READY state. On success it transitions through
   * STARTING to STARTED. During STARTING, onSignalStatusChanged() is always
   * fired at least once on the ICompositeInputControllerListener to indicate
   * the current signal state.
   *
   * Only one port may be in STARTED state at a time unless the platform
   * declares maximumConcurrentStartedPorts > 1 in PlatformCapabilities.
   *
   * @see stop(), ICompositeInputPort.open(), PlatformCapabilities.maximumConcurrentStartedPorts
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not in READY state, or if
   *                     starting this port would exceed maximumConcurrentStartedPorts.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the composite input port.
   *
   * The port must be in STARTED state. On success it transitions through
   * STOPPING to READY state.
   *
   * @see start(), ICompositeInputPort.close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not in STARTED state.
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Sets a property value for this port.
   *
   * The key must be one of the PortProperty enum values declared by the
   * platform in its HFP under ports[].supportedProperties. Read-only keys
   * (PropertyMetadata.readOnly == true) throw EX_UNSUPPORTED_OPERATION.
   *
   * @param[in] property   Property key (from PortProperty enum).
   * @param[in] value      Property value; union field must match PropertyMetadata.type.
   *
   * @see ICompositeInputPort.getProperty(), setPropertyMulti()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if property is unknown or
   *                     value type does not match.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if property is read-only.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) = 0;
  // @aidl-doc
  /**
   * Sets multiple property values atomically.
   *
   * All entries are validated before any are applied. If any entry is invalid
   * the entire call fails and no properties are changed.
   *
   * @param[in] properties  Array of PropertyKVPair with keys and values to set.
   *
   * @see setProperty(), ICompositeInputPort.getPropertyMulti()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if any entry is invalid or
   *                     contains a type mismatch.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if any property is read-only.
   */
  virtual ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& properties) = 0;
  // @aidl-doc
  /**
   * Resets telemetry metric counters for this port.
   *
   * Clears all accumulated METRIC_* values on this port back to their initial
   * state, and updates METRIC_LAST_RESET_TIMESTAMP to the current wall-clock time.
   *
   * @see PortProperty, ICompositeInputPort.getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if port is not in STARTED state.
   */
  virtual ::android::binder::Status resetMetrics() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputController

class ICompositeInputControllerDefault : public ICompositeInputController {
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
  ::android::binder::Status setProperty(::com::rdk::hal::compositeinput::PortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& /*properties*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status resetMetrics() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputControllerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
