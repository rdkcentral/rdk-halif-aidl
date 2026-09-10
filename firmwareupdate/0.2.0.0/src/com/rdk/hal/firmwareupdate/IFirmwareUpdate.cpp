#include <com/rdk/hal/firmwareupdate/IFirmwareUpdate.h>
#include <com/rdk/hal/firmwareupdate/BpFirmwareUpdate.h>
namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(FirmwareUpdate, "com.rdk.hal.firmwareupdate.IFirmwareUpdate")
const ::std::string& IFirmwareUpdate::serviceName() {
  static const ::std::string value("firmwareupdate");
  return value;
}
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/firmwareupdate/BpFirmwareUpdate.h>
#include <com/rdk/hal/firmwareupdate/BnFirmwareUpdate.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {

BpFirmwareUpdate::BpFirmwareUpdate(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IFirmwareUpdate>(_aidl_impl){
}

::android::binder::Status BpFirmwareUpdate::updateFirmwareFromFile(const ::std::string& filename, const ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener>& listener, bool* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeUtf8AsUtf16(filename);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeStrongBinder(listener);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnFirmwareUpdate::TRANSACTION_updateFirmwareFromFile, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IFirmwareUpdate::getDefaultImpl())) {
     return IFirmwareUpdate::getDefaultImpl()->updateFirmwareFromFile(filename, listener, _aidl_return);
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
  _aidl_ret_status = _aidl_reply.readBool(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpFirmwareUpdate::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnFirmwareUpdate::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpFirmwareUpdate::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnFirmwareUpdate::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/firmwareupdate/BnFirmwareUpdate.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace firmwareupdate {

BnFirmwareUpdate::BnFirmwareUpdate()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnFirmwareUpdate::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnFirmwareUpdate::TRANSACTION_updateFirmwareFromFile:
  {
    ::std::string in_filename;
    ::android::sp<::com::rdk::hal::firmwareupdate::IFirmwareUpdateListener> in_listener;
    bool _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readUtf8FromUtf16(&in_filename);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readStrongBinder(&in_listener);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(updateFirmwareFromFile(in_filename, in_listener, &_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeBool(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnFirmwareUpdate::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IFirmwareUpdate::VERSION);
  }
  break;
  case BnFirmwareUpdate::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IFirmwareUpdate::HASH);
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

int32_t BnFirmwareUpdate::getInterfaceVersion() {
  return IFirmwareUpdate::VERSION;
}
std::string BnFirmwareUpdate::getInterfaceHash() {
  return IFirmwareUpdate::HASH;
}
}  // namespace firmwareupdate
}  // namespace hal
}  // namespace rdk
}  // namespace com
