#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/bootreason/BootCause.h>
#include <com/rdk/hal/bootreason/Capabilities.h>
#include <com/rdk/hal/bootreason/PowerSource.h>
#include <com/rdk/hal/bootreason/ResetType.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
// @aidl-doc
/**
 *  @brief     Boot Reason HAL interface.
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
class IBootReason : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BootReason)
  static const int32_t VERSION = 2000;
  const std::string HASH = "de5227a84a66a5cdace02359b26bf83ff8671f75";
  static constexpr char* HASHVALUE = "de5227a84a66a5cdace02359b26bf83ff8671f75";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the capabilities of the boot service.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the reason the device was booted.
   *
   * @param[out] _aidl_return BootCause
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the reboot reason that will be associated with the next reboot.
   * This function is used for validation testing the retrieval method of various boot
   * scenarios.
   *
   * @param[in] cause           BootCause value.
   * @param[in] reasonString    Free-form reboot reason string (64 bytes)
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause cause, const ::std::string& reasonString) = 0;
  // @aidl-doc
  /**
   * Performs a shutdown and warm reboot of the device.
   *
   * A number of reset types can be applied as part of the reboot process.
   * On success this function does not return.
   *
   * @param[in] resetType     ResetType value
   * @param[in] reasonString  Free-form reset reason string (64 bytes)
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType resetType, const ::std::string& reasonString) = 0;
  // @aidl-doc
  /**
   * Gets the device power source.
   *
   * @param[out] _aidl_return PowerSource
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBootReason

class IBootReasonDefault : public IBootReason {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::bootreason::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getBootCause(::com::rdk::hal::bootreason::BootCause* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setBootCause(::com::rdk::hal::bootreason::BootCause /*cause*/, const ::std::string& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status reboot(::com::rdk::hal::bootreason::ResetType /*resetType*/, const ::std::string& /*reasonString*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPowerSource(::com::rdk::hal::bootreason::PowerSource* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBootReasonDefault
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
