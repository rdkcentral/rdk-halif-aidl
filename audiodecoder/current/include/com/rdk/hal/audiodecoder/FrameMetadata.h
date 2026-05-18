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
class FrameMetadata : public ::android::Parcelable {
public:
  ::com::rdk::hal::audiodecoder::FrameType type = ::com::rdk::hal::audiodecoder::FrameType(0);
  ::com::rdk::hal::audiodecoder::Codec sourceCodec = ::com::rdk::hal::audiodecoder::Codec(0);
  bool isDolbyAtmos = false;
  int32_t trimStartNs = 0;
  int32_t trimEndNs = 0;
  bool lowLatency = false;
  bool endOfStream = false;
  bool discontinuity = false;
  ::com::rdk::hal::AVSource source = ::com::rdk::hal::AVSource(0);
  ::std::optional<::com::rdk::hal::audiodecoder::PCMMetadata> metadata;
  ::std::vector<uint8_t> SoCPrivate;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) != std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator<(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) < std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator<=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) <= std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator==(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) == std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator>(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) > std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
  }
  inline bool operator>=(const FrameMetadata& rhs) const {
    return std::tie(type, sourceCodec, isDolbyAtmos, trimStartNs, trimEndNs, lowLatency, endOfStream, discontinuity, source, metadata, SoCPrivate, extension) >= std::tie(rhs.type, rhs.sourceCodec, rhs.isDolbyAtmos, rhs.trimStartNs, rhs.trimEndNs, rhs.lowLatency, rhs.endOfStream, rhs.discontinuity, rhs.source, rhs.metadata, rhs.SoCPrivate, rhs.extension);
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
    os << ", endOfStream: " << ::android::internal::ToString(endOfStream);
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
