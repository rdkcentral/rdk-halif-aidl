#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/ImplementationVersion.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
class ImplementationVersion : public ::android::Parcelable {
public:
  class Version : public ::android::Parcelable {
  public:
    int32_t major = 0;
    int32_t minor = 0;
    int32_t patch = 0;
    inline bool operator!=(const Version& rhs) const {
      return std::tie(major, minor, patch) != std::tie(rhs.major, rhs.minor, rhs.patch);
    }
    inline bool operator<(const Version& rhs) const {
      return std::tie(major, minor, patch) < std::tie(rhs.major, rhs.minor, rhs.patch);
    }
    inline bool operator<=(const Version& rhs) const {
      return std::tie(major, minor, patch) <= std::tie(rhs.major, rhs.minor, rhs.patch);
    }
    inline bool operator==(const Version& rhs) const {
      return std::tie(major, minor, patch) == std::tie(rhs.major, rhs.minor, rhs.patch);
    }
    inline bool operator>(const Version& rhs) const {
      return std::tie(major, minor, patch) > std::tie(rhs.major, rhs.minor, rhs.patch);
    }
    inline bool operator>=(const Version& rhs) const {
      return std::tie(major, minor, patch) >= std::tie(rhs.major, rhs.minor, rhs.patch);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.ImplementationVersion.Version");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Version{";
      os << "major: " << ::android::internal::ToString(major);
      os << ", minor: " << ::android::internal::ToString(minor);
      os << ", patch: " << ::android::internal::ToString(patch);
      os << "}";
      return os.str();
    }
  };  // class Version
  ::com::rdk::hal::broadcast::ImplementationVersion::Version version;
  ::std::string name;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) != std::tie(rhs.version, rhs.name, rhs.extension);
  }
  inline bool operator<(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) < std::tie(rhs.version, rhs.name, rhs.extension);
  }
  inline bool operator<=(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) <= std::tie(rhs.version, rhs.name, rhs.extension);
  }
  inline bool operator==(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) == std::tie(rhs.version, rhs.name, rhs.extension);
  }
  inline bool operator>(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) > std::tie(rhs.version, rhs.name, rhs.extension);
  }
  inline bool operator>=(const ImplementationVersion& rhs) const {
    return std::tie(version, name, extension) >= std::tie(rhs.version, rhs.name, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.ImplementationVersion");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ImplementationVersion{";
    os << "version: " << ::android::internal::ToString(version);
    os << ", name: " << ::android::internal::ToString(name);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class ImplementationVersion
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
