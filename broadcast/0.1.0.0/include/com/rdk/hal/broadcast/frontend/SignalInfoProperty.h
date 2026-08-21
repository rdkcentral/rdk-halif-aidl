#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
enum class SignalInfoProperty : int32_t {
  UNDEFINED = 0,
  ACTUAL_FREQUENCY = 1,
  DEMOD_LOCK = 2,
  RF_LOCK = 3,
  RF_LEVEL = 4,
  CNR = 5,
  BER = 6,
  PRE_BER = 7,
  UNCORRECTED_ERRORS = 8,
  SSI = 9,
  SQI = 10,
  PLP_ID = 11,
  PLP_IDS = 12,
  T2_SYSTEM_ID = 13,
  MODULATION = 14,
  GUARD_INTERVAL = 15,
  TRANSMISSION_MODE = 16,
  BANDWIDTH = 17,
  SYMBOL_RATE = 18,
  DVB_T_STANDARD = 19,
  DVB_S_STANDARD = 20,
  CODING_RATE = 21,
  DVB_T_CODING_RATE = 22,
};
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(SignalInfoProperty val) {
  switch(val) {
  case SignalInfoProperty::UNDEFINED:
    return "UNDEFINED";
  case SignalInfoProperty::ACTUAL_FREQUENCY:
    return "ACTUAL_FREQUENCY";
  case SignalInfoProperty::DEMOD_LOCK:
    return "DEMOD_LOCK";
  case SignalInfoProperty::RF_LOCK:
    return "RF_LOCK";
  case SignalInfoProperty::RF_LEVEL:
    return "RF_LEVEL";
  case SignalInfoProperty::CNR:
    return "CNR";
  case SignalInfoProperty::BER:
    return "BER";
  case SignalInfoProperty::PRE_BER:
    return "PRE_BER";
  case SignalInfoProperty::UNCORRECTED_ERRORS:
    return "UNCORRECTED_ERRORS";
  case SignalInfoProperty::SSI:
    return "SSI";
  case SignalInfoProperty::SQI:
    return "SQI";
  case SignalInfoProperty::PLP_ID:
    return "PLP_ID";
  case SignalInfoProperty::PLP_IDS:
    return "PLP_IDS";
  case SignalInfoProperty::T2_SYSTEM_ID:
    return "T2_SYSTEM_ID";
  case SignalInfoProperty::MODULATION:
    return "MODULATION";
  case SignalInfoProperty::GUARD_INTERVAL:
    return "GUARD_INTERVAL";
  case SignalInfoProperty::TRANSMISSION_MODE:
    return "TRANSMISSION_MODE";
  case SignalInfoProperty::BANDWIDTH:
    return "BANDWIDTH";
  case SignalInfoProperty::SYMBOL_RATE:
    return "SYMBOL_RATE";
  case SignalInfoProperty::DVB_T_STANDARD:
    return "DVB_T_STANDARD";
  case SignalInfoProperty::DVB_S_STANDARD:
    return "DVB_S_STANDARD";
  case SignalInfoProperty::CODING_RATE:
    return "CODING_RATE";
  case SignalInfoProperty::DVB_T_CODING_RATE:
    return "DVB_T_CODING_RATE";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SignalInfoProperty, 23> enum_values<::com::rdk::hal::broadcast::frontend::SignalInfoProperty> = {
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::ACTUAL_FREQUENCY,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DEMOD_LOCK,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::RF_LOCK,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::RF_LEVEL,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::CNR,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::BER,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::PRE_BER,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::UNCORRECTED_ERRORS,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::SSI,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::SQI,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::PLP_ID,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::PLP_IDS,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::T2_SYSTEM_ID,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::MODULATION,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::GUARD_INTERVAL,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::TRANSMISSION_MODE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::BANDWIDTH,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::SYMBOL_RATE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_T_STANDARD,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_S_STANDARD,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::CODING_RATE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_T_CODING_RATE,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
