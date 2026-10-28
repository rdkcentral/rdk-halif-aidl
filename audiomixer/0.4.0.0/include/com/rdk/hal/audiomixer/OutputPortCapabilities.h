#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AQProcessor.h>
#include <com/rdk/hal/audiomixer/OutputFormat.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <com/rdk/hal/audiomixer/OutputPortType.h>
#include <optional>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief    Capabilities for an audio output port.
 * Enumerates which properties can be set or queried for a given port,
 *           plus codec/format support and AQ processors.
 * @note     This structure is descriptive only. Property reads use
 *           IAudioOutputPort.getProperty(); property writes use
 *           IAudioOutputPortController.setProperty() (controller acquired via
 *           IAudioOutputPort.open()).
 */
class OutputPortCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * @brief Human-readable name or role for this output port (e.g., "HDMI", "SPDIF", "Speakers").
   * @details Required, declared per output port in hfp-audiomixer.yaml under
   *          outputPorts[].portName. Used for debugging, logging, and
   *          user-facing diagnostics. For programmatic type identification
   *          and policy branching, use `portType` instead.
   */
  ::std::string portName;
  // @aidl-doc
  /**
   * @brief Programmatic type of this output port.
   * @details Declared per output port in hfp-audiomixer.yaml under
   *          outputPorts[].portType. Middleware should branch on this enum
   *          (not on the string `portName`) when applying type-specific
   *          policy — e.g. transcode-to-AC3 only on SPDIF, hot-unplug
   *          handling only on HDMI/ARC/EARC, pairing flow only on BLUETOOTH.
   *
   *          Multiple ports of the same type may exist (e.g. two HDMI
   *          outputs); use `portName` to distinguish them.
   */
  ::com::rdk::hal::audiomixer::OutputPortType portType = ::com::rdk::hal::audiomixer::OutputPortType(0);
  // @aidl-doc
  /**
   * List of property keys supported by this output port (see OutputPortProperty).
   * E.g., VOLUME, DELAY_MS, OUTPUT_FORMAT, etc.
   */
  ::std::vector<::com::rdk::hal::audiomixer::OutputPortProperty> supportedProperties;
  // @aidl-doc
  /** List of supported output audio formats. */
  ::std::vector<::com::rdk::hal::audiomixer::OutputFormat> supportedOutputFormats;
  // @aidl-doc
  /** List of AQ processor instances supported (first is default). */
  ::std::vector<::com::rdk::hal::audiomixer::AQProcessor> supportedAQProcessors;
  // @aidl-doc
  /**
   * List Dolby MS12 Audio Profiles (first is default).
   * If there are no defined MS12 Audio Profiles for this audio port then
   * dolbyMs12AudioProfiles is not populated with profile strings.
   */
  ::std::optional<::std::vector<::std::optional<::std::string>>> dolbyMs12AudioProfiles;
  // @aidl-doc
  /**
   * @brief   True when this port supports audio capture via
   *          IAudioOutputPortController.getAudioCapture().
   *
   * @details If true, clients holding the port controller (acquired
   *          via IAudioOutputPort.open()) may call
   *          IAudioOutputPortController.getAudioCapture(listener) to
   *          obtain an IAudioCapture interface for streaming audio
   *          from this port. If false, calling @c getAudioCapture()
   *          throws binder::Status EX_UNSUPPORTED_OPERATION. Capture
   *          acquisition is gated by holding the port controller —
   *          the read-side IAudioOutputPort handle does not expose
   *          getAudioCapture().
   *
   * @see     IAudioOutputPortController.getAudioCapture()
   */
  bool supportsAudioCapture = false;
  inline bool operator!=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) != std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator<(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) < std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator<=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) <= std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator==(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) == std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator>(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) > std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }
  inline bool operator>=(const OutputPortCapabilities& rhs) const {
    return std::tie(portName, portType, supportedProperties, supportedOutputFormats, supportedAQProcessors, dolbyMs12AudioProfiles, supportsAudioCapture) >= std::tie(rhs.portName, rhs.portType, rhs.supportedProperties, rhs.supportedOutputFormats, rhs.supportedAQProcessors, rhs.dolbyMs12AudioProfiles, rhs.supportsAudioCapture);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.OutputPortCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "OutputPortCapabilities{";
    os << "portName: " << ::android::internal::ToString(portName);
    os << ", portType: " << ::android::internal::ToString(portType);
    os << ", supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", supportedOutputFormats: " << ::android::internal::ToString(supportedOutputFormats);
    os << ", supportedAQProcessors: " << ::android::internal::ToString(supportedAQProcessors);
    os << ", dolbyMs12AudioProfiles: " << ::android::internal::ToString(dolbyMs12AudioProfiles);
    os << ", supportsAudioCapture: " << ::android::internal::ToString(supportsAudioCapture);
    os << "}";
    return os.str();
  }
};  // class OutputPortCapabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
