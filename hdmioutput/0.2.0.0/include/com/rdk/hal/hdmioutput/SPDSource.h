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
 *  @brief     HDMI SPD InfoFrame source type enumeration (Data Byte 25).
 *
 *  Enumerates the source device class reported in the HDMI SPD InfoFrame,
 *  as defined in CTA-861. This field helps receivers interpret and adapt
 *  rendering modes (e.g., game mode, cinema presets).
 *
 *  This value is set in SPDInfoFrame.spdSourceInformation.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 *  @author    Gerald Weatherup
 */
enum class SPDSource : int8_t {
  // @aidl-doc
  /** Unknown or undefined source */
  UNKNOWN = 0,
  // @aidl-doc
  /** Digital Set-Top Box */
  DIGITAL_STB = 1,
  // @aidl-doc
  /** DVD player */
  DVD_PLAYER = 2,
  // @aidl-doc
  /** D-VHS device */
  D_VHS = 3,
  // @aidl-doc
  /** HDD-based video recorder */
  HDD_VIDEORECORDER = 4,
  // @aidl-doc
  /** Digital Video Camera (DVC) */
  DVC = 5,
  // @aidl-doc
  /** Digital Still Camera (DSC) */
  DSC = 6,
  // @aidl-doc
  /** Video CD player */
  VIDEO_CD = 7,
  // @aidl-doc
  /** Game console */
  GAME = 8,
  // @aidl-doc
  /** Personal computer (general use) */
  PC_GENERAL = 9,
  // @aidl-doc
  /** Blu-ray Disc player */
  BLU_RAY_DISC = 10,
  // @aidl-doc
  /** Super Audio CD (SACD) player */
  SUPER_AUDIO_CD = 11,
  // @aidl-doc
  /** HD-DVD player */
  HD_DVD = 12,
};
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
[[nodiscard]] static inline std::string toString(SPDSource val) {
  switch(val) {
  case SPDSource::UNKNOWN:
    return "UNKNOWN";
  case SPDSource::DIGITAL_STB:
    return "DIGITAL_STB";
  case SPDSource::DVD_PLAYER:
    return "DVD_PLAYER";
  case SPDSource::D_VHS:
    return "D_VHS";
  case SPDSource::HDD_VIDEORECORDER:
    return "HDD_VIDEORECORDER";
  case SPDSource::DVC:
    return "DVC";
  case SPDSource::DSC:
    return "DSC";
  case SPDSource::VIDEO_CD:
    return "VIDEO_CD";
  case SPDSource::GAME:
    return "GAME";
  case SPDSource::PC_GENERAL:
    return "PC_GENERAL";
  case SPDSource::BLU_RAY_DISC:
    return "BLU_RAY_DISC";
  case SPDSource::SUPER_AUDIO_CD:
    return "SUPER_AUDIO_CD";
  case SPDSource::HD_DVD:
    return "HD_DVD";
  default:
    return std::to_string(static_cast<int8_t>(val));
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
constexpr inline std::array<::com::rdk::hal::hdmioutput::SPDSource, 13> enum_values<::com::rdk::hal::hdmioutput::SPDSource> = {
  ::com::rdk::hal::hdmioutput::SPDSource::UNKNOWN,
  ::com::rdk::hal::hdmioutput::SPDSource::DIGITAL_STB,
  ::com::rdk::hal::hdmioutput::SPDSource::DVD_PLAYER,
  ::com::rdk::hal::hdmioutput::SPDSource::D_VHS,
  ::com::rdk::hal::hdmioutput::SPDSource::HDD_VIDEORECORDER,
  ::com::rdk::hal::hdmioutput::SPDSource::DVC,
  ::com::rdk::hal::hdmioutput::SPDSource::DSC,
  ::com::rdk::hal::hdmioutput::SPDSource::VIDEO_CD,
  ::com::rdk::hal::hdmioutput::SPDSource::GAME,
  ::com::rdk::hal::hdmioutput::SPDSource::PC_GENERAL,
  ::com::rdk::hal::hdmioutput::SPDSource::BLU_RAY_DISC,
  ::com::rdk::hal::hdmioutput::SPDSource::SUPER_AUDIO_CD,
  ::com::rdk::hal::hdmioutput::SPDSource::HD_DVD,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
