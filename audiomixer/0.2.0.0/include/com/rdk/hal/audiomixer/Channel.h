#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
enum class Channel : int32_t {
  CH_FL = 0,
  CH_FR = 1,
  CH_FC = 2,
  CH_LFE = 3,
  CH_SL = 4,
  CH_SR = 5,
  CH_RL = 6,
  CH_RR = 7,
  CH_RC = 8,
  CH_TFL = 9,
  CH_TFR = 10,
  CH_TFC = 11,
  CH_TSL = 12,
  CH_TSR = 13,
  CH_TRL = 14,
  CH_TRR = 15,
  CH_WL = 16,
  CH_WR = 17,
};
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(Channel val) {
  switch(val) {
  case Channel::CH_FL:
    return "CH_FL";
  case Channel::CH_FR:
    return "CH_FR";
  case Channel::CH_FC:
    return "CH_FC";
  case Channel::CH_LFE:
    return "CH_LFE";
  case Channel::CH_SL:
    return "CH_SL";
  case Channel::CH_SR:
    return "CH_SR";
  case Channel::CH_RL:
    return "CH_RL";
  case Channel::CH_RR:
    return "CH_RR";
  case Channel::CH_RC:
    return "CH_RC";
  case Channel::CH_TFL:
    return "CH_TFL";
  case Channel::CH_TFR:
    return "CH_TFR";
  case Channel::CH_TFC:
    return "CH_TFC";
  case Channel::CH_TSL:
    return "CH_TSL";
  case Channel::CH_TSR:
    return "CH_TSR";
  case Channel::CH_TRL:
    return "CH_TRL";
  case Channel::CH_TRR:
    return "CH_TRR";
  case Channel::CH_WL:
    return "CH_WL";
  case Channel::CH_WR:
    return "CH_WR";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::Channel, 18> enum_values<::com::rdk::hal::audiomixer::Channel> = {
  ::com::rdk::hal::audiomixer::Channel::CH_FL,
  ::com::rdk::hal::audiomixer::Channel::CH_FR,
  ::com::rdk::hal::audiomixer::Channel::CH_FC,
  ::com::rdk::hal::audiomixer::Channel::CH_LFE,
  ::com::rdk::hal::audiomixer::Channel::CH_SL,
  ::com::rdk::hal::audiomixer::Channel::CH_SR,
  ::com::rdk::hal::audiomixer::Channel::CH_RL,
  ::com::rdk::hal::audiomixer::Channel::CH_RR,
  ::com::rdk::hal::audiomixer::Channel::CH_RC,
  ::com::rdk::hal::audiomixer::Channel::CH_TFL,
  ::com::rdk::hal::audiomixer::Channel::CH_TFR,
  ::com::rdk::hal::audiomixer::Channel::CH_TFC,
  ::com::rdk::hal::audiomixer::Channel::CH_TSL,
  ::com::rdk::hal::audiomixer::Channel::CH_TSR,
  ::com::rdk::hal::audiomixer::Channel::CH_TRL,
  ::com::rdk::hal::audiomixer::Channel::CH_TRR,
  ::com::rdk::hal::audiomixer::Channel::CH_WL,
  ::com::rdk::hal::audiomixer::Channel::CH_WR,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
