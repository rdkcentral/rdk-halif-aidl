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
// @aidl-doc
/**
 * @brief Available frontend signal info property types.
 *
 * Note that this enum is shared across all frontend types and thus includes values that are only usable on some of
 * them. You should always request and consult the list of supported status properties from the frontend before using
 * any of them.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
enum class SignalInfoProperty : int32_t {
  // @aidl-doc
  /** Clean value when default initialized. */
  UNDEFINED = 0,
  // @aidl-doc
  /**
   * The type of the frontend associated with this signal info (e.g., DVB-T, DVB-S, DVB-C).
   *
   * Readiness is UNAVAILABLE until the frontend has been tuned.
   */
  FRONTEND_TYPE = 1,
  // @aidl-doc
  /** The actual frequency that the tuner is locked on (in Hertz). */
  ACTUAL_FREQUENCY = 2,
  // @aidl-doc
  /** Demod Lock status. */
  DEMOD_LOCK = 3,
  // @aidl-doc
  /** RF Lock status. */
  RF_LOCK = 4,
  // @aidl-doc
  /** RF signal level in dBm. */
  RF_LEVEL = 5,
  // @aidl-doc
  /** Carrier to noise ratio in dB. */
  CNR = 6,
  // @aidl-doc
  /** Bit error rate - The number of error bits per 1 billion bits (range 0-1,000,000,000). */
  BER = 7,
  // @aidl-doc
  /** Pre Viterbi BER - The number of error bits per 1 billion bits before correction (range 0-1,000,000,000). */
  PRE_BER = 8,
  // @aidl-doc
  /** Uncorrected error count. */
  UNCORRECTED_ERRORS = 9,
  // @aidl-doc
  /** Signal Strength Indicator as defined in NorDig (range 0-100). */
  SSI = 10,
  // @aidl-doc
  /** Signal Quality Indicator as defined in NorDig (range 0-100). */
  SQI = 11,
  // @aidl-doc
  /** Physical Layer Pipe ID (range 0-255). */
  PLP_ID = 12,
  // @aidl-doc
  /** Physical Layer Pipe IDs (range 0-255). */
  PLP_IDS = 13,
  // @aidl-doc
  /** DVB-T2 System Id. */
  T2_SYSTEM_ID = 14,
  // @aidl-doc
  /** The used modulation / sub-modulation. */
  MODULATION = 15,
  // @aidl-doc
  /** The used guard interval. */
  GUARD_INTERVAL = 16,
  // @aidl-doc
  /** The used transmission mode. */
  TRANSMISSION_MODE = 17,
  // @aidl-doc
  /** Bandwidth. */
  BANDWIDTH = 18,
  // @aidl-doc
  /** Symbol Rate. */
  SYMBOL_RATE = 19,
  // @aidl-doc
  /** DVB-T Standard. */
  DVB_T_STANDARD = 20,
  // @aidl-doc
  /** DVB-S Standard. */
  DVB_S_STANDARD = 21,
  // @aidl-doc
  /** Code rate; for DVB-S/S2/S2X, the value is the inner FEC. */
  CODE_RATE = 22,
  // @aidl-doc
  /** DVB-C Annex. */
  DVB_C_ANNEX = 23,
  // @aidl-doc
  /** Spectral inversion mode. */
  SPECTRAL_INVERSION = 24,
  // @aidl-doc
  /** roll-off factor. */
  ROLL_OFF = 25,
  // @aidl-doc
  /** DVB-T hierarchical transmission mode. */
  DVB_T_HIERARCHY = 26,
  // @aidl-doc
  /** DVB-T MISO mode. */
  DVB_T_MISO = 27,
  // @aidl-doc
  /** DVB-S2/S2X pilot mode. */
  DVB_S_PILOT = 28,
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling mode. */
  DVB_S_PLS_MODE = 29,
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling code. */
  DVB_S_PLS_CODE = 30,
  // @aidl-doc
  /** DVB-S2/S2X input stream identifier. */
  DVB_S_INPUT_STREAM_ID = 31,
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
  case SignalInfoProperty::FRONTEND_TYPE:
    return "FRONTEND_TYPE";
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
  case SignalInfoProperty::CODE_RATE:
    return "CODE_RATE";
  case SignalInfoProperty::DVB_C_ANNEX:
    return "DVB_C_ANNEX";
  case SignalInfoProperty::SPECTRAL_INVERSION:
    return "SPECTRAL_INVERSION";
  case SignalInfoProperty::ROLL_OFF:
    return "ROLL_OFF";
  case SignalInfoProperty::DVB_T_HIERARCHY:
    return "DVB_T_HIERARCHY";
  case SignalInfoProperty::DVB_T_MISO:
    return "DVB_T_MISO";
  case SignalInfoProperty::DVB_S_PILOT:
    return "DVB_S_PILOT";
  case SignalInfoProperty::DVB_S_PLS_MODE:
    return "DVB_S_PLS_MODE";
  case SignalInfoProperty::DVB_S_PLS_CODE:
    return "DVB_S_PLS_CODE";
  case SignalInfoProperty::DVB_S_INPUT_STREAM_ID:
    return "DVB_S_INPUT_STREAM_ID";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SignalInfoProperty, 32> enum_values<::com::rdk::hal::broadcast::frontend::SignalInfoProperty> = {
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::FRONTEND_TYPE,
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
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::CODE_RATE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_C_ANNEX,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::SPECTRAL_INVERSION,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::ROLL_OFF,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_T_HIERARCHY,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_T_MISO,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_S_PILOT,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_S_PLS_MODE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_S_PLS_CODE,
  ::com::rdk::hal::broadcast::frontend::SignalInfoProperty::DVB_S_INPUT_STREAM_ID,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
