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
namespace videosink {
// @aidl-doc
/**
 *  @brief     Video Sink capabilities parcelable definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 *
 *  Per-instance, immutable Video Sink capabilities, populated by the SoC
 *  vendor from the HAL Feature Profile (`hfp-videosink.yaml`). The values
 *  returned by `IVideoSink.getCapabilities()` must not change between calls
 *  for the lifetime of the Video Sink instance.
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Indicates whether this Video Sink instance can synchronise frame
   * presentation against an AV Clock. When `false`, the sink presents
   * frames as soon as they are decoded (best-effort display).
   * Mirrors `IVideoSink[i].supportsAVSync` in the HFP.
   */
  bool supportsAVSync = false;
  // @aidl-doc
  /**
   * Vendor-characterised latency, in nanoseconds, between the moment a
   * frame is committed for display and the moment it is actually scanned
   * out on the display. Used by AV-sync logic to compensate for sink
   * pipeline delay. Mirrors `IVideoSink[i].vsyncDisplayLatencyNs` in the
   * HFP.
   */
  int64_t vsyncDisplayLatencyNs = 0L;
  // @aidl-doc
  /**
   * Indicates whether this Video Sink instance can hold and continue to
   * display the most recent frame after the upstream source stops
   * delivering frames (for example on `stop()` or underflow), rather than
   * blanking the output. Mirrors `IVideoSink[i].supportsHoldLastFrame`
   * in the HFP.
   */
  bool supportsHoldLastFrame = false;
  // @aidl-doc
  /**
   * Indicates whether this Video Sink instance is able to operate in
   * Secure Video Path (SVP) mode and consume buffers carrying protected
   * content. Mirrors `IVideoSink[i].supportsSecure` in the HFP.
   */
  bool supportsSecure = false;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) != std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) < std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) <= std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) == std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) > std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportsAVSync, vsyncDisplayLatencyNs, supportsHoldLastFrame, supportsSecure) >= std::tie(rhs.supportsAVSync, rhs.vsyncDisplayLatencyNs, rhs.supportsHoldLastFrame, rhs.supportsSecure);
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
    os << "supportsAVSync: " << ::android::internal::ToString(supportsAVSync);
    os << ", vsyncDisplayLatencyNs: " << ::android::internal::ToString(vsyncDisplayLatencyNs);
    os << ", supportsHoldLastFrame: " << ::android::internal::ToString(supportsHoldLastFrame);
    os << ", supportsSecure: " << ::android::internal::ToString(supportsSecure);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
