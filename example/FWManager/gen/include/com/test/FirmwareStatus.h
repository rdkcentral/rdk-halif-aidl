#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace test {
class FirmwareStatus : public ::android::Parcelable {
public:
  ::android::String16 state;
  int32_t percentProgress = 0;
  bool compulsory = false;
  inline bool operator!=(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) != std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }
  inline bool operator<(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) < std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }
  inline bool operator<=(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) <= std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }
  inline bool operator==(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) == std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }
  inline bool operator>(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) > std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }
  inline bool operator>=(const FirmwareStatus& rhs) const {
    return std::tie(state, percentProgress, compulsory) >= std::tie(rhs.state, rhs.percentProgress, rhs.compulsory);
  }

  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.test.FirmwareStatus");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FirmwareStatus{";
    os << "state: " << ::android::internal::ToString(state);
    os << ", percentProgress: " << ::android::internal::ToString(percentProgress);
    os << ", compulsory: " << ::android::internal::ToString(compulsory);
    os << "}";
    return os.str();
  }
};  // class FirmwareStatus
}  // namespace test
}  // namespace com
