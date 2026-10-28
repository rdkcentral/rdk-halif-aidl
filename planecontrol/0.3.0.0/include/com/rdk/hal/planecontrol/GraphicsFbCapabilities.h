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
// @aidl-doc
/**
 *  @brief      Dma-Buf interface capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class GraphicsFbCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The maxGraphicsFrameBuffers indicates the maximum number of frame buffers that can be created for use on this
   * plane.
   */
  int32_t maxGraphicsFrameBuffers = 0;
  // @aidl-doc
  /**
   * The maximum width and height in pixels that the frame buffer can be created with.
   * Typically the width and height will match the plane width and height.
   */
  int32_t maxGraphicsFbWidth = 0;
  // @aidl-doc
  /** The maximum height in pixels that the frame buffer can be created with. */
  int32_t maxGraphicsFbHeight = 0;
  // @aidl-doc
  /**
   * The pixel format of the returned graphics frame.
   * This is an opaque value expected to be known to the client EGL implementation.
   * For validation purposes a constant value in the hfp can be used.
   * This value is opaque in that it is passed through this interface without any understanding of its value.
   */
  int32_t format = 0;
  // @aidl-doc
  /**
   * Modifiers that describe the buffer format.
   * This is an opaque value expected to be known to the client EGL implementation.
   * For validation purposes a constant value in the hfp can be used.
   * This value is opaque in that it is passed through this interface without any understanding of its value.
   */
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
