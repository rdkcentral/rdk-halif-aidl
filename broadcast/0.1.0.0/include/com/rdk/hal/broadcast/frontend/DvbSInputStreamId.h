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
 * @brief A DVB-S2/S2X Input Stream Identifier (ISI).
 *
 * Selects one stream of a multiple input stream (MIS) carrier. Input stream selection is optional, so a specific
 * identifier may only be requested where the frontend reports DvbSCapabilities.isInputStreamIdSupported.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class DvbSInputStreamId : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The actual input stream identifier. */
  int32_t value = -1;
  inline bool operator!=(const DvbSInputStreamId& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const DvbSInputStreamId& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const DvbSInputStreamId& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const DvbSInputStreamId& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const DvbSInputStreamId& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const DvbSInputStreamId& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  // @aidl-doc
  /** No specific input stream selected. */
  enum : int32_t { UNDEFINED = -1 };
  // @aidl-doc
  /** The lowest valid input stream identifier. */
  enum : int32_t { MIN = 0 };
  // @aidl-doc
  /** The highest valid input stream identifier. */
  enum : int32_t { MAX = 255 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.DvbSInputStreamId");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DvbSInputStreamId{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class DvbSInputStreamId
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
