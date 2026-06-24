#include <com/rdk/hal/planecontrol/IGraphicsFbProviderListener.h>
#include <com/rdk/hal/planecontrol/BpGraphicsFbProviderListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(GraphicsFbProviderListener, "com.rdk.hal.planecontrol.IGraphicsFbProviderListener")
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/planecontrol/BpGraphicsFbProviderListener.h>
#include <com/rdk/hal/planecontrol/BnGraphicsFbProviderListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {

BpGraphicsFbProviderListener::BpGraphicsFbProviderListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IGraphicsFbProviderListener>(_aidl_impl){
}

::android::binder::Status BpGraphicsFbProviderListener::onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t elapsedRealtimeNanos) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt32(oldGraphicsFbId);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt64(elapsedRealtimeNanos);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnGraphicsFbProviderListener::TRANSACTION_onGraphicsFbReleased, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IGraphicsFbProviderListener::getDefaultImpl())) {
     return IGraphicsFbProviderListener::getDefaultImpl()->onGraphicsFbReleased(oldGraphicsFbId, elapsedRealtimeNanos);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpGraphicsFbProviderListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnGraphicsFbProviderListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpGraphicsFbProviderListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnGraphicsFbProviderListener::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/planecontrol/BnGraphicsFbProviderListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {

BnGraphicsFbProviderListener::BnGraphicsFbProviderListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnGraphicsFbProviderListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnGraphicsFbProviderListener::TRANSACTION_onGraphicsFbReleased:
  {
    int32_t in_oldGraphicsFbId;
    int64_t in_elapsedRealtimeNanos;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt32(&in_oldGraphicsFbId);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt64(&in_elapsedRealtimeNanos);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onGraphicsFbReleased(in_oldGraphicsFbId, in_elapsedRealtimeNanos));
  }
  break;
  case BnGraphicsFbProviderListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IGraphicsFbProviderListener::VERSION);
  }
  break;
  case BnGraphicsFbProviderListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IGraphicsFbProviderListener::HASH);
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

int32_t BnGraphicsFbProviderListener::getInterfaceVersion() {
  return IGraphicsFbProviderListener::VERSION;
}
std::string BnGraphicsFbProviderListener::getInterfaceHash() {
  return IGraphicsFbProviderListener::HASH;
}
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
