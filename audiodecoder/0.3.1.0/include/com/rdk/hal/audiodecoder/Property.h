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
/**
 * @brief	Audio decoder properties used in property get/set functions.
 * 			All properties can be read in any state.
 * @author	Luc Kennedy-Lamb
 * @author	Peter Stieglitz
 * @author	Douglas Adler
 */
enum class Property : int32_t {
  // @aidl-doc
  /**
   * Unique ID of the audio decoder resource instance.
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
   * Controls the low latency mode.
   * The low latency mode is also set inside the FrameMetadata when output by a decoder.
   *
   * Type: Integer
   *  0 - off (default on open)
   *  1 - on (only if supported)
   * Access: Read-write.
   * Write in states: READY
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  LOW_LATENCY_MODE = 1,
  // @aidl-doc
  /**
   * Set by the client to specify the AV source of the stream.
   *
   * The AVSource is also set inside the FrameMetadata when output by a decoder.
   * Type: Integer
   *  Default is 0 - AVSource::UNKNOWN.
   * Access: Read-write.
   * Write in states: READY
   * @see enum AVSource for possible values.
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_ILLEGAL_STATE if try to modify in non READY state.
   *
   */
  AV_SOURCE = 3,
  // @aidl-doc
  /**
   * Indicates if the audio decoder was opened for secure audio path.
   *
   * Type: Integer
   *  0 - off
   *  1 - on (only if supported)
   * Access: Read-only.
   * @see Capabilities.supportsSecure IAudioDecoder.open()
   *
   * @exception binder::Status::Exception::EX_NONE for success
   * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION if try to modify Read-only property.
   *
   */
  SECURE_AUDIO = 4,
  // @aidl-doc
  /**
   * Dolby AC-4 audio presentation group index.
   *
   * Type: Integer
   *  -1 - automatic selection by language and associated type. (default)
   *  0..n - AC-4 presentation group index.
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_PRESENTATION_GROUP_INDEX = 200,
  // @aidl-doc
  /**
   * Dolby AC-4 audio primary preferred language.
   *
   * Type: String
   *  "" - no override, selection should use the user preference set in audio mixer. (default)
   *  Otherwise the string should be a 3 letter language code from ISO 639.
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_PREFERRED_LANG1 = 201,
  // @aidl-doc
  /**
   * Dolby AC-4 audio secondary preferred language.
   *
   * Type: String
   *  "" - no override, selection should use the user preference set in audio mixer. (default)
   *  Otherwise the string should be a 3 letter language code from ISO 639.
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_PREFERRED_LANG2 = 202,
  // @aidl-doc
  /**
   * Dolby AC-4 audio associated audio stream type.
   *
   * Type: Integer
   *  -1 - no override, selection should use the user preference set in audio mixer. (default)
   *  0 - visually impaired
   *  1 - hearing impaired
   *  2 - commentary
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_ASSOCIATED_TYPE = 203,
  // @aidl-doc
  /**
   * Dolby AC-4 audio automatic presentation group selection priority.
   *
   * Type: Integer
   *  -1 - no override, selection should use the user preference set in audio mixer. (default)
   *  0 - language - Prioritize preferred language in the automatic selection of the presentation group.
   *  1 - associated type - Prioritize the preferred associated type in the automatic selection of the presentation
   * group. Access: Read-write. Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_AUTO_SELECTION_PRIORITY = 204,
  // @aidl-doc
  /**
   * Dolby AC-4 audio mixer balance between associated audio and main audio.
   *
   * Type: Integer
   *  255 - no override, selection should use the user preference set in audio mixer. (default)
   *  -32..32 - Mixer balance from -32 (mute associated) to 32 (mute main).
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_MIXER_BALANCE = 205,
  // @aidl-doc
  /**
   * Dolby AC-4 audio associated audio mixing control.
   *
   * Type: Integer
   *  -1 - no override, selection should use the user preference set in audio mixer. (default)
   *  0 - off
   *  1 - on
   * Access: Read-write.
   * Writeable in states: All
   *
   * @exception binder::Status::Exception::EX_NONE for success
   */
  AC4_ASSOCIATED_AUDIO_MIXING_ENABLE = 206,
  // @aidl-doc
  /**
   * Count of decoded frames.
   * This metric is reset on open() and flush() calls.
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
   * This metric is reset on open() and flush() calls.
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
   * deliver a frame suitable for mixing.
   * This metric is reset on open() and flush() calls.
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
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
[[nodiscard]] static inline std::string toString(Property val) {
  switch(val) {
  case Property::RESOURCE_ID:
    return "RESOURCE_ID";
  case Property::LOW_LATENCY_MODE:
    return "LOW_LATENCY_MODE";
  case Property::AV_SOURCE:
    return "AV_SOURCE";
  case Property::SECURE_AUDIO:
    return "SECURE_AUDIO";
  case Property::AC4_PRESENTATION_GROUP_INDEX:
    return "AC4_PRESENTATION_GROUP_INDEX";
  case Property::AC4_PREFERRED_LANG1:
    return "AC4_PREFERRED_LANG1";
  case Property::AC4_PREFERRED_LANG2:
    return "AC4_PREFERRED_LANG2";
  case Property::AC4_ASSOCIATED_TYPE:
    return "AC4_ASSOCIATED_TYPE";
  case Property::AC4_AUTO_SELECTION_PRIORITY:
    return "AC4_AUTO_SELECTION_PRIORITY";
  case Property::AC4_MIXER_BALANCE:
    return "AC4_MIXER_BALANCE";
  case Property::AC4_ASSOCIATED_AUDIO_MIXING_ENABLE:
    return "AC4_ASSOCIATED_AUDIO_MIXING_ENABLE";
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
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiodecoder::Property, 14> enum_values<::com::rdk::hal::audiodecoder::Property> = {
  ::com::rdk::hal::audiodecoder::Property::RESOURCE_ID,
  ::com::rdk::hal::audiodecoder::Property::LOW_LATENCY_MODE,
  ::com::rdk::hal::audiodecoder::Property::AV_SOURCE,
  ::com::rdk::hal::audiodecoder::Property::SECURE_AUDIO,
  ::com::rdk::hal::audiodecoder::Property::AC4_PRESENTATION_GROUP_INDEX,
  ::com::rdk::hal::audiodecoder::Property::AC4_PREFERRED_LANG1,
  ::com::rdk::hal::audiodecoder::Property::AC4_PREFERRED_LANG2,
  ::com::rdk::hal::audiodecoder::Property::AC4_ASSOCIATED_TYPE,
  ::com::rdk::hal::audiodecoder::Property::AC4_AUTO_SELECTION_PRIORITY,
  ::com::rdk::hal::audiodecoder::Property::AC4_MIXER_BALANCE,
  ::com::rdk::hal::audiodecoder::Property::AC4_ASSOCIATED_AUDIO_MIXING_ENABLE,
  ::com::rdk::hal::audiodecoder::Property::METRIC_FRAMES_DECODED,
  ::com::rdk::hal::audiodecoder::Property::METRIC_DECODE_ERRORS,
  ::com::rdk::hal::audiodecoder::Property::METRIC_FRAMES_DROPPED,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
