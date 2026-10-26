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
 * @brief A DVB-T2 Physical Layer Pipe (PLP) identifier.
 *
 * Applies to DVB-T2 only and is ignored when tuning DVB-T. PLP selection is mandatory for a DVB-T2 frontend, so any
 * frontend reporting DvbTStandard.T2 in DvbTCapabilities.dvbTStandards accepts an identifier in the range MIN to MAX,
 * as well as AUTO.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbTPlpId : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual PLP identifier. */
  int32_t value = -2;
  inline bool operator!=(const DvbTPlpId& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const DvbTPlpId& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const DvbTPlpId& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const DvbTPlpId& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const DvbTPlpId& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const DvbTPlpId& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No PLP selected. */
  enum : int32_t { UNDEFINED = -2 };
  // @aidl-doc
  /** Select the PLP automatically. */
  enum : int32_t { AUTO = -1 };
  // @aidl-doc
  /** The lowest valid PLP identifier. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid PLP identifier. */
  enum : int32_t { MAX = 255 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbTPlpId");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbTPlpId{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class DvbTPlpId
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
