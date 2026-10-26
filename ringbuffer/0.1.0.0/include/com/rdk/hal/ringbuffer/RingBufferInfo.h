#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/OverflowBehaviour.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
// @aidl-doc
/**
 * @brief Information about an IRingBuffer.
 *
 * The parcelable is kept as small as possible to avoid unnecessary overhead when sending it over Binder. For example,
 * the number of bytes available for writing is not included, as it can be calculated from the size and the number of
 * bytes available for reading.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class RingBufferInfo : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The size of the ring buffer in bytes. */
  int32_t bytes = -1;
  // @aidl-doc
  /** The number of bytes currently available for reading in the ring buffer. */
  int32_t availableForReading = -1;
  // @aidl-doc
  /** The overflow behaviour in effect for the ring buffer. */
  ::com::rdk::hal::ringbuffer::OverflowBehaviour overflowBehaviour = ::com::rdk::hal::ringbuffer::OverflowBehaviour(0);
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) != std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
  }
  inline bool operator<(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) < std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
  }
  inline bool operator<=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) <= std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
  }
  inline bool operator==(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) == std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
  }
  inline bool operator>(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) > std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
  }
  inline bool operator>=(const RingBufferInfo& rhs) const {
    return std::tie(bytes, availableForReading, overflowBehaviour, extension) >= std::tie(rhs.bytes, rhs.availableForReading, rhs.overflowBehaviour, rhs.extension);
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
    os << ", overflowBehaviour: " << ::android::internal::ToString(overflowBehaviour);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class RingBufferInfo
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
