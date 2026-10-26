#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
// @aidl-doc
/**
 *  @brief     AV Clock properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique ID per AV Clock resource instance.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  RESOURCE_ID = 0,
  // @aidl-doc
  /**
   * Last measured A/V synchronisation accuracy in the session.
   *
   * This is the relative time of audio AFTER video.
   * It can be a negative value if audio is before video.
   * Only valid if audio and video decoders are defined in the sync group.
   *
   * This metric is reset on `open()` and `flush()` calls.
   *
   * Type: Integer
   *  -1 means this metric is not yet implemented by the vendor.
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_AV_SYNC_ACCURACY_MS = 1000,
  // @aidl-doc
  /**
   * Count of re-sync events to bring audio and video in lip sync.
   *
   * This metric is reset on `open()` and `flush()` calls.
   *
   * Type: Integer
   *  -1 means this metric is not yet implemented by the vendor.
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_AV_RESYNC_COUNT = 1001,
};
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace avclock {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::METRIC_AV_SYNC_ACCURACY_MS:
    return "METRIC_AV_SYNC_ACCURACY_MS";
  case Property::METRIC_AV_RESYNC_COUNT:
    return "METRIC_AV_RESYNC_COUNT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::avclock::Property, 3> enum_values<::com::rdk::hal::avclock::Property> = {
  ::com::rdk::hal::avclock::Property::RESOURCE_ID,
  ::com::rdk::hal::avclock::Property::METRIC_AV_SYNC_ACCURACY_MS,
  ::com::rdk::hal::avclock::Property::METRIC_AV_RESYNC_COUNT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
