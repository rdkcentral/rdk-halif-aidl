#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/videodecoder/Colorimetry.h>
#include <com/rdk/hal/videodecoder/ContentLightLevel.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <com/rdk/hal/videodecoder/MasteringDisplayInfo.h>
#include <com/rdk/hal/videodecoder/PixelFormat.h>
#include <com/rdk/hal/videodecoder/ScanType.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Decoded video frame metadata, relating to the frame output from the video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class FrameMetadata : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Pixel aspect ratio (PAR) defined as the ratio parX:parY.
   * e.g. 1:1 for square pixels, 480i=10:11, 576i=59:54
   * @see Rec.601 and https://en.wikipedia.org/wiki/Pixel_aspect_ratio
   */
  int32_t parX = 0;
  // @aidl-doc
  /** Pixel aspect ratio Y component. See `parX`. */
  int32_t parY = 0;
  // @aidl-doc
  /**
   * Source aspect ratio (SAR) defined as the ratio sarX:sarY.
   * e.g. 720:480, 3840:2160
   */
  int32_t sarX = 0;
  // @aidl-doc
  /** Source aspect ratio Y component. See `sarX`. */
  int32_t sarY = 0;
  // @aidl-doc
  /**
   * The coded width and height of the video frame in pixels.
   * Decoded video frame buffers hold the video frame in coded dimensions.
   */
  int32_t codedWidth = 0;
  // @aidl-doc
  /** The coded height of the video frame in pixels. See `codedWidth`. */
  int32_t codedHeight = 0;
  // @aidl-doc
  /**
   * The active display dimensions of the video frame in pixels.
   * These dimensions can be smaller than the coded dimensions to specify a
   * smaller central region to display inside the coded video frame.
   * The active dimensions should reflect any display frame or bar data from the stream.
   */
  int32_t activeX = 0;
  // @aidl-doc
  /** The Y position of the active display region within the coded frame, in pixels. See `activeX`. */
  int32_t activeY = 0;
  // @aidl-doc
  /** The width of the active display region in pixels. See `activeX`. */
  int32_t activeWidth = 0;
  // @aidl-doc
  /** The height of the active display region in pixels. See `activeX`. */
  int32_t activeHeight = 0;
  // @aidl-doc
  /**
   * The color depth in bits.
   * e.g. 8, 10, 12.
   */
  int32_t colorDepth = 0;
  // @aidl-doc
  /** Pixel format of the video frame. */
  ::com::rdk::hal::videodecoder::PixelFormat pixelFormat = ::com::rdk::hal::videodecoder::PixelFormat(0);
  // @aidl-doc
  /** Dynamic range of the video frame. */
  ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
  // @aidl-doc
  /** The picture scan type output from the decoder. */
  ::com::rdk::hal::videodecoder::ScanType scanType = ::com::rdk::hal::videodecoder::ScanType(0);
  // @aidl-doc
  /**
   * Active format description code.
   * See https://en.wikipedia.org/wiki/Active_Format_Description
   */
  int32_t afd = 0;
  // @aidl-doc
  /**
   * Frame rate decoded from the video stream expressed as a fraction.
   * Use 0/0 if unknown.e
   * e.g. 24fps = 24/1, 59.94fps = 60000/1001
   */
  int32_t frameRateNumerator = 0;
  // @aidl-doc
  /** The frame rate denominator. See `frameRateNumerator`. */
  int32_t frameRateDenominator = 0;
  // @aidl-doc
  /**
   * In-bitstream end-of-stream marker.
   *
   * Set true by the HAL on an output frame when it parses an end-of-stream /
   * sequence-end marker from the elementary stream itself - MPEG-2
   * sequence_end_code, H.264/H.265 end_of_stream NAL, MPEG-4 Part 2
   * visual_object_sequence_end_code.
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
   * via `IVideoDecoderController.signalEndOfStream()`: the HAL drains every
   * held frame, and then fires
   * `IVideoDecoderControllerListener.onEndOfStream()` exactly once after the
   * final `onFrameOutput()`.
   *
   * @see IVideoDecoderController.signalEndOfStream()
   * @see IVideoDecoderControllerListener.onEndOfStream()
   */
  bool bitstreamEOS = false;
  // @aidl-doc
  /**
   * Discontinuity indicator where the PTS for this frame is discontinuous
   * to the previous frame.
   *
   * Set true on the first frame output from buffers passed to
   * `decodeBufferWithMetadata()` after
   * `IVideoDecoderController.signalDiscontinuity()`.
   *
   * @see IVideoDecoderController.signalDiscontinuity()
   */
  bool discontinuity = false;
  // @aidl-doc
  /** Indicates if the video should be delivered in low latency mode. */
  bool lowLatency = false;
  // @aidl-doc
  /**
   * Colorimetry (range / matrix / transfer / primaries) of the video
   * frame as reported by the decoder. Each axis is set to its `UNKNOWN`
   * sentinel when not signalled in the stream; the parcelable itself is
   * never null on the frame-output path.
   */
  ::com::rdk::hal::videodecoder::Colorimetry colorimetry;
  // @aidl-doc
  /**
   * Mastering display colour volume metadata (SMPTE ST 2086).
   * Extracted from HEVC SEI type 137 or equivalent. Null if not present in the stream.
   */
  ::std::optional<::com::rdk::hal::videodecoder::MasteringDisplayInfo> masteringDisplayInfo;
  // @aidl-doc
  /**
   * Content light level static HDR metadata (MaxCLL/MaxFALL as defined in CTA-861.3).
   * Extracted from HEVC SEI type 144 or equivalent. Null if not present in the stream.
   */
  ::std::optional<::com::rdk::hal::videodecoder::ContentLightLevel> contentLightLevel;
  // @aidl-doc
  /**
   * The source of the video frame.
   * When the frame is presented the source may be used to configure the TV picture mode settings.
   */
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  // @aidl-doc
  /**
   * SHA1 calculation value.
   * Only set when SHA1_CALC is set 1=on
   */
  ::std::vector<uint8_t> sha1;
  // @aidl-doc
  /** Private extension for future use. */
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) != std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator<(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) < std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator<=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) <= std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator==(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) == std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator>(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) > std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator>=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, bitstreamEOS, discontinuity, lowLatency, colorimetry, masteringDisplayInfo, contentLightLevel, source, sha1, extension) >= std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.bitstreamEOS, rhs.discontinuity, rhs.lowLatency, rhs.colorimetry, rhs.masteringDisplayInfo, rhs.contentLightLevel, rhs.source, rhs.sha1, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.FrameMetadata");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FrameMetadata{";
    os << "parX: " << ::android::internal::ToString(parX);
    os << ", parY: " << ::android::internal::ToString(parY);
    os << ", sarX: " << ::android::internal::ToString(sarX);
    os << ", sarY: " << ::android::internal::ToString(sarY);
    os << ", codedWidth: " << ::android::internal::ToString(codedWidth);
    os << ", codedHeight: " << ::android::internal::ToString(codedHeight);
    os << ", activeX: " << ::android::internal::ToString(activeX);
    os << ", activeY: " << ::android::internal::ToString(activeY);
    os << ", activeWidth: " << ::android::internal::ToString(activeWidth);
    os << ", activeHeight: " << ::android::internal::ToString(activeHeight);
    os << ", colorDepth: " << ::android::internal::ToString(colorDepth);
    os << ", pixelFormat: " << ::android::internal::ToString(pixelFormat);
    os << ", dynamicRange: " << ::android::internal::ToString(dynamicRange);
    os << ", scanType: " << ::android::internal::ToString(scanType);
    os << ", afd: " << ::android::internal::ToString(afd);
    os << ", frameRateNumerator: " << ::android::internal::ToString(frameRateNumerator);
    os << ", frameRateDenominator: " << ::android::internal::ToString(frameRateDenominator);
    os << ", bitstreamEOS: " << ::android::internal::ToString(bitstreamEOS);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << ", lowLatency: " << ::android::internal::ToString(lowLatency);
    os << ", colorimetry: " << ::android::internal::ToString(colorimetry);
    os << ", masteringDisplayInfo: " << ::android::internal::ToString(masteringDisplayInfo);
    os << ", contentLightLevel: " << ::android::internal::ToString(contentLightLevel);
    os << ", source: " << ::android::internal::ToString(source);
    os << ", sha1: " << ::android::internal::ToString(sha1);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class FrameMetadata
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
