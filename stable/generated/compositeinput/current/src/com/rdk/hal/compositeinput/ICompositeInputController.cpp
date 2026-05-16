#include <com/rdk/hal/compositeinput/ICompositeInputController.h>
#include <com/rdk/hal/compositeinput/BpCompositeInputController.h>
namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(CompositeInputController, "com.rdk.hal.compositeinput.ICompositeInputController")
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/compositeinput/BpCompositeInputController.h>
#include <com/rdk/hal/compositeinput/BnCompositeInputController.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {

BpCompositeInputController::BpCompositeInputController(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<ICompositeInputController>(_aidl_impl){
}

::android::binder::Status BpCompositeInputController::start() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCompositeInputController::TRANSACTION_start, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICompositeInputController::getDefaultImpl())) {
     return ICompositeInputController::getDefaultImpl()->start();
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
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpCompositeInputController::stop() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCompositeInputController::TRANSACTION_stop, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICompositeInputController::getDefaultImpl())) {
     return ICompositeInputController::getDefaultImpl()->stop();
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
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpCompositeInputController::setProperty(::com::rdk::hal::compositeinput::PortProperty property, const ::com::rdk::hal::PropertyValue& value) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(property));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(value);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCompositeInputController::TRANSACTION_setProperty, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICompositeInputController::getDefaultImpl())) {
     return ICompositeInputController::getDefaultImpl()->setProperty(property, value);
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
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpCompositeInputController::setPropertyMulti(const ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair>& properties) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelableVector(properties);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCompositeInputController::TRANSACTION_setPropertyMulti, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICompositeInputController::getDefaultImpl())) {
     return ICompositeInputController::getDefaultImpl()->setPropertyMulti(properties);
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
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpCompositeInputController::resetMetrics() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCompositeInputController::TRANSACTION_resetMetrics, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICompositeInputController::getDefaultImpl())) {
     return ICompositeInputController::getDefaultImpl()->resetMetrics();
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
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpCompositeInputController::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnCompositeInputController::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpCompositeInputController::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnCompositeInputController::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/compositeinput/BnCompositeInputController.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace compositeinput {

BnCompositeInputController::BnCompositeInputController()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnCompositeInputController::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnCompositeInputController::TRANSACTION_start:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(start());
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCompositeInputController::TRANSACTION_stop:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(stop());
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCompositeInputController::TRANSACTION_setProperty:
  {
    ::com::rdk::hal::compositeinput::PortProperty in_property;
    ::com::rdk::hal::PropertyValue in_value;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_property));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_value);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(setProperty(in_property, in_value));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCompositeInputController::TRANSACTION_setPropertyMulti:
  {
    ::std::vector<::com::rdk::hal::compositeinput::PropertyKVPair> in_properties;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelableVector(&in_properties);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(setPropertyMulti(in_properties));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCompositeInputController::TRANSACTION_resetMetrics:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(resetMetrics());
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCompositeInputController::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(ICompositeInputController::VERSION);
  }
  break;
  case BnCompositeInputController::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(ICompositeInputController::HASH);
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

int32_t BnCompositeInputController::getInterfaceVersion() {
  return ICompositeInputController::VERSION;
}
std::string BnCompositeInputController::getInterfaceHash() {
  return ICompositeInputController::HASH;
}
}  // namespace compositeinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
