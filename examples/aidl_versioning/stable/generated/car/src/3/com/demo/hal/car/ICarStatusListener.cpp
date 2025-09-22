#include <com/demo/hal/car/ICarStatusListener.h>
#include <com/demo/hal/car/BpCarStatusListener.h>
namespace com {
namespace demo {
namespace hal {
namespace car {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(CarStatusListener, "com.demo.hal.car.ICarStatusListener")
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
#include <com/demo/hal/car/BpCarStatusListener.h>
#include <com/demo/hal/car/BnCarStatusListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace demo {
namespace hal {
namespace car {

BpCarStatusListener::BpCarStatusListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<ICarStatusListener>(_aidl_impl){
}

::android::binder::Status BpCarStatusListener::onCarStatusChanged(const ::com::demo::hal::car::CarStatus& newStatus) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(newStatus);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnCarStatusListener::TRANSACTION_onCarStatusChanged, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && ICarStatusListener::getDefaultImpl())) {
     return ICarStatusListener::getDefaultImpl()->onCarStatusChanged(newStatus);
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

int32_t BpCarStatusListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnCarStatusListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpCarStatusListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnCarStatusListener::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
#include <com/demo/hal/car/BnCarStatusListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace demo {
namespace hal {
namespace car {

BnCarStatusListener::BnCarStatusListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnCarStatusListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnCarStatusListener::TRANSACTION_onCarStatusChanged:
  {
    ::com::demo::hal::car::CarStatus in_newStatus;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_newStatus);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onCarStatusChanged(in_newStatus));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
  }
  break;
  case BnCarStatusListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(ICarStatusListener::VERSION);
  }
  break;
  case BnCarStatusListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(ICarStatusListener::HASH);
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

int32_t BnCarStatusListener::getInterfaceVersion() {
  return ICarStatusListener::VERSION;
}
std::string BnCarStatusListener::getInterfaceHash() {
  return ICarStatusListener::HASH;
}
}  // namespace car
}  // namespace hal
}  // namespace demo
}  // namespace com
