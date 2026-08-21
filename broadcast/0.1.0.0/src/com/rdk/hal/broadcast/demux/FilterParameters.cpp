#include <com/rdk/hal/broadcast/demux/FilterParameters.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
::android::status_t FilterParameters::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case mpeg2TsData: {
    ::com::rdk::hal::broadcast::demux::Mpeg2TsDataFilterParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::demux::Mpeg2TsDataFilterParameters>) {
      set<mpeg2TsData>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsData>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case mpeg2TsClock: {
    ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters>) {
      set<mpeg2TsClock>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsClock>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case mpeg2TsVideo: {
    ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters>) {
      set<mpeg2TsVideo>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsVideo>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case mpeg2TsAudio: {
    ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters>) {
      set<mpeg2TsAudio>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsAudio>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case mpeg2TsSupplementaryAudio: {
    ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters>) {
      set<mpeg2TsSupplementaryAudio>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsSupplementaryAudio>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t FilterParameters::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case mpeg2TsData: return _aidl_parcel->writeParcelable(get<mpeg2TsData>());
  case mpeg2TsClock: return _aidl_parcel->writeParcelable(get<mpeg2TsClock>());
  case mpeg2TsVideo: return _aidl_parcel->writeParcelable(get<mpeg2TsVideo>());
  case mpeg2TsAudio: return _aidl_parcel->writeParcelable(get<mpeg2TsAudio>());
  case mpeg2TsSupplementaryAudio: return _aidl_parcel->writeParcelable(get<mpeg2TsSupplementaryAudio>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
