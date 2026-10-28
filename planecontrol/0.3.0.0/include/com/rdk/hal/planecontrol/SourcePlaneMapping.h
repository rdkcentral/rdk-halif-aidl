#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/planecontrol/SourceType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
// @aidl-doc
/**
 *  @brief     Video source to plane mapping definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class SourcePlaneMapping : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The video source type to map. */
  ::com::rdk::hal::planecontrol::SourceType sourceType = ::com::rdk::hal::planecontrol::SourceType(0);
  // @aidl-doc
  /**
   * The index of the video source.
   * Ignored if `sourceType` is `SourceType.NONE`.
   */
  int32_t sourceIndex = 0;
  // @aidl-doc
  /**
   * The index of the plane to use as the destination for the video source.
   * A value of -1 indicates no plane.
   */
  int32_t destinationPlaneIndex = 0;
  inline bool operator!=(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) != std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }
  inline bool operator<(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) < std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }
  inline bool operator<=(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) <= std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }
  inline bool operator==(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) == std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }
  inline bool operator>(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) > std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }
  inline bool operator>=(const SourcePlaneMapping& rhs) const {
    return std::tie(sourceType, sourceIndex, destinationPlaneIndex) >= std::tie(rhs.sourceType, rhs.sourceIndex, rhs.destinationPlaneIndex);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.planecontrol.SourcePlaneMapping");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SourcePlaneMapping{";
    os << "sourceType: " << ::android::internal::ToString(sourceType);
    os << ", sourceIndex: " << ::android::internal::ToString(sourceIndex);
    os << ", destinationPlaneIndex: " << ::android::internal::ToString(destinationPlaneIndex);
    os << "}";
    return os.str();
  }
};  // class SourcePlaneMapping
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
