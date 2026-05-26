#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/AdditionalColorimetryExtension.h>
#include <com/rdk/hal/hdmioutput/Colorimetry.h>
#include <com/rdk/hal/hdmioutput/ExtendedColorimetry.h>
#include <com/rdk/hal/hdmioutput/HDCPProtocolVersion.h>
#include <com/rdk/hal/hdmioutput/HDMIVersion.h>
#include <com/rdk/hal/hdmioutput/HDROutputMode.h>
#include <com/rdk/hal/hdmioutput/PixelFormat.h>
#include <com/rdk/hal/hdmioutput/VIC.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::hdmioutput::HDMIVersion> supportedVersions;
  ::std::vector<::com::rdk::hal::hdmioutput::VIC> supportedVICs;
  ::std::vector<::com::rdk::hal::hdmioutput::HDROutputMode> supportedHDROutputModes;
  bool supportsForcedHDROutputModes = false;
  ::std::vector<::com::rdk::hal::hdmioutput::HDCPProtocolVersion> supportedHDCPProtocolVersions;
  ::std::vector<::com::rdk::hal::hdmioutput::Colorimetry> supportedColorimetries;
  ::std::vector<::com::rdk::hal::hdmioutput::ExtendedColorimetry> supportedExtendedColorimetries;
  ::std::vector<::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension> supportedAdditionalColorimetryExtensions;
  ::std::vector<int32_t> supportedColorDepths;
  ::std::vector<::com::rdk::hal::hdmioutput::PixelFormat> supportedPixelFormats;
  bool supports3D = false;
  bool supportsFRL = false;
  bool supportsVRR = false;
  bool supportsFreeSync = false;
  bool supportsQMS = false;
  bool supportsALLM = false;
  bool supportsQFT = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) != std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) < std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) <= std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) == std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) > std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedVersions, supportedVICs, supportedHDROutputModes, supportsForcedHDROutputModes, supportedHDCPProtocolVersions, supportedColorimetries, supportedExtendedColorimetries, supportedAdditionalColorimetryExtensions, supportedColorDepths, supportedPixelFormats, supports3D, supportsFRL, supportsVRR, supportsFreeSync, supportsQMS, supportsALLM, supportsQFT) >= std::tie(rhs.supportedVersions, rhs.supportedVICs, rhs.supportedHDROutputModes, rhs.supportsForcedHDROutputModes, rhs.supportedHDCPProtocolVersions, rhs.supportedColorimetries, rhs.supportedExtendedColorimetries, rhs.supportedAdditionalColorimetryExtensions, rhs.supportedColorDepths, rhs.supportedPixelFormats, rhs.supports3D, rhs.supportsFRL, rhs.supportsVRR, rhs.supportsFreeSync, rhs.supportsQMS, rhs.supportsALLM, rhs.supportsQFT);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedVersions: " << ::android::internal::ToString(supportedVersions);
    os << ", supportedVICs: " << ::android::internal::ToString(supportedVICs);
    os << ", supportedHDROutputModes: " << ::android::internal::ToString(supportedHDROutputModes);
    os << ", supportsForcedHDROutputModes: " << ::android::internal::ToString(supportsForcedHDROutputModes);
    os << ", supportedHDCPProtocolVersions: " << ::android::internal::ToString(supportedHDCPProtocolVersions);
    os << ", supportedColorimetries: " << ::android::internal::ToString(supportedColorimetries);
    os << ", supportedExtendedColorimetries: " << ::android::internal::ToString(supportedExtendedColorimetries);
    os << ", supportedAdditionalColorimetryExtensions: " << ::android::internal::ToString(supportedAdditionalColorimetryExtensions);
    os << ", supportedColorDepths: " << ::android::internal::ToString(supportedColorDepths);
    os << ", supportedPixelFormats: " << ::android::internal::ToString(supportedPixelFormats);
    os << ", supports3D: " << ::android::internal::ToString(supports3D);
    os << ", supportsFRL: " << ::android::internal::ToString(supportsFRL);
    os << ", supportsVRR: " << ::android::internal::ToString(supportsVRR);
    os << ", supportsFreeSync: " << ::android::internal::ToString(supportsFreeSync);
    os << ", supportsQMS: " << ::android::internal::ToString(supportsQMS);
    os << ", supportsALLM: " << ::android::internal::ToString(supportsALLM);
    os << ", supportsQFT: " << ::android::internal::ToString(supportsQFT);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
