#include <com/rdk/hal/broadcast/frontend/TuneParameters.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
::android::status_t TuneParameters::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case atsc: {
    ::com::rdk::hal::broadcast::frontend::AtscTuneParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::AtscTuneParameters>) {
      set<atsc>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<atsc>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbC: {
    ::com::rdk::hal::broadcast::frontend::DvbCTuneParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbCTuneParameters>) {
      set<dvbC>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbC>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbS: {
    ::com::rdk::hal::broadcast::frontend::DvbSTuneParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSTuneParameters>) {
      set<dvbS>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbS>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbT: {
    ::com::rdk::hal::broadcast::frontend::DvbTTuneParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTTuneParameters>) {
      set<dvbT>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbT>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t TuneParameters::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case atsc: return _aidl_parcel->writeParcelable(get<atsc>());
  case dvbC: return _aidl_parcel->writeParcelable(get<dvbC>());
  case dvbS: return _aidl_parcel->writeParcelable(get<dvbS>());
  case dvbT: return _aidl_parcel->writeParcelable(get<dvbT>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
