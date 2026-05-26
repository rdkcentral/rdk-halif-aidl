#include <com/rdk/hal/audiodecoder/IAudioDecoderManager.h>
#include <com/rdk/hal/audiodecoder/BpAudioDecoderManager.h>
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(AudioDecoderManager, "com.rdk.hal.audiodecoder.IAudioDecoderManager")
const ::std::string& IAudioDecoderManager::serviceName() {
  static const ::std::string value("audiodecodermanager");
  return value;
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/audiodecoder/BpAudioDecoderManager.h>
#include <com/rdk/hal/audiodecoder/BnAudioDecoderManager.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {

BpAudioDecoderManager::BpAudioDecoderManager(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IAudioDecoderManager>(_aidl_impl){
}

::android::binder::Status BpAudioDecoderManager::getAudioDecoderIds(::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id>* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnAudioDecoderManager::TRANSACTION_getAudioDecoderIds, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IAudioDecoderManager::getDefaultImpl())) {
     return IAudioDecoderManager::getDefaultImpl()->getAudioDecoderIds(_aidl_return);
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
  _aidl_ret_status = _aidl_reply.readParcelableVector(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

::android::binder::Status BpAudioDecoderManager::getAudioDecoder(const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& decoderResourceId, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoder>* _aidl_return) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeParcelable(decoderResourceId);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnAudioDecoderManager::TRANSACTION_getAudioDecoder, _aidl_data, &_aidl_reply, 0);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IAudioDecoderManager::getDefaultImpl())) {
     return IAudioDecoderManager::getDefaultImpl()->getAudioDecoder(decoderResourceId, _aidl_return);
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
  _aidl_ret_status = _aidl_reply.readNullableStrongBinder(_aidl_return);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpAudioDecoderManager::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnAudioDecoderManager::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpAudioDecoderManager::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnAudioDecoderManager::TRANSACTION_getInterfaceHash, data, &reply);
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

}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/audiodecoder/BnAudioDecoderManager.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {

BnAudioDecoderManager::BnAudioDecoderManager()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnAudioDecoderManager::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnAudioDecoderManager::TRANSACTION_getAudioDecoderIds:
  {
    ::std::vector<::com::rdk::hal::audiodecoder::IAudioDecoder::Id> _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    ::android::binder::Status _aidl_status(getAudioDecoderIds(&_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeParcelableVector(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnAudioDecoderManager::TRANSACTION_getAudioDecoder:
  {
    ::com::rdk::hal::audiodecoder::IAudioDecoder::Id in_decoderResourceId;
    ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoder> _aidl_return;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_decoderResourceId);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(getAudioDecoder(in_decoderResourceId, &_aidl_return));
    _aidl_ret_status = _aidl_status.writeToParcel(_aidl_reply);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (!_aidl_status.isOk()) {
      break;
    }
    _aidl_ret_status = _aidl_reply->writeStrongBinder(_aidl_return);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
  }
  break;
  case BnAudioDecoderManager::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IAudioDecoderManager::VERSION);
  }
  break;
  case BnAudioDecoderManager::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IAudioDecoderManager::HASH);
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

int32_t BnAudioDecoderManager::getInterfaceVersion() {
  return IAudioDecoderManager::VERSION;
}
std::string BnAudioDecoderManager::getInterfaceHash() {
  return IAudioDecoderManager::HASH;
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
