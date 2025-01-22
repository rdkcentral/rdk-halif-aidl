#include <com/test/IFirmwareUpdateStateListener.h>
#include <com/test/BpFirmwareUpdateStateListener.h>
namespace com {
namespace test {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(FirmwareUpdateStateListener, "com.test.IFirmwareUpdateStateListener")
}  // namespace test
}  // namespace com
#include <com/test/BpFirmwareUpdateStateListener.h>
#include <com/test/BnFirmwareUpdateStateListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace test {

BpFirmwareUpdateStateListener::BpFirmwareUpdateStateListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IFirmwareUpdateStateListener>(_aidl_impl){
}

::android::binder::Status BpFirmwareUpdateStateListener::onFirmwareUpdateStateChanged(const ::com::test::FirmwareStatus& status) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(status);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnFirmwareUpdateStateListener::TRANSACTION_onFirmwareUpdateStateChanged, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IFirmwareUpdateStateListener::getDefaultImpl())) {
     return IFirmwareUpdateStateListener::getDefaultImpl()->onFirmwareUpdateStateChanged(status);
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

}  // namespace test
}  // namespace com
#include <com/test/BnFirmwareUpdateStateListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace test {

BnFirmwareUpdateStateListener::BnFirmwareUpdateStateListener()
{
  ::android::internal::Stability::markCompilationUnit(this);
}

::android::status_t BnFirmwareUpdateStateListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnFirmwareUpdateStateListener::TRANSACTION_onFirmwareUpdateStateChanged:
  {
    ::com::test::FirmwareStatus in_status;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_status);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    ::android::binder::Status _aidl_status(onFirmwareUpdateStateChanged(in_status));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
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

}  // namespace test
}  // namespace com
