#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class PQParameterConfiguration : public ::android::Parcelable {
public:
  ::com::rdk::hal::panel::PQParameter pqParameter = ::com::rdk::hal::panel::PQParameter(0);
  ::std::optional<::android::String16> pictureMode;
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  ::com::rdk::hal::videodecoder::DynamicRange format = ::com::rdk::hal::videodecoder::DynamicRange(0);
  int32_t value = 0;
  inline bool operator!=(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) != std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
  }
  inline bool operator<(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) < std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
  }
  inline bool operator<=(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) <= std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
  }
  inline bool operator==(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) == std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
  }
  inline bool operator>(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) > std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
  }
  inline bool operator>=(const PQParameterConfiguration& rhs) const {
    return std::tie(pqParameter, pictureMode, source, format, value) >= std::tie(rhs.pqParameter, rhs.pictureMode, rhs.source, rhs.format, rhs.value);
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
    os << "pqParameter: " << ::android::internal::ToString(pqParameter);
    os << ", pictureMode: " << ::android::internal::ToString(pictureMode);
    os << ", source: " << ::android::internal::ToString(source);
    os << ", format: " << ::android::internal::ToString(format);
    os << ", value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class PQParameterConfiguration
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
