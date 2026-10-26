#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/panel/ColourManagementSettings.h>
#include <com/rdk/hal/panel/DimmingLevel.h>
#include <com/rdk/hal/panel/DimmingMode.h>
#include <com/rdk/hal/panel/DimmingSettings.h>
#include <com/rdk/hal/panel/DolbyVisionCalibrationSettings.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PQParameterCapabilities.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/panel/SDRGamma.h>
#include <com/rdk/hal/panel/ToneMappingLevel.h>
#include <com/rdk/hal/panel/ToneMappingMode.h>
#include <com/rdk/hal/panel/ToneMappingSettings.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <utils/String16.h>
#include <variant>
#include <vector>

#ifndef __BIONIC__
#define __assert2(a,b,c,d) ((void)0)
#endif

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/** @brief Panel PQ parameter capabilities. */
class PQParameterCapabilities : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * Scalar integer minimum/maximum bounds used by simple integer-backed PQ
   * parameters.
   */
  class IntBounds : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** Spacing between allowed values, for regularly spaced controls. */
    class StepValue : public ::android::Parcelable {
    public:
      // @aidl-doc
      /** The step between consecutive allowed values. */
      int32_t value = 0;
      inline bool operator!=(const StepValue& rhs) const {
        return std::tie(value) != std::tie(rhs.value);
      }
      inline bool operator<(const StepValue& rhs) const {
        return std::tie(value) < std::tie(rhs.value);
      }
      inline bool operator<=(const StepValue& rhs) const {
        return std::tie(value) <= std::tie(rhs.value);
      }
      inline bool operator==(const StepValue& rhs) const {
        return std::tie(value) == std::tie(rhs.value);
      }
      inline bool operator>(const StepValue& rhs) const {
        return std::tie(value) > std::tie(rhs.value);
      }
      inline bool operator>=(const StepValue& rhs) const {
        return std::tie(value) >= std::tie(rhs.value);
      }

      ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
      ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
      ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
      static const ::android::String16& getParcelableDescriptor() {
        static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.IntBounds.StepValue");
        return DESCIPTOR;
      }
      inline std::string toString() const {
        std::ostringstream os;
        os << "StepValue{";
        os << "value: " << ::android::internal::ToString(value);
        os << "}";
        return os.str();
      }
    };  // class StepValue
    // @aidl-doc
    /** Minimum value. */
    int32_t minValue = 0;
    // @aidl-doc
    /** Maximum value. */
    int32_t maxValue = 0;
    // @aidl-doc
    /** The step value. Null if the allowed values are not regularly spaced. */
    ::std::optional<::com::rdk::hal::panel::PQParameterCapabilities::IntBounds::StepValue> stepValue;
    inline bool operator!=(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) != std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }
    inline bool operator<(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) < std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }
    inline bool operator<=(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) <= std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }
    inline bool operator==(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) == std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }
    inline bool operator>(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) > std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }
    inline bool operator>=(const IntBounds& rhs) const {
      return std::tie(minValue, maxValue, stepValue) >= std::tie(rhs.minValue, rhs.maxValue, rhs.stepValue);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.IntBounds");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "IntBounds{";
      os << "minValue: " << ::android::internal::ToString(minValue);
      os << ", maxValue: " << ::android::internal::ToString(maxValue);
      os << ", stepValue: " << ::android::internal::ToString(stepValue);
      os << "}";
      return os.str();
    }
  };  // class IntBounds
  // @aidl-doc
  /**
   * Per-dimming-mode level limits used when pqParameter ==
   * PQParameter.DIMMING_SETTINGS.
   */
  class DimmingModeLevelCapability : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The dimming mode. */
    ::com::rdk::hal::panel::DimmingMode dimmingMode = ::com::rdk::hal::panel::DimmingMode(0);
    // @aidl-doc
    /** Number of levels supported for the mode, the length of supportedValues. */
    int32_t numSupportedLevels = 0;
    // @aidl-doc
    /** The levels supported for the mode. */
    ::std::vector<::com::rdk::hal::panel::DimmingLevel> supportedValues;
    inline bool operator!=(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) != std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator<(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) < std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator<=(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) <= std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator==(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) == std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator>(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) > std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator>=(const DimmingModeLevelCapability& rhs) const {
      return std::tie(dimmingMode, numSupportedLevels, supportedValues) >= std::tie(rhs.dimmingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.DimmingModeLevelCapability");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "DimmingModeLevelCapability{";
      os << "dimmingMode: " << ::android::internal::ToString(dimmingMode);
      os << ", numSupportedLevels: " << ::android::internal::ToString(numSupportedLevels);
      os << ", supportedValues: " << ::android::internal::ToString(supportedValues);
      os << "}";
      return os.str();
    }
  };  // class DimmingModeLevelCapability
  // @aidl-doc
  /** Wrapper for the list of per-mode dimming level capabilities. */
  class DimmingModeLevelCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** One entry for each supported dimming mode. */
    ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::DimmingModeLevelCapability> entries;
    inline bool operator!=(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) != std::tie(rhs.entries);
    }
    inline bool operator<(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) < std::tie(rhs.entries);
    }
    inline bool operator<=(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) <= std::tie(rhs.entries);
    }
    inline bool operator==(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) == std::tie(rhs.entries);
    }
    inline bool operator>(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) > std::tie(rhs.entries);
    }
    inline bool operator>=(const DimmingModeLevelCapabilities& rhs) const {
      return std::tie(entries) >= std::tie(rhs.entries);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.DimmingModeLevelCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "DimmingModeLevelCapabilities{";
      os << "entries: " << ::android::internal::ToString(entries);
      os << "}";
      return os.str();
    }
  };  // class DimmingModeLevelCapabilities
  // @aidl-doc
  /** Capabilities for grouped dimming settings. */
  class DimmingSettingsCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The supported dimming levels for each dimming mode. */
    ::com::rdk::hal::panel::PQParameterCapabilities::DimmingModeLevelCapabilities modeLevelCapabilities;
    inline bool operator!=(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) != std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator<(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) < std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator<=(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) <= std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator==(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) == std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator>(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) > std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator>=(const DimmingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) >= std::tie(rhs.modeLevelCapabilities);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.DimmingSettingsCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "DimmingSettingsCapabilities{";
      os << "modeLevelCapabilities: " << ::android::internal::ToString(modeLevelCapabilities);
      os << "}";
      return os.str();
    }
  };  // class DimmingSettingsCapabilities
  // @aidl-doc
  /**
   * Per-tone-mapping-mode level support used when pqParameter ==
   * PQParameter.TONE_MAPPING_SETTINGS.
   */
  class ToneMappingModeLevelCapability : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The tone-mapping mode. */
    ::com::rdk::hal::panel::ToneMappingMode toneMappingMode = ::com::rdk::hal::panel::ToneMappingMode(0);
    // @aidl-doc
    /** Number of levels supported for the mode, the length of supportedValues. */
    int32_t numSupportedLevels = 0;
    // @aidl-doc
    /** The levels supported for the mode. */
    ::std::vector<::com::rdk::hal::panel::ToneMappingLevel> supportedValues;
    inline bool operator!=(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) != std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator<(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) < std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator<=(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) <= std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator==(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) == std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator>(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) > std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }
    inline bool operator>=(const ToneMappingModeLevelCapability& rhs) const {
      return std::tie(toneMappingMode, numSupportedLevels, supportedValues) >= std::tie(rhs.toneMappingMode, rhs.numSupportedLevels, rhs.supportedValues);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.ToneMappingModeLevelCapability");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "ToneMappingModeLevelCapability{";
      os << "toneMappingMode: " << ::android::internal::ToString(toneMappingMode);
      os << ", numSupportedLevels: " << ::android::internal::ToString(numSupportedLevels);
      os << ", supportedValues: " << ::android::internal::ToString(supportedValues);
      os << "}";
      return os.str();
    }
  };  // class ToneMappingModeLevelCapability
  // @aidl-doc
  /** Wrapper for the list of per-mode tone-mapping level capabilities. */
  class ToneMappingModeLevelCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** One entry for each supported tone-mapping mode. */
    ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::ToneMappingModeLevelCapability> entries;
    inline bool operator!=(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) != std::tie(rhs.entries);
    }
    inline bool operator<(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) < std::tie(rhs.entries);
    }
    inline bool operator<=(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) <= std::tie(rhs.entries);
    }
    inline bool operator==(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) == std::tie(rhs.entries);
    }
    inline bool operator>(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) > std::tie(rhs.entries);
    }
    inline bool operator>=(const ToneMappingModeLevelCapabilities& rhs) const {
      return std::tie(entries) >= std::tie(rhs.entries);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.ToneMappingModeLevelCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "ToneMappingModeLevelCapabilities{";
      os << "entries: " << ::android::internal::ToString(entries);
      os << "}";
      return os.str();
    }
  };  // class ToneMappingModeLevelCapabilities
  // @aidl-doc
  /** Capabilities for grouped tone-mapping settings. */
  class ToneMappingSettingsCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The supported tone-mapping levels for each tone-mapping mode. */
    ::com::rdk::hal::panel::PQParameterCapabilities::ToneMappingModeLevelCapabilities modeLevelCapabilities;
    inline bool operator!=(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) != std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator<(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) < std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator<=(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) <= std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator==(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) == std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator>(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) > std::tie(rhs.modeLevelCapabilities);
    }
    inline bool operator>=(const ToneMappingSettingsCapabilities& rhs) const {
      return std::tie(modeLevelCapabilities) >= std::tie(rhs.modeLevelCapabilities);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.ToneMappingSettingsCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "ToneMappingSettingsCapabilities{";
      os << "modeLevelCapabilities: " << ::android::internal::ToString(modeLevelCapabilities);
      os << "}";
      return os.str();
    }
  };  // class ToneMappingSettingsCapabilities
  // @aidl-doc
  /** Bounds used when pqParameter == PQParameter.DV_CALIBRATION. */
  class DvCalibrationBounds : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The minimum value of each field. */
    ::com::rdk::hal::panel::DolbyVisionCalibrationSettings minBound;
    // @aidl-doc
    /** The maximum value of each field. */
    ::com::rdk::hal::panel::DolbyVisionCalibrationSettings maxBound;
    inline bool operator!=(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) != std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator<(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) < std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator<=(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) <= std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator==(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) == std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator>(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) > std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator>=(const DvCalibrationBounds& rhs) const {
      return std::tie(minBound, maxBound) >= std::tie(rhs.minBound, rhs.maxBound);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.DvCalibrationBounds");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "DvCalibrationBounds{";
      os << "minBound: " << ::android::internal::ToString(minBound);
      os << ", maxBound: " << ::android::internal::ToString(maxBound);
      os << "}";
      return os.str();
    }
  };  // class DvCalibrationBounds
  // @aidl-doc
  /**
   * Capability bounds used when pqParameter == PQParameter.TWO_POINT_WB.
   *
   * The supported colour temperatures are discrete strings and are listed in
   * SupportedValues. This structure only carries the allowed numeric ranges
   * for the RGB gain and offset fields.
   */
  class TwoPointWBCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** Bounds for the red gain. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds redGain;
    // @aidl-doc
    /** Bounds for the red offset. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds redOffset;
    // @aidl-doc
    /** Bounds for the green gain. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds greenGain;
    // @aidl-doc
    /** Bounds for the green offset. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds greenOffset;
    // @aidl-doc
    /** Bounds for the blue gain. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds blueGain;
    // @aidl-doc
    /** Bounds for the blue offset. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds blueOffset;
    inline bool operator!=(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) != std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }
    inline bool operator<(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) < std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }
    inline bool operator<=(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) <= std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }
    inline bool operator==(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) == std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }
    inline bool operator>(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) > std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }
    inline bool operator>=(const TwoPointWBCapabilities& rhs) const {
      return std::tie(redGain, redOffset, greenGain, greenOffset, blueGain, blueOffset) >= std::tie(rhs.redGain, rhs.redOffset, rhs.greenGain, rhs.greenOffset, rhs.blueGain, rhs.blueOffset);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.TwoPointWBCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "TwoPointWBCapabilities{";
      os << "redGain: " << ::android::internal::ToString(redGain);
      os << ", redOffset: " << ::android::internal::ToString(redOffset);
      os << ", greenGain: " << ::android::internal::ToString(greenGain);
      os << ", greenOffset: " << ::android::internal::ToString(greenOffset);
      os << ", blueGain: " << ::android::internal::ToString(blueGain);
      os << ", blueOffset: " << ::android::internal::ToString(blueOffset);
      os << "}";
      return os.str();
    }
  };  // class TwoPointWBCapabilities
  // @aidl-doc
  /**
   * Capability bounds used when pqParameter == PQParameter.MULTI_POINT_WB.
   *
   * The supported colour temperatures are discrete strings and are listed in
   * SupportedValues. This structure only carries the fixed min/max bounds for
   * the red, green, and blue channel values.
   */
  class MultiPointWBCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** Bounds for the red channel values. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds r;
    // @aidl-doc
    /** Bounds for the green channel values. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds g;
    // @aidl-doc
    /** Bounds for the blue channel values. */
    ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds b;
    inline bool operator!=(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) != std::tie(rhs.r, rhs.g, rhs.b);
    }
    inline bool operator<(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) < std::tie(rhs.r, rhs.g, rhs.b);
    }
    inline bool operator<=(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) <= std::tie(rhs.r, rhs.g, rhs.b);
    }
    inline bool operator==(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) == std::tie(rhs.r, rhs.g, rhs.b);
    }
    inline bool operator>(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) > std::tie(rhs.r, rhs.g, rhs.b);
    }
    inline bool operator>=(const MultiPointWBCapabilities& rhs) const {
      return std::tie(r, g, b) >= std::tie(rhs.r, rhs.g, rhs.b);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.MultiPointWBCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "MultiPointWBCapabilities{";
      os << "r: " << ::android::internal::ToString(r);
      os << ", g: " << ::android::internal::ToString(g);
      os << ", b: " << ::android::internal::ToString(b);
      os << "}";
      return os.str();
    }
  };  // class MultiPointWBCapabilities
  // @aidl-doc
  /** Bounds used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
  class ColourManagementSettingsBounds : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The minimum value of each field. */
    ::com::rdk::hal::panel::ColourManagementSettings minBound;
    // @aidl-doc
    /** The maximum value of each field. */
    ::com::rdk::hal::panel::ColourManagementSettings maxBound;
    inline bool operator!=(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) != std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator<(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) < std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator<=(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) <= std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator==(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) == std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator>(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) > std::tie(rhs.minBound, rhs.maxBound);
    }
    inline bool operator>=(const ColourManagementSettingsBounds& rhs) const {
      return std::tie(minBound, maxBound) >= std::tie(rhs.minBound, rhs.maxBound);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.ColourManagementSettingsBounds");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "ColourManagementSettingsBounds{";
      os << "minBound: " << ::android::internal::ToString(minBound);
      os << ", maxBound: " << ::android::internal::ToString(maxBound);
      os << "}";
      return os.str();
    }
  };  // class ColourManagementSettingsBounds
  // @aidl-doc
  /**
   * Bounds information for the PQ parameter.
   *
   * Only one bounds shape is valid for a given PQ parameter, so the active
   * variant identifies how the parameter's legal range is described.
   * Integer-backed parameters may also carry an optional step value so large
   * numeric domains can be represented compactly without enumerating every
   * allowed value.
   * Structured parcelables such as DolbyVisionCalibrationSettings,
   * TwoPointWBCapabilities, MultiPointWBCapabilities, and
   * ColourManagementSettings do not use stepValue. For white balance, the
   * numeric field limits live in RangeBound while the discrete colour
   * temperature names live in SupportedValues. When the preset arrays are
   * omitted or empty, the structured min/max bounds define the full supported
   * numeric domain.
   */
  class RangeBound : public ::android::Parcelable {
  public:
    enum class Tag : int32_t {
      // @aidl-doc
      /** Bounds for simple integer-backed PQ parameters. */
      intBounds = 0,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.DIMMING_SETTINGS. */
      dimmingSettingsCapabilities = 1,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
      toneMappingSettingsCapabilities = 2,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.DV_CALIBRATION. */
      dvCalibrationBounds = 3,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.TWO_POINT_WB. */
      twoPointWBCapabilities = 4,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.MULTI_POINT_WB. */
      multiPointWBCapabilities = 5,
      // @aidl-doc
      /** Used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
      colourManagementSettingsBounds = 6,
    };
    // Expose tag symbols for legacy code
    // @aidl-doc
    /** Bounds for simple integer-backed PQ parameters. */
    static const inline Tag intBounds = Tag::intBounds;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.DIMMING_SETTINGS. */
    static const inline Tag dimmingSettingsCapabilities = Tag::dimmingSettingsCapabilities;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
    static const inline Tag toneMappingSettingsCapabilities = Tag::toneMappingSettingsCapabilities;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.DV_CALIBRATION. */
    static const inline Tag dvCalibrationBounds = Tag::dvCalibrationBounds;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.TWO_POINT_WB. */
    static const inline Tag twoPointWBCapabilities = Tag::twoPointWBCapabilities;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.MULTI_POINT_WB. */
    static const inline Tag multiPointWBCapabilities = Tag::multiPointWBCapabilities;
    // @aidl-doc
    /** Used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
    static const inline Tag colourManagementSettingsBounds = Tag::colourManagementSettingsBounds;

    template<typename _Tp>
    static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, RangeBound>;

    RangeBound() : _value(std::in_place_index<static_cast<size_t>(intBounds)>, ::com::rdk::hal::panel::PQParameterCapabilities::IntBounds()) { }

    template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr RangeBound(_Tp&& _arg)
        : _value(std::forward<_Tp>(_arg)) {}

    template <size_t _Np, typename... _Tp>
    constexpr explicit RangeBound(std::in_place_index_t<_Np>, _Tp&&... _args)
        : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

    template <Tag _tag, typename... _Tp>
    static RangeBound make(_Tp&&... _args) {
      return RangeBound(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
    }

    template <Tag _tag, typename _Tp, typename... _Up>
    static RangeBound make(std::initializer_list<_Tp> _il, _Up&&... _args) {
      return RangeBound(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
    }

    Tag getTag() const {
      return static_cast<Tag>(_value.index());
    }

    template <Tag _tag>
    const auto& get() const {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag>
    auto& get() {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag, typename... _Tp>
    void set(_Tp&&... _args) {
      _value.emplace<static_cast<size_t>(_tag)>(std::forward<_Tp>(_args)...);
    }

    inline bool operator!=(const RangeBound& rhs) const {
      return _value != rhs._value;
    }
    inline bool operator<(const RangeBound& rhs) const {
      return _value < rhs._value;
    }
    inline bool operator<=(const RangeBound& rhs) const {
      return _value <= rhs._value;
    }
    inline bool operator==(const RangeBound& rhs) const {
      return _value == rhs._value;
    }
    inline bool operator>(const RangeBound& rhs) const {
      return _value > rhs._value;
    }
    inline bool operator>=(const RangeBound& rhs) const {
      return _value >= rhs._value;
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.RangeBound");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "RangeBound{";
      switch (getTag()) {
      case intBounds: os << "intBounds: " << ::android::internal::ToString(get<intBounds>()); break;
      case dimmingSettingsCapabilities: os << "dimmingSettingsCapabilities: " << ::android::internal::ToString(get<dimmingSettingsCapabilities>()); break;
      case toneMappingSettingsCapabilities: os << "toneMappingSettingsCapabilities: " << ::android::internal::ToString(get<toneMappingSettingsCapabilities>()); break;
      case dvCalibrationBounds: os << "dvCalibrationBounds: " << ::android::internal::ToString(get<dvCalibrationBounds>()); break;
      case twoPointWBCapabilities: os << "twoPointWBCapabilities: " << ::android::internal::ToString(get<twoPointWBCapabilities>()); break;
      case multiPointWBCapabilities: os << "multiPointWBCapabilities: " << ::android::internal::ToString(get<multiPointWBCapabilities>()); break;
      case colourManagementSettingsBounds: os << "colourManagementSettingsBounds: " << ::android::internal::ToString(get<colourManagementSettingsBounds>()); break;
      }
      os << "}";
      return os.str();
    }
  private:
    std::variant<::com::rdk::hal::panel::PQParameterCapabilities::IntBounds, ::com::rdk::hal::panel::PQParameterCapabilities::DimmingSettingsCapabilities, ::com::rdk::hal::panel::PQParameterCapabilities::ToneMappingSettingsCapabilities, ::com::rdk::hal::panel::PQParameterCapabilities::DvCalibrationBounds, ::com::rdk::hal::panel::PQParameterCapabilities::TwoPointWBCapabilities, ::com::rdk::hal::panel::PQParameterCapabilities::MultiPointWBCapabilities, ::com::rdk::hal::panel::PQParameterCapabilities::ColourManagementSettingsBounds> _value;
  };  // class RangeBound
  // @aidl-doc
  /**
   * Discrete supported values for the PQ parameter.
   *
   * Only one supported-values shape is valid for a given PQ parameter, so the
   * active variant identifies how explicit preset values are conveyed.
   * This is intended for finite preset lists rather than large numeric
   * domains. These arrays are nullable; implementations may omit them or use
   * an empty array when no explicit presets are advertised. When a structured
   * capability uses min/max bounds instead of explicit presets, the bounds
   * describe the full supported domain.
   */
  class SupportedValues : public ::android::Parcelable {
  public:
    enum class Tag : int32_t {
      // @aidl-doc
      /**
       * Specific integer values supported for simple integer-backed PQ
       * parameters.
       * Empty array means every integer allowed by `rangeBound.intBounds` is
       * valid.
       */
      supportedIntValues = 0,
      // @aidl-doc
      /**
       * Supported SDR gamma values used when pqParameter ==
       * PQParameter.SDR_GAMMA.
       */
      supportedSdrGammaValues = 1,
      // @aidl-doc
      /**
       * Supported string values used when pqParameter ==
       * PQParameter.COLOR_TEMPERATURE.
       */
      supportedStringValues = 2,
      // @aidl-doc
      /** Specific grouped dimming presets that are supported. */
      supportedDimmingSettingsValues = 3,
      // @aidl-doc
      /** Specific Dolby Vision calibration presets that are supported. */
      supportedDvCalibrationValues = 4,
      // @aidl-doc
      /**
       * Specific 2-point white balance colour-temperature strings that are
       * supported.
       */
      supportedTwoPointWBValues = 5,
      // @aidl-doc
      /**
       * Specific multi-point white balance colour-temperature strings that
       * are supported.
       */
      supportedMultiPointWBValues = 6,
      // @aidl-doc
      /** Specific grouped colour-management presets that are supported. */
      supportedColourManagementSettingsValues = 7,
      // @aidl-doc
      /** Specific grouped tone-mapping presets that are supported. */
      supportedToneMappingSettingsValues = 8,
    };
    // Expose tag symbols for legacy code
    // @aidl-doc
    /**
     * Specific integer values supported for simple integer-backed PQ
     * parameters.
     * Empty array means every integer allowed by `rangeBound.intBounds` is
     * valid.
     */
    static const inline Tag supportedIntValues = Tag::supportedIntValues;
    // @aidl-doc
    /**
     * Supported SDR gamma values used when pqParameter ==
     * PQParameter.SDR_GAMMA.
     */
    static const inline Tag supportedSdrGammaValues = Tag::supportedSdrGammaValues;
    // @aidl-doc
    /**
     * Supported string values used when pqParameter ==
     * PQParameter.COLOR_TEMPERATURE.
     */
    static const inline Tag supportedStringValues = Tag::supportedStringValues;
    // @aidl-doc
    /** Specific grouped dimming presets that are supported. */
    static const inline Tag supportedDimmingSettingsValues = Tag::supportedDimmingSettingsValues;
    // @aidl-doc
    /** Specific Dolby Vision calibration presets that are supported. */
    static const inline Tag supportedDvCalibrationValues = Tag::supportedDvCalibrationValues;
    // @aidl-doc
    /**
     * Specific 2-point white balance colour-temperature strings that are
     * supported.
     */
    static const inline Tag supportedTwoPointWBValues = Tag::supportedTwoPointWBValues;
    // @aidl-doc
    /**
     * Specific multi-point white balance colour-temperature strings that
     * are supported.
     */
    static const inline Tag supportedMultiPointWBValues = Tag::supportedMultiPointWBValues;
    // @aidl-doc
    /** Specific grouped colour-management presets that are supported. */
    static const inline Tag supportedColourManagementSettingsValues = Tag::supportedColourManagementSettingsValues;
    // @aidl-doc
    /** Specific grouped tone-mapping presets that are supported. */
    static const inline Tag supportedToneMappingSettingsValues = Tag::supportedToneMappingSettingsValues;

    template<typename _Tp>
    static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, SupportedValues>;

    SupportedValues() : _value(std::in_place_index<static_cast<size_t>(supportedIntValues)>, ::std::optional<::std::vector<int32_t>>()) { }

    template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr SupportedValues(_Tp&& _arg)
        : _value(std::forward<_Tp>(_arg)) {}

    template <size_t _Np, typename... _Tp>
    constexpr explicit SupportedValues(std::in_place_index_t<_Np>, _Tp&&... _args)
        : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

    template <Tag _tag, typename... _Tp>
    static SupportedValues make(_Tp&&... _args) {
      return SupportedValues(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
    }

    template <Tag _tag, typename _Tp, typename... _Up>
    static SupportedValues make(std::initializer_list<_Tp> _il, _Up&&... _args) {
      return SupportedValues(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
    }

    Tag getTag() const {
      return static_cast<Tag>(_value.index());
    }

    template <Tag _tag>
    const auto& get() const {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag>
    auto& get() {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag, typename... _Tp>
    void set(_Tp&&... _args) {
      _value.emplace<static_cast<size_t>(_tag)>(std::forward<_Tp>(_args)...);
    }

    inline bool operator!=(const SupportedValues& rhs) const {
      return _value != rhs._value;
    }
    inline bool operator<(const SupportedValues& rhs) const {
      return _value < rhs._value;
    }
    inline bool operator<=(const SupportedValues& rhs) const {
      return _value <= rhs._value;
    }
    inline bool operator==(const SupportedValues& rhs) const {
      return _value == rhs._value;
    }
    inline bool operator>(const SupportedValues& rhs) const {
      return _value > rhs._value;
    }
    inline bool operator>=(const SupportedValues& rhs) const {
      return _value >= rhs._value;
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.SupportedValues");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "SupportedValues{";
      switch (getTag()) {
      case supportedIntValues: os << "supportedIntValues: " << ::android::internal::ToString(get<supportedIntValues>()); break;
      case supportedSdrGammaValues: os << "supportedSdrGammaValues: " << ::android::internal::ToString(get<supportedSdrGammaValues>()); break;
      case supportedStringValues: os << "supportedStringValues: " << ::android::internal::ToString(get<supportedStringValues>()); break;
      case supportedDimmingSettingsValues: os << "supportedDimmingSettingsValues: " << ::android::internal::ToString(get<supportedDimmingSettingsValues>()); break;
      case supportedDvCalibrationValues: os << "supportedDvCalibrationValues: " << ::android::internal::ToString(get<supportedDvCalibrationValues>()); break;
      case supportedTwoPointWBValues: os << "supportedTwoPointWBValues: " << ::android::internal::ToString(get<supportedTwoPointWBValues>()); break;
      case supportedMultiPointWBValues: os << "supportedMultiPointWBValues: " << ::android::internal::ToString(get<supportedMultiPointWBValues>()); break;
      case supportedColourManagementSettingsValues: os << "supportedColourManagementSettingsValues: " << ::android::internal::ToString(get<supportedColourManagementSettingsValues>()); break;
      case supportedToneMappingSettingsValues: os << "supportedToneMappingSettingsValues: " << ::android::internal::ToString(get<supportedToneMappingSettingsValues>()); break;
      }
      os << "}";
      return os.str();
    }
  private:
    std::variant<::std::optional<::std::vector<int32_t>>, ::std::optional<::std::vector<::com::rdk::hal::panel::SDRGamma>>, ::std::optional<::std::vector<::std::optional<::std::string>>>, ::std::optional<::std::vector<::std::optional<::com::rdk::hal::panel::DimmingSettings>>>, ::std::optional<::std::vector<::std::optional<::com::rdk::hal::panel::DolbyVisionCalibrationSettings>>>, ::std::optional<::std::vector<::std::optional<::std::string>>>, ::std::optional<::std::vector<::std::optional<::std::string>>>, ::std::optional<::std::vector<::std::optional<::com::rdk::hal::panel::ColourManagementSettings>>>, ::std::optional<::std::vector<::std::optional<::com::rdk::hal::panel::ToneMappingSettings>>>> _value;
  };  // class SupportedValues
  // @aidl-doc
  /** Nested PQ parameter picture-mode capabilities definition. */
  class PQParamPictureModeCapabilities : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** Nested PQ parameter dynamic-range capabilities definition. */
    class PQParamDynamicRangeCapabilities : public ::android::Parcelable {
    public:
      // @aidl-doc
      /** The dynamic range. */
      ::com::rdk::hal::videodecoder::DynamicRange dynamicRange = ::com::rdk::hal::videodecoder::DynamicRange(0);
      // @aidl-doc
      /** The AV sources for which the PQ parameter is supported in this picture mode and dynamic range. */
      ::std::vector<::com::rdk::hal::panel::PanelSource> supportedAVSources;
      inline bool operator!=(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) != std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator<(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) < std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator<=(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) <= std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator==(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) == std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator>(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) > std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }
      inline bool operator>=(const PQParamDynamicRangeCapabilities& rhs) const {
        return std::tie(dynamicRange, supportedAVSources) >= std::tie(rhs.dynamicRange, rhs.supportedAVSources);
      }

      ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
      ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
      ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
      static const ::android::String16& getParcelableDescriptor() {
        static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.PQParamPictureModeCapabilities.PQParamDynamicRangeCapabilities");
        return DESCIPTOR;
      }
      inline std::string toString() const {
        std::ostringstream os;
        os << "PQParamDynamicRangeCapabilities{";
        os << "dynamicRange: " << ::android::internal::ToString(dynamicRange);
        os << ", supportedAVSources: " << ::android::internal::ToString(supportedAVSources);
        os << "}";
        return os.str();
      }
    };  // class PQParamDynamicRangeCapabilities
    // @aidl-doc
    /** The picture mode. */
    ::std::string pictureMode;
    // @aidl-doc
    /** The dynamic ranges, and their AV sources, supported for this picture mode. */
    ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::PQParamPictureModeCapabilities::PQParamDynamicRangeCapabilities> pqParamDynamicRangeCapabilities;
    inline bool operator!=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) != std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }
    inline bool operator<(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) < std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }
    inline bool operator<=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) <= std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }
    inline bool operator==(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) == std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }
    inline bool operator>(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) > std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }
    inline bool operator>=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamDynamicRangeCapabilities) >= std::tie(rhs.pictureMode, rhs.pqParamDynamicRangeCapabilities);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.PQParamPictureModeCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "PQParamPictureModeCapabilities{";
      os << "pictureMode: " << ::android::internal::ToString(pictureMode);
      os << ", pqParamDynamicRangeCapabilities: " << ::android::internal::ToString(pqParamDynamicRangeCapabilities);
      os << "}";
      return os.str();
    }
  };  // class PQParamPictureModeCapabilities
  // @aidl-doc
  /** The PQ parameter being referenced in these capabilities. */
  ::com::rdk::hal::panel::PQParameter pqParameter = ::com::rdk::hal::panel::PQParameter(0);
  // @aidl-doc
  /**
   * Whether this PQ parameter is supported on the platform.
   * If unsupported, all other fields in this parcelable should be ignored.
   */
  bool isSupported = false;
  // @aidl-doc
  /**
   * Whether this PQ parameter globally affects the composite image,
   * including the graphics plane and all video planes, or is limited to
   * video.
   */
  bool isGlobal = false;
  // @aidl-doc
  /** The bounds for the PQ parameter. Null if the parameter uses supportedValues only. */
  ::std::optional<::com::rdk::hal::panel::PQParameterCapabilities::RangeBound> rangeBound;
  // @aidl-doc
  /** The discrete preset values for the PQ parameter. Null if it uses rangeBound only. */
  ::std::optional<::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues> supportedValues;
  // @aidl-doc
  /** Array of PQ parameter capabilities for picture modes. */
  ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::PQParamPictureModeCapabilities> pqParamPictureModeCapabilities;
  inline bool operator!=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) != std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator<(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) < std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator<=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) <= std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator==(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) == std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator>(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) > std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator>=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, rangeBound, supportedValues, pqParamPictureModeCapabilities) >= std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.rangeBound, rhs.supportedValues, rhs.pqParamPictureModeCapabilities);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PQParameterCapabilities{";
    os << "pqParameter: " << ::android::internal::ToString(pqParameter);
    os << ", isSupported: " << ::android::internal::ToString(isSupported);
    os << ", isGlobal: " << ::android::internal::ToString(isGlobal);
    os << ", rangeBound: " << ::android::internal::ToString(rangeBound);
    os << ", supportedValues: " << ::android::internal::ToString(supportedValues);
    os << ", pqParamPictureModeCapabilities: " << ::android::internal::ToString(pqParamPictureModeCapabilities);
    os << "}";
    return os.str();
  }
};  // class PQParameterCapabilities
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(PQParameterCapabilities::RangeBound::Tag val) {
  switch(val) {
  case PQParameterCapabilities::RangeBound::Tag::intBounds:
    return "intBounds";
  case PQParameterCapabilities::RangeBound::Tag::dimmingSettingsCapabilities:
    return "dimmingSettingsCapabilities";
  case PQParameterCapabilities::RangeBound::Tag::toneMappingSettingsCapabilities:
    return "toneMappingSettingsCapabilities";
  case PQParameterCapabilities::RangeBound::Tag::dvCalibrationBounds:
    return "dvCalibrationBounds";
  case PQParameterCapabilities::RangeBound::Tag::twoPointWBCapabilities:
    return "twoPointWBCapabilities";
  case PQParameterCapabilities::RangeBound::Tag::multiPointWBCapabilities:
    return "multiPointWBCapabilities";
  case PQParameterCapabilities::RangeBound::Tag::colourManagementSettingsBounds:
    return "colourManagementSettingsBounds";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag, 7> enum_values<::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag> = {
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::intBounds,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::dimmingSettingsCapabilities,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::toneMappingSettingsCapabilities,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::dvCalibrationBounds,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::twoPointWBCapabilities,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::multiPointWBCapabilities,
  ::com::rdk::hal::panel::PQParameterCapabilities::RangeBound::Tag::colourManagementSettingsBounds,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(PQParameterCapabilities::SupportedValues::Tag val) {
  switch(val) {
  case PQParameterCapabilities::SupportedValues::Tag::supportedIntValues:
    return "supportedIntValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedSdrGammaValues:
    return "supportedSdrGammaValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedStringValues:
    return "supportedStringValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedDimmingSettingsValues:
    return "supportedDimmingSettingsValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedDvCalibrationValues:
    return "supportedDvCalibrationValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedTwoPointWBValues:
    return "supportedTwoPointWBValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedMultiPointWBValues:
    return "supportedMultiPointWBValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedColourManagementSettingsValues:
    return "supportedColourManagementSettingsValues";
  case PQParameterCapabilities::SupportedValues::Tag::supportedToneMappingSettingsValues:
    return "supportedToneMappingSettingsValues";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag, 9> enum_values<::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag> = {
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedIntValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedSdrGammaValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedStringValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedDimmingSettingsValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedDvCalibrationValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedTwoPointWBValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedMultiPointWBValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedColourManagementSettingsValues,
  ::com::rdk::hal::panel::PQParameterCapabilities::SupportedValues::Tag::supportedToneMappingSettingsValues,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
