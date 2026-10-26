#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
// @aidl-doc
/**
 * @brief Video Sink properties definition.
 *
 * These properties are used to configure or query the state of a video sink resource.
 * Each property has a defined type and access mode (Read-only or Read/Write).
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique 0 based index per video sink resource instance.
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
   * The number of frames in the video sink that are queued for display.
   * This property must give a correct value in both tunnelled and non-tunnelled modes.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  SINK_QUEUE_DEPTH = 1,
  // @aidl-doc
  /**
   * Set by the client to specify the AV source of the stream.
   * The AVSource is also set inside the FrameMetadata when output by a decoder.
   * Default is 0 - AVUNKNOWN.
   * @see AVSource
   *
   * Type: Integer (enum AVSource)
   * Access: Read/Write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   *
   */
  AV_SOURCE = 2,
  // @aidl-doc
  /**
   * Specifies whether the first frame is rendered ahead of full playback.
   *
   * The AV Clock linked to the Video Sink can be in a playing or paused state.
   * If the first frame is ahead of the AV Clock time, it will display but subsequent
   * frames will not display until their presentation times match the AV Clock.
   *
   * Type: Boolean (0 = don't render, 1 = render)
   * Access: Read/Write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   *
   */
  RENDER_FIRST_FRAME = 3,
  // @aidl-doc
  /**
   * Count of frames received. Not necessarily displayed.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_RECEIVED = 1000,
  // @aidl-doc
  /**
   * Count of frames presented to the display.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_PRESENTED = 1001,
  // @aidl-doc
  /**
   * Count of frames dropped due to late delivery (missed presentation deadline).
   * Not relevant for graphics plane.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_DROPPED_LATE = 1002,
  // @aidl-doc
  /**
   * Count of frames dropped as part of frame rate conversion logic.
   * Not relevant for graphics plane.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_DROPPED_FRC = 1003,
  // @aidl-doc
  /**
   * Count of frames repeated due to frame rate conversion.
   * Not relevant for graphics plane.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_REPEATED_FRC = 1004,
  // @aidl-doc
  /**
   * Count of frames repeated because of missing input at expected presentation time.
   * Not relevant for graphics plane.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_REPEATED_MISSING_FRAME = 1005,
  // @aidl-doc
  /**
   * Count of underflow events due to empty frame queue at time of presentation.
   * Not relevant for graphics plane.
   * -1 means this metric is not yet implemented by the vendor.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_UNDERFLOWED = 1006,
};
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videosink {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::SINK_QUEUE_DEPTH:
    return "SINK_QUEUE_DEPTH";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::RENDER_FIRST_FRAME:
    return "RENDER_FIRST_FRAME";
  case Property::METRIC_FRAMES_RECEIVED:
    return "METRIC_FRAMES_RECEIVED";
  case Property::METRIC_FRAMES_PRESENTED:
    return "METRIC_FRAMES_PRESENTED";
  case Property::METRIC_FRAMES_DROPPED_LATE:
    return "METRIC_FRAMES_DROPPED_LATE";
  case Property::METRIC_FRAMES_DROPPED_FRC:
    return "METRIC_FRAMES_DROPPED_FRC";
  case Property::METRIC_FRAMES_REPEATED_FRC:
    return "METRIC_FRAMES_REPEATED_FRC";
  case Property::METRIC_FRAMES_REPEATED_MISSING_FRAME:
    return "METRIC_FRAMES_REPEATED_MISSING_FRAME";
  case Property::METRIC_UNDERFLOWED:
    return "METRIC_UNDERFLOWED";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::videosink::Property, 11> enum_values<::com::rdk::hal::videosink::Property> = {
  ::com::rdk::hal::videosink::Property::RESOURCE_ID,
  ::com::rdk::hal::videosink::Property::SINK_QUEUE_DEPTH,
  ::com::rdk::hal::videosink::Property::AV_SOURCE,
  ::com::rdk::hal::videosink::Property::RENDER_FIRST_FRAME,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_RECEIVED,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_PRESENTED,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_DROPPED_LATE,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_DROPPED_FRC,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_REPEATED_FRC,
  ::com::rdk::hal::videosink::Property::METRIC_FRAMES_REPEATED_MISSING_FRAME,
  ::com::rdk::hal::videosink::Property::METRIC_UNDERFLOWED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
