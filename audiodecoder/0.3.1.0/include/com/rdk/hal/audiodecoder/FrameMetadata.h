#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiodecoder/FrameType.h>
#include <com/rdk/hal/audiodecoder/PCMMetadata.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Audio frame metadata.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class FrameMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The type of audio data output by the decoder */
  ::com::rdk::hal::audiodecoder::FrameType type = ::com::rdk::hal::audiodecoder::FrameType(0);
  // @aidl-doc
  /** The original source codec of the audio frame. */
  ::com::rdk::hal::audiodecoder::Codec sourceCodec = ::com::rdk::hal::audiodecoder::Codec(0);
  // @aidl-doc
  /** The buffer contains Dolby Atmos audio and metadata. */
  bool isDolbyAtmos = false;
  // @aidl-doc
  /**
   * Audio trim durations to apply when presenting this decoded frame.
   *
   * `trimStartNs` is the duration to discard from the start of the decoded
   * audio frame; `trimEndNs` from the end. Both are durations in nanoseconds,
   * relative to the frame's own boundaries (not absolute timestamps).
   *
   * Per-frame — applies only to this decoded frame, not to the stream as a
   * whole. Set to 0 (the common case) for no trim.
   *
   * These fields carry the trim still outstanding for this frame, and the
   * AudioSink applies it before presenting the PCM to the mixer. A decoder
   * that has already trimmed the frame itself sets both to 0, so the samples
   * are discarded exactly once.
   *
   * In non-tunnelled mode, a frame with a non-zero trim always carries
   * non-null metadata on `IAudioDecoderControllerListener.onFrameOutput()`,
   * even when the trim repeats the previous frame's trim. A null metadata
   * means zero trim for that frame.
   *
   * Used for codec priming / encoder delay (AAC LC/HE, Opus pre-skip), AAC
   * SBR padding, and gapless playback across track boundaries.
   *
   * Type rationale: `int` (not `long`) — at nanosecond precision, max value
   * is ~2.1 seconds, sufficient for any per-frame priming/padding trim.
   *
   * @see IAudioDecoderController.decodeBufferWithMetadata()
   * @see InputBufferMetadata.trimStartNs
   * @see InputBufferMetadata.trimEndNs
   */
  int32_t trimStartNs = 0;
  // @aidl-doc
  /** Duration in nanoseconds to discard from the end of the decoded frame. See `trimStartNs`. */
  int32_t trimEndNs = 0;
  // @aidl-doc
  /** Indicates if the audio should be delivered in low latency mode. */
  bool lowLatency = false;
  // @aidl-doc
  /**
   * In-bitstream end-of-stream marker.
   *
   * Set true by the HAL on an output frame when it parses a codec-level
   * end-of-stream marker from the audio elementary stream itself - for
   * example, Dolby TrueHD substream termination, or any analogous
   * end-of-sequence indicator defined by the source codec.
   *
   * Many common audio formats (raw PCM, MP3, AAC LC, AC-3) carry no
   * in-stream EOS marker; for those, this flag is always false.
   *
   * Advisory and informational only:
   * - It does NOT end the decode session and never triggers teardown.
   * - It may appear more than once in a session - at a splice or
   *   concatenation point an end-of-sequence is a sequence boundary, not
   *   necessarily end-of-presentation.
   * - No callback fires for it; it is surfaced purely as this flag for any
   *   consumer that cares (e.g. splice-aware middleware).
   *
   * Client-signalled EOS is NOT carried here. The discrete EOS signal flows
   * via `IAudioDecoderController.signalEndOfStream()`: the HAL drains every
   * held frame, and then fires
   * `IAudioDecoderControllerListener.onEndOfStream()` exactly once after the
   * final `onFrameOutput()`.
   *
   * @see IAudioDecoderController.signalEndOfStream()
   * @see IAudioDecoderControllerListener.onEndOfStream()
   */
  bool bitstreamEOS = false;
  // @aidl-doc
  /**
   * Discontinuity indicator where the PTS for this frame is discontinuous
   * to the previous frame.
   *
   * Set true on the first frame output from buffers passed to
   * `decodeBufferWithMetadata()` after
   * `IAudioDecoderController.signalDiscontinuity()`.
   *
   * @see IAudioDecoderController.signalDiscontinuity()
   */
  bool discontinuity = false;
  // @aidl-doc
  /**
   * The source of the audio frame.
   * When the frame is presented the source may be used to configure the audio settings.
   */
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  // @aidl-doc
  /**
   * If the frame is PCM audio data this parcelable contains the PCM metadata.
   * Else metadata is null.
   */
  ::std::optional<::com::rdk::hal::audiodecoder::PCMMetadata> metadata;
  // @aidl-doc
  /**
   * Proprietary metadata passed from Decoder HAL to Sink HAL.
   * When the frame type is SOC_PROPRIETARY, SoCPrivate MAY contain opaque HAL metadata (indicated by non-zero length)
   * that is used by the Audio Sink and MUST be passed to the Audio Sink.
   */
  ::std::vector<uint8_t> SoCPrivate;
  // @aidl-doc
  /** Private extension for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) != std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator<(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) < std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator<=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) <= std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator==(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) == std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator>(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) > std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator>=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, bitstreamEOS, discontinuity, source, metadata, SoCPrivate, extension) >= std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.bitstreamEOS, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.FrameMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FrameMetadata{";
    os << "type: " << ::android::internal::ToString(type);
    os << ", sourceCodec: " << ::android::internal::ToString(sourceCodec);
    os << ", isDolbyAtmos: " << ::android::internal::ToString(isDolbyAtmos);
    os << ", trimStartNs: " << ::android::internal::ToString(trimStartNs);
    os << ", trimEndNs: " << ::android::internal::ToString(trimEndNs);
    os << ", lowLatency: " << ::android::internal::ToString(lowLatency);
    os << ", bitstreamEOS: " << ::android::internal::ToString(bitstreamEOS);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << ", source: " << ::android::internal::ToString(source);
    os << ", metadata: " << ::android::internal::ToString(metadata);
    os << ", SoCPrivate: " << ::android::internal::ToString(SoCPrivate);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class FrameMetadata
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
