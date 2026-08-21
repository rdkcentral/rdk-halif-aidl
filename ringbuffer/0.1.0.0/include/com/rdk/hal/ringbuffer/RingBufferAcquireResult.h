#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/ringbuffer/RingBufferAcquireResult.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace ringbuffer {
class RingBufferAcquireResult : public ::android::Parcelable {
public:
  class Id : public ::android::Parcelable {
  public:
    int32_t id = 0;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(id) != std::tie(rhs.id);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(id) < std::tie(rhs.id);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(id) <= std::tie(rhs.id);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(id) == std::tie(rhs.id);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(id) > std::tie(rhs.id);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(id) >= std::tie(rhs.id);
    }

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
      os << "id: " << ::android::internal::ToString(id);
      os << "}";
      return os.str();
    }
  };  // class Id
  ::com::rdk::hal::ringbuffer::RingBufferAcquireResult::Id id;
  int32_t offset = 0;
  int32_t bytes = 0;
  int32_t remaining = 0;
  inline bool operator!=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) != std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
  }
  inline bool operator<(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) < std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
  }
  inline bool operator<=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) <= std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
  }
  inline bool operator==(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) == std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
  }
  inline bool operator>(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) > std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
  }
  inline bool operator>=(const RingBufferAcquireResult& rhs) const {
    return std::tie(id, offset, bytes, remaining) >= std::tie(rhs.id, rhs.offset, rhs.bytes, rhs.remaining);
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
    os << "}";
    return os.str();
  }
};  // class RingBufferAcquireResult
}  // namespace ringbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
