#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/SPDSource.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class SPDInfoFrame : public ::android::Parcelable {
public:
  std::array<uint8_t, 8> vendorName = {{}};
  std::array<uint8_t, 16> productDescription = {{}};
  ::com::rdk::hal::hdmioutput::SPDSource spdSourceInformation = ::com::rdk::hal::hdmioutput::SPDSource(0);
  inline bool operator!=(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) != std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }
  inline bool operator<(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) < std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }
  inline bool operator<=(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) <= std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }
  inline bool operator==(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) == std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }
  inline bool operator>(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) > std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }
  inline bool operator>=(const SPDInfoFrame& rhs) const {
    return std::tie(vendorName, productDescription, spdSourceInformation) >= std::tie(rhs.vendorName, rhs.productDescription, rhs.spdSourceInformation);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.SPDInfoFrame");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SPDInfoFrame{";
    os << "vendorName: " << ::android::internal::ToString(vendorName);
    os << ", productDescription: " << ::android::internal::ToString(productDescription);
    os << ", spdSourceInformation: " << ::android::internal::ToString(spdSourceInformation);
    os << "}";
    return os.str();
  }
};  // class SPDInfoFrame
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
