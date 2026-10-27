#include <com/rdk/hal/broadcast/demux/Filter.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
::android::status_t Filter::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case mpeg2TsData: {
    ::android::sp<::com::rdk::hal::broadcast::demux::IMpeg2TsDataFilter> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readStrongBinder(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::sp<::com::rdk::hal::broadcast::demux::IMpeg2TsDataFilter>>) {
      set<mpeg2TsData>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<mpeg2TsData>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case clock: {
    ::android::sp<::com::rdk::hal::broadcast::demux::IClockFilter> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readStrongBinder(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::sp<::com::rdk::hal::broadcast::demux::IClockFilter>>) {
      set<clock>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<clock>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case video: {
    ::android::sp<::com::rdk::hal::broadcast::demux::IVideoFilter> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readStrongBinder(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::sp<::com::rdk::hal::broadcast::demux::IVideoFilter>>) {
      set<video>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<video>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case audio: {
    ::android::sp<::com::rdk::hal::broadcast::demux::IAudioFilter> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readStrongBinder(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::sp<::com::rdk::hal::broadcast::demux::IAudioFilter>>) {
      set<audio>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<audio>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case supplementaryAudio: {
    ::android::sp<::com::rdk::hal::broadcast::demux::ISupplementaryAudioFilter> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readStrongBinder(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::android::sp<::com::rdk::hal::broadcast::demux::ISupplementaryAudioFilter>>) {
      set<supplementaryAudio>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<supplementaryAudio>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t Filter::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case mpeg2TsData: return _aidl_parcel->writeStrongBinder(get<mpeg2TsData>());
  case clock: return _aidl_parcel->writeStrongBinder(get<clock>());
  case video: return _aidl_parcel->writeStrongBinder(get<video>());
  case audio: return _aidl_parcel->writeStrongBinder(get<audio>());
  case supplementaryAudio: return _aidl_parcel->writeStrongBinder(get<supplementaryAudio>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
