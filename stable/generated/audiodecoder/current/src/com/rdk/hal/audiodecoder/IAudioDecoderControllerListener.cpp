#include <com/rdk/hal/audiodecoder/IAudioDecoderControllerListener.h>
#include <com/rdk/hal/audiodecoder/BpAudioDecoderControllerListener.h>
namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
DO_NOT_DIRECTLY_USE_ME_IMPLEMENT_META_INTERFACE(AudioDecoderControllerListener, "com.rdk.hal.audiodecoder.IAudioDecoderControllerListener")
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
#include <com/rdk/hal/audiodecoder/BpAudioDecoderControllerListener.h>
#include <com/rdk/hal/audiodecoder/BnAudioDecoderControllerListener.h>
#include <binder/Parcel.h>
#include <android-base/macros.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {

BpAudioDecoderControllerListener::BpAudioDecoderControllerListener(const ::android::sp<::android::IBinder>& _aidl_impl)
    : BpInterface<IAudioDecoderControllerListener>(_aidl_impl){
}

::android::binder::Status BpAudioDecoderControllerListener::onFrameOutput(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& metadata) {
  ::android::Parcel _aidl_data;
  _aidl_data.markForBinder(remoteStrong());
  ::android::Parcel _aidl_reply;
  ::android::status_t _aidl_ret_status = ::android::OK;
  ::android::binder::Status _aidl_status;
  _aidl_ret_status = _aidl_data.writeInterfaceToken(getInterfaceDescriptor());
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt64(nsPresentationTime);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeInt64(frameBufferHandle);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = _aidl_data.writeNullableParcelable(metadata);
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_ret_status = remote()->transact(BnAudioDecoderControllerListener::TRANSACTION_onFrameOutput, _aidl_data, &_aidl_reply, ::android::IBinder::FLAG_ONEWAY);
  if (UNLIKELY(_aidl_ret_status == ::android::UNKNOWN_TRANSACTION && IAudioDecoderControllerListener::getDefaultImpl())) {
     return IAudioDecoderControllerListener::getDefaultImpl()->onFrameOutput(nsPresentationTime, frameBufferHandle, metadata);
  }
  if (((_aidl_ret_status) != (::android::OK))) {
    goto _aidl_error;
  }
  _aidl_error:
  _aidl_status.setFromStatusT(_aidl_ret_status);
  return _aidl_status;
}

int32_t BpAudioDecoderControllerListener::getInterfaceVersion() {
  if (cached_version_ == -1) {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnAudioDecoderControllerListener::TRANSACTION_getInterfaceVersion, data, &reply);
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


std::string BpAudioDecoderControllerListener::getInterfaceHash() {
  std::lock_guard<std::mutex> lockGuard(cached_hash_mutex_);
  if (cached_hash_ == "-1") {
    ::android::Parcel data;
    ::android::Parcel reply;
    data.writeInterfaceToken(getInterfaceDescriptor());
    ::android::status_t err = remote()->transact(BnAudioDecoderControllerListener::TRANSACTION_getInterfaceHash, data, &reply);
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
#include <com/rdk/hal/audiodecoder/BnAudioDecoderControllerListener.h>
#include <binder/Parcel.h>
#include <binder/Stability.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {

BnAudioDecoderControllerListener::BnAudioDecoderControllerListener()
{
  ::android::internal::Stability::markVintf(this);
}

::android::status_t BnAudioDecoderControllerListener::onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) {
  ::android::status_t _aidl_ret_status = ::android::OK;
  switch (_aidl_code) {
  case BnAudioDecoderControllerListener::TRANSACTION_onFrameOutput:
  {
    int64_t in_nsPresentationTime;
    int64_t in_frameBufferHandle;
    ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata> in_metadata;
    if (!(_aidl_data.checkInterface(this))) {
      _aidl_ret_status = ::android::BAD_TYPE;
      break;
    }
    _aidl_ret_status = _aidl_data.readInt64(&in_nsPresentationTime);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readInt64(&in_frameBufferHandle);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    _aidl_ret_status = _aidl_data.readParcelable(&in_metadata);
    if (((_aidl_ret_status) != (::android::OK))) {
      break;
    }
    if (auto st = _aidl_data.enforceNoDataAvail(); !st.isOk()) {
      _aidl_ret_status = st.writeToParcel(_aidl_reply);
      break;
    }
    ::android::binder::Status _aidl_status(onFrameOutput(in_nsPresentationTime, in_frameBufferHandle, in_metadata));
  }
  break;
  case BnAudioDecoderControllerListener::TRANSACTION_getInterfaceVersion:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeInt32(IAudioDecoderControllerListener::VERSION);
  }
  break;
  case BnAudioDecoderControllerListener::TRANSACTION_getInterfaceHash:
  {
    _aidl_data.checkInterface(this);
    _aidl_reply->writeNoException();
    _aidl_reply->writeUtf8AsUtf16(IAudioDecoderControllerListener::HASH);
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

int32_t BnAudioDecoderControllerListener::getInterfaceVersion() {
  return IAudioDecoderControllerListener::VERSION;
}
std::string BnAudioDecoderControllerListener::getInterfaceHash() {
  return IAudioDecoderControllerListener::HASH;
}
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
