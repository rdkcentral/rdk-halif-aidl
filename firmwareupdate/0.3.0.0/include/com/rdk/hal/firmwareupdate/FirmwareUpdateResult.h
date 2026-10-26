#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
// @aidl-doc
/**
 *  @brief     Firmware update result codes enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class FirmwareUpdateResult : int32_t {
  // @aidl-doc
  /**
   * General error result code.
   * Additional details should be provided in the `onCompleted()` `report` string parameter.
   */
  ERROR_GENERAL = -1,
  // @aidl-doc
  /** Image was updated successfully. */
  SUCCESS = 0,
  // @aidl-doc
  /**
   * Failed to open input file.
   * The filename is invalid, the file does not exist or cannot be opened for reading.
   */
  ERROR_FILE_OPEN_FAIL = 1,
  // @aidl-doc
  /** The image cannot be recognised as a valid firmware image. */
  ERROR_IMAGE_INVALID_TYPE = 2,
  // @aidl-doc
  /**
   * The image signature failed verification during pre-update validation.
   * This error occurs during the initial validation phase before any data is written.
   */
  ERROR_IMAGE_INVALID_SIGNATURE = 3,
  // @aidl-doc
  /** Image size does not fit into the target firmware area. */
  ERROR_IMAGE_INVALID_SIZE = 4,
  // @aidl-doc
  /** Image is incompatible with this product. */
  ERROR_IMAGE_INVALID_PRODUCT = 5,
  // @aidl-doc
  /** Firmware write operation failed. */
  ERROR_FW_UPDATE_WRITE_FAILED = 6,
  // @aidl-doc
  /**
   * Read-back verify operation failed after writing.
   * This error indicates that data written to the target firmware area does not match the source
   * image data when read back for verification. This is a data integrity check performed after the
   * firmware write operation completes.
   */
  ERROR_FW_UPDATE_VERIFY_FAILED = 7,
  // @aidl-doc
  /**
   * Firmware image signature failed verification after writing.
   *
   * This error occurs during the post-update validation phase and indicates that the
   * signature verification of the image data read back from the target firmware area has failed.
   *
   * Implementation Requirements:
   * - This validation MUST be performed after the firmware write operation completes.
   * - The implementation MUST read the written image data back from the target firmware area.
   * - If a signature exists in the image, the implementation MUST verify it against
   *   the image data read back.
   * - This is a critical security validation step to ensure the integrity of the
   *   written image and detect any corruption or tampering that may have occurred
   *   during the write process.
   * - The signature verification algorithm and key management are platform-specific
   *   and should align with the platform's secure boot requirements.
   */
  ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED = 8,
};
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
[[nodiscard]] static inline std::string toString(FirmwareUpdateResult val) {
  switch(val) {
  case FirmwareUpdateResult::ERROR_GENERAL:
    return "ERROR_GENERAL";
  case FirmwareUpdateResult::SUCCESS:
    return "SUCCESS";
  case FirmwareUpdateResult::ERROR_FILE_OPEN_FAIL:
    return "ERROR_FILE_OPEN_FAIL";
  case FirmwareUpdateResult::ERROR_IMAGE_INVALID_TYPE:
    return "ERROR_IMAGE_INVALID_TYPE";
  case FirmwareUpdateResult::ERROR_IMAGE_INVALID_SIGNATURE:
    return "ERROR_IMAGE_INVALID_SIGNATURE";
  case FirmwareUpdateResult::ERROR_IMAGE_INVALID_SIZE:
    return "ERROR_IMAGE_INVALID_SIZE";
  case FirmwareUpdateResult::ERROR_IMAGE_INVALID_PRODUCT:
    return "ERROR_IMAGE_INVALID_PRODUCT";
  case FirmwareUpdateResult::ERROR_FW_UPDATE_WRITE_FAILED:
    return "ERROR_FW_UPDATE_WRITE_FAILED";
  case FirmwareUpdateResult::ERROR_FW_UPDATE_VERIFY_FAILED:
    return "ERROR_FW_UPDATE_VERIFY_FAILED";
  case FirmwareUpdateResult::ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED:
    return "ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::firmwareupdate::FirmwareUpdateResult, 10> enum_values<::com::rdk::hal::firmwareupdate::FirmwareUpdateResult> = {
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_GENERAL,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::SUCCESS,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_FILE_OPEN_FAIL,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_IMAGE_INVALID_TYPE,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_IMAGE_INVALID_SIGNATURE,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_IMAGE_INVALID_SIZE,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_IMAGE_INVALID_PRODUCT,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_FW_UPDATE_WRITE_FAILED,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_FW_UPDATE_VERIFY_FAILED,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_FW_UPDATE_VERIFY_SIGNATURE_FAILED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
