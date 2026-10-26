#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/panel/ColourManagementSettings.h>
#include <com/rdk/hal/panel/DimmingSettings.h>
#include <com/rdk/hal/panel/DolbyVisionCalibrationSettings.h>
#include <com/rdk/hal/panel/SDRGamma.h>
#include <com/rdk/hal/panel/ToneMappingSettings.h>
#include <com/rdk/hal/panel/TwoPointWB.h>
#include <com/rdk/hal/panel/WhiteBalanceMultiPointSettings.h>
#include <cstdint>
#include <string>
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
/** @brief Value union for a PQ parameter configuration. */
class PQParameterValue : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    // @aidl-doc
    /** Integer value used by all PQ parameters except SDR_GAMMA, COLOR_TEMPERATURE, DIMMING_SETTINGS, DV_CALIBRATION, TWO_POINT_WB, MULTI_POINT_WB, COLOUR_MANAGEMENT_SETTINGS, and TONE_MAPPING_SETTINGS. */
    intValue = 0,
    // @aidl-doc
    /** SDR gamma value used when pqParameter == PQParameter.SDR_GAMMA. */
    sdrGamma = 1,
    // @aidl-doc
    /** String value used when pqParameter == PQParameter.COLOR_TEMPERATURE. */
    stringValue = 2,
    // @aidl-doc
    /** Grouped dimming settings used when pqParameter == PQParameter.DIMMING_SETTINGS. */
    dimmingSettings = 3,
    // @aidl-doc
    /** Dolby Vision calibration settings used when pqParameter == PQParameter.DV_CALIBRATION. */
    dvCalibrationSettings = 4,
    // @aidl-doc
    /** Aggregate 2-point white balance settings used when pqParameter == PQParameter.TWO_POINT_WB; the array contains the full bundle for the resolved selector context. */
    twoPointWBSettings = 5,
    // @aidl-doc
    /** Aggregate multi-point white balance settings used when pqParameter == PQParameter.MULTI_POINT_WB; the array contains the full bundle for the resolved selector context. */
    multiPointWBSettings = 6,
    // @aidl-doc
    /** Grouped colour-management settings used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
    colourManagementSettings = 7,
    // @aidl-doc
    /** Grouped tone-mapping settings used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
    toneMappingSettings = 8,
  };
  // Expose tag symbols for legacy code
  // @aidl-doc
  /** Integer value used by all PQ parameters except SDR_GAMMA, COLOR_TEMPERATURE, DIMMING_SETTINGS, DV_CALIBRATION, TWO_POINT_WB, MULTI_POINT_WB, COLOUR_MANAGEMENT_SETTINGS, and TONE_MAPPING_SETTINGS. */
  static const inline Tag intValue = Tag::intValue;
  // @aidl-doc
  /** SDR gamma value used when pqParameter == PQParameter.SDR_GAMMA. */
  static const inline Tag sdrGamma = Tag::sdrGamma;
  // @aidl-doc
  /** String value used when pqParameter == PQParameter.COLOR_TEMPERATURE. */
  static const inline Tag stringValue = Tag::stringValue;
  // @aidl-doc
  /** Grouped dimming settings used when pqParameter == PQParameter.DIMMING_SETTINGS. */
  static const inline Tag dimmingSettings = Tag::dimmingSettings;
  // @aidl-doc
  /** Dolby Vision calibration settings used when pqParameter == PQParameter.DV_CALIBRATION. */
  static const inline Tag dvCalibrationSettings = Tag::dvCalibrationSettings;
  // @aidl-doc
  /** Aggregate 2-point white balance settings used when pqParameter == PQParameter.TWO_POINT_WB; the array contains the full bundle for the resolved selector context. */
  static const inline Tag twoPointWBSettings = Tag::twoPointWBSettings;
  // @aidl-doc
  /** Aggregate multi-point white balance settings used when pqParameter == PQParameter.MULTI_POINT_WB; the array contains the full bundle for the resolved selector context. */
  static const inline Tag multiPointWBSettings = Tag::multiPointWBSettings;
  // @aidl-doc
  /** Grouped colour-management settings used when pqParameter == PQParameter.COLOUR_MANAGEMENT_SETTINGS. */
  static const inline Tag colourManagementSettings = Tag::colourManagementSettings;
  // @aidl-doc
  /** Grouped tone-mapping settings used when pqParameter == PQParameter.TONE_MAPPING_SETTINGS. */
  static const inline Tag toneMappingSettings = Tag::toneMappingSettings;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, PQParameterValue>;

  PQParameterValue() : _value(std::in_place_index<static_cast<size_t>(intValue)>, int32_t(0)) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr PQParameterValue(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit PQParameterValue(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static PQParameterValue make(_Tp&&... _args) {
    return PQParameterValue(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static PQParameterValue make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return PQParameterValue(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const PQParameterValue& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const PQParameterValue& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const PQParameterValue& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const PQParameterValue& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const PQParameterValue& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const PQParameterValue& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PQParameterValue{";
    switch (getTag()) {
    case intValue: os << "intValue: " << ::android::internal::ToString(get<intValue>()); break;
    case sdrGamma: os << "sdrGamma: " << ::android::internal::ToString(get<sdrGamma>()); break;
    case stringValue: os << "stringValue: " << ::android::internal::ToString(get<stringValue>()); break;
    case dimmingSettings: os << "dimmingSettings: " << ::android::internal::ToString(get<dimmingSettings>()); break;
    case dvCalibrationSettings: os << "dvCalibrationSettings: " << ::android::internal::ToString(get<dvCalibrationSettings>()); break;
    case twoPointWBSettings: os << "twoPointWBSettings: " << ::android::internal::ToString(get<twoPointWBSettings>()); break;
    case multiPointWBSettings: os << "multiPointWBSettings: " << ::android::internal::ToString(get<multiPointWBSettings>()); break;
    case colourManagementSettings: os << "colourManagementSettings: " << ::android::internal::ToString(get<colourManagementSettings>()); break;
    case toneMappingSettings: os << "toneMappingSettings: " << ::android::internal::ToString(get<toneMappingSettings>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<int32_t, ::com::rdk::hal::panel::SDRGamma, ::android::String16, ::com::rdk::hal::panel::DimmingSettings, ::com::rdk::hal::panel::DolbyVisionCalibrationSettings, ::std::vector<::com::rdk::hal::panel::TwoPointWB>, ::std::vector<::com::rdk::hal::panel::WhiteBalanceMultiPointSettings>, ::com::rdk::hal::panel::ColourManagementSettings, ::com::rdk::hal::panel::ToneMappingSettings> _value;
};  // class PQParameterValue
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(PQParameterValue::Tag val) {
  switch(val) {
  case PQParameterValue::Tag::intValue:
    return "intValue";
  case PQParameterValue::Tag::sdrGamma:
    return "sdrGamma";
  case PQParameterValue::Tag::stringValue:
    return "stringValue";
  case PQParameterValue::Tag::dimmingSettings:
    return "dimmingSettings";
  case PQParameterValue::Tag::dvCalibrationSettings:
    return "dvCalibrationSettings";
  case PQParameterValue::Tag::twoPointWBSettings:
    return "twoPointWBSettings";
  case PQParameterValue::Tag::multiPointWBSettings:
    return "multiPointWBSettings";
  case PQParameterValue::Tag::colourManagementSettings:
    return "colourManagementSettings";
  case PQParameterValue::Tag::toneMappingSettings:
    return "toneMappingSettings";
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
constexpr inline std::array<::com::rdk::hal::panel::PQParameterValue::Tag, 9> enum_values<::com::rdk::hal::panel::PQParameterValue::Tag> = {
  ::com::rdk::hal::panel::PQParameterValue::Tag::intValue,
  ::com::rdk::hal::panel::PQParameterValue::Tag::sdrGamma,
  ::com::rdk::hal::panel::PQParameterValue::Tag::stringValue,
  ::com::rdk::hal::panel::PQParameterValue::Tag::dimmingSettings,
  ::com::rdk::hal::panel::PQParameterValue::Tag::dvCalibrationSettings,
  ::com::rdk::hal::panel::PQParameterValue::Tag::twoPointWBSettings,
  ::com::rdk::hal::panel::PQParameterValue::Tag::multiPointWBSettings,
  ::com::rdk::hal::panel::PQParameterValue::Tag::colourManagementSettings,
  ::com::rdk::hal::panel::PQParameterValue::Tag::toneMappingSettings,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
