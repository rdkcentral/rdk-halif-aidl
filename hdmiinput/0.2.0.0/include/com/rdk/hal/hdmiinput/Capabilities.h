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
// @aidl-doc
/**
 *  @brief     HDMI input port device capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The array of HDMI versions the port supports.
   * Specifying more than one HDMI version indicates support for switching between versions.
   * @Note: supportsQMS requires supportsVRR to be true. supportsFreeSync is only meaningful if supportsVRR is true.
   */
  ::std::vector<::com::rdk::hal::hdmiinput::HDMIVersion> supportedVersions;
  // @aidl-doc
  /** The array of VIC the port supports. */
  ::std::vector<::com::rdk::hal::hdmiinput::VIC> supportedVICs;
  // @aidl-doc
  /** The array of HDCP protocol versions the HDMI input port supports. */
  ::std::vector<::com::rdk::hal::hdmiinput::HDCPProtocolVersion> supportedHDCPProtocolVersions;
  // @aidl-doc
  /** Indicates support for stereo (3D) video. */
  bool supports3D = false;
  // @aidl-doc
  /** Indicates support for fixed rate link (FRL). */
  bool supportsFRL = false;
  // @aidl-doc
  /**
   * Indicates support for HDMI Forum variable refresh rate (VRR),
   * as defined by the HDMI 2.1 specification.
   * AMD FreeSync support is indicated separately by supportsFreeSync.
   */
  bool supportsVRR = false;
  // @aidl-doc
  /**
   * Indicates support for AMD FreeSync.
   * @see PlatformCapabilities.freeSync to determine the type of FreeSync.
   */
  bool supportsFreeSync = false;
  // @aidl-doc
  /** Indicates support quick media switching (QMS is VRR with M_CONST). */
  bool supportsQMS = false;
  // @aidl-doc
  /** Indicates support for automatic low latency mode (ALLM). */
  bool supportsALLM = false;
  // @aidl-doc
  /** Indicates support for quick frame transport (QFT is aka Fast VActive). */
  bool supportsQFT = false;
  // @aidl-doc
  /** Indicates support for audio return channel (ARC). */
  bool supportsARC = false;
  // @aidl-doc
  /** Indicates support for enhanced audio return channel (eARC). */
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
