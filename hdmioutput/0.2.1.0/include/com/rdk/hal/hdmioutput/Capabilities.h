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
// @aidl-doc
/**
 *  @brief     HDMI output port device capabilities definition.
 *
 *  This parcelable encapsulates all HDMI output-related feature support
 *  exposed by a specific output port. It provides a comprehensive overview
 *  of supported resolutions, formats, protocols, and HDMI-specific extensions.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The array of HDMI versions the port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::HDMIVersion> supportedVersions;
  // @aidl-doc
  /** The array of VICs (Video Identification Codes) the port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::VIC> supportedVICs;
  // @aidl-doc
  /** The array of HDR modes the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::HDROutputMode> supportedHDROutputModes;
  // @aidl-doc
  /**
   * Whether the SoC supports forced HDR modes on the HDMI output.
   *
   * When forced, the current HDR dynamic range is locked as the output
   * format and does not change based on the primary video content.
   */
  bool supportsForcedHDROutputModes = false;
  // @aidl-doc
  /** The array of HDCP protocol versions the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::HDCPProtocolVersion> supportedHDCPProtocolVersions;
  // @aidl-doc
  /** The array of base colorimetries the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::Colorimetry> supportedColorimetries;
  // @aidl-doc
  /** The array of extended colorimetries the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::ExtendedColorimetry> supportedExtendedColorimetries;
  // @aidl-doc
  /** The array of additional colorimetry extensions the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::AdditionalColorimetryExtension> supportedAdditionalColorimetryExtensions;
  // @aidl-doc
  /**
   * The array of color bit depths the HDMI output port supports.
   * Example values: [8, 10, 12, 16]
   */
  ::std::vector<int32_t> supportedColorDepths;
  // @aidl-doc
  /** The array of pixel formats the HDMI output port supports. */
  ::std::vector<::com::rdk::hal::hdmioutput::PixelFormat> supportedPixelFormats;
  // @aidl-doc
  /** Indicates whether the HDMI output port supports stereo (3D) video. */
  bool supports3D = false;
  // @aidl-doc
  /** Indicates support for Fixed Rate Link (FRL). */
  bool supportsFRL = false;
  // @aidl-doc
  /** Indicates support for Variable Refresh Rate (VRR). */
  bool supportsVRR = false;
  // @aidl-doc
  /**
   * Indicates support for AMD FreeSync.
   *
   * @see PlatformCapabilities.freeSync for FreeSync capability level.
   */
  bool supportsFreeSync = false;
  // @aidl-doc
  /**
   * Indicates support for Quick Media Switching (QMS).
   * QMS is implemented using VRR with M_CONST.
   */
  bool supportsQMS = false;
  // @aidl-doc
  /** Indicates support for Auto Low Latency Mode (ALLM). */
  bool supportsALLM = false;
  // @aidl-doc
  /**
   * Indicates support for Quick Frame Transport (QFT).
   * QFT is based on Fast VActive signaling.
   */
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
