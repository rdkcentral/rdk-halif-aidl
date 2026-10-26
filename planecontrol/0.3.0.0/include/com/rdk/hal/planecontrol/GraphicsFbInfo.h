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
 *  @brief     Graphics Frame Buffer Info.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class GraphicsFbInfo : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Uniquely identifies this Graphics Frame Buffer. */
  int32_t graphicsFbId = 0;
  // @aidl-doc
  /** Width of the created gfx frame in pixels. */
  int32_t pixelWidth = 0;
  // @aidl-doc
  /** Height of the created gfx frame in pixels. */
  int32_t pixelHeight = 0;
  // @aidl-doc
  /** Stride - The number of bytes from the start of one row of pixels to the start of the next row. */
  int32_t stride = 0;
  // @aidl-doc
  /**
   * Offset - The number of bytes from the very beginning of the DMA-BUF file descriptor's memory to the actual start
   * of the pixel data.
   */
  int32_t offset = 0;
  inline bool operator!=(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) != std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }
  inline bool operator<(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) < std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }
  inline bool operator<=(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) <= std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }
  inline bool operator==(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) == std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }
  inline bool operator>(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) > std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }
  inline bool operator>=(const GraphicsFbInfo& rhs) const {
    return std::tie(graphicsFbId, pixelWidth, pixelHeight, stride, offset) >= std::tie(rhs.graphicsFbId, rhs.pixelWidth, rhs.pixelHeight, rhs.stride, rhs.offset);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.planecontrol.GraphicsFbInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "GraphicsFbInfo{";
    os << "graphicsFbId: " << ::android::internal::ToString(graphicsFbId);
    os << ", pixelWidth: " << ::android::internal::ToString(pixelWidth);
    os << ", pixelHeight: " << ::android::internal::ToString(pixelHeight);
    os << ", stride: " << ::android::internal::ToString(stride);
    os << ", offset: " << ::android::internal::ToString(offset);
    os << "}";
    return os.str();
  }
};  // class GraphicsFbInfo
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
