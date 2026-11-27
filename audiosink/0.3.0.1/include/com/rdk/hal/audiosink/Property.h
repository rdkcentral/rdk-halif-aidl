#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Audio sink properties used in property get/set functions.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique 0 based index per audio sink resource instance.
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
   * dB reference level of the audio stream.
   * The default reference level for an audio sink session is -31dB.
   *
   * Type: Integer
   *  -31 is default on open
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  REFERENCE_LEVEL = 1,
  // @aidl-doc
  /**
   * The render output latency in nanoseconds.
   * This is the time from an audio frame being rendered from the queue to being output (HDMI/ARC/BT/internal
   * speakers).
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  RENDER_LATENCY_NS = 2,
  // @aidl-doc
  /**
   * The queue depth of the audio output path in nanoseconds.
   *
   * This value represents the total amount of audio data, measured in nanoseconds,
   * that is currently buffered and queued for playback in the audio output path.
   *
   * Type: Integer
   * Access: Read-only.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  QUEUE_DEPTH_NS = 3,
  // @aidl-doc
  /**
   * The index of the audio mixer that the audio sink is input to.
   *
   * Type: Integer
   *  0 is the default system mixer. (default on open)
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  MIXER_ID = 4,
  // @aidl-doc
  /**
   * Set by the client to specify the AV source of the stream.
   * The AVSource is also set inside the FrameMetadata when output by a decoder.
   *
   * Type: Integer
   *  0 - AVUNKNOWN (default on open)
   * @see enum com.rdk.hal.AVSource for possible values.
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  AV_SOURCE = 5,
  // @aidl-doc
  /**  */
  METRIC_xxxx = 1000,
};
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::REFERENCE_LEVEL:
    return "REFERENCE_LEVEL";
  case Property::RENDER_LATENCY_NS:
    return "RENDER_LATENCY_NS";
  case Property::QUEUE_DEPTH_NS:
    return "QUEUE_DEPTH_NS";
  case Property::MIXER_ID:
    return "MIXER_ID";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::METRIC_xxxx:
    return "METRIC_xxxx";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiosink::Property, 7> enum_values<::com::rdk::hal::audiosink::Property> = {
  ::com::rdk::hal::audiosink::Property::RESOURCE_ID,
  ::com::rdk::hal::audiosink::Property::REFERENCE_LEVEL,
  ::com::rdk::hal::audiosink::Property::RENDER_LATENCY_NS,
  ::com::rdk::hal::audiosink::Property::QUEUE_DEPTH_NS,
  ::com::rdk::hal::audiosink::Property::MIXER_ID,
  ::com::rdk::hal::audiosink::Property::AV_SOURCE,
  ::com::rdk::hal::audiosink::Property::METRIC_xxxx,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
