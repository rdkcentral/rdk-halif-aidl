#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video decoder properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique ID per decoder resource instance.
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
   * Video decode buffer input queue size in bytes.
   * The default is set by the vendor to best suit the platform.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  INPUT_QUEUE_DEPTH = 1,
  // @aidl-doc
  /**
   * Number of frame buffers in the vendor frame buffer pool.
   * The default is vendor defined.
   *
   * Type: Integer
   * Access: Read-only
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   * .
   */
  OUTPUT_FRAME_POOL_SIZE = 2,
  // @aidl-doc
  /**
   * Low latency mode sets the expectation that no B-frames will be delivered in
   * the video stream or B-frames can be skipped over and the decoder should
   * output decoded frames as soon as possible.
   * Low latency video is often combined with low latency audio decoder/sink
   * operation for gaming and casting applications.
   * Can be set while video decoder resource is in READY.
   *
   * Type: Integer
   *  0 - off (default on open)
   *  1 - on
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  LOW_LATENCY_MODE = 4,
  // @aidl-doc
  /**
   * The policy to follow when video decode errors occur.
   *
   * Type: Integer
   *  0 - output corrupt frames (default on open)
   *  1 - conceal corrupt frames, not output from decoder
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  DECODE_ERROR_POLICY = 5,
  // @aidl-doc
  /**
   * Set by the client to specify the AV source of the stream.
   * The AVSource is also set inside the FrameMetadata when output by a decoder.
   *
   * Type: Integer
   *  0 - AVUNKNOWN (default on open)
   * @see enum AVSource for possible values.
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  AV_SOURCE = 6,
  // @aidl-doc
  /**
   * Set by the client to request SHA-1 calculation for the decoded video frame.
   * Scans pixel locations from the top left, along lines and down all rows.
   * The SHA-1 is returned in the frame metadata.
   *
   * Type: Integer
   *  0 - off (default on open)
   *  1 - on
   * Access: Read-write.
   * Write in states: READY, STARTED
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state or non STARTED state.
   *
   */
  SHA1_CALC = 7,
  // @aidl-doc
  /**
   * Indicates if the video decoder was opened for secure video path.
   *
   * Type: Integer
   *  0 - off
   *  1 - on (only if supported)
   * Access: Read-only.
   * @see Capabilities.supportsSecure IVideoDecoder.open()
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  SECURE_VIDEO = 8,
  // @aidl-doc
  /**
   * Count of decoded frames.
   * This metric is reset on open(), flush() and stop() calls.
   *
   * Type: Integer
   *  -1 means this metric is not yet implemented by the vendor.
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_FRAMES_DECODED = 1000,
  // @aidl-doc
  /**
   * Count of decode errors.
   * This metric is reset on open(), flush() and stop() calls.
   *
   * Type: Integer
   *  -1 means this metric is not yet implemented by the vendor.
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  METRIC_DECODE_ERRORS = 1001,
  // @aidl-doc
  /**
   * Count of frames dropped.
   * No frame was output due to corruption or decode error that could not
   * deliver a frame suitable for display.
   * This count includes any frames received before the first reference frame.
   * This metric is reset on open(), flush() and stop() calls.
   *
   * Type: Integer
   *  -1 means this metric is not yet implemented by the vendor.
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
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
constexpr inline std::array<::com::rdk::hal::videodecoder::Property, 11> enum_values<::com::rdk::hal::videodecoder::Property> = {
  ::com::rdk::hal::videodecoder::Property::RESOURCE_ID,
  ::com::rdk::hal::videodecoder::Property::INPUT_QUEUE_DEPTH,
  ::com::rdk::hal::videodecoder::Property::OUTPUT_FRAME_POOL_SIZE,
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
