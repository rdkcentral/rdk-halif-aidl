#include <com/rdk/hal/sensor/motion/IMotionSensorManager.h>
#include <com/rdk/hal/sensor/motion/BpMotionSensorManager.h>
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(MotionSensorManager, "com.rdk.hal.sensor.motion.IMotionSensorManager")
const ::std::string& IMotionSensorManager::serviceName() {
  static const ::std::string value("sensor.motion");
  return value;
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/sensor/motion/BpMotionSensorManager.h>
#include <com/rdk/hal/sensor/motion/BnMotionSensorManager.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BpMotionSensorManager::BpMotionSensorManager(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IMotionSensorManager>(_aidl_impl){
}

::android::binder::Status BpMotionSensorManager::getMotionSensorIds(::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>>* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorManager::TRANSACTION_getMotionSensorIds, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorManager::getDefaultImpl())) {
     return IMotionSensorManager::getDefaultImpl()->getMotionSensorIds(_aidl_return);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  if (!_aidl_status.isOk()) {
    return _aidl_status;
  }
  _aidl_ret_status = _aidl_reply.readParcelableVector(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpMotionSensorManager::getMotionSensor(const ::com::rdk::hal::sensor::motion::IMotionSensor::Id& motionSensorId, ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor>* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(motionSensorId);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorManager::TRANSACTION_getMotionSensor, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorManager::getDefaultImpl())) {
     return IMotionSensorManager::getDefaultImpl()->getMotionSensor(motionSensorId, _aidl_return);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_status.readFromParcel(_aidl_reply);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  if (!_aidl_status.isOk()) {
    return _aidl_status;
  }
  _aidl_ret_status = _aidl_reply.readNullableStrongBinder(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpMotionSensorManager::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorManager::TRANSACTION_getInterfaceVersion, data, &reply);
    if (err == ::android::OK) {
      ::android::binder::Status _aidl_status;
      err = _aidl_status.readFromParcel(reply);
      if (err == ::android::OK && _aidl_status.isOk()) {
        cached_version_ = reply.readInt32();
      }
    }
  }
  return cached_version_;
}


std::string BpMotionSensorManager::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorManager::TRANSACTION_getInterfaceHash, data, &reply);
    if (err == ::android::OK) {
      ::android::binder::Status _aidl_status;
      err = _aidl_status.readFromParcel(reply);
      if (err == ::android::OK && _aidl_status.isOk()) {
        reply.readUtf8FromUtf16(&cached_hash_);
      }
    }
  }
  return cached_hash_;
}

}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/sensor/motion/BnMotionSensorManager.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BnMotionSensorManager::BnMotionSensorManager()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnMotionSensorManager::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnMotionSensorManager::TRANSACTION_getMotionSensorIds:
  {
    ::std::optional<::std::vector<::std::optional<::com::rdk::hal::sensor::motion::IMotionSensor::Id>>> _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(getMotionSensorIds(&_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeParcelableVector(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnMotionSensorManager::TRANSACTION_getMotionSensor:
  {
    ::com::rdk::hal::sensor::motion::IMotionSensor::Id in_motionSensorId;
    ::android::sp<::com::rdk::hal::sensor::motion::IMotionSensor> _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_motionSensorId);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(getMotionSensor(in_motionSensorId, &_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeStrongBinder(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnMotionSensorManager::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IMotionSensorManager::VERSION);
  }
  break;
  case BnMotionSensorManager::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IMotionSensorManager::HASH);
  }
  break;
  default:
  {
    _aidl_ret_status = ::android::BBinder::onTransact(_aidl_code, _aidl_data, _aidl_reply, _aidl_flags);
  }
  break;
  }
  if (_aidl_ret_status == ::android::UNEXPECTED_NULL) {
    _aidl_ret_status = ::android::binder::Status::fromExceptionCode(::android::binder::Status::EX_NULL_POINTER).writeOverParcel(_aidl_reply);
  }
  return _aidl_ret_status;
}

int32_t BnMotionSensorManager::getInterfaceVersion() {
  return IMotionSensorManager::VERSION;
}
std::string BnMotionSensorManager::getInterfaceHash() {
  return IMotionSensorManager::HASH;
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
