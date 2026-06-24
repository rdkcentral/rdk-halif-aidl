#include <com/rdk/hal/sensor/motion/IMotionSensorControllerListener.h>
#include <com/rdk/hal/sensor/motion/BpMotionSensorControllerListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(MotionSensorControllerListener, "com.rdk.hal.sensor.motion.IMotionSensorControllerListener")
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/sensor/motion/BpMotionSensorControllerListener.h>
#include <com/rdk/hal/sensor/motion/BnMotionSensorControllerListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BpMotionSensorControllerListener::BpMotionSensorControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IMotionSensorControllerListener>(_aidl_impl){
}

::android::binder::Status BpMotionSensorControllerListener::onStateChanged(::com::rdk::hal::sensor::motion::State oldState, ::com::rdk::hal::sensor::motion::State newState) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeByte(static_cast<int8_t>(oldState));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeByte(static_cast<int8_t>(newState));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorControllerListener::TRANSACTION_onStateChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorControllerListener::getDefaultImpl())) {
     return IMotionSensorControllerListener::getDefaultImpl()->onStateChanged(oldState, newState);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpMotionSensorControllerListener::onActiveWindowEntered() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorControllerListener::TRANSACTION_onActiveWindowEntered, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorControllerListener::getDefaultImpl())) {
     return IMotionSensorControllerListener::getDefaultImpl()->onActiveWindowEntered();
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpMotionSensorControllerListener::onActiveWindowExited() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnMotionSensorControllerListener::TRANSACTION_onActiveWindowExited, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IMotionSensorControllerListener::getDefaultImpl())) {
     return IMotionSensorControllerListener::getDefaultImpl()->onActiveWindowExited();
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpMotionSensorControllerListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorControllerListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpMotionSensorControllerListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnMotionSensorControllerListener::TRANSACTION_getInterfaceHash, data, &reply);
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
#include <com/rdk/hal/sensor/motion/BnMotionSensorControllerListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace sensor {
namespace motion {

BnMotionSensorControllerListener::BnMotionSensorControllerListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnMotionSensorControllerListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnMotionSensorControllerListener::TRANSACTION_onStateChanged:
  {
    ::com::rdk::hal::sensor::motion::State in_oldState;
    ::com::rdk::hal::sensor::motion::State in_newState;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readByte(reinterpret_cast<int8_t *>(&in_oldState));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readByte(reinterpret_cast<int8_t *>(&in_newState));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onStateChanged(in_oldState, in_newState));
  }
  break;
  case BnMotionSensorControllerListener::TRANSACTION_onActiveWindowEntered:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(onActiveWindowEntered());
  }
  break;
  case BnMotionSensorControllerListener::TRANSACTION_onActiveWindowExited:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(onActiveWindowExited());
  }
  break;
  case BnMotionSensorControllerListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IMotionSensorControllerListener::VERSION);
  }
  break;
  case BnMotionSensorControllerListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IMotionSensorControllerListener::HASH);
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

int32_t BnMotionSensorControllerListener::getInterfaceVersion() {
  return IMotionSensorControllerListener::VERSION;
}
std::string BnMotionSensorControllerListener::getInterfaceHash() {
  return IMotionSensorControllerListener::HASH;
}
}  // namespace motion
}  // namespace sensor
}  // namespace hal
}  // namespace rdk
}  // namespace com
