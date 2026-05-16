#include <com/rdk/hal/drm/DrmMetricValue.h>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
::android::status_t DrmMetricValue::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case int64Value: {
    int64_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt64(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int64_t>) {
      set<int64Value>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<int64Value>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case doubleValue: {
    double _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readDouble(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<double>) {
      set<doubleValue>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<doubleValue>(std::move(_aidl_value));
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
  }
  return ::android::BAD_VALUE;
}
::android::status_t DrmMetricValue::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case int64Value: return _aidl_parcel->writeInt64(get<int64Value>());
  case doubleValue: return _aidl_parcel->writeDouble(get<doubleValue>());
  case stringValue: return _aidl_parcel->writeString16(get<stringValue>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
