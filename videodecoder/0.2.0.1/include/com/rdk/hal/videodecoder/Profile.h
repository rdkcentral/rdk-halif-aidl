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
class Profile : public ::android::Parcelable {
public:
  ::com::rdk::hal::videodecoder::CodecProfile profile = ::com::rdk::hal::videodecoder::CodecProfile(0);
  ::com::rdk::hal::videodecoder::CodecLevel maxLevel = ::com::rdk::hal::videodecoder::CodecLevel(0);
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
