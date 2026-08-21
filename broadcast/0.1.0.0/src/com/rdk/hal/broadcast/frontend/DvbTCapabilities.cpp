#include <com/rdk/hal/broadcast/frontend/DvbTCapabilities.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
::android::status_t DvbTCapabilities::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  size_t _aidl_start_pos = _aidl_parcel->dataPosition();
  int32_t _aidl_parcelable_raw_size = 0;
  _aidl_ret_status = _aidl_parcel->readInt32(&_aidl_parcelable_raw_size);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcelable_raw_size < 4) return ::android::BAD_VALUE;
  size_t _aidl_parcelable_size = static_cast<size_t>(_aidl_parcelable_raw_size);
  if (_aidl_start_pos > SIZE_MAX - _aidl_parcelable_size) return ::android::BAD_VALUE;
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&bandwidths);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&subCarrierModulations);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&codingRates);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&dvbTStandards);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&guardIntervals);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readEnumVector(&transmissionModes);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  if (_aidl_parcel->dataPosition() - _aidl_start_pos >= _aidl_parcelable_size) {
    _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->readParcelable(&extension);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_parcel->setDataPosition(_aidl_start_pos + _aidl_parcelable_size);
  return _aidl_ret_status;
}
::android::status_t DvbTCapabilities::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = ::android::OK;
  auto _aidl_start_pos = _aidl_parcel->dataPosition();
  _aidl_parcel->writeInt32(0);
  _aidl_ret_status = _aidl_parcel->writeEnumVector(bandwidths);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeEnumVector(subCarrierModulations);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeEnumVector(codingRates);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeEnumVector(dvbTStandards);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeEnumVector(guardIntervals);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeEnumVector(transmissionModes);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  _aidl_ret_status = _aidl_parcel->writeParcelable(extension);
  if (((_aidl_ret_status) != (::android::OK))) {
    return _aidl_ret_status;
  }
  auto _aidl_end_pos = _aidl_parcel->dataPosition();
  _aidl_parcel->setDataPosition(_aidl_start_pos);
  _aidl_parcel->writeInt32(_aidl_end_pos - _aidl_start_pos);
  _aidl_parcel->setDataPosition(_aidl_end_pos);
  return _aidl_ret_status;
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
