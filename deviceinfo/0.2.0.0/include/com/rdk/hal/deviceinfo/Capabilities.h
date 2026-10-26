#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace deviceinfo {
// @aidl-doc
/**
 *  @brief     Device Information HAL capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Array of supported property key strings. */
  ::std::vector<::std::string> supportedProperties;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(supportedProperties) != std::tie(rhs.supportedProperties);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(supportedProperties) < std::tie(rhs.supportedProperties);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(supportedProperties) <= std::tie(rhs.supportedProperties);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(supportedProperties) == std::tie(rhs.supportedProperties);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(supportedProperties) > std::tie(rhs.supportedProperties);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(supportedProperties) >= std::tie(rhs.supportedProperties);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.deviceinfo.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "supportedProperties: " << ::android::internal::ToString(supportedProperties);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace deviceinfo
}  // namespace hal
}  // namespace rdk
}  // namespace com
