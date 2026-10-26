#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/Capabilities.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Panel capabilities definition.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 */
class Capabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /** Defines the dynamic range and AV source capabilities for a picture mode. */
  class PictureModeCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /**
     * Defines the list of dynamic ranges, and the list of AV sources for each
     * dynamic range, that can be associated with a given picture mode.
     */
    class DynamicRangeCapabilities : public ::android::Parcelable {
    public:
      // @aidl-doc
      /** The dynamic range that can be associated for the picture mode. */
      ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
      // @aidl-doc
      /**
       * Defines list of AV sources that can be associated for a given
       * picture mode and a given dynamic range.
       */
      ::std::vector<::com::rdk::hal::panel::PanelSource> supportedAVSources;
      inline bool operator!=(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) != std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator<(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) < std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator<=(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) <= std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator==(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) == std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator>(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) > std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator>=(const DynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) >= std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }

      ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
      ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
      ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
      static const ::android::String16& getParcelableDescriptor() {
        static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.Capabilities.PictureModeCapabilities.DynamicRangeCapabilities");
        return DESCIPTOR;
      }
      inline std::string toString() const {
        std::ostringstream os;
        os << "DynamicRangeCapabilities{";
        os << "dynamicRange: " << ::android::internal::ToString(dynamicRange);
        os << ", supportedAVSources: " << ::android::internal::ToString(supportedAVSources);
        os << "}";
        return os.str();
      }
    };  // class DynamicRangeCapabilities
    // @aidl-doc
    /** The picture mode. */
    ::android::String16 pictureMode;
    // @aidl-doc
    /** Lists the dynamic range capabilities for a picture mode. */
    ::std::vector<::com::rdk::hal::panel::Capabilities::PictureModeCapabilities::DynamicRangeCapabilities> dynamicRangeCapabilities;
    inline bool operator!=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) != std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
    }
    inline bool operator<(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) < std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
    }
    inline bool operator<=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) <= std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
    }
    inline bool operator==(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) == std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
    }
    inline bool operator>(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) > std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
    }
    inline bool operator>=(const PictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, dynamicRangeCapabilities) >= std::tie(rhs.pictureMode, rhs.dynamicRangeCapabilities);
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
      os << ", dynamicRangeCapabilities: " << ::android::internal::ToString(dynamicRangeCapabilities);
      os << "}";
      return os.str();
    }
  };  // class PictureModeCapabilities
  // @aidl-doc
  /** The panel type. */
  ::android::String16 panelType;
  int32_t pixelWidth = 0;
  int32_t pixelHeight = 0;
  int32_t widthCm = 0;
  int32_t heightCm = 0;
  // @aidl-doc
  /** Whether frame rate matching is supported by the device. */
  bool frameRateMatchingSupported = false;
  // @aidl-doc
  /** The list of supported PQParameters. */
  ::std::vector<::com::rdk::hal::panel::PQParameter> supportedPQParameters;
  // @aidl-doc
  /** Panel display refresh rates supported in Hz, used in frame rate matching. */
  ::std::vector<double> supportedRefreshRatesHz;
  // @aidl-doc
  /**
   * Array of supported colour temperature presets.
   *
   * These strings are used directly by `PQParameter.COLOR_TEMPERATURE`
   * and by colour-temperature-scoped white balance operations.
   */
  ::std::vector<::android::String16> supportedColourTemperatures;
  // @aidl-doc
  /** All AV sources supported by the panel. */
  ::std::vector<::com::rdk::hal::panel::PanelSource> supportedAVSources;
  // @aidl-doc
  /** All dynamic ranges supported by the panel. */
  ::std::vector<::com::rdk::hal::videodecoder::DynamicRange> supportedDynamicRanges;
  // @aidl-doc
  /** Array of picture modes and their capabilities, listing the dynamic ranges and AV sources supported. */
  ::std::vector<::com::rdk::hal::panel::Capabilities::PictureModeCapabilities> pictureModeCapabilities;
  inline bool operator!=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) != std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
  }
  inline bool operator<(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) < std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
  }
  inline bool operator<=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) <= std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
  }
  inline bool operator==(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) == std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
  }
  inline bool operator>(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) > std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
  }
  inline bool operator>=(const Capabilities& rhs) const {
    return std::tie(panelType, pixelWidth, pixelHeight, widthCm, heightCm, frameRateMatchingSupported, supportedPQParameters, supportedRefreshRatesHz, supportedColourTemperatures, supportedAVSources, supportedDynamicRanges, pictureModeCapabilities) >= std::tie(rhs.panelType, rhs.pixelWidth, rhs.pixelHeight, rhs.widthCm, rhs.heightCm, rhs.frameRateMatchingSupported, rhs.supportedPQParameters, rhs.supportedRefreshRatesHz, rhs.supportedColourTemperatures, rhs.supportedAVSources, rhs.supportedDynamicRanges, rhs.pictureModeCapabilities);
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
    os << ", supportedPQParameters: " << ::android::internal::ToString(supportedPQParameters);
    os << ", supportedRefreshRatesHz: " << ::android::internal::ToString(supportedRefreshRatesHz);
    os << ", supportedColourTemperatures: " << ::android::internal::ToString(supportedColourTemperatures);
    os << ", supportedAVSources: " << ::android::internal::ToString(supportedAVSources);
    os << ", supportedDynamicRanges: " << ::android::internal::ToString(supportedDynamicRanges);
    os << ", pictureModeCapabilities: " << ::android::internal::ToString(pictureModeCapabilities);
    os << "}";
    return os.str();
  }
};  // class Capabilities
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
