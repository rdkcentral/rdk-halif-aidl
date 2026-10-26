#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/firmwareupdate/FirmwareUpdateResult.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
// @aidl-doc
/**
 *  @brief     Firmware update listener callbacks interface definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IFirmwareUpdateListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FirmwareUpdateListener)
  static const int32_t VERSION = 2001;
  const std::string HASH = "dc1f5075772b5e571d1f3951ace6e320039c1406";
  static constexpr char* HASHVALUE = "dc1f5075772b5e571d1f3951ace6e320039c1406";
  // @aidl-doc
  /**
   * Callback which occurs during the background firmware update operation to provide progress reports.
   *
   * The `onProgress()` callback provides a percentage complete report.
   *
   * Progress Reporting Timeline:
   * - Pre-update validation (existence, type, signature, size, product compatibility) occurs first.
   * - After all pre-update validations are complete and as the firmware write is about to start,
   *   0% progress is reported.
   * - Progress callbacks continue as the image is written to the target firmware area.
   * - On success, 100% progress is reported after the firmware write completes and before
   *   post-update validation begins.
   * - Post-update validation (data integrity check and signature re-verification) occurs
   *   after 100% progress is reported.
   * - The `onCompleted()` callback is made after all validation is complete.
   *
   * @param[in] percentComplete   Percentage complete (0~100)
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onProgress(int32_t percentComplete) = 0;
  // @aidl-doc
  /**
   * Callback which occurs when the background firmware update operation has completed.
   *
   * On a successful update operation, the FirmwareUpdateResult::SUCCESS is returned, otherwise
   * an error result code is returned.
   *
   * The `report` parameter can be an empty string, but it is recommended that error result codes
   * provide additional details in this parameter which can be logged by the RDK middleware
   * for analysis.
   *
   * @param[in] result        Success or error FirmwareUpdateResult code.
   * @param[in] report        Optional string report to provide additional result details.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onCompleted(::com::rdk::hal::firmwareupdate::FirmwareUpdateResult result, const ::std::string& report) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFirmwareUpdateListener

class IFirmwareUpdateListenerDefault : public IFirmwareUpdateListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onProgress(int32_t /*percentComplete*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onCompleted(::com::rdk::hal::firmwareupdate::FirmwareUpdateResult /*result*/, const ::std::string& /*report*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFirmwareUpdateListenerDefault
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
