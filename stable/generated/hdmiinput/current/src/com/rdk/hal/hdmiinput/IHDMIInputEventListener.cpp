#include <com/rdk/hal/hdmiinput/IHDMIInputEventListener.h>
#include <com/rdk/hal/hdmiinput/BpHDMIInputEventListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(HDMIInputEventListener, "com.rdk.hal.hdmiinput.IHDMIInputEventListener")
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/hdmiinput/BpHDMIInputEventListener.h>
#include <com/rdk/hal/hdmiinput/BnHDMIInputEventListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {

BpHDMIInputEventListener::BpHDMIInputEventListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IHDMIInputEventListener>(_aidl_impl){
}

::android::binder::Status BpHDMIInputEventListener::onStateChanged(::com::rdk::hal::hdmiinput::State oldState, ::com::rdk::hal::hdmiinput::State newState) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(oldState));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(newState));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnHDMIInputEventListener::TRANSACTION_onStateChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIInputEventListener::getDefaultImpl())) {
     return IHDMIInputEventListener::getDefaultImpl()->onStateChanged(oldState, newState);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpHDMIInputEventListener::onEDIDChange(const ::std::vector<uint8_t>& edid) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeByteVector(edid);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnHDMIInputEventListener::TRANSACTION_onEDIDChange, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIInputEventListener::getDefaultImpl())) {
     return IHDMIInputEventListener::getDefaultImpl()->onEDIDChange(edid);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpHDMIInputEventListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnHDMIInputEventListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpHDMIInputEventListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnHDMIInputEventListener::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/hdmiinput/BnHDMIInputEventListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {

BnHDMIInputEventListener::BnHDMIInputEventListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnHDMIInputEventListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnHDMIInputEventListener::TRANSACTION_onStateChanged:
  {
    ::com::rdk::hal::hdmiinput::State in_oldState;
    ::com::rdk::hal::hdmiinput::State in_newState;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_oldState));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_newState));
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
  case BnHDMIInputEventListener::TRANSACTION_onEDIDChange:
  {
    ::std::vector<uint8_t> in_edid;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readByteVector(&in_edid);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onEDIDChange(in_edid));
  }
  break;
  case BnHDMIInputEventListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IHDMIInputEventListener::VERSION);
  }
  break;
  case BnHDMIInputEventListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IHDMIInputEventListener::HASH);
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

int32_t BnHDMIInputEventListener::getInterfaceVersion() {
  return IHDMIInputEventListener::VERSION;
}
std::string BnHDMIInputEventListener::getInterfaceHash() {
  return IHDMIInputEventListener::HASH;
}
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
