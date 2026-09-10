#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class GraphicsFbCapabilities : public ::android::Parcelable {
public:
  int32_t maxGraphicsFrameBuffers = 0;
  int32_t maxGraphicsFbWidth = 0;
  int32_t maxGraphicsFbHeight = 0;
  int32_t format = 0;
  int64_t modifier = 0L;
  inline bool operator!=(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) != std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }
  inline bool operator<(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) < std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }
  inline bool operator<=(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) <= std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }
  inline bool operator==(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) == std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }
  inline bool operator>(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) > std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }
  inline bool operator>=(const GraphicsFbCapabilities& rhs) const {
    return std::tie(maxGraphicsFrameBuffers, maxGraphicsFbWidth, maxGraphicsFbHeight, format, modifier) >= std::tie(rhs.maxGraphicsFrameBuffers, rhs.maxGraphicsFbWidth, rhs.maxGraphicsFbHeight, rhs.format, rhs.modifier);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.planecontrol.GraphicsFbCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "GraphicsFbCapabilities{";
    os << "maxGraphicsFrameBuffers: " << ::android::internal::ToString(maxGraphicsFrameBuffers);
    os << ", maxGraphicsFbWidth: " << ::android::internal::ToString(maxGraphicsFbWidth);
    os << ", maxGraphicsFbHeight: " << ::android::internal::ToString(maxGraphicsFbHeight);
    os << ", format: " << ::android::internal::ToString(format);
    os << ", modifier: " << ::android::internal::ToString(modifier);
    os << "}";
    return os.str();
  }
};  // class GraphicsFbCapabilities
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
