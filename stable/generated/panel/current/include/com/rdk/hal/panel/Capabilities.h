#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/panel/Capabilities.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PanelType.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class Capabilities : public ::android::Parcelable {
public:
  class PictureModeCapabilities : public ::android::Parcelable {
  public:
    class VideoFormatCapabilities : public ::android::Parcelable {
    public:
      ::com::rdk::hal::videodecoder::DynamicRange videoFormat = ::com::rdk::hal::videodecoder::DynamicRange(0);
      ::std::vector<::com::rdk::hal::AVSource> supportedAVSources;
      inline bool operator!=(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) != std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }
      inline bool operator<(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) < std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }
      inline bool operator<=(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) <= std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }
      inline bool operator==(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) == std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }
      inline bool operator>(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) > std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }
      inline bool operator>=(const VideoFormatCapabilities& rhs) const {
        return std::tie(videoFormat, supportedAVSources) >= std::tie(rhs.videoFormat, rhs.supportedAVSources);
      }

      ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
      ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
      ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
      static const ::android::String16& getParcelableDescriptor() {
        static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.Capabilities.PictureModeCapabilities.VideoFormatCapabilities");
        return DESCIPTOR;
      }
      inline std::string toString() const {
        std::ostringstream os;
        os << "VideoFormatCapabilities{";
        os << "videoFormat: " << ::android::internal::ToString(videoFormat);
        os << ", supportedAVSources: " << ::android::internal::ToString(supportedAVSources);
        os << "}";
        return os.str();
      }
    };  // class VideoFormatCapabilities
    ::android::String16 pictureMode;
    ::std::vector<::com::rdk::hal::panel::Capabilities::PictureModeCapabilities::VideoFormatCapabilities> videoFormatCapabilities;
    inline bool operator!=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) != std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }
    inline bool operator<(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) < std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }
    inline bool operator<=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) <= std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }
    inline bool operator==(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) == std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }
    inline bool operator>(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) > std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }
    inline bool operator>=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, videoFormatCapabilities) >= std::tie(rhs.pictureMode, rhs.videoFormatCapabilities);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.Capabilities.PictureModeCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "PictureModeCapabilities{";
      os << "pictureMode: " << ::android::internal::ToString(pictureMode);
      os << ", videoFormatCapabilities: " << ::android::internal::ToString(videoFormatCapabilities);
      os << "}";
      return os.str();
    }
  };  // class PictureModeCapabilities
  ::com::rdk::hal::panel::PanelType panelType = ::com::rdk::hal::panel::PanelType(0);
  int32_t pixelWidth = 0;
  int32_t pixelHeight = 0;
  int32_t widthCm = 0;
  int32_t heightCm = 0;
  bool frameRateMatchingSupported = false;
  bool fadeDisplaySupported = false;
  ::std::vector<::com::rdk::hal::panel::PQParameter> supportedPQParameters;
  ::std::vector<double> supportedRefreshRatesHz;
  ::std::vector<::com::rdk::hal::panel::Capabilities::PictureModeCapabilities> pictureModeCapabilities;
  ::std::vector<::android::String16> colorTemperatureNames;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) != std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) < std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) <= std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) == std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) > std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, fadeDisplaySupported, supportedPQParameters, supportedRefreshRatesHz, pictureModeCapabilities, colorTemperatureNames) >= std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.fadeDisplaySupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.pictureModeCapabilities, rhs.colorTemperatureNames);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.Capabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Capabilities{";
    os << "panelType: " << ::android::internal::ToString(panelType);
    os << ", pixelWidth: " << ::android::internal::ToString(pixelWidth);
    os << ", pixelHeight: " << ::android::internal::ToString(pixelHeight);
    os << ", widthCm: " << ::android::internal::ToString(widthCm);
    os << ", heightCm: " << ::android::internal::ToString(heightCm);
    os << ", frameRateMatchingSupported: " << ::android::internal::ToString(frameRateMatchingSupported);
    os << ", fadeDisplaySupported: " << ::android::internal::ToString(fadeDisplaySupported);
    os << ", supportedPQParameters: " << ::android::internal::ToString(supportedPQParameters);
    os << ", supportedRefreshRatesHz: " << ::android::internal::ToString(supportedRefreshRatesHz);
    os << ", pictureModeCapabilities: " << ::android::internal::ToString(pictureModeCapabilities);
    os << ", colorTemperatureNames: " << ::android::internal::ToString(colorTemperatureNames);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
