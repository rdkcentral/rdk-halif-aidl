#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
// @aidl-doc
/** @brief Enum for property types in DeviceInfo HAL. */
enum class PropertyType : int8_t {
  // @aidl-doc
  /** Generic string value */
  STRING = 0,
  // @aidl-doc
  /** MAC address, format XX:XX:XX:XX:XX:XX, uppercase */
  MAC = 1,
  // @aidl-doc
  /** Numeric string, e.g., PIN codes */
  NUMERIC = 2,
  // @aidl-doc
  /** ISO 3166 country code, 2 characters */
  ISO3166 = 3,
  // @aidl-doc
  /** ISO 639 language code, 2 characters */
  ISO639 = 4,
  // @aidl-doc
  /** Uppercase hexadecimal string */
  UPPERCASEHEX = 5,
  // @aidl-doc
  /** Semantic version string, e.g., 1.0.0 */
  SEMANTICVERSION = 6,
};
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
[[nodiscard]] static inline std::string toString(PropertyType val) {
  switch(val) {
  case PropertyType::STRING:
    return "STRING";
  case PropertyType::MAC:
    return "MAC";
  case PropertyType::NUMERIC:
    return "NUMERIC";
  case PropertyType::ISO3166:
    return "ISO3166";
  case PropertyType::ISO639:
    return "ISO639";
  case PropertyType::UPPERCASEHEX:
    return "UPPERCASEHEX";
  case PropertyType::SEMANTICVERSION:
    return "SEMANTICVERSION";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::deviceinfo::PropertyType, 7> enum_values<::com::rdk::hal::deviceinfo::PropertyType> = {
  ::com::rdk::hal::deviceinfo::PropertyType::STRING,
  ::com::rdk::hal::deviceinfo::PropertyType::MAC,
  ::com::rdk::hal::deviceinfo::PropertyType::NUMERIC,
  ::com::rdk::hal::deviceinfo::PropertyType::ISO3166,
  ::com::rdk::hal::deviceinfo::PropertyType::ISO639,
  ::com::rdk::hal::deviceinfo::PropertyType::UPPERCASEHEX,
  ::com::rdk::hal::deviceinfo::PropertyType::SEMANTICVERSION,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
