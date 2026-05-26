#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/WhiteBalance2PointSettings.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class WhiteBalance2PointSettings : public ::android::Parcelable {
public:
  class Point : public ::android::Parcelable {
  public:
    int32_t gain = 0;
    int32_t offset = 0;
    inline bool operator!=(const Point& rhs) const {
      return std::tie(gain, offset) != std::tie(rhs.gain, rhs.offset);
    }
    inline bool operator<(const Point& rhs) const {
      return std::tie(gain, offset) < std::tie(rhs.gain, rhs.offset);
    }
    inline bool operator<=(const Point& rhs) const {
      return std::tie(gain, offset) <= std::tie(rhs.gain, rhs.offset);
    }
    inline bool operator==(const Point& rhs) const {
      return std::tie(gain, offset) == std::tie(rhs.gain, rhs.offset);
    }
    inline bool operator>(const Point& rhs) const {
      return std::tie(gain, offset) > std::tie(rhs.gain, rhs.offset);
    }
    inline bool operator>=(const Point& rhs) const {
      return std::tie(gain, offset) >= std::tie(rhs.gain, rhs.offset);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.WhiteBalance2PointSettings.Point");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Point{";
      os << "gain: " << ::android::internal::ToString(gain);
      os << ", offset: " << ::android::internal::ToString(offset);
      os << "}";
      return os.str();
    }
  };  // class Point
  ::com::rdk::hal::panel::WhiteBalance2PointSettings::Point r;
  ::com::rdk::hal::panel::WhiteBalance2PointSettings::Point g;
  ::com::rdk::hal::panel::WhiteBalance2PointSettings::Point b;
  inline bool operator!=(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) != std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) < std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator<=(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) <= std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator==(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) == std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) > std::tie(rhs.r, rhs.g, rhs.b);
  }
  inline bool operator>=(const WhiteBalance2PointSettings& rhs) const {
    return std::tie(r, g, b) >= std::tie(rhs.r, rhs.g, rhs.b);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.WhiteBalance2PointSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "WhiteBalance2PointSettings{";
    os << "r: " << ::android::internal::ToString(r);
    os << ", g: " << ::android::internal::ToString(g);
    os << ", b: " << ::android::internal::ToString(b);
    os << "}";
    return os.str();
  }
};  // class WhiteBalance2PointSettings
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
