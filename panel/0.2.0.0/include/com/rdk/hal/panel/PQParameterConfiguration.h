#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/PQParameterSelector.h>
#include <com/rdk/hal/panel/PQParameterValue.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     PQ parameter configuration.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class PQParameterConfiguration : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Selector identifying the PQ parameter instance. */
  ::com::rdk::hal::panel::PQParameterSelector selector;
  // @aidl-doc
  /**
   * The value for the PQ parameter.
   * The active variant must match `selector.pqParameter`.
   */
  ::com::rdk::hal::panel::PQParameterValue value;
  inline bool operator!=(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) != std::tie(rhs.selector, rhs.value);
  }
  inline bool operator<(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) < std::tie(rhs.selector, rhs.value);
  }
  inline bool operator<=(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) <= std::tie(rhs.selector, rhs.value);
  }
  inline bool operator==(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) == std::tie(rhs.selector, rhs.value);
  }
  inline bool operator>(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) > std::tie(rhs.selector, rhs.value);
  }
  inline bool operator>=(const PQParameterConfiguration& rhs) const {
    return std::tie(selector, value) >= std::tie(rhs.selector, rhs.value);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterConfiguration");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PQParameterConfiguration{";
    os << "selector: " << ::android::internal::ToString(selector);
    os << ", value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class PQParameterConfiguration
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
