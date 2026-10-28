#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/FreeSync.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDMI input platform capabilities definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class PlatformCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Defines the maximum number of HDMI input ports that can be concurrently started.
   * This is a hardware/platform constraint that limits how many HDMI input ports
   * can be in the STARTED state simultaneously. Attempting to start an additional
   * port beyond this limit will result in an EX_ILLEGAL_STATE exception.
   *
   * @see IHDMIInputController.start()
   */
  int32_t maximumConcurrentStartedPorts = 0;
  // @aidl-doc
  /**
   * Indicates type of AMD FreeSync supported by the platform.
   * `FreeSync.UNSUPPORTED` if not supported.
   * @see Capabilities.supportsFreeSync to identify which ports support FreeSync.
   */
  ::com::rdk::hal::hdmiinput::FreeSync freeSync = ::com::rdk::hal::hdmiinput::FreeSync(0);
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) != std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) < std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) <= std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) == std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) > std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(maximumConcurrentStartedPorts, freeSync) >= std::tie(rhs.maximumConcurrentStartedPorts, rhs.freeSync);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmiinput.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "maximumConcurrentStartedPorts: " << ::android::internal::ToString(maximumConcurrentStartedPorts);
    os << ", freeSync: " << ::android::internal::ToString(freeSync);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
