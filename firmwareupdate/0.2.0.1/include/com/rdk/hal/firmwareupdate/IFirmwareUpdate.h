#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/firmwareupdate/IFirmwareUpdateListener.h>
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
 *  @brief     Firmware Update HAL interface definition.
 *
 *  The Firmware Update HAL manages the update lifecycle for multiple
 *  classes of firmware that live at various locations across the system
 *  (bootloader regions, application partitions, peripheral firmware blobs,
 *  vendor-specific images). The unifying concept is the update lifecycle,
 *  not the underlying storage medium.
 *
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
class IFirmwareUpdate : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FirmwareUpdate)
  static const int32_t VERSION = 2001;
  const std::string HASH = "dc1f5075772b5e571d1f3951ace6e320039c1406";
  static constexpr char* HASHVALUE = "dc1f5075772b5e571d1f3951ace6e320039c1406";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Updates a firmware image file onto the device.
   *
   * The image file may contain any firmware type supported by the platform,
   * including (but not limited to): application images, disaster-recovery
   * images, bootloaders, bootloader splash-screen images, and peripheral
   * firmware blobs. The target location for the firmware (boot region,
   * application partition, peripheral device, etc.) is platform-dependent
   * and is determined by examination of the image file contents.
   *
   * The `updateFirmwareFromFile()` function is non-blocking and requests the
   * firmware update operation in background.
   *
   * The progress of the update operation is provided in the
   * `IFirmwareUpdateListener` listener callbacks.
   *
   * Only one background firmware update operation is supported at any time.
   *
   * Image Validation Process:
   *
   * Before the update begins, the image file is validated through the following steps:
   *  - Checked for existence (ERROR_FILE_OPEN_FAIL if not found or cannot be opened).
   *  - Checked to be a valid firmware image file (ERROR_IMAGE_INVALID_TYPE if not recognised).
   *  - Signature verified if present in the image (ERROR_IMAGE_INVALID_SIGNATURE if verification fails).
   *  - Checked to be the correct size for the target firmware area (ERROR_IMAGE_INVALID_SIZE if too large).
   *  - Checked to be targeted at and compatible with the product (ERROR_IMAGE_INVALID_PRODUCT if incompatible).
   *
   * If any pre-update validation fails, the operation is aborted and onCompleted() is called
   * with the appropriate error code. No data is written to the target firmware location in this case.
   *
   * After the image is written, post-update validation is performed:
   *  - The written data is read back from the target firmware area and compared to the source image data
   *    (ERROR_FW_UPDATE_VERIFY_FAILED if data integrity check fails).
   *  - If a signature exists in the image, it is re-verified against the data read back
   *    (ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED if post-update signature verification fails).
   *
   * The post-update validation is a critical security step to ensure the integrity of the
   * written image and detect any corruption or tampering during the write process.
   *
   * The background update operation shall run at a priority which does not
   * impact foreground audio, video or graphics operations.
   *
   * Once the background firmware update operation has completed successfully, the new
   * image is flagged as the preferred chosen image when next loaded and run.
   *
   * @param[in] filename      Filename of the image.
   * @param[in] listener      IFirmwareUpdateListener instance for callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The firmware update request was started.
   *   - false: The firmware update request was not started because a firmware update
   *     operation is already in progress.
   * @see IFirmwareUpdateListener
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status updateFirmwareFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& listener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFirmwareUpdate

class IFirmwareUpdateDefault : public IFirmwareUpdate {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status updateFirmwareFromFile(const ::std::string& /*filename*/, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFirmwareUpdateDefault
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
