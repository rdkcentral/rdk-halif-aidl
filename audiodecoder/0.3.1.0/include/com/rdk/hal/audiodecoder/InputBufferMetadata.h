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
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Per-buffer metadata carried with input buffers submitted via
 *             `IAudioDecoderController.decodeBufferWithMetadata()`.
 *
 *  Describes properties of the encoded audio frame that cannot be derived from
 *  the buffer contents alone, such as its presentation time and trim
 *  durations.
 *
 *  Each `decodeBufferWithMetadata()` call is self-describing: the HAL MUST NOT
 *  carry state from this parcelable across calls. In particular, `trimStartNs`
 *  and `trimEndNs` apply only to the buffer of the current call and do not
 *  carry forward.
 *
 *  @see IAudioDecoderController.decodeBufferWithMetadata()
 *
 *  @author    Gerald Weatherup
 */
class InputBufferMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Presentation time of the encoded audio frame in nanoseconds. */
  int64_t nsPresentationTime = 0L;
  // @aidl-doc
  /**
   * Duration to trim from the start of the decoded audio frame, in nanoseconds.
   *
   * Per-frame trim — applied to the single decoded frame produced from this
   * input buffer, not to the stream as a whole. Relative to the frame's own
   * boundaries (a duration to discard from the leading edge), not an absolute
   * timestamp. Applies only to the buffer of the current
   * `decodeBufferWithMetadata()` call; not carried forward across calls.
   *
   * Set to 0 (the common case) to apply no trim to this frame's start.
   *
   * Primary use cases:
   * - Codec priming / encoder delay (e.g. AAC LC/HE prepended silence)
   * - Opus pre-skip
   * - AAC SBR padding
   * - Gapless playback across track boundaries
   *
   * Data flow: the middleware sets this here on each
   * `decodeBufferWithMetadata()` call, and the trim is applied exactly once
   * before the PCM reaches the mixer. Either the decoder trims the frame
   * itself and sets both `FrameMetadata.trimStartNs` and
   * `FrameMetadata.trimEndNs` to 0, or it passes both through on
   * `IAudioDecoderControllerListener.onFrameOutput()` and the AudioSink
   * applies them.
   *
   * Type rationale: `int` (not `long`) — at nanosecond precision, max value is
   * ~2.1 seconds, sufficient for any per-frame priming/padding trim.
   *
   * @see FrameMetadata.trimStartNs
   */
  int32_t trimStartNs = 0;
  // @aidl-doc
  /**
   * Duration to trim from the end of the decoded audio frame, in nanoseconds.
   *
   * Per-frame trim — applied to the single decoded frame produced from this
   * input buffer, not to the stream as a whole. Relative to the frame's own
   * boundaries (a duration to discard from the trailing edge), not an
   * absolute timestamp. Applies only to the buffer of the current
   * `decodeBufferWithMetadata()` call; not carried forward across calls.
   *
   * Set to 0 (the common case) to apply no trim to this frame's end.
   *
   * Use cases, data flow, and type rationale as for `trimStartNs` above.
   *
   * @see FrameMetadata.trimEndNs
   */
  int32_t trimEndNs = 0;
  inline bool operator!=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) != std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator<(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) < std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator<=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) <= std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator==(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) == std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator>(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) > std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }
  inline bool operator>=(const InputBufferMetadata& rhs) const {
    return std::tie(nsPresentationTime, trimStartNs, trimEndNs) >= std::tie(rhs.nsPresentationTime, rhs.trimStartNs, rhs.trimEndNs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.InputBufferMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "InputBufferMetadata{";
    os << "nsPresentationTime: " << ::android::internal::ToString(nsPresentationTime);
    os << ", trimStartNs: " << ::android::internal::ToString(trimStartNs);
    os << ", trimEndNs: " << ::android::internal::ToString(trimEndNs);
    os << "}";
    return os.str();
  }
};  // class InputBufferMetadata
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
