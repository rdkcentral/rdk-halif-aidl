#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/common/TransmissionType.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace demo {
namespace hal {
namespace common {
class TransmissionDetails : public ::android::Parcelable {
public:
  ::com::demo::hal::common::TransmissionType transmissionType = ::com::demo::hal::common::TransmissionType(0);
  int32_t numberOfGears = 0;
  ::std::optional<::android::String16> transmissionMode;
  inline bool operator!=(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) != std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }
  inline bool operator<(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) < std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }
  inline bool operator<=(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) <= std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }
  inline bool operator==(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) == std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }
  inline bool operator>(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) > std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }
  inline bool operator>=(const TransmissionDetails& rhs) const {
    return std::tie(transmissionType, numberOfGears, transmissionMode) >= std::tie(rhs.transmissionType, rhs.numberOfGears, rhs.transmissionMode);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.demo.hal.common.TransmissionDetails");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TransmissionDetails{";
    os << "transmissionType: " << ::android::internal::ToString(transmissionType);
    os << ", numberOfGears: " << ::android::internal::ToString(numberOfGears);
    os << ", transmissionMode: " << ::android::internal::ToString(transmissionMode);
    os << "}";
    return os.str();
  }
};  // class TransmissionDetails
}  // namespace common
}  // namespace hal
}  // namespace demo
}  // namespace com
