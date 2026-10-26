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
 * @brief A DVB-S2/S2X physical-layer scrambling code (scrambling-sequence index).
 *
 * The index is in the range MIN to MAX, i.e. 0x00000 to 0x3FFFE. Which values within that range are usable depends on
 * the DvbSPlsMode the code is used with, so a frontend still rejects a code it cannot apply for the requested mode.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbSPlsCode : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual scrambling-sequence index. */
  int32_t value = -1;
  inline bool operator!=(const DvbSPlsCode& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const DvbSPlsCode& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const DvbSPlsCode& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const DvbSPlsCode& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const DvbSPlsCode& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const DvbSPlsCode& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No physical-layer scrambling code selected. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid scrambling-sequence index, i.e. 0x00000. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid scrambling-sequence index, i.e. 0x3FFFE. */
  enum : int32_t { MAX = 262142 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbSPlsCode");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbSPlsCode{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class DvbSPlsCode
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
