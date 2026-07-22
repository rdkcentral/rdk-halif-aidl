#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/ColorMatrix.h>
#include <com/rdk/hal/videodecoder/ColorPrimaries.h>
#include <com/rdk/hal/videodecoder/ColorRange.h>
#include <com/rdk/hal/videodecoder/TransferCharacteristics.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class Colorimetry : public ::android::Parcelable {
public:
  ::com::rdk::hal::videodecoder::ColorRange range = ::com::rdk::hal::videodecoder::ColorRange::UNKNOWN;
  ::com::rdk::hal::videodecoder::ColorMatrix matrix = ::com::rdk::hal::videodecoder::ColorMatrix::UNKNOWN;
  ::com::rdk::hal::videodecoder::TransferCharacteristics transfer = ::com::rdk::hal::videodecoder::TransferCharacteristics::UNKNOWN;
  ::com::rdk::hal::videodecoder::ColorPrimaries primaries = ::com::rdk::hal::videodecoder::ColorPrimaries::UNKNOWN;
  inline bool operator!=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) != std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator<(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) < std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator<=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) <= std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator==(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) == std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator>(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) > std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }
  inline bool operator>=(const Colorimetry& rhs) const {
    return std::tie(range, matrix, transfer, primaries) >= std::tie(rhs.range, rhs.matrix, rhs.transfer, rhs.primaries);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.Colorimetry");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Colorimetry{";
    os << "range: " << ::android::internal::ToString(range);
    os << ", matrix: " << ::android::internal::ToString(matrix);
    os << ", transfer: " << ::android::internal::ToString(transfer);
    os << ", primaries: " << ::android::internal::ToString(primaries);
    os << "}";
    return os.str();
  }
};  // class Colorimetry
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
