#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/demux/BpDemuxDataProvider.h>
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(DemuxDataProvider, "com.rdk.hal.broadcast.demux.IDemuxDataProvider")
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/broadcast/demux/BpDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/demux/BnDemuxDataProvider.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {

BpDemuxDataProvider::BpDemuxDataProvider(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IDemuxDataProvider>(_aidl_impl){
}

int32_t BpDemuxDataProvider::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnDemuxDataProvider::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpDemuxDataProvider::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnDemuxDataProvider::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/broadcast/demux/BnDemuxDataProvider.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {

BnDemuxDataProvider::BnDemuxDataProvider()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnDemuxDataProvider::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnDemuxDataProvider::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IDemuxDataProvider::VERSION);
  }
  break;
  case BnDemuxDataProvider::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IDemuxDataProvider::HASH);
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

int32_t BnDemuxDataProvider::getInterfaceVersion() {
  return IDemuxDataProvider::VERSION;
}
std::string BnDemuxDataProvider::getInterfaceHash() {
  return IDemuxDataProvider::HASH;
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
