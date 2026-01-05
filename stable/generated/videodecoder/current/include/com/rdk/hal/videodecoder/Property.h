#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
enum class Property : int32_t {
  RESOURCE_ID = 0,
  INPUT_QUEUE_DEPTH = 1,
  OUTPUT_FRAME_POOL_SIZE = 2,
  OPERATIONAL_MODE = 3,
  LOW_LATENCY_MODE = 4,
  DECODE_ERROR_POLICY = 5,
  AV_SOURCE = 6,
  SHA1_CALC = 7,
  SECURE_VIDEO = 8,
  METRIC_FRAMES_DECODED = 1000,
  METRIC_DECODE_ERRORS = 1001,
  METRIC_FRAMES_DROPPED = 1002,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::INPUT_QUEUE_DEPTH:
    return "INPUT_QUEUE_DEPTH";
  case Property::OUTPUT_FRAME_POOL_SIZE:
    return "OUTPUT_FRAME_POOL_SIZE";
  case Property::OPERATIONAL_MODE:
    return "OPERATIONAL_MODE";
  case Property::LOW_LATENCY_MODE:
    return "LOW_LATENCY_MODE";
  case Property::DECODE_ERROR_POLICY:
    return "DECODE_ERROR_POLICY";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::SHA1_CALC:
    return "SHA1_CALC";
  case Property::SECURE_VIDEO:
    return "SECURE_VIDEO";
  case Property::METRIC_FRAMES_DECODED:
    return "METRIC_FRAMES_DECODED";
  case Property::METRIC_DECODE_ERRORS:
    return "METRIC_DECODE_ERRORS";
  case Property::METRIC_FRAMES_DROPPED:
    return "METRIC_FRAMES_DROPPED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videodecoder::Property, 12> enum_values<::com::rdk::hal::videodecoder::Property> = {
  ::com::rdk::hal::videodecoder::Property::RESOURCE_ID,
  ::com::rdk::hal::videodecoder::Property::INPUT_QUEUE_DEPTH,
  ::com::rdk::hal::videodecoder::Property::OUTPUT_FRAME_POOL_SIZE,
  ::com::rdk::hal::videodecoder::Property::OPERATIONAL_MODE,
  ::com::rdk::hal::videodecoder::Property::LOW_LATENCY_MODE,
  ::com::rdk::hal::videodecoder::Property::DECODE_ERROR_POLICY,
  ::com::rdk::hal::videodecoder::Property::AV_SOURCE,
  ::com::rdk::hal::videodecoder::Property::SHA1_CALC,
  ::com::rdk::hal::videodecoder::Property::SECURE_VIDEO,
  ::com::rdk::hal::videodecoder::Property::METRIC_FRAMES_DECODED,
  ::com::rdk::hal::videodecoder::Property::METRIC_DECODE_ERRORS,
  ::com::rdk::hal::videodecoder::Property::METRIC_FRAMES_DROPPED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
