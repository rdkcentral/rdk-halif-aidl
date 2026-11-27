#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/MixerInput.h>
#include <com/rdk/hal/audiomixer/Property.h>
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
 * @brief Capabilities structure for Audio Mixer.
 *
 * Describes whether the mixer supports secure audio processing and
 * details all supported input configurations, including the number
 * and type of inputs, supported content types and codecs.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief Indicates if this mixer instance supports secure audio path mode. */
  bool supportsSecure = false;
  // @aidl-doc
  /**
   * List of property keys supported by this mixer.
   * e.g. MIXING_MODE and MUTE.
   */
  ::std::vector<::com::rdk::hal::audiomixer::Property> supportedProperties;
  // @aidl-doc
  /**
   * @brief Describes the available audio mixer input specifications.
   *
   * Contains N mixer input capability definitions where each array element describes
   * the capabilities of the mixer input at that index position.
   *
   * The array index directly corresponds to the mixer input index:
   * - inputs[0] = mixer input 0 capabilities
   * - inputs[1] = mixer input 1 capabilities
   * - etc.
   *
   * When routing audio sources via setInputRouting(), check this array to:
   * 1. Find which mixer input(s) support your required codec (e.g., AC3, PCM)
   * 2. Verify the input supports your content type (STREAM, CLIP, TTS)
   * 3. Use the matching array index in the InputRouting array to connect your source
   *
   * The array length indicates the total number of mixer inputs available.
   */
  ::std::vector<::com::rdk::hal::audiomixer::MixerInput> inputs;
  // @aidl-doc
  /**
   * @brief Human-readable name for this audio mixer instance.
   * May be null if not set by the platform.
   *          Although optional, this field is intended to aid debugging, logging, and platform introspection.
   */
  ::std::optional<::std::string> name;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) != std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) < std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) <= std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) == std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) > std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportsSecure, supportedProperties, inputs, name) >= std::tie(rhs.supportsSecure, rhs.supportedProperties, rhs.inputs, rhs.name);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << ", supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << ", inputs: " << ::android::internal::ToString(inputs);
    os << ", name: " << ::android::internal::ToString(name);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
