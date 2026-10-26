#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
// @aidl-doc
/** @brief HDMI CEC HAL property identifiers. */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * CEC version supported by the HAL and HW.
   *
   * A byte value representing the CEC version supported by the HW and SW HAL implementation.
   * The value complies with the encoding used by the [CEC Version] CEC operand described in the appropriate HDMI
   * specification.
   *
   * Please note that this value is NOT transmitted or obtained over the CEC bus. It is statically defined by the
   * implementation.
   *
   * Type: Byte - 8-bit integer value.
   * Access: Read-only.
   */
  HAL_CEC_VERSION = 0,
  // @aidl-doc
  /**
   * Returns the primary CEC device type configured for the physical device.
   * The value is one of the DeviceType enum values.
   *
   * Type: Int - 32-bit integer value.
   * Access: Read-only.
   */
  PRIMARY_DEVICE_TYPE = 1,
  // @aidl-doc
  /**
   * Returns the secondary CEC device type configured for the physical device,
   * or DeviceType::NONE when no secondary type is configured.
   *
   * Type: Int - 32-bit integer value.
   * Access: Read-only.
   */
  SECONDARY_DEVICE_TYPE = 2,
  // @aidl-doc
  /**
   * Returns the total number of Directed CEC messages sent since open.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * If this property is read in the CLOSED state it will report 0.
   *
   * Type: Int - 32-bit signed integer value.
   * Access: Read-only.
   *
   */
  METRIC_DIRECTED_MESSAGES_SENT = 1000,
  // @aidl-doc
  /**
   * Returns the number of Broadcast CEC messages sent since open.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * If this property is read in the CLOSED state it will report 0.
   *
   * Type: Int - 32-bit signed integer value.
   * Access: Read-only.
   *
   */
  METRIC_BROADCAST_MESSAGES_SENT = 1001,
  // @aidl-doc
  /**
   * Returns the total number of Directed CEC messages sent and acknowledged since open.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * If this property is read in the CLOSED state it will report 0.
   *
   * Type: Int - 32-bit signed integer value.
   * Access: Read-only.
   *
   */
  METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED = 1002,
  // @aidl-doc
  /**
   * Returns the total number of Broadcast CEC messages sent and acknowledged since open.
   * An acknowledgement implies a NACK in accordance with the inverted sense described in CEC specification.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * If this property is read in the CLOSED state it will report 0.
   *
   * Type: Int - 32-bit signed integer value.
   * Access: Read-only.
   *
   */
  METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED = 1003,
  // @aidl-doc
  /**
   * Returns the total number of arbitration failures since open.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * If this property is read in the CLOSED state it will report 0.
   *
   * Type: Int - 32-bit signed integer value.
   * Access: Read-only.
   *
   */
  METRIC_ARBITRATION_FAILURES = 1004,
};
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::HAL_CEC_VERSION:
    return "HAL_CEC_VERSION";
  case Property::PRIMARY_DEVICE_TYPE:
    return "PRIMARY_DEVICE_TYPE";
  case Property::SECONDARY_DEVICE_TYPE:
    return "SECONDARY_DEVICE_TYPE";
  case Property::METRIC_DIRECTED_MESSAGES_SENT:
    return "METRIC_DIRECTED_MESSAGES_SENT";
  case Property::METRIC_BROADCAST_MESSAGES_SENT:
    return "METRIC_BROADCAST_MESSAGES_SENT";
  case Property::METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED:
    return "METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED";
  case Property::METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED:
    return "METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED";
  case Property::METRIC_ARBITRATION_FAILURES:
    return "METRIC_ARBITRATION_FAILURES";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmicec::Property, 8> enum_values<::com::rdk::hal::hdmicec::Property> = {
  ::com::rdk::hal::hdmicec::Property::HAL_CEC_VERSION,
  ::com::rdk::hal::hdmicec::Property::PRIMARY_DEVICE_TYPE,
  ::com::rdk::hal::hdmicec::Property::SECONDARY_DEVICE_TYPE,
  ::com::rdk::hal::hdmicec::Property::METRIC_DIRECTED_MESSAGES_SENT,
  ::com::rdk::hal::hdmicec::Property::METRIC_BROADCAST_MESSAGES_SENT,
  ::com::rdk::hal::hdmicec::Property::METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED,
  ::com::rdk::hal::hdmicec::Property::METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED,
  ::com::rdk::hal::hdmicec::Property::METRIC_ARBITRATION_FAILURES,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
