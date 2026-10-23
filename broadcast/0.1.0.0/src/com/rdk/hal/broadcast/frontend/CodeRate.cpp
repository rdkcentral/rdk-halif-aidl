#include <com/rdk/hal/broadcast/frontend/CodeRate.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
::android::status_t CodeRate::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case dvbC: {
    ::com::rdk::hal::broadcast::frontend::DvbCCodeRate _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbCCodeRate>) {
      set<dvbC>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbC>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbS: {
    ::com::rdk::hal::broadcast::frontend::DvbSInnerFec _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSInnerFec>) {
      set<dvbS>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbS>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbT: {
    ::com::rdk::hal::broadcast::frontend::DvbTCodeRates _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTCodeRates>) {
      set<dvbT>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbT>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t CodeRate::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case dvbC: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbC>()));
  case dvbS: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbS>()));
  case dvbT: return _aidl_parcel->writeParcelable(get<dvbT>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
