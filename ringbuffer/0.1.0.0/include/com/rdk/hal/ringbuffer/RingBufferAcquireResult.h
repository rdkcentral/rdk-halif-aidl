#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/RingBufferAcquireResult.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
// @aidl-doc
/**
 * @brief Results of a call to acquire() for either reading or writing data in the ring buffer.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class RingBufferAcquireResult : public ::android::Parcelable {
public:
  // @aidl-doc
  /** A type-safe ID. */
  class Id : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The actual ID. */
    int32_t value = -1;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    // @aidl-doc
    /** The undefined ID value. */
    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.ringbuffer.RingBufferAcquireResult.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  // @aidl-doc
  /** The ID to correlate acquire and release calls. */
  ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id id;
  // @aidl-doc
  /** The offset in the ring buffer where data can be read/written. */
  int32_t offset = -1;
  // @aidl-doc
  /**
   * The number of bytes that were actually acquired for reading/writing.
   *
   * @note The number of bytes acquired can be less than the requested size, and even zero. The consumer/producer
   * should check the number of bytes acquired in the returned RingBufferAcquireResult and only read/write that many
   * bytes.
   */
  int32_t bytes = -1;
  // @aidl-doc
  /**
   * The number of remaining bytes available for reading/writing in the ring buffer after this acquire.
   *
   * The remaining bytes may not be accessed until acquired in a subsequent acquire() call, as the ring buffer is a
   * circular buffer and the data may wrap around to the beginning of the buffer.
   *
   * @note remaining bytes can be greater than zero even if bytes is smaller than the requested size. This can happen
   * when the acquired data is located right before the end of the ring buffer, and the remaining data is located at
   * the beginning of the ring buffer.
   */
  int32_t remaining = -1;
  // @aidl-doc
  /** Reserved for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) != std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }
  inline bool operator<(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) < std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }
  inline bool operator<=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) <= std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }
  inline bool operator==(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) == std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }
  inline bool operator>(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) > std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }
  inline bool operator>=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining, extension) >= std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.ringbuffer.RingBufferAcquireResult");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "RingBufferAcquireResult{";
    os << "id: " << ::android::internal::ToString(id);
    os << ", offset: " << ::android::internal::ToString(offset);
    os << ", bytes: " << ::android::internal::ToString(bytes);
    os << ", remaining: " << ::android::internal::ToString(remaining);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class RingBufferAcquireResult
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
