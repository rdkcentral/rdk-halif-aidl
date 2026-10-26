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
namespace avclock {
// @aidl-doc
/**
 * @brief Represents a snapshot of the AV System Time Clock (STC) along with its associated Linux system timestamp.
 *
 * In AV systems multiple clocks exist that may run at different rates.
 * The System Time Clock (STC) is used to regulate AV playback, ensuring both Audio and Video stay in sync.
 * On some platforms the Audio clock *is* the STC, and it may not match the Linux wall clock.
 *
 * This structure allows consumers to retrieve the current STC value and know when (in system time) that value was
 * sampled. This is essential for tasks such as subtitle scheduling or time-domain synchronization.
 *
 * Common use-case: Subtitle rendering
 *
 * Subtitle timestamps (PTS) are expressed in the STC domain. To render a subtitle at the right moment,
 * we need to convert that STC time to Linux wall clock time using:
 *
 * @code
 * SubtitleWallClockTime = SubtitlePTS - clockTimeNs + sampleTimestampNs
 * @endcode
 *
 * This method gives a close approximation suitable for short durations. Over long durations, drift may occur.
 *
 * Note on virtual devices:
 * On virtual platforms (e.g., QEMU), the STC and the system clock may initially progress at the same rate.
 * Thus, clockTimeNs may be equal to sampleTimestampNs. This will change if proper broadcast clock recovery is
 * introduced.
 *
 * @see https://linux.die.net/man/2/clock_gettime for CLOCK_MONOTONIC_RAW behavior.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
class ClockTime : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * The current STC (System Time Clock) value in nanoseconds.
   * This clock governs AV playback timing and may differ in rate from system wall clock time.
   */
  int64_t clockTimeNs = 0L;
  // @aidl-doc
  /**
   * The Linux CLOCK_MONOTONIC_RAW nanosecond timestamp when the STC value was sampled.
   * This allows consumers to relate AV time (STC) to system time.
   */
  int64_t sampleTimestampNs = 0L;
  inline bool operator!=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) != std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator<(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) < std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator<=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) <= std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator==(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) == std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator>(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) > std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }
  inline bool operator>=(const ClockTime& rhs) const {
    return std::tie(clockTimeNs, sampleTimestampNs) >= std::tie(rhs.clockTimeNs, rhs.sampleTimestampNs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.avclock.ClockTime");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "ClockTime{";
    os << "clockTimeNs: " << ::android::internal::ToString(clockTimeNs);
    os << ", sampleTimestampNs: " << ::android::internal::ToString(sampleTimestampNs);
    os << "}";
    return os.str();
  }
};  // class ClockTime
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
