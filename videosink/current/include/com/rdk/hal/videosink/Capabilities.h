#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videosink/MemoryType.h>
#include <com/rdk/hal/videosink/PixelFormat.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
class Capabilities : public ::android::Parcelable {
public:
  ::std::vector<::com::rdk::hal::videosink::PixelFormat> supportedPixelFormats;
  ::std::vector<::com::rdk::hal::videosink::MemoryType> supportedMemoryTypes;
  int32_t sinkQueueDepth = 0;
  bool supportsAVSync = false;
  int64_t vsyncDisplayLatencyNs = 0L;
  bool supportsHoldLastFrame = false;
  bool supportsSecure = false;
  int32_t planeIndex = 0;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) != std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) < std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) <= std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) == std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) > std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedPixelFormats, supportedMemoryTypes, sinkQueueDepth, supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure, planeIndex) >= std::tie(rhs.supportedPixelFormats, rhs.supportedMemoryTypes, rhs.sinkQueueDepth, rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure, rhs.planeIndex);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videosink.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedPixelFormats: " << ::android::internal::ToString(supportedPixelFormats);
    os << ", supportedMemoryTypes: " << ::android::internal::ToString(supportedMemoryTypes);
    os << ", sinkQueueDepth: " << ::android::internal::ToString(sinkQueueDepth);
    os << ", supportsAVSync: " << ::android::internal::ToString(supportsAVSync);
    os << ", vsyncDisplayLatencyNs: " << ::android::internal::ToString(vsyncDisplayLatencyNs);
    os << ", supportsHoldLastFrame: " << ::android::internal::ToString(supportsHoldLastFrame);
    os << ", supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << ", planeIndex: " << ::android::internal::ToString(planeIndex);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
