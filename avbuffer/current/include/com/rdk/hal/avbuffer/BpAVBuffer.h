#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/avbuffer/IAVBuffer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
class BpAVBuffer : public ::android::BpInterface<IAVBuffer> {
public:
  explicit BpAVBuffer(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpAVBuffer() = default;
  ::android::binder::Status getHeapMetrics(bool secureHeap, ::com::rdk::hal::avbuffer::HeapMetrics* _aidl_return) override;
  ::android::binder::Status createVideoPool(bool secureHeap, const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) override;
  ::android::binder::Status createAudioPool(bool secureHeap, const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) override;
  ::android::binder::Status destroyPool(const ::com::rdk::hal::avbuffer::Pool& poolHandle, bool* _aidl_return) override;
  ::android::binder::Status getPoolMetrics(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::com::rdk::hal::avbuffer::PoolMetrics* _aidl_return) override;
  ::android::binder::Status getAllPoolMetrics(bool secureHeap, ::std::vector<::com::rdk::hal::avbuffer::PoolMetrics>* _aidl_return) override;
  ::android::binder::Status alloc(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, int64_t* _aidl_return) override;
  ::android::binder::Status notifyWhenSpaceAvailable(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, bool* _aidl_return) override;
  ::android::binder::Status trimSize(int64_t bufferHandle, int32_t newSize, bool* _aidl_return) override;
  ::android::binder::Status free(int64_t bufferHandle, bool* _aidl_return) override;
  ::android::binder::Status isValid(int64_t bufferHandle, bool* _aidl_return) override;
  ::android::binder::Status getAllocList(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::std::vector<int64_t>* _aidl_return) override;
  ::android::binder::Status calculateSHA1(int64_t bufferHandle, ::std::vector<uint8_t>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpAVBuffer
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
