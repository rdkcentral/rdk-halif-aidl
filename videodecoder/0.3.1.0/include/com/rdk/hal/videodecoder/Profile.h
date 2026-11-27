#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/CodecLevel.h>
#include <com/rdk/hal/videodecoder/CodecProfile.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Per-profile capability descriptor for a codec — pairs a
 *             `CodecProfile` with the maximum level and bitrate the
 *             decoder advertises for that profile.
 *
 *  Used inside `CodecCapabilities.profiles[]` so a codec entry can
 *  advertise multiple profiles independently. The previous model
 *  (single `profile` + `level` per codec) couldn't express the common
 *  case where hardware supports several profiles per codec at the same
 *  level (e.g. H.265 supporting MAIN, MAIN_10, and MAIN_10_HDR10 each
 *  at LEVEL_5_2).
 *
 *  <h3>"Max" semantics</h3>
 *  Both `maxLevel` and `maxBitrateInBps` are inclusive ceilings. All
 *  lower levels for the same profile are implicitly supported. A
 *  bitstream at or below `maxLevel` and at or below `maxBitrateInBps`
 *  is in-spec for this profile.
 *
 *  Shape mirrors `rdk-hpk-documentation/hfp-reference/videodecoder/
 *  hfp-videodecoder.yaml` field-for-field so the HFP YAML reads as a
 *  direct serialisation of the AIDL parcelable.
 *
 *  @author    Gerald Weatherup
 */
class Profile : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The codec profile this descriptor applies to (e.g. `H265_MAIN`,
   * `H265_MAIN_10`, `AV1_MAIN`).
   */
  ::com::rdk::hal::videodecoder::CodecProfile profile = ::com::rdk::hal::videodecoder::CodecProfile(0);
  // @aidl-doc
  /**
   * The maximum supported level for this profile. All lower levels
   * for the same profile are also supported.
   */
  ::com::rdk::hal::videodecoder::CodecLevel maxLevel = ::com::rdk::hal::videodecoder::CodecLevel(0);
  // @aidl-doc
  /**
   * The maximum decode bitrate in bits per second for this
   * profile/level combination.
   *
   * Use `0` to indicate "no explicit limit advertised" — most
   * platforms should report a real ceiling here, but `0` keeps the
   * field non-null for cases where the SoC vendor genuinely doesn't
   * publish a bitrate cap.
   */
  int64_t maxBitrateInBps = 0L;
  inline bool operator!=(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) != std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }
  inline bool operator<(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) < std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }
  inline bool operator<=(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) <= std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }
  inline bool operator==(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) == std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }
  inline bool operator>(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) > std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }
  inline bool operator>=(const Profile& rhs) const {
    return std::tie(profile, maxLevel, maxBitrateInBps) >= std::tie(rhs.profile, rhs.maxLevel, rhs.maxBitrateInBps);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Profile");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Profile{";
    os << "profile: " << ::android::internal::ToString(profile);
    os << ", maxLevel: " << ::android::internal::ToString(maxLevel);
    os << ", maxBitrateInBps: " << ::android::internal::ToString(maxBitrateInBps);
    os << "}";
    return os.str();
  }
};  // class Profile
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
