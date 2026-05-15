#include <com/rdk/hal/hdmioutput/IHDMIOutputControllerListener.h>
#include <com/rdk/hal/hdmioutput/BpHDMIOutputControllerListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(HDMIOutputControllerListener, "com.rdk.hal.hdmioutput.IHDMIOutputControllerListener")
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/hdmioutput/BpHDMIOutputControllerListener.h>
#include <com/rdk/hal/hdmioutput/BnHDMIOutputControllerListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {

BpHDMIOutputControllerListener::BpHDMIOutputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IHDMIOutputControllerListener>(_aidl_impl){
}

::android::binder::Status BpHDMIOutputControllerListener::onHotPlugDetectStateChanged(bool state) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeBool(state);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_onHotPlugDetectStateChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIOutputControllerListener::getDefaultImpl())) {
     return IHDMIOutputControllerListener::getDefaultImpl()->onHotPlugDetectStateChanged(state);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpHDMIOutputControllerListener::onFrameRateChanged() {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_onFrameRateChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIOutputControllerListener::getDefaultImpl())) {
     return IHDMIOutputControllerListener::getDefaultImpl()->onFrameRateChanged();
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpHDMIOutputControllerListener::onHDCPStatusChanged(::com::rdk::hal::hdmioutput::HDCPStatus hdcpStatus, ::com::rdk::hal::hdmioutput::HDCPProtocolVersion hdcpProtocolVersion) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(hdcpStatus));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(hdcpProtocolVersion));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_onHDCPStatusChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIOutputControllerListener::getDefaultImpl())) {
     return IHDMIOutputControllerListener::getDefaultImpl()->onHDCPStatusChanged(hdcpStatus, hdcpProtocolVersion);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpHDMIOutputControllerListener::onEDID(const ::std::vector<uint8_t>& edid) {
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
  _aidl_ret_status = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_onEDID, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IHDMIOutputControllerListener::getDefaultImpl())) {
     return IHDMIOutputControllerListener::getDefaultImpl()->onEDID(edid);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpHDMIOutputControllerListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpHDMIOutputControllerListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnHDMIOutputControllerListener::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/hdmioutput/BnHDMIOutputControllerListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {

BnHDMIOutputControllerListener::BnHDMIOutputControllerListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnHDMIOutputControllerListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnHDMIOutputControllerListener::TRANSACTION_onHotPlugDetectStateChanged:
  {
    bool in_state;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readBool(&in_state);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onHotPlugDetectStateChanged(in_state));
  }
  break;
  case BnHDMIOutputControllerListener::TRANSACTION_onFrameRateChanged:
  {
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(onFrameRateChanged());
  }
  break;
  case BnHDMIOutputControllerListener::TRANSACTION_onHDCPStatusChanged:
  {
    ::com::rdk::hal::hdmioutput::HDCPStatus in_hdcpStatus;
    ::com::rdk::hal::hdmioutput::HDCPProtocolVersion in_hdcpProtocolVersion;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_hdcpStatus));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_hdcpProtocolVersion));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onHDCPStatusChanged(in_hdcpStatus, in_hdcpProtocolVersion));
  }
  break;
  case BnHDMIOutputControllerListener::TRANSACTION_onEDID:
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
    ::android::binder::Status _aidl_status(onEDID(in_edid));
  }
  break;
  case BnHDMIOutputControllerListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IHDMIOutputControllerListener::VERSION);
  }
  break;
  case BnHDMIOutputControllerListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IHDMIOutputControllerListener::HASH);
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

int32_t BnHDMIOutputControllerListener::getInterfaceVersion() {
  return IHDMIOutputControllerListener::VERSION;
}
std::string BnHDMIOutputControllerListener::getInterfaceHash() {
  return IHDMIOutputControllerListener::HASH;
}
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
