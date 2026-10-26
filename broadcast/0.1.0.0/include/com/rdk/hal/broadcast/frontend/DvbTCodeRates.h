#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCodeRates.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief DVB-T and DVB-T2 code rate.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbTCodeRates : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Possible Dvb-T code rate values. */
  enum class Value : int32_t {
    // @aidl-doc
    /** Clean value when default initialized. */
    UNDEFINED = 0,
    // @aidl-doc
    /** The code rate is auto-detected. */
    AUTO = 1,
    // @aidl-doc
    /** CR_1_2 applies to DVB-T and DVB-T2. */
    CR_1_2 = 2,
    // @aidl-doc
    /** CR_2_3 applies to DVB-T and DVB-T2. */
    CR_2_3 = 3,
    // @aidl-doc
    /** CR_3_4 applies to DVB-T and DVB-T2. */
    CR_3_4 = 4,
    // @aidl-doc
    /** CR_3_5 applies to DVB-T2. */
    CR_3_5 = 5,
    // @aidl-doc
    /** CR_4_5 applies to DVB-T2. */
    CR_4_5 = 6,
    // @aidl-doc
    /** CR_5_6 applies to DVB-T and DVB-T2. */
    CR_5_6 = 7,
    // @aidl-doc
    /** CR_7_8 applies to DVB-T. */
    CR_7_8 = 8,
  };
  // @aidl-doc
  /** LP code rate for DVB-T/T2. */
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value lowPriority = ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value(0);
  // @aidl-doc
  /** HP code rate for DVB-T/T2. */
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value highPriority = ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value(0);
  inline bool operator!=(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) != std::tie(rhs.lowPriority, rhs.highPriority);
  }
  inline bool operator<(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) < std::tie(rhs.lowPriority, rhs.highPriority);
  }
  inline bool operator<=(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) <= std::tie(rhs.lowPriority, rhs.highPriority);
  }
  inline bool operator==(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) == std::tie(rhs.lowPriority, rhs.highPriority);
  }
  inline bool operator>(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) > std::tie(rhs.lowPriority, rhs.highPriority);
  }
  inline bool operator>=(const DvbTCodeRates& rhs) const {
    return std::tie(lowPriority, highPriority) >= std::tie(rhs.lowPriority, rhs.highPriority);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbTCodeRates");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbTCodeRates{";
    os << "lowPriority: " << ::android::internal::ToString(lowPriority);
    os << ", highPriority: " << ::android::internal::ToString(highPriority);
    os << "}";
    return os.str();
  }
};  // class DvbTCodeRates
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
[[nodiscard]] static inline std::string toString(DvbTCodeRates::Value val) {
  switch(val) {
  case DvbTCodeRates::Value::UNDEFINED:
    return "UNDEFINED";
  case DvbTCodeRates::Value::AUTO:
    return "AUTO";
  case DvbTCodeRates::Value::CR_1_2:
    return "CR_1_2";
  case DvbTCodeRates::Value::CR_2_3:
    return "CR_2_3";
  case DvbTCodeRates::Value::CR_3_4:
    return "CR_3_4";
  case DvbTCodeRates::Value::CR_3_5:
    return "CR_3_5";
  case DvbTCodeRates::Value::CR_4_5:
    return "CR_4_5";
  case DvbTCodeRates::Value::CR_5_6:
    return "CR_5_6";
  case DvbTCodeRates::Value::CR_7_8:
    return "CR_7_8";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value, 9> enum_values<::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value> = {
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::UNDEFINED,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::AUTO,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_1_2,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_2_3,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_3_4,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_3_5,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_4_5,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_5_6,
  ::com::rdk::hal::broadcast::frontend::DvbTCodeRates::Value::CR_7_8,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
