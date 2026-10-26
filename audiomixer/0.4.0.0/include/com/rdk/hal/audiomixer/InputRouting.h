#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioSourceType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief     Audio source to mixer input routing definition.
 * Specifies which audio source is connected to a mixer input.
 *            The target mixer input is determined by the position in the
 *            InputRouting[] array passed to setInputRouting()/returned by
 *            getInputRouting():
 *            - routing[0] maps mixer input 0
 *            - routing[1] maps mixer input 1
 *            - etc.
 *
 *            This parcelable therefore only describes the source side of
 *            the mapping for one mixer input entry.
 *            Follows the pattern established by planecontrol::SourcePlaneMapping.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
class InputRouting : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The audio source type to route to this mixer input. */
  ::com::rdk::hal::audiomixer::AudioSourceType sourceType = ::com::rdk::hal::audiomixer::AudioSourceType(0);
  // @aidl-doc
  /**
   * The instance index of the specified audio source type.
   *
   * For example:
   * - If sourceType is AUDIO_SINK, sourceIndex specifies which sink instance (0, 1, 2...).
   * - If sourceType is HDMI_INPUT, sourceIndex specifies which HDMI input port (0, 1, 2...).
   *
   * Ignored if `sourceType` is `AudioSourceType.NONE`.
   */
  int32_t sourceIndex = 0;
  inline bool operator!=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) != std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator<(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) < std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator<=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) <= std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator==(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) == std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator>(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) > std::tie(rhs.sourceType, rhs.sourceIndex);
  }
  inline bool operator>=(const InputRouting& rhs) const {
    return std::tie(sourceType, sourceIndex) >= std::tie(rhs.sourceType, rhs.sourceIndex);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.InputRouting");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputRouting{";
    os << "sourceType: " << ::android::internal::ToString(sourceType);
    os << ", sourceIndex: " << ::android::internal::ToString(sourceIndex);
    os << "}";
    return os.str();
  }
};  // class InputRouting
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
