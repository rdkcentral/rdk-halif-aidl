#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/compositeinput/ICompositeInputPort.h>
#include <com/rdk/hal/compositeinput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
// @aidl-doc
/**
 * @brief Composite Input Manager interface.
 *
 * Provides platform-independent access to composite video input functionality.
 * This manager interface allows discovery and access to individual composite input ports.
 */
class ICompositeInputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(CompositeInputManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  static constexpr char* HASHVALUE = "4a4b778a630f5ef455e24d1488d4160d46a2789f";
  // @aidl-doc
  /** The service name to publish. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the platform capabilities for composite input.
   *
   * This function can be called at any time and returns platform-wide information
   * about supported features and properties. The returned value is constant and
   * must not change between calls.
   *
   * @param[out] _aidl_return PlatformCapabilities parcelable containing platform-wide capabilities.
   *
   * @see PlatformCapabilities
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the list of available composite input port IDs.
   *
   * Returns an array of valid port identifiers that can be used with getPort().
   * The array size matches PlatformCapabilities.maxPorts and is constant.
   *
   * @param[out] _aidl_return Array of port IDs available on this platform (typically 0 to maxPorts-1).
   *
   * @see getPort()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getPortIds(::std::vector<int32_t>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the interface for a specific composite input port.
   *
   * Returns a port-specific interface for controlling and querying an individual
   * composite input port. Each port can be independently controlled.
   *
   * @param[in] portId     The port ID to access. Must be one of the IDs returned by getPortIds().
   * @param[out] _aidl_return ICompositeInputPort interface for the requested port, or null if port not found.
   *
   *   - ICompositeInputPort: Valid port interface for the specified portId.
   *   - null: Port ID not found or invalid.
   * @pre portId must be valid (from getPortIds()).
   *
   * @see ICompositeInputPort, getPortIds()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if portId is out of range.
   */
  virtual ::android::binder::Status getPort(int32_t portId, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ICompositeInputManager

class ICompositeInputManagerDefault : public ICompositeInputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::compositeinput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPortIds(::std::vector<int32_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPort(int32_t /*portId*/, ::android::sp<::com::rdk::hal::compositeinput::ICompositeInputPort>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ICompositeInputManagerDefault
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
