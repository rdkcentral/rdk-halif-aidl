#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_VirtualizerMode.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Surround virtualizer settings returned by
 *        IDolbyMs12_2_6_Dap.getSurroundVirtualizer().
 *
 * Packages the current virtualizer mode and boost into a single parcelable so
 * the accessor can return both atomically. AIDL primitive parameters cannot be
 * `out`, which forces a parcelable return shape for paired accessors that
 * combine an enum with a primitive.
 */
class DolbyMs12_2_6_VirtualizerSettings : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Current surround virtualizer mode. */
  ::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode mode = ::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode(0);
  // @aidl-doc
  /** Current surround virtualizer boost in range 0 to 96. */
  int32_t boost = 0;
  inline bool operator!=(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) != std::tie(rhs.mode, rhs.boost);
  }
  inline bool operator<(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) < std::tie(rhs.mode, rhs.boost);
  }
  inline bool operator<=(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) <= std::tie(rhs.mode, rhs.boost);
  }
  inline bool operator==(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) == std::tie(rhs.mode, rhs.boost);
  }
  inline bool operator>(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) > std::tie(rhs.mode, rhs.boost);
  }
  inline bool operator>=(const DolbyMs12_2_6_VirtualizerSettings& rhs) const {
    return std::tie(mode, boost) >= std::tie(rhs.mode, rhs.boost);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiomixer.DolbyMs12_2_6_VirtualizerSettings");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DolbyMs12_2_6_VirtualizerSettings{";
    os << "mode: " << ::android::internal::ToString(mode);
    os << ", boost: " << ::android::internal::ToString(boost);
    os << "}";
    return os.str();
  }
};  // class DolbyMs12_2_6_VirtualizerSettings
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
