#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutput.h>
#include <com/rdk/hal/hdmioutput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI Output Manager HAL interface.
 *
 *  Responsible for HDMI output resource discovery and platform-wide feature exposure.
 *  The manager serves as the entry point for clients to enumerate and obtain handles
 *  to HDMI output ports and retrieve static platform-level capabilities.
 *
 *  This interface must remain stable and query-safe regardless of runtime HDMI activity.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 *
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */
class IHDMIOutputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputManager)
  static const int32_t VERSION = 2000;
  const std::string HASH = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  static constexpr char* HASHVALUE = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  // @aidl-doc
  /**
   * The systemd/Binder service name for this HAL service.
   *
   * Returned by the implementation via `getServiceName()` and used for
   * registration and discovery in the AIDL Binder service manager.
   */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the static platform capabilities for HDMI outputs.
   *
   * This describes global support across all HDMI ports, such as max resolution,
   * HDR formats, and FreeSync tiers. The result is immutable and cached.
   *
   * This can be safely called before any HDMI output instance is opened.
   *
   * @param[out] _aidl_return PlatformCapabilities
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Enumerates available HDMI output IDs on the platform.
   *
   * This list provides the logical identifiers needed to call `getHDMIOutput()`.
   * Each returned ID is guaranteed to be valid unless the underlying resource
   * becomes unavailable (e.g., hot-removed HDMI transmitters in some systems).
   *
   * @param[out] _aidl_return IHDMIOutput.Id[]  Array of valid HDMI output identifiers.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Retrieves a HDMI output instance associated with a given ID.
   *
   * The returned interface represents a client-specific connection to a port.
   * The output must be explicitly opened using `IHDMIOutput.open()` before it
   * enters an active state. Multiple clients may query the same ID, but only
   * one may successfully open a session at a time.
   *
   * @param[in] hdmiOutputId  ID of the HDMI output to access.
   *
   * @param[out] _aidl_return IHDMIOutput
   *   - null: The ID was invalid or the resource is unavailable.
   * @see IHDMIOutput
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& hdmiOutputId, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputManager

class IHDMIOutputManagerDefault : public IHDMIOutputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& /*hdmiOutputId*/, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputManagerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
