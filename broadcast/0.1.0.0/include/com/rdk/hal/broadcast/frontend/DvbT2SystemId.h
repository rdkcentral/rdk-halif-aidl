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
namespace frontend {
// @aidl-doc
/**
 * @brief A DVB-T2 system identifier, as carried in the T2 L1 pre-signalling.
 *
 * Reported through SignalInfoValue for SignalInfoProperty.T2_SYSTEM_ID.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbT2SystemId : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual system identifier. */
  int32_t value = -1;
  inline bool operator!=(const DvbT2SystemId& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const DvbT2SystemId& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const DvbT2SystemId& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const DvbT2SystemId& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const DvbT2SystemId& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const DvbT2SystemId& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No system identifier. Distinct from MIN, which is a valid identifier. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid system identifier. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid system identifier. */
  enum : int32_t { MAX = 65535 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbT2SystemId");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbT2SystemId{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class DvbT2SystemId
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
