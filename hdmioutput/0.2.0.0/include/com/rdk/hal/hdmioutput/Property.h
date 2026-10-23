#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI output properties used in get/set functions.
 *
 *  These enumerated keys are used in property-based APIs such as `getProperty()`,
 *  `setProperty()`, and their multi-property equivalents.
 *
 *  Each key maps to a defined type and access model, and represents a field within
 *  the HDMI AVI InfoFrame or device-specific runtime metadata.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique ID for the HDMI output resource instance.
   *
   * Type: Integer
   * Access: Read-only.
   */
  RESOURCE_ID = 0,
  // @aidl-doc
  /**
   * Video Identification Code (VIC).
   * Controls resolution, refresh rate, and format for the HDMI output.
   * Maps to AVI InfoFrame VIC[0..7].
   *
   * When changed in STARTED state, AVMUTE is asserted/deasserted per HDMI specification,
   * causing a brief display interruption.
   *
   * Type: Integer — enum VIC
   * Default: VIC.VIC0_UNAVAILABLE
   * Access: Read-write.
   */
  VIC = 1,
  // @aidl-doc
  /**
   * Content type as defined by CTA-861.
   * Maps to AVI InfoFrame ITC and CN[0..1].
   *
   * Type: Integer — enum ContentType
   * Default: ContentType.UNSPECIFIED on open()
   * Access: Read-write.
   */
  CONTENT_TYPE = 2,
  // @aidl-doc
  /**
   * Active Format Description — used to signal aspect ratio of active area.
   * Maps to AVI InfoFrame A0 and R[0..3].
   *
   * Type: Integer — enum AFD
   * Default: AFD.UNSPECIFIED on open()
   * Access: Read-write.
   */
  AFD = 3,
  // @aidl-doc
  /**
   * HDR output signalling mode.
   *
   * Allows selection of a fixed output HDR mode, where incoming video will be tone-mapped
   * or converted to the configured dynamic range as needed.
   *
   * Type: Integer — enum HDROutputMode
   * Default: HDROutputMode.AUTO on open()
   * Access: Read-write.
   */
  HDR_OUTPUT_MODE = 4,
  // @aidl-doc
  /**
   * Scan information metadata for the AVI InfoFrame.
   * Indicates whether the output content is composed for overscanned or underscanned display.
   * Maps to AVI InfoFrame S[0..1].
   *
   * Type: Integer — enum ScanInformation
   * Default: ScanInformation.NO_DATA on open()
   * Access: Read-write.
   */
  SCAN_INFORMATION = 5,
  // @aidl-doc
  /**
   * Placeholder vendor-specific metric.
   *
   * Tracks a debug or QoS-related count value, reset on `open()`.
   * A value of `-1` indicates the metric is not implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   */
  METRIC_xxx = 1000,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::VIC:
    return "VIC";
  case Property::CONTENT_TYPE:
    return "CONTENT_TYPE";
  case Property::AFD:
    return "AFD";
  case Property::HDR_OUTPUT_MODE:
    return "HDR_OUTPUT_MODE";
  case Property::SCAN_INFORMATION:
    return "SCAN_INFORMATION";
  case Property::METRIC_xxx:
    return "METRIC_xxx";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::hdmioutput::Property, 7> enum_values<::com::rdk::hal::hdmioutput::Property> = {
  ::com::rdk::hal::hdmioutput::Property::RESOURCE_ID,
  ::com::rdk::hal::hdmioutput::Property::VIC,
  ::com::rdk::hal::hdmioutput::Property::CONTENT_TYPE,
  ::com::rdk::hal::hdmioutput::Property::AFD,
  ::com::rdk::hal::hdmioutput::Property::HDR_OUTPUT_MODE,
  ::com::rdk::hal::hdmioutput::Property::SCAN_INFORMATION,
  ::com::rdk::hal::hdmioutput::Property::METRIC_xxx,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
