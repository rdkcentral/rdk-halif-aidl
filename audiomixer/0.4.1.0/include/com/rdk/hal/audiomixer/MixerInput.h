#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/ContentType.h>
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
 * @brief Audio Mixer Input Capability Definition.
 *
 * Describes the capabilities of a single mixer input, including supported
 * content types (STREAM, CLIP, TTS) and codecs (PCM, AC3, etc.).
 *
 * Usage workflow:
 * 1. Call IAudioMixer.getCapabilities() to retrieve Capabilities.inputs[] array
 * 2. Examine each inputs[i] to find a mixer input that supports your codec/content type
 * 3. Use the array index i in InputRouting to connect your audio source to that mixer input
 *
 * For example, to route compressed AC3 audio:
 * - Check inputs[0].supportedCodecs contains Codec.AC3
 * - Use setInputRouting() with routing[0] to connect your source to mixer input 0
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
class MixerInput : public ::android::Parcelable {
public:
  // @aidl-doc
  /** @brief List of content types this input supports. */
  ::std::vector<::com::rdk::hal::audiomixer::ContentType> supportedContentTypes;
  // @aidl-doc
  /** @brief List of codecs supported for this input. */
  ::std::vector<::com::rdk::hal::audiodecoder::Codec> supportedCodecs;
  // @aidl-doc
  /**
   * @brief Human-readable name for this audio mixer input.
   * May be null if not set by the platform.
   *          Examples: "main", "assoc", "pcm1", "pcm2", "aux".
   *          Although optional, this field aids debugging, logging, and platform introspection.
   */
  ::std::optional<::std::string> name;
  inline bool operator!=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) != std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator<(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) < std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator<=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) <= std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator==(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) == std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator>(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) > std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }
  inline bool operator>=(const MixerInput& rhs) const {
    return std::tie(supportedContentTypes, supportedCodecs, name) >= std::tie(rhs.supportedContentTypes, rhs.supportedCodecs, rhs.name);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.MixerInput");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "MixerInput{";
    os << "supportedContentTypes: " << ::android::internal::ToString(supportedContentTypes);
    os << ", supportedCodecs: " << ::android::internal::ToString(supportedCodecs);
    os << ", name: " << ::android::internal::ToString(name);
    os << "}";
    return os.str();
  }
};  // class MixerInput
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
