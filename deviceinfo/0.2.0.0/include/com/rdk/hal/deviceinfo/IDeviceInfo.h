#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/deviceinfo/Capabilities.h>
#include <com/rdk/hal/deviceinfo/Property.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
// @aidl-doc
/**
 *  @brief     Device Information HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Amit Patel
 *  @author    Milorad Neskovic
 *  @author    Tijo Thomas
 *  @author    Gerald Weatherup
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IDeviceInfo : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeviceInfo)
  static const int32_t VERSION = 2000;
  const std::string HASH = "e3b467c28f59222a54389289c945dfbcc51849a1";
  static constexpr char* HASHVALUE = "e3b467c28f59222a54389289c945dfbcc51849a1";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the capabilities of the Device Info service.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a persisted device property by key.
   *
   * On success, returns a `Property` parcelable (see Property.aidl).
   * @see `PropertyType.aidl` for supported formats and validation rules.
   *
   * Property key strings must be one of the keys listed in `getCapabilities().supportedProperties[]`.
   *
   * @param[in] propertyKey  The key of a property to retrieve.
   * @param[out] _aidl_return Property parcelable with metadata, or null if unsupported.
   *
   *
   * @see getCapabilities(), Property.aidl, PropertyType.aidl
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getProperty(const ::std::string& propertyKey, ::std::optional<::com::rdk::hal::deviceinfo::Property>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDeviceInfo

class IDeviceInfoDefault : public IDeviceInfo {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::deviceinfo::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(const ::std::string& /*propertyKey*/, ::std::optional<::com::rdk::hal::deviceinfo::Property>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDeviceInfoDefault
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
