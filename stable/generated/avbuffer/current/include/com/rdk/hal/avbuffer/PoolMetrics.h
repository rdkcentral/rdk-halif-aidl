#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/avbuffer/Pool.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
class PoolMetrics : public ::android::Parcelable {
public:
  ::com::rdk::hal::avbuffer::Pool poolHandle;
  int32_t bytesUsed = 0;
  int32_t bytesTotal = 0;
  inline bool operator!=(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) != std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }
  inline bool operator<(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) < std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }
  inline bool operator<=(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) <= std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }
  inline bool operator==(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) == std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }
  inline bool operator>(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) > std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }
  inline bool operator>=(const PoolMetrics& rhs) const {
    return std::tie(poolHandle, bytesUsed, bytesTotal) >= std::tie(rhs.poolHandle, rhs.bytesUsed, rhs.bytesTotal);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avbuffer.PoolMetrics");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PoolMetrics{";
    os << "poolHandle: " << ::android::internal::ToString(poolHandle);
    os << ", bytesUsed: " << ::android::internal::ToString(bytesUsed);
    os << ", bytesTotal: " << ::android::internal::ToString(bytesTotal);
    os << "}";
    return os.str();
  }
};  // class PoolMetrics
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
