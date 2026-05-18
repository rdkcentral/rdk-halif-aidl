#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
enum class SPDSource : int8_t {
  UNKNOWN = 0,
  DIGITAL_STB = 1,
  DVD_PLAYER = 2,
  D_VHS = 3,
  HDD_VIDEORECORDER = 4,
  DVC = 5,
  DSC = 6,
  VIDEO_CD = 7,
  GAME = 8,
  PC_GENERAL = 9,
  BLU_RAY_DISC = 10,
  SUPER_AUDIO_CD = 11,
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
