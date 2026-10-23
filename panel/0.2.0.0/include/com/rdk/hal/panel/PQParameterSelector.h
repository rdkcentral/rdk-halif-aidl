#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 * @brief Selector for a PQ parameter configuration.
 *
 * The selector identifies the PQ parameter and its runtime context only.
 * White-balance values are not addressed by additional selector keys; the
 * corresponding read operations return the complete 2-point or multi-point
 * white-balance bundle for the selected picture-mode, source, and dynamic-
 * range context.
 */
class PQParameterSelector : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The PQ parameter. */
  ::com::rdk::hal::panel::PQParameter pqParameter = ::com::rdk::hal::panel::PQParameter(0);
  // @aidl-doc
  /** The picture mode. */
  ::android::String16 pictureMode;
  // @aidl-doc
  /** The AV source. */
  ::com::rdk::hal::panel::PanelSource source;
  // @aidl-doc
  /**
   * The dynamic range.
   * DynamicRange.UNKNOWN means wildcard which applies to all supported dynamic ranges.
   */
  ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
  inline bool operator!=(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) != std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }
  inline bool operator<(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) < std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }
  inline bool operator<=(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) <= std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }
  inline bool operator==(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) == std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }
  inline bool operator>(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) > std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }
  inline bool operator>=(const PQParameterSelector& rhs) const {
    return std::tie(pqParameter, pictureMode, source, dynamicRange) >= std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.dynamicRange);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterSelector");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PQParameterSelector{";
    os << "pqParameter: " << ::android::internal::ToString(pqParameter);
    os << ", pictureMode: " << ::android::internal::ToString(pictureMode);
    os << ", source: " << ::android::internal::ToString(source);
    os << ", dynamicRange: " << ::android::internal::ToString(dynamicRange);
    os << "}";
    return os.str();
  }
};  // class PQParameterSelector
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
