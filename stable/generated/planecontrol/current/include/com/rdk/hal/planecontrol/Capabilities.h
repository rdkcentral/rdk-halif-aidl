#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/planecontrol/PlaneType.h>
#include <com/rdk/hal/planecontrol/SourceType.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <com/rdk/hal/videodecoder/PixelFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class Capabilities : public ::android::Parcelable {
public:
  int32_t planeIndex = 0;
  ::com::rdk::hal::planecontrol::PlaneType type = ::com::rdk::hal::planecontrol::PlaneType(0);
  ::std::vector<::com::rdk::hal::videodecoder::PixelFormat> pixelFormats;
  ::std::vector<::com::rdk::hal::planecontrol::SourceType> sourceTypes;
  int32_t maxWidth = 0;
  int32_t maxHeight = 0;
  int32_t frameWidth = 0;
  int32_t frameHeight = 0;
  ::std::vector<::com::rdk::hal::videodecoder::DynamicRange> supportedDynamicRanges;
  int32_t colorDepth = 0;
  int32_t maxFrameRate = 0;
  bool supportsAlpha = false;
  bool supportsZOrder = false;
  int32_t vsyncDisplayLatency = 0;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) != std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) < std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) <= std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) == std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) > std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) >= std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.planecontrol.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "planeIndex: " << ::android::internal::ToString(planeIndex);
    os << ", type: " << ::android::internal::ToString(type);
    os << ", pixelFormats: " << ::android::internal::ToString(pixelFormats);
    os << ", sourceTypes: " << ::android::internal::ToString(sourceTypes);
    os << ", maxWidth: " << ::android::internal::ToString(maxWidth);
    os << ", maxHeight: " << ::android::internal::ToString(maxHeight);
    os << ", frameWidth: " << ::android::internal::ToString(frameWidth);
    os << ", frameHeight: " << ::android::internal::ToString(frameHeight);
    os << ", supportedDynamicRanges: " << ::android::internal::ToString(supportedDynamicRanges);
    os << ", colorDepth: " << ::android::internal::ToString(colorDepth);
    os << ", maxFrameRate: " << ::android::internal::ToString(maxFrameRate);
    os << ", supportsAlpha: " << ::android::internal::ToString(supportsAlpha);
    os << ", supportsZOrder: " << ::android::internal::ToString(supportsZOrder);
    os << ", vsyncDisplayLatency: " << ::android::internal::ToString(vsyncDisplayLatency);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
