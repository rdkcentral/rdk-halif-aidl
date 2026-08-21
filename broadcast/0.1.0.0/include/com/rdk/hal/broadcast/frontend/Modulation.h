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
enum class Modulation : int32_t {
  UNDEFINED = 0,
  AUTO = 1,
  QPSK = 2,
  DQPSK = 3,
  PSK_8 = 4,
  APSK_16 = 5,
  APSK_32 = 6,
  QAM_4 = 7,
  QAM_4_NR = 8,
  QAM_16 = 9,
  QAM_32 = 10,
  QAM_64 = 11,
  QAM_128 = 12,
  QAM_256 = 13,
  QAM_AUTO = 14,
  VSB_8 = 15,
  VSB_16 = 16,
  COFDM = 17,
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
[[nodiscard]] static inline std::string toString(Modulation val) {
  switch(val) {
  case Modulation::UNDEFINED:
    return "UNDEFINED";
  case Modulation::AUTO:
    return "AUTO";
  case Modulation::QPSK:
    return "QPSK";
  case Modulation::DQPSK:
    return "DQPSK";
  case Modulation::PSK_8:
    return "PSK_8";
  case Modulation::APSK_16:
    return "APSK_16";
  case Modulation::APSK_32:
    return "APSK_32";
  case Modulation::QAM_4:
    return "QAM_4";
  case Modulation::QAM_4_NR:
    return "QAM_4_NR";
  case Modulation::QAM_16:
    return "QAM_16";
  case Modulation::QAM_32:
    return "QAM_32";
  case Modulation::QAM_64:
    return "QAM_64";
  case Modulation::QAM_128:
    return "QAM_128";
  case Modulation::QAM_256:
    return "QAM_256";
  case Modulation::QAM_AUTO:
    return "QAM_AUTO";
  case Modulation::VSB_8:
    return "VSB_8";
  case Modulation::VSB_16:
    return "VSB_16";
  case Modulation::COFDM:
    return "COFDM";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::Modulation, 18> enum_values<::com::rdk::hal::broadcast::frontend::Modulation> = {
  ::com::rdk::hal::broadcast::frontend::Modulation::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::Modulation::AUTO,
  ::com::rdk::hal::broadcast::frontend::Modulation::QPSK,
  ::com::rdk::hal::broadcast::frontend::Modulation::DQPSK,
  ::com::rdk::hal::broadcast::frontend::Modulation::PSK_8,
  ::com::rdk::hal::broadcast::frontend::Modulation::APSK_16,
  ::com::rdk::hal::broadcast::frontend::Modulation::APSK_32,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_4,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_4_NR,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_16,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_32,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_64,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_128,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_256,
  ::com::rdk::hal::broadcast::frontend::Modulation::QAM_AUTO,
  ::com::rdk::hal::broadcast::frontend::Modulation::VSB_8,
  ::com::rdk::hal::broadcast::frontend::Modulation::VSB_16,
  ::com::rdk::hal::broadcast::frontend::Modulation::COFDM,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
