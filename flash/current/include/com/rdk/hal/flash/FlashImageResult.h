#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace flash {
enum class FlashImageResult : int32_t {
  ERROR_GENERAL = -1,
  SUCCESS = 0,
  ERROR_FILE_OPEN_FAIL = 1,
  ERROR_IMAGE_INVALID_TYPE = 2,
  ERROR_IMAGE_INVALID_SIGNATURE = 3,
  ERROR_IMAGE_INVALID_SIZE = 4,
  ERROR_IMAGE_INVALID_PRODUCT = 5,
  ERROR_FLASH_WRITE_FAILED = 6,
  ERROR_FLASH_VERIFY_FAILED = 7,
  ERROR_FLASH_VERIFY_SIGNATURE_FAILED = 8,
};
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace flash {
[[nodiscard]] static inline std::string toString(FlashImageResult val) {
  switch(val) {
  case FlashImageResult::ERROR_GENERAL:
    return "ERROR_GENERAL";
  case FlashImageResult::SUCCESS:
    return "SUCCESS";
  case FlashImageResult::ERROR_FILE_OPEN_FAIL:
    return "ERROR_FILE_OPEN_FAIL";
  case FlashImageResult::ERROR_IMAGE_INVALID_TYPE:
    return "ERROR_IMAGE_INVALID_TYPE";
  case FlashImageResult::ERROR_IMAGE_INVALID_SIGNATURE:
    return "ERROR_IMAGE_INVALID_SIGNATURE";
  case FlashImageResult::ERROR_IMAGE_INVALID_SIZE:
    return "ERROR_IMAGE_INVALID_SIZE";
  case FlashImageResult::ERROR_IMAGE_INVALID_PRODUCT:
    return "ERROR_IMAGE_INVALID_PRODUCT";
  case FlashImageResult::ERROR_FLASH_WRITE_FAILED:
    return "ERROR_FLASH_WRITE_FAILED";
  case FlashImageResult::ERROR_FLASH_VERIFY_FAILED:
    return "ERROR_FLASH_VERIFY_FAILED";
  case FlashImageResult::ERROR_FLASH_VERIFY_SIGNATURE_FAILED:
    return "ERROR_FLASH_VERIFY_SIGNATURE_FAILED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace flash
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::flash::FlashImageResult, 10> enum_values<::com::rdk::hal::flash::FlashImageResult> = {
  ::com::rdk::hal::flash::FlashImageResult::ERROR_GENERAL,
  ::com::rdk::hal::flash::FlashImageResult::SUCCESS,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_FILE_OPEN_FAIL,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_IMAGE_INVALID_TYPE,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_IMAGE_INVALID_SIGNATURE,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_IMAGE_INVALID_SIZE,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_IMAGE_INVALID_PRODUCT,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_FLASH_WRITE_FAILED,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_FLASH_VERIFY_FAILED,
  ::com::rdk::hal::flash::FlashImageResult::ERROR_FLASH_VERIFY_SIGNATURE_FAILED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
