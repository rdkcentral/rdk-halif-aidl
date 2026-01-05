#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmiinput/HDMIVersion.h>
#include <com/rdk/hal/hdmiinput/VIC.h>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::hdmiinput::HDMIVersion> supportedVersions;
  ::std::vector<::com::rdk::hal::hdmiinput::VIC> supportedVICs;
  ::std::vector<::com::rdk::hal::hdmiinput::HDCPProtocolVersion> supportedHDCPProtocolVersions;
  bool supports3D = false;
  bool supportsFRL = false;
  bool supportsVRR = false;
  bool supportsFreeSync = false;
  bool supportsQMS = false;
  bool supportsALLM = false;
  bool supportsQFT = false;
  bool supportsARC = false;
  bool supportsEARC = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) != std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) < std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) <= std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) == std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) > std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDCPProtocolVersions, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT, supportsARC, supportsEARC) >= std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDCPProtocolVersions, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT, rhs.supportsARC, rhs.supportsEARC);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmiinput.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedVersions: " << ::android::internal::ToString(supportedVersions);
    os << ", supportedVICs: " << ::android::internal::ToString(supportedVICs);
    os << ", supportedHDCPProtocolVersions: " << ::android::internal::ToString(supportedHDCPProtocolVersions);
    os << ", supports3D: " << ::android::internal::ToString(supports3D);
    os << ", supportsFRL: " << ::android::internal::ToString(supportsFRL);
    os << ", supportsVRR: " << ::android::internal::ToString(supportsVRR);
    os << ", supportsFreeSync: " << ::android::internal::ToString(supportsFreeSync);
    os << ", supportsQMS: " << ::android::internal::ToString(supportsQMS);
    os << ", supportsALLM: " << ::android::internal::ToString(supportsALLM);
    os << ", supportsQFT: " << ::android::internal::ToString(supportsQFT);
    os << ", supportsARC: " << ::android::internal::ToString(supportsARC);
    os << ", supportsEARC: " << ::android::internal::ToString(supportsEARC);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
