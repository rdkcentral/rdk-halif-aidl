#include <com/rdk/hal/panel/IPanelOutputControllerListener.h>
#include <com/rdk/hal/panel/BpPanelOutputControllerListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace panel {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(PanelOutputControllerListener, "com.rdk.hal.panel.IPanelOutputControllerListener")
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/panel/BpPanelOutputControllerListener.h>
#include <com/rdk/hal/panel/BnPanelOutputControllerListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {

BpPanelOutputControllerListener::BpPanelOutputControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IPanelOutputControllerListener>(_aidl_impl){
}

::android::binder::Status BpPanelOutputControllerListener::onPictureModeChanged(const ::android::String16& pictureMode) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeString16(pictureMode);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnPanelOutputControllerListener::TRANSACTION_onPictureModeChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IPanelOutputControllerListener::getDefaultImpl())) {
     return IPanelOutputControllerListener::getDefaultImpl()->onPictureModeChanged(pictureMode);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpPanelOutputControllerListener::onPQParameterChanged(const ::android::String16& pictureMode, const ::com::rdk::hal::panel::PanelSource& avSource, ::com::rdk::hal::videodecoder::DynamicRange dynamicRange, ::com::rdk::hal::panel::PQParameter pictureProperty, const ::com::rdk::hal::panel::PQParameterValue& picturePropertyValue) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeString16(pictureMode);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(avSource);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(dynamicRange));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(static_cast<int32_t>(pictureProperty));
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(picturePropertyValue);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnPanelOutputControllerListener::TRANSACTION_onPQParameterChanged, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IPanelOutputControllerListener::getDefaultImpl())) {
     return IPanelOutputControllerListener::getDefaultImpl()->onPQParameterChanged(pictureMode, avSource, dynamicRange, pictureProperty, picturePropertyValue);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpPanelOutputControllerListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnPanelOutputControllerListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpPanelOutputControllerListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnPanelOutputControllerListener::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/panel/BnPanelOutputControllerListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {

BnPanelOutputControllerListener::BnPanelOutputControllerListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnPanelOutputControllerListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnPanelOutputControllerListener::TRANSACTION_onPictureModeChanged:
  {
    ::android::String16 in_pictureMode;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readString16(&in_pictureMode);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onPictureModeChanged(in_pictureMode));
  }
  break;
  case BnPanelOutputControllerListener::TRANSACTION_onPQParameterChanged:
  {
    ::android::String16 in_pictureMode;
    ::com::rdk::hal::panel::PanelSource in_avSource;
    ::com::rdk::hal::videodecoder::DynamicRange in_dynamicRange;
    ::com::rdk::hal::panel::PQParameter in_pictureProperty;
    ::com::rdk::hal::panel::PQParameterValue in_picturePropertyValue;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readString16(&in_pictureMode);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_avSource);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_dynamicRange));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(reinterpret_cast<int32_t *>(&in_pictureProperty));
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_picturePropertyValue);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onPQParameterChanged(in_pictureMode, in_avSource, in_dynamicRange, in_pictureProperty, in_picturePropertyValue));
  }
  break;
  case BnPanelOutputControllerListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IPanelOutputControllerListener::VERSION);
  }
  break;
  case BnPanelOutputControllerListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IPanelOutputControllerListener::HASH);
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

int32_t BnPanelOutputControllerListener::getInterfaceVersion() {
  return IPanelOutputControllerListener::VERSION;
}
std::string BnPanelOutputControllerListener::getInterfaceHash() {
  return IPanelOutputControllerListener::HASH;
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
