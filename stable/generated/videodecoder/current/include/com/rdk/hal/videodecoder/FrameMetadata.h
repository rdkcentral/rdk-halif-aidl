#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <com/rdk/hal/videodecoder/PixelFormat.h>
#include <com/rdk/hal/videodecoder/ScanType.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
class FrameMetadata : public ::android::Parcelable {
public:
  int32_t parX = 0;
  int32_t parY = 0;
  int32_t sarX = 0;
  int32_t sarY = 0;
  int32_t codedWidth = 0;
  int32_t codedHeight = 0;
  int32_t activeX = 0;
  int32_t activeY = 0;
  int32_t activeWidth = 0;
  int32_t activeHeight = 0;
  int32_t colorDepth = 0;
  ::com::rdk::hal::videodecoder::PixelFormat pixelFormat = ::com::rdk::hal::videodecoder::PixelFormat(0);
  ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
  ::com::rdk::hal::videodecoder::ScanType scanType = ::com::rdk::hal::videodecoder::ScanType(0);
  int32_t afd = 0;
  int32_t frameRateNumerator = 0;
  int32_t frameRateDenominator = 0;
  bool endOfStream = false;
  bool discontinuity = false;
  bool lowLatency = false;
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  ::std::vector<uint8_t> sha1;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) != std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator<(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) < std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator<=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) <= std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator==(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) == std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator>(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) > std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
  }
  inline bool operator>=(const FrameMetadata& rhs) const {
    return std::tie(parX, parY, sarX, sarY, codedWidth, codedHeight, activeX, activeY, activeWidth, activeHeight, colorDepth, pixelFormat, dynamicRange, scanType, afd, frameRateNumerator, frameRateDenominator, endOfStream, discontinuity, lowLatency, source, sha1, extension) >= std::tie(rhs.parX, rhs.parY, rhs.sarX, rhs.sarY, rhs.codedWidth, rhs.codedHeight, rhs.activeX, rhs.activeY, rhs.activeWidth, rhs.activeHeight, rhs.colorDepth, rhs.pixelFormat, rhs.dynamicRange, rhs.scanType, rhs.afd, rhs.frameRateNumerator, rhs.frameRateDenominator, rhs.endOfStream, rhs.discontinuity, rhs.lowLatency, rhs.source, rhs.sha1, rhs.extension);
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
    os << ", endOfStream: " << ::android::internal::ToString(endOfStream);
    os << ", discontinuity: " << ::android::internal::ToString(discontinuity);
    os << ", lowLatency: " << ::android::internal::ToString(lowLatency);
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
