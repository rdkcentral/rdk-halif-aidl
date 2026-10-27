#include <com/rdk/hal/broadcast/IBroadcastClientToken.h>
#include <com/rdk/hal/broadcast/BpBroadcastClientToken.h>
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(BroadcastClientToken, "com.rdk.hal.broadcast.IBroadcastClientToken")
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/broadcast/BpBroadcastClientToken.h>
#include <com/rdk/hal/broadcast/BnBroadcastClientToken.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {

BpBroadcastClientToken::BpBroadcastClientToken(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IBroadcastClientToken>(_aidl_impl){
}

::android::binder::Status BpBroadcastClientToken::getWhoAmI(::std::string* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnBroadcastClientToken::TRANSACTION_getWhoAmI, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IBroadcastClientToken::getDefaultImpl())) {
     return IBroadcastClientToken::getDefaultImpl()->getWhoAmI(_aidl_return);
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
  _aidl_ret_status = _aidl_reply.readUtf8FromUtf16(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpBroadcastClientToken::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnBroadcastClientToken::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpBroadcastClientToken::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnBroadcastClientToken::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/broadcast/BnBroadcastClientToken.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {

BnBroadcastClientToken::BnBroadcastClientToken()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnBroadcastClientToken::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnBroadcastClientToken::TRANSACTION_getWhoAmI:
  {
    ::std::string _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(getWhoAmI(&_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeUtf8AsUtf16(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnBroadcastClientToken::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IBroadcastClientToken::VERSION);
  }
  break;
  case BnBroadcastClientToken::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IBroadcastClientToken::HASH);
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

int32_t BnBroadcastClientToken::getInterfaceVersion() {
  return IBroadcastClientToken::VERSION;
}
std::string BnBroadcastClientToken::getInterfaceHash() {
  return IBroadcastClientToken::HASH;
}
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
