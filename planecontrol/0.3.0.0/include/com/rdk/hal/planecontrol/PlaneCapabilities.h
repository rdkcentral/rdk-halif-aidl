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
// @aidl-doc
/**
 *  @brief     Plane resource capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class PlaneCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * 0 based index of this plane resource.
   * Video planes shall be listed first, with the primary video plane at resource index 0.
   * Graphics planes are listed next.
   */
  int32_t planeIndex = 0;
  // @aidl-doc
  /** The type of plane. */
  ::com::rdk::hal::planecontrol::PlaneType type = ::com::rdk::hal::planecontrol::PlaneType(0);
  // @aidl-doc
  /** The list of pixel formats supported by this plane. */
  ::std::vector<::com::rdk::hal::videodecoder::PixelFormat> pixelFormats;
  // @aidl-doc
  /** The list of video source types the plane supports. */
  ::std::vector<::com::rdk::hal::planecontrol::SourceType> sourceTypes;
  // @aidl-doc
  /**
   * The maximum width and height in pixels the plane can be set to.
   * `maxWidth` must be <= `frameWidth` and `maxHeight` must be <= `frameHeight`.
   */
  int32_t maxWidth = 0;
  // @aidl-doc
  /** The maximum height in pixels the plane can be set to. */
  int32_t maxHeight = 0;
  // @aidl-doc
  /**
   * The frame width and height the plane geometry references.
   * This defines the full frame coordinate system that `maxWidth`, `maxHeight` and other properties
   * are defined by.
   */
  int32_t frameWidth = 0;
  // @aidl-doc
  /** The frame height the plane geometry references. */
  int32_t frameHeight = 0;
  // @aidl-doc
  /** Array of DynamicRange values supported by this plane instance. */
  ::std::vector<::com::rdk::hal::videodecoder::DynamicRange> supportedDynamicRanges;
  // @aidl-doc
  /**
   * The color depth of the pixel format.
   * e.g. 8, 10, 12.
   */
  int32_t colorDepth = 0;
  // @aidl-doc
  /**
   * The maximum frame rate supported by the plane in frames per second.
   * e.g. 60, 120.
   */
  int32_t maxFrameRate = 0;
  // @aidl-doc
  /** Indicates if the plane supports the ALPHA property. */
  bool supportsAlpha = false;
  // @aidl-doc
  /**
   * Indicates whether the plane supports the ZORDER property.
   * Must be false for the primary graphics plane.
   */
  bool supportsZOrder = false;
  // @aidl-doc
  /**
   * Specifies the display latency of this plane.
   * Measured in vsync periods, the display latency is measured from
   * the moment a change is made to plane (e.g. video frame presented)
   * to the moment it appears on the output display (e.g. panel or HDMI output).
   */
  int32_t vsyncDisplayLatency = 0;
  inline bool operator!=(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) != std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator<(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) < std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator<=(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) <= std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator==(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) == std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator>(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) > std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }
  inline bool operator>=(const PlaneCapabilities& rhs) const {
    return std::tie(planeIndex, type, pixelFormats, sourceTypes, maxWidth, maxHeight, frameWidth, frameHeight, supportedDynamicRanges, colorDepth, maxFrameRate, supportsAlpha, supportsZOrder, vsyncDisplayLatency) >= std::tie(rhs.planeIndex, rhs.type, rhs.pixelFormats, rhs.sourceTypes, rhs.maxWidth, rhs.maxHeight, rhs.frameWidth, rhs.frameHeight, rhs.supportedDynamicRanges, rhs.colorDepth, rhs.maxFrameRate, rhs.supportsAlpha, rhs.supportsZOrder, rhs.vsyncDisplayLatency);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.planecontrol.PlaneCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlaneCapabilities{";
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
};  // class PlaneCapabilities
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
