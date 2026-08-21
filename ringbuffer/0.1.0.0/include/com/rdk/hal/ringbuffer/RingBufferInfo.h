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
namespace ringbuffer {
class RingBufferInfo : public ::android::Parcelable {
public:
  int32_t bytes = 0;
  int32_t availableForReading = 0;
  bool isOverflowing = false;
  inline bool operator!=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) != std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }
  inline bool operator<(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) < std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }
  inline bool operator<=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) <= std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }
  inline bool operator==(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) == std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }
  inline bool operator>(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) > std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }
  inline bool operator>=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, isOverflowing) >= std::tie(rhs.bytes, rhs.availableForReading, rhs.isOverflowing);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.ringbuffer.RingBufferInfo");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "RingBufferInfo{";
    os << "bytes: " << ::android::internal::ToString(bytes);
    os << ", availableForReading: " << ::android::internal::ToString(availableForReading);
    os << ", isOverflowing: " << ::android::internal::ToString(isOverflowing);
    os << "}";
    return os.str();
  }
};  // class RingBufferInfo
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
