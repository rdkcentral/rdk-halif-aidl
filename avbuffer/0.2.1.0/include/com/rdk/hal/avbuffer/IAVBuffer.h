#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoder.h>
#include <com/rdk/hal/avbuffer/HeapMetrics.h>
#include <com/rdk/hal/avbuffer/IAVBufferSpaceListener.h>
#include <com/rdk/hal/avbuffer/Pool.h>
#include <com/rdk/hal/avbuffer/PoolMetrics.h>
#include <com/rdk/hal/videodecoder/IVideoDecoder.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {
// @aidl-doc
/**
 *  @brief     AV buffer HAL interface definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IAVBuffer : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVBuffer)
  static const int32_t VERSION = 2010;
  const std::string HASH = "e23536cdc5897ca90beb1b091801b131dd54541e";
  static constexpr char* HASHVALUE = "e23536cdc5897ca90beb1b091801b131dd54541e";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the number of used/total bytes in a memory heap.
   *
   * @param[in] secureHeap        Specifies the secure heap when true or non-secure heap when false.
   *
   * @param[out] _aidl_return HeapMetrics
   *
   * @see createVideoPool(), createAudioPool(), destroyPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getHeapMetrics(bool secureHeap, ::com::rdk::hal::avbuffer::HeapMetrics* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Creates a video memory buffer pool of a secure or non-secure type from which allocations can be made.
   *
   * @note Pools are intended to be **long-lived**: create once per pipeline
   *       session (e.g. at decoder open), reuse the returned `Pool` handle
   *       for all `alloc()` / `free()` calls during that session, and call
   *       `destroyPool()` once at teardown. Calling `createVideoPool()` per
   *       decode operation is incorrect — see `HAL.AVBUF.10`.
   * @note The pool size is determined by the vendor implementation from the
   *       `videoDecoderId` — the API takes no size parameter and exposes no
   *       method to query the pool's capacity. Pool sizing, handle assignment,
   *       and internal memory management are vendor-specific behind the binder.
   * @note The returned `Pool` handle is an opaque token. Callers MUST NOT
   *       interpret or derive meaning from its value; comparison is limited
   *       to **equality only**. The vendor MAY reassign a destroyed handle's
   *       numeric value to a new pool, so callers MUST drop destroyed
   *       handles immediately.
   *
   * If the `videoDecoderId` is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
   *
   * If the platform has exhausted all available memory from the requested heap then the exception status
   * `binder::Status::Exception::EX_SERVICE_SPECIFIC` is returned (out-of-memory).
   *
   * If a `secureHeap` is created and the video decoder has not been configured then the exception status
   * `binder::Status::Exception::EX_ILLEGAL_STATE` is returned.
   *
   * @param[in] secureHeap            Indicates if the pool is secure.
   * @param[in] videoDecoderId        The id of the video decoder resource.
   * @param[in] listener              Listener for space available callbacks.
   *
   * @param[out] _aidl_return A new `Pool` object with a valid handle, intended for the full lifetime of the pipeline session.
   *
   * @pre The IVideoDecoder.Id must have been obtained from IVideoDecoderManager.getVideoDecoderIds()
   *
   * @see destroyPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if videoDecoderId is invalid
   * @retval ::android::binder::Status::EX_SERVICE_SPECIFIC if heap is exhausted (out-of-memory)
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE decoder not configured
   */
  virtual ::android::binder::Status createVideoPool(bool secureHeap, const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Creates an audio memory buffer pool of a secure or non-secure type from which allocations can be made.
   *
   * @note Pools are intended to be **long-lived**: create once per pipeline
   *       session (e.g. at decoder open), reuse the returned `Pool` handle
   *       for all `alloc()` / `free()` calls during that session, and call
   *       `destroyPool()` once at teardown. Calling `createAudioPool()` per
   *       decode operation is incorrect — see `HAL.AVBUF.10`.
   * @note The pool size is determined by the vendor implementation from the
   *       `audioDecoderId` — the API takes no size parameter and exposes no
   *       method to query the pool's capacity. Pool sizing, handle assignment,
   *       and internal memory management are vendor-specific behind the binder.
   * @note The returned `Pool` handle is an opaque token. Callers MUST NOT
   *       interpret or derive meaning from its value; comparison is limited
   *       to **equality only**. The vendor MAY reassign a destroyed handle's
   *       numeric value to a new pool, so callers MUST drop destroyed
   *       handles immediately.
   *
   * If the audio pool is for audio data not destined for a vendor audio decoder
   * (e.g. system audio PCM) then the ID must be IAudioDecoder.Id.UNDEFINED.
   *
   * If the platform has exhausted all available memory from the requested heap then the exception status
   * `binder::Status::Exception::EX_SERVICE_SPECIFIC` is returned (out-of-memory).
   *
   * If a `secureHeap` is created and the audio decoder has not been configured then the exception status
   * `binder::Status::Exception::EX_ILLEGAL_STATE` is returned.
   *
   * If the `audioDecoderId` is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
   *
   * @param[in] secureHeap            Indicates if the pool is secure.
   * @param[in] audioDecoderId        The ID of the audio decoder resource.
   * @param[in] listener              Listener for space available callbacks.
   *
   * @param[out] _aidl_return A new `Pool` object with a valid handle, intended for the full lifetime of the pipeline session.
   *
   * @pre The IAudioDecoder.Id must have been obtained from IAudioDecoderManager.getAudioDecoderIds()
   *      or IAudioDecoder.Id.UNDEFINED must be used.
   *
   * @see destroyPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if audioDecoderId is invalid
   * @retval ::android::binder::Status::EX_SERVICE_SPECIFIC if heap is exhausted (out-of-memory)
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE decoder not configured
   */
  virtual ::android::binder::Status createAudioPool(bool secureHeap, const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& audioDecoderId, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& listener, ::com::rdk::hal::avbuffer::Pool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Destroys a memory buffer pool previously created with createVideoPool() or createAudioPool().
   *
   * The AV buffer pool must be empty, with all previously allocated buffers from the pool freed.
   * If any buffer allocations are outstanding then the exception status
   * `binder::Status::Exception::EX_SERVICE_SPECIFIC` (pool-not-empty) is returned.
   *
   * @param[in] poolHandle      Pool handle.
   *
   * @param[out] _aidl_return boolean
   *   - true: The pool handle is valid.
   *   - false: The pool handle is invalid.
   * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
   * @pre The pool must have all allocations freed.
   *
   * @see createVideoPool(), createAudioPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_SERVICE_SPECIFIC if outstanding allocations remain (pool-not-empty)
   */
  virtual ::android::binder::Status destroyPool(const ::com::rdk::hal::avbuffer::Pool& poolHandle, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the number of used/total bytes in a memory pool.
   *
   * If the pool handle is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
   *
   * @param[in] poolHandle        Pool handle.
   *
   * @param[out] _aidl_return PoolMetrics
   *
   * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
   *
   * @see alloc(), free(), createVideoPool(), createAudioPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT
   */
  virtual ::android::binder::Status getPoolMetrics(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::com::rdk::hal::avbuffer::PoolMetrics* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the list of all pools metrics in a specified heap.
   *
   * @param[in] secureHeap    Specifies the heap type - true is secure, false is non-secure.
   *
   * @param[out] _aidl_return PoolMetrics[] array is sized to cover all created pools.
   *
   * @see alloc(), free(), createVideoPool(), createAudioPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAllPoolMetrics(bool secureHeap, ::std::vector<::com::rdk::hal::avbuffer::PoolMetrics>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Allocates a memory buffer from a given buffer pool.
   *
   * The allocation will be satisfied immediately or fail if a memory buffer of the given size is not available.
   * On success, a valid handle is returned that must eventually be used in a call to `free()` to release the memory
   * block.
   *
   * If the allocation fails due to an out of memory condition then `binder::Status::Exception::EX_SERVICE_SPECIFIC`
   * (out-of-memory) is returned and the client can call `notifyWhenSpaceAvailable()` to be notified when space
   * becomes available.
   *
   * @param[in] poolHandle    Pool handle.
   * @param[in] size          Size of the memory block allocation in bytes. Must be > 0.
   *
   * @param[out] _aidl_return long            The handle of the new buffer allocation.
   *
   * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
   *
   * @see free(), createVideoPool(), createAudioPool(), notifyWhenSpaceAvailable()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if pool handle is invalid or size is invalid
   * @retval ::android::binder::Status::EX_SERVICE_SPECIFIC if allocation fails (out-of-memory)
   */
  virtual ::android::binder::Status alloc(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, int64_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Requests notification when enough space in a pool becomes available for an allocation of `size` bytes.
   *
   * This function is usually called after a call to `alloc()` has failed with an out of memory condition.
   * The notification callback occurs on the `IAVBufferSpaceListener` passed in by the client when the pool was
   * created.
   *
   * @param[in] poolHandle    Pool handle.
   * @param[in] size          Size of the memory block in bytes. Must be > 0 and <= the pool size.
   *
   * @param[out] _aidl_return boolean
   *   - true: The notification request was successful and a callback will follow.
   *   - false: Invalid pool handle or size.
   * @pre A Pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
   *
   * @see IAVBufferSpaceListener.onSpaceAvailable()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status notifyWhenSpaceAvailable(const ::com::rdk::hal::avbuffer::Pool& poolHandle, int32_t size, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Trims the size of the last alloc() block from a pool to a smaller size.
   *
   * If the buffer handle passed is not the last allocated from a pool then `binder::Status EX_ILLEGAL_STATE` is
   * returned.
   *
   * @param[in] bufferHandle  Memory buffer handle.
   * @param[in] newSize       New size of the memory block in bytes.  Must be > 0 and <= original size.
   *
   * @param[out] _aidl_return boolean
   *   - true: The trim was successful.
   *   - false: The bufferHandle or newSize was invalid.
   * @pre The `bufferHandle` must be the last one returned from a call to `alloc()`.
   *
   * @see alloc()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if buffer is not the last allocated from the pool
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if bufferHandle or newSize is invalid
   */
  virtual ::android::binder::Status trimSize(int64_t bufferHandle, int32_t newSize, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Frees a memory buffer previously allocated through `alloc()` or privately allocated by HAL services
   * from the video frame pool or audio frame pool.
   *
   * @param[in] bufferHandle        Memory buffer handle.
   *
   * @param[out] _aidl_return boolean
   *   - true: The free was successful.
   *   - false: The bufferHandle was invalid.
   * @see alloc()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status free(int64_t bufferHandle, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Check if a given buffer handle is a valid allocated handle.
   *
   * @param[in] bufferHandle        Memory buffer handle.
   *
   * @param[out] _aidl_return boolean
   *   - true: The handle is valid.
   *   - false: The handle is invalid.
   * @see alloc(), free()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status isValid(int64_t bufferHandle, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the allocated list of memory buffers from a pool.
   *
   * If the pool handle is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
   *
   * This API is intended for debug purposes and not general use.
   *
   * @param[in] poolHandle    Pool handle.
   *
   * @param[out] _aidl_return long[] array of buffer handles.
   *
   * @see alloc(), createVideoPool(), createAudioPool()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT
   */
  virtual ::android::binder::Status getAllocList(const ::com::rdk::hal::avbuffer::Pool& poolHandle, ::std::vector<int64_t>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Calculates the SHA-1 for the data contained inside an AV buffer.
   *
   * Note: This is only available in developer/debug/vbn builds and never in production builds.
   * This aids in testing the decrypted output from DRM/CDM.
   *
   * If the `bufferHandle` passed is invalid, then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is
   * returned.
   *
   * Implementing this function is optional and if not implemented the function must return
   * the `binder::Status EX_UNSUPPORTED_OPERATION` exception status if called.
   *
   * @param[in] bufferHandle              Memory buffer handle.
   *
   * @param[out] _aidl_return byte[] SHA-1 result buffer.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION
   */
  virtual ::android::binder::Status calculateSHA1(int64_t bufferHandle, ::std::vector<uint8_t>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVBuffer

class IAVBufferDefault : public IAVBuffer {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getHeapMetrics(bool /*secureHeap*/, ::com::rdk::hal::avbuffer::HeapMetrics* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createVideoPool(bool /*secureHeap*/, const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& /*videoDecoderId*/, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& /*listener*/, ::com::rdk::hal::avbuffer::Pool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createAudioPool(bool /*secureHeap*/, const ::com::rdk::hal::audiodecoder::IAudioDecoder::Id& /*audioDecoderId*/, const ::android::sp<::com::rdk::hal::avbuffer::IAVBufferSpaceListener>& /*listener*/, ::com::rdk::hal::avbuffer::Pool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status destroyPool(const ::com::rdk::hal::avbuffer::Pool& /*poolHandle*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPoolMetrics(const ::com::rdk::hal::avbuffer::Pool& /*poolHandle*/, ::com::rdk::hal::avbuffer::PoolMetrics* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAllPoolMetrics(bool /*secureHeap*/, ::std::vector<::com::rdk::hal::avbuffer::PoolMetrics>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status alloc(const ::com::rdk::hal::avbuffer::Pool& /*poolHandle*/, int32_t /*size*/, int64_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyWhenSpaceAvailable(const ::com::rdk::hal::avbuffer::Pool& /*poolHandle*/, int32_t /*size*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status trimSize(int64_t /*bufferHandle*/, int32_t /*newSize*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status free(int64_t /*bufferHandle*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isValid(int64_t /*bufferHandle*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAllocList(const ::com::rdk::hal::avbuffer::Pool& /*poolHandle*/, ::std::vector<int64_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status calculateSHA1(int64_t /*bufferHandle*/, ::std::vector<uint8_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVBufferDefault
}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com
