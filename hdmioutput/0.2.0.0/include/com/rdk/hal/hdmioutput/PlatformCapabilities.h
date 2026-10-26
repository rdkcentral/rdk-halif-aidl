#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/FreeSync.h>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
// @aidl-doc
/**
 *  @brief     HDMI output platform capabilities definition.
 *
 *  Describes static HDMI capabilities that apply across the entire platform.
 *  These are useful for test drivers, validation tools, or middleware decisions
 *  that need to understand global default behavior or hardware-specific constraints.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class PlatformCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The default/native frame rate the platform uses for HDMI output.
   *
   * Typically defined per territory (e.g., 50.0 Hz for PAL or 59.94 Hz for NTSC).
   * If set to 0.0, it is considered undefined, and the application or middleware
   * may determine the preferred default dynamically.
   */
  double nativeFrameRate = 0.000000;
  // @aidl-doc
  /**
   * The AMD FreeSync capability level supported globally by the platform.
   *
   * This indicates the highest FreeSync tier available on any output.
   * The per-port presence of FreeSync is reflected in Capabilities.supportsFreeSync.
   *
   * @see Capabilities.supportsFreeSync
   */
  ::com::rdk::hal::hdmioutput::FreeSync freeSync = ::com::rdk::hal::hdmioutput::FreeSync(0);
  inline bool operator!=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) != std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator<(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) < std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator<=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) <= std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator==(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) == std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator>(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) > std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }
  inline bool operator>=(const PlatformCapabilities& rhs) const {
    return std::tie(nativeFrameRate, freeSync) >= std::tie(rhs.nativeFrameRate, rhs.freeSync);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.hdmioutput.PlatformCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PlatformCapabilities{";
    os << "nativeFrameRate: " << ::android::internal::ToString(nativeFrameRate);
    os << ", freeSync: " << ::android::internal::ToString(freeSync);
    os << "}";
    return os.str();
  }
};  // class PlatformCapabilities
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
