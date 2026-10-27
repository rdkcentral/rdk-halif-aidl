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
 * Enum representing the video format for decoder configuration records.
 *
 * This enum defines the different video formats associated with decoder configuration records.
 * Each enum value corresponds to a specific video codec and its corresponding
 * configuration record structure. The configuration record starts with a version byte.
 *
 * These configuration records provide necessary codec parameters such as sequence headers,
 * SPS (Sequence Parameter Set), PPS (Picture Parameter Set), and codec initialization details.
 *
 * @enum CSDVideoFormat
 */
enum class CSDVideoFormat : int32_t {
  // @aidl-doc
  /**
   * AVC Decoder Configuration Record (H.264/AVC).
   *
   * Represents the `AVCDecoderConfigurationRecord` as defined in:
   * - **ISO/IEC 14496-15:2022**, Section 5.3.3.1.2
   * - More info: @see https://www.iso.org/standard/83336.html
   */
  AVC_DECODER_CONFIGURATION_RECORD = 0,
  // @aidl-doc
  /**
   * HEVC Decoder Configuration Record (H.265/HEVC).
   *
   * Represents the `HEVCDecoderConfigurationRecord` as defined in:
   * - **ISO/IEC 23008-2 (HEVC)**
   * - More info: @see https://www.iso.org/standard/85457.html
   */
  HEVC_DECODER_CONFIGURATION_RECORD = 1,
  // @aidl-doc
  /**
   * AV1 Decoder Configuration Record.
   *
   * Represents the `AV1CodecConfigurationRecord` as defined in:
   * - **AOM AV1 ISOBMFF specification**
   * - More info: @see https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
   */
  AV1_DECODER_CONFIGURATION_RECORD = 2,
};
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
[[nodiscard]] static inline std::string toString(CSDVideoFormat val) {
  switch(val) {
  case CSDVideoFormat::AVC_DECODER_CONFIGURATION_RECORD:
    return "AVC_DECODER_CONFIGURATION_RECORD";
  case CSDVideoFormat::HEVC_DECODER_CONFIGURATION_RECORD:
    return "HEVC_DECODER_CONFIGURATION_RECORD";
  case CSDVideoFormat::AV1_DECODER_CONFIGURATION_RECORD:
    return "AV1_DECODER_CONFIGURATION_RECORD";
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
constexpr inline std::array<::com::rdk::hal::videodecoder::CSDVideoFormat, 3> enum_values<::com::rdk::hal::videodecoder::CSDVideoFormat> = {
  ::com::rdk::hal::videodecoder::CSDVideoFormat::AVC_DECODER_CONFIGURATION_RECORD,
  ::com::rdk::hal::videodecoder::CSDVideoFormat::HEVC_DECODER_CONFIGURATION_RECORD,
  ::com::rdk::hal::videodecoder::CSDVideoFormat::AV1_DECODER_CONFIGURATION_RECORD,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
