#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/** @brief Defines error codes for audio decoder operations. */
enum class ErrorCode : int32_t {
  // @aidl-doc
  /** Operation completed successfully. */
  SUCCESS = 0,
  // @aidl-doc
  /** The buffer is full and cannot accept more data. */
  BUFFER_FULL = 1,
  // @aidl-doc
  /** The requested resource is invalid or unavailable. */
  INVALID_RESOURCE = 2,
  // @aidl-doc
  /** The specified codec is not supported or recognized. */
  INVALID_CODEC = 3,
  // @aidl-doc
  /** The operation has been deferred and will be retried later. */
  DEFERRED = 4,
  // @aidl-doc
  /** Memory allocation failed. */
  OUT_OF_MEMORY = 5,
  // @aidl-doc
  /** Operation attempted to access data out of valid bounds. */
  OUT_OF_BOUNDS = 6,
  // @aidl-doc
  /** Expected container is not empty when it should be. */
  NOT_EMPTY = 7,
  // @aidl-doc
  /** An invalid argument was passed to the function. */
  INVALID_ARGUMENT = 8,
};
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(ErrorCode val) {
  switch(val) {
  case ErrorCode::SUCCESS:
    return "SUCCESS";
  case ErrorCode::BUFFER_FULL:
    return "BUFFER_FULL";
  case ErrorCode::INVALID_RESOURCE:
    return "INVALID_RESOURCE";
  case ErrorCode::INVALID_CODEC:
    return "INVALID_CODEC";
  case ErrorCode::DEFERRED:
    return "DEFERRED";
  case ErrorCode::OUT_OF_MEMORY:
    return "OUT_OF_MEMORY";
  case ErrorCode::OUT_OF_BOUNDS:
    return "OUT_OF_BOUNDS";
  case ErrorCode::NOT_EMPTY:
    return "NOT_EMPTY";
  case ErrorCode::INVALID_ARGUMENT:
    return "INVALID_ARGUMENT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::ErrorCode, 9> enum_values<::com::rdk::hal::audiodecoder::ErrorCode> = {
  ::com::rdk::hal::audiodecoder::ErrorCode::SUCCESS,
  ::com::rdk::hal::audiodecoder::ErrorCode::BUFFER_FULL,
  ::com::rdk::hal::audiodecoder::ErrorCode::INVALID_RESOURCE,
  ::com::rdk::hal::audiodecoder::ErrorCode::INVALID_CODEC,
  ::com::rdk::hal::audiodecoder::ErrorCode::DEFERRED,
  ::com::rdk::hal::audiodecoder::ErrorCode::OUT_OF_MEMORY,
  ::com::rdk::hal::audiodecoder::ErrorCode::OUT_OF_BOUNDS,
  ::com::rdk::hal::audiodecoder::ErrorCode::NOT_EMPTY,
  ::com::rdk::hal::audiodecoder::ErrorCode::INVALID_ARGUMENT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
