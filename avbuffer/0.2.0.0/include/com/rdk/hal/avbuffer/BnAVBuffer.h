#pragma once

#include <binder/IInterface.h>
#include <com/rdk/hal/avbuffer/IAVBuffer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
class BnAVBuffer : public ::android::BnInterface<IAVBuffer> {
public:
  static constexpr uint32_t TRANSACTION_getHeapMetrics = ::android::IBinder::FIRST_CALL_TRANSACTION + 0;
  static constexpr uint32_t TRANSACTION_createVideoPool = ::android::IBinder::FIRST_CALL_TRANSACTION + 1;
  static constexpr uint32_t TRANSACTION_createAudioPool = ::android::IBinder::FIRST_CALL_TRANSACTION + 2;
  static constexpr uint32_t TRANSACTION_destroyPool = ::android::IBinder::FIRST_CALL_TRANSACTION + 3;
  static constexpr uint32_t TRANSACTION_getPoolMetrics = ::android::IBinder::FIRST_CALL_TRANSACTION + 4;
  static constexpr uint32_t TRANSACTION_getAllPoolMetrics = ::android::IBinder::FIRST_CALL_TRANSACTION + 5;
  static constexpr uint32_t TRANSACTION_alloc = ::android::IBinder::FIRST_CALL_TRANSACTION + 6;
  static constexpr uint32_t TRANSACTION_notifyWhenSpaceAvailable = ::android::IBinder::FIRST_CALL_TRANSACTION + 7;
  static constexpr uint32_t TRANSACTION_trimSize = ::android::IBinder::FIRST_CALL_TRANSACTION + 8;
  static constexpr uint32_t TRANSACTION_free = ::android::IBinder::FIRST_CALL_TRANSACTION + 9;
  static constexpr uint32_t TRANSACTION_isValid = ::android::IBinder::FIRST_CALL_TRANSACTION + 10;
  static constexpr uint32_t TRANSACTION_getAllocList = ::android::IBinder::FIRST_CALL_TRANSACTION + 11;
  static constexpr uint32_t TRANSACTION_calculateSHA1 = ::android::IBinder::FIRST_CALL_TRANSACTION + 12;
  static constexpr uint32_t TRANSACTION_getInterfaceVersion = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777214;
  static constexpr uint32_t TRANSACTION_getInterfaceHash = ::android::IBinder::FIRST_CALL_TRANSACTION + 16777213;
  explicit BnAVBuffer();
  ::android::status_t onTransact(uint32_t _aidl_code, const ::android::Parcel& _aidl_data, ::android::Parcel* _aidl_reply, uint32_t _aidl_flags) override;
  int32_t getInterfaceVersion();
  std::string getInterfaceHash();
};  // class BnAVBuffer

class IAVBufferDelegator : public BnAVBuffer {
public:
  explicit IAVBufferDelegator(::android::sp<IAVBuffer> &impl) : _aidl_delegate(impl) {}

  ::android::binder::Status getHeapMetrics(bool secureHeap, ::com::rdk::hal::avbuffer::HeapMetrics* _aidl_return) override {
    return _aidl_delegate->getHeapMetrics(secureHeap, _aidl_return);
  }
  ::android::binder::Status createVideoPool(bool secureHeap, const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) override {
    return _aidl_delegate->createVideoPool(secureHeap, videoDecoderId, listener, _aidl_return);
  }
  ::android::binder::Status createAudioPool(bool secureHeap, const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) override {
    return _aidl_delegate->createAudioPool(secureHeap, audioDecoderId, listener, _aidl_return);
  }
  ::android::binder::Status destroyPool(const ::com::rdk::hal::avbuffer::Pool& poolHandle, bool* _aidl_return) override {
    return _aidl_delegate->destroyPool(poolHandle, _aidl_return);
  }
  ::android::binder::Status getPoolMetrics(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::com::rdk::hal::avbuffer::PoolMetrics* _aidl_return) override {
    return _aidl_delegate->getPoolMetrics(poolHandle, _aidl_return);
  }
  ::android::binder::Status getAllPoolMetrics(bool secureHeap, ::std::vector<::com::rdk::hal::avbuffer::PoolMetrics>* _aidl_return) override {
    return _aidl_delegate->getAllPoolMetrics(secureHeap, _aidl_return);
  }
  ::android::binder::Status alloc(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, int64_t* _aidl_return) override {
    return _aidl_delegate->alloc(poolHandle, size, _aidl_return);
  }
  ::android::binder::Status notifyWhenSpaceAvailable(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, bool* _aidl_return) override {
    return _aidl_delegate->notifyWhenSpaceAvailable(poolHandle, size, _aidl_return);
  }
  ::android::binder::Status trimSize(int64_t bufferHandle, int32_t newSize, bool* _aidl_return) override {
    return _aidl_delegate->trimSize(bufferHandle, newSize, _aidl_return);
  }
  ::android::binder::Status free(int64_t bufferHandle, bool* _aidl_return) override {
    return _aidl_delegate->free(bufferHandle, _aidl_return);
  }
  ::android::binder::Status isValid(int64_t bufferHandle, bool* _aidl_return) override {
    return _aidl_delegate->isValid(bufferHandle, _aidl_return);
  }
  ::android::binder::Status getAllocList(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::std::vector<int64_t>* _aidl_return) override {
    return _aidl_delegate->getAllocList(poolHandle, _aidl_return);
  }
  ::android::binder::Status calculateSHA1(int64_t bufferHandle, ::std::vector<uint8_t>* _aidl_return) override {
    return _aidl_delegate->calculateSHA1(bufferHandle, _aidl_return);
  }
  int32_t getInterfaceVersion() override {
    int32_t _delegator_ver = BnAVBuffer::getInterfaceVersion();
    int32_t _impl_ver = _aidl_delegate->getInterfaceVersion();
    return _delegator_ver < _impl_ver ? _delegator_ver : _impl_ver;
  }
  std::string getInterfaceHash() override {
    return _aidl_delegate->getInterfaceHash();
  }
private:
  ::android::sp<IAVBuffer> _aidl_delegate;
};  // class IAVBufferDelegator
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
