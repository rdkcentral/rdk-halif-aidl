#include <com/rdk/hal/sensor/motion/IMotionSensorEventListener.h>
#include <com/rdk/hal/sensor/motion/BpMotionSensorEventListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(MotionSensorEventListener, "com.rdk.hal.sensor.motion.IMotionSensorEventListener")
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/sensor/motion/BpMotionSensorEventListener.h>
#include <com/rdk/hal/sensor/motion/BnMotionSensorEventListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BpMotionSensorEventListener::BpMotionSensorEventListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IMotionSensorEventListener>(_aidl_impl){
}

::android::binder::Status BpMotionSensorEventListener::onEvent(::com::rdk::hal::sensor::motion::OperationalMode mode) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeByte(static_cast<int8_t>(mode));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorEventListener::TRANSACTION_onEvent, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorEventListener::getDefaultImpl())) {
     return IMotionSensorEventListener::getDefaultImpl()->onEvent(mode);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpMotionSensorEventListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorEventListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpMotionSensorEventListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorEventListener::TRANSACTION_getInterfaceHash, data, &reply);
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
#include <com/rdk/hal/sensor/motion/BnMotionSensorEventListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BnMotionSensorEventListener::BnMotionSensorEventListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnMotionSensorEventListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnMotionSensorEventListener::TRANSACTION_onEvent:
  {
    ::com::rdk::hal::sensor::motion::OperationalMode in_mode;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readByte(reinterpret_cast<int8_t *>(&in_mode));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onEvent(in_mode));
  }
  break;
  case BnMotionSensorEventListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IMotionSensorEventListener::VERSION);
  }
  break;
  case BnMotionSensorEventListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IMotionSensorEventListener::HASH);
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

int32_t BnMotionSensorEventListener::getInterfaceVersion() {
  return IMotionSensorEventListener::VERSION;
}
std::string BnMotionSensorEventListener::getInterfaceHash() {
  return IMotionSensorEventListener::HASH;
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
