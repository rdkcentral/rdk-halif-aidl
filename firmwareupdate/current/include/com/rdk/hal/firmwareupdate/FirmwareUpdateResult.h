#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
enum class FirmwareUpdateResult : int32_t {
  ERROR_GENERAL = -1,
  SUCCESS = 0,
  ERROR_FILE_OPEN_FAIL = 1,
  ERROR_IMAGE_INVALID_TYPE = 2,
  ERROR_IMAGE_INVALID_SIGNATURE = 3,
  ERROR_IMAGE_INVALID_SIZE = 4,
  ERROR_IMAGE_INVALID_PRODUCT = 5,
  ERROR_UPDATE_WRITE_FAILED = 6,
  ERROR_UPDATE_VERIFY_FAILED = 7,
  ERROR_UPDATE_VERIFY_SIGNATURE_FAILED = 8,
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
  case FirmwareUpdateResult::ERROR_UPDATE_WRITE_FAILED:
    return "ERROR_UPDATE_WRITE_FAILED";
  case FirmwareUpdateResult::ERROR_UPDATE_VERIFY_FAILED:
    return "ERROR_UPDATE_VERIFY_FAILED";
  case FirmwareUpdateResult::ERROR_UPDATE_VERIFY_SIGNATURE_FAILED:
    return "ERROR_UPDATE_VERIFY_SIGNATURE_FAILED";
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
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_UPDATE_WRITE_FAILED,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_UPDATE_VERIFY_FAILED,
  ::com::rdk::hal::firmwareupdate::FirmwareUpdateResult::ERROR_UPDATE_VERIFY_SIGNATURE_FAILED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
