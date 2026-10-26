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
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief An MPEG-2 Transport Stream packet identifier.
 *
 * Used by every filter that selects packets by PID, whether the filtered data is returned to the client through a
 * ring buffer or tunnelled to a decoder.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class Mpeg2TsPid : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual PID. */
  int32_t value = -1;
  inline bool operator!=(const Mpeg2TsPid& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const Mpeg2TsPid& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const Mpeg2TsPid& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const Mpeg2TsPid& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const Mpeg2TsPid& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const Mpeg2TsPid& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No PID selected. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid PID. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid PID, i.e. 0x1FFF. */
  enum : int32_t { MAX = 8191 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.Mpeg2TsPid");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Mpeg2TsPid{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class Mpeg2TsPid
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
