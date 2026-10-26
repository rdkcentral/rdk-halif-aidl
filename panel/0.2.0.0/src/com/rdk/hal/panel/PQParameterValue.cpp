#include <com/rdk/hal/panel/PQParameterValue.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
::android::status_t PQParameterValue::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case intValue: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<intValue>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<intValue>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case sdrGamma: {
    ::com::rdk::hal::panel::SDRGamma _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::panel::SDRGamma>) {
      set<sdrGamma>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<sdrGamma>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case stringValue: {
    ::android::String16 _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readString16(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::String16>) {
      set<stringValue>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<stringValue>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dimmingSettings: {
    ::com::rdk::hal::panel::DimmingSettings _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::panel::DimmingSettings>) {
      set<dimmingSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dimmingSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvCalibrationSettings: {
    ::com::rdk::hal::panel::DolbyVisionCalibrationSettings _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::panel::DolbyVisionCalibrationSettings>) {
      set<dvCalibrationSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvCalibrationSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case twoPointWBSettings: {
    ::std::vector<::com::rdk::hal::panel::TwoPointWB> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelableVector(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::std::vector<::com::rdk::hal::panel::TwoPointWB>>) {
      set<twoPointWBSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<twoPointWBSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case multiPointWBSettings: {
    ::std::vector<::com::rdk::hal::panel::WhiteBalanceMultiPointSettings> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelableVector(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::std::vector<::com::rdk::hal::panel::WhiteBalanceMultiPointSettings>>) {
      set<multiPointWBSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<multiPointWBSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case colourManagementSettings: {
    ::com::rdk::hal::panel::ColourManagementSettings _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::panel::ColourManagementSettings>) {
      set<colourManagementSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<colourManagementSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case toneMappingSettings: {
    ::com::rdk::hal::panel::ToneMappingSettings _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::panel::ToneMappingSettings>) {
      set<toneMappingSettings>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<toneMappingSettings>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t PQParameterValue::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case intValue: return _aidl_parcel->writeInt32(get<intValue>());
  case sdrGamma: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<sdrGamma>()));
  case stringValue: return _aidl_parcel->writeString16(get<stringValue>());
  case dimmingSettings: return _aidl_parcel->writeParcelable(get<dimmingSettings>());
  case dvCalibrationSettings: return _aidl_parcel->writeParcelable(get<dvCalibrationSettings>());
  case twoPointWBSettings: return _aidl_parcel->writeParcelableVector(get<twoPointWBSettings>());
  case multiPointWBSettings: return _aidl_parcel->writeParcelableVector(get<multiPointWBSettings>());
  case colourManagementSettings: return _aidl_parcel->writeParcelable(get<colourManagementSettings>());
  case toneMappingSettings: return _aidl_parcel->writeParcelable(get<toneMappingSettings>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
