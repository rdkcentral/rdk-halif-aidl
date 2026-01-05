#include <mutex>
#include <com/rdk/hal/planecontrol/IPlaneControlListener.h>
#include <com/rdk/hal/planecontrol/BpPlaneControlListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(PlaneControlListener, "com.rdk.hal.planecontrol.IPlaneControlListener")
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/planecontrol/BpPlaneControlListener.h>
#include <com/rdk/hal/planecontrol/BnPlaneControlListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {

BpPlaneControlListener::BpPlaneControlListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IPlaneControlListener>(_aidl_impl){
}

int32_t BpPlaneControlListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnPlaneControlListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpPlaneControlListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnPlaneControlListener::TRANSACTION_getInterfaceHash, data, &reply);
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
#include <com/rdk/hal/planecontrol/BnPlaneControlListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {

BnPlaneControlListener::BnPlaneControlListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnPlaneControlListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnPlaneControlListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IPlaneControlListener::VERSION);
  }
  break;
  case BnPlaneControlListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IPlaneControlListener::HASH);
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

int32_t BnPlaneControlListener::getInterfaceVersion() {
  return IPlaneControlListener::VERSION;
}
std::string BnPlaneControlListener::getInterfaceHash() {
  return IPlaneControlListener::HASH;
}
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
