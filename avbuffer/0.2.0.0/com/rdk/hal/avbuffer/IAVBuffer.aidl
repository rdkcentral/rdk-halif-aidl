/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2024 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.avbuffer;
import com.rdk.hal.avbuffer.IAVBufferSpaceListener;
import com.rdk.hal.avbuffer.HeapMetrics;
import com.rdk.hal.avbuffer.Pool;
import com.rdk.hal.avbuffer.PoolMetrics;
import com.rdk.hal.videodecoder.IVideoDecoder;
import com.rdk.hal.audiodecoder.IAudioDecoder;

/** 
 *  @brief     AV buffer HAL interface definition.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IAVBuffer
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "AVBuffer";

    /**
     * Gets the number of used/total bytes in a memory heap.
     *
     * @param[in] secureHeap        Specifies the secure heap when true or non-secure heap when false.
     * 
     * @returns HeapMetrics
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see createVideoPool(), createAudioPool(), destroyPool()
     */  
    HeapMetrics getHeapMetrics(in boolean secureHeap);

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
     * @returns A new `Pool` object with a valid handle, intended for the full lifetime of the pipeline session.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT  if videoDecoderId is invalid
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC  if heap is exhausted (out-of-memory)
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE decoder not configured
     *
     * @pre The IVideoDecoder.Id must have been obtained from IVideoDecoderManager.getVideoDecoderIds()
     * 
     * @see destroyPool()
     */
    Pool createVideoPool(in boolean secureHeap, in IVideoDecoder.Id videoDecoderId, in IAVBufferSpaceListener listener);

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
     * @returns A new `Pool` object with a valid handle, intended for the full lifetime of the pipeline session.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if audioDecoderId is invalid
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC  if heap is exhausted (out-of-memory)
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE decoder not configured
     * 
     * @pre The IAudioDecoder.Id must have been obtained from IAudioDecoderManager.getAudioDecoderIds()
     *      or IAudioDecoder.Id.UNDEFINED must be used.
     * 
     * @see destroyPool()
     */
    Pool createAudioPool(in boolean secureHeap, in IAudioDecoder.Id audioDecoderId, in IAVBufferSpaceListener listener);

    /**
     * Destroys a memory buffer pool previously created with createVideoPool() or createAudioPool().
     * 
     * The AV buffer pool must be empty, with all previously allocated buffers from the pool freed.
     * If any buffer allocations are outstanding then the exception status `binder::Status::Exception::EX_SERVICE_SPECIFIC` (pool-not-empty)
     * is returned.
     *
     * @param[in] poolHandle      Pool handle.
     *
     * @returns boolean
     * @retval true     The pool handle is valid.
     * @retval false    The pool handle is invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC  if outstanding allocations remain (pool-not-empty)
     * 
     * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
     * @pre The pool must have all allocations freed.
     * 
     * @see createVideoPool(), createAudioPool()
     */
    boolean destroyPool(in Pool poolHandle);

    /**
     * Gets the number of used/total bytes in a memory pool.
     *
     * If the pool handle is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
     * 
     * @param[in] poolHandle        Pool handle.
     * 
     * @returns PoolMetrics
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT
     * 
     * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
     * 
     * @see alloc(), free(), createVideoPool(), createAudioPool()
     */
    PoolMetrics getPoolMetrics(in Pool poolHandle);
 
    /**
     * Gets the list of all pools metrics in a specified heap.
     *
     * @param[in] secureHeap    Specifies the heap type - true is secure, false is non-secure.
     * 
     * @returns PoolMetrics[] array is sized to cover all created pools.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     * 
     * @see alloc(), free(), createVideoPool(), createAudioPool()
     */
    PoolMetrics[] getAllPoolMetrics(in boolean secureHeap);
 
    /**
     * Allocates a memory buffer from a given buffer pool.
     * 
     * The allocation will be satisfied immediately or fail if a memory buffer of the given size is not available.
     * On success, a valid handle is returned that must eventually be used in a call to `free()` to release the memory block.
     * 
     * If the allocation fails due to an out of memory condition then `binder::Status::Exception::EX_SERVICE_SPECIFIC` (out-of-memory)
     * is returned and the client can call `notifyWhenSpaceAvailable()` to be notified when space becomes available.
     *
     * @param[in] poolHandle    Pool handle.
     * @param[in] size          Size of the memory block allocation in bytes. Must be > 0.
     *
     * @returns long            The handle of the new buffer allocation.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if pool handle is invalid or size is invalid
     * @exception binder::Status::Exception::EX_SERVICE_SPECIFIC if allocation fails (out-of-memory)
     *
     * 
     * @pre A pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
     * 
     * @see free(), createVideoPool(), createAudioPool(), notifyWhenSpaceAvailable()
     */
    long alloc(in Pool poolHandle, in int size);

    /**
     * Requests notification when enough space in a pool becomes available for an allocation of `size` bytes.
     * 
     * This function is usually called after a call to `alloc()` has failed with an out of memory condition.
     * The notification callback occurs on the `IAVBufferSpaceListener` passed in by the client when the pool was created.
     * 
     * @param[in] poolHandle    Pool handle.
     * @param[in] size          Size of the memory block in bytes. Must be > 0 and <= the pool size.
     * 
     * @returns boolean
     * @retval true     The notification request was successful and a callback will follow.
     * @retval false    Invalid pool handle or size.
     * 
     * @pre A Pool handle must have been obtained from `createVideoPool()` or `createAudioPool()`.
     * 
     * @see IAVBufferSpaceListener.onSpaceAvailable()
     */
    boolean notifyWhenSpaceAvailable(in Pool poolHandle, in int size);

    /**
     * Trims the size of the last alloc() block from a pool to a smaller size.
     * 
     * If the buffer handle passed is not the last allocated from a pool then `binder::Status EX_ILLEGAL_STATE` is returned.
     *
     * @param[in] bufferHandle  Memory buffer handle.
     * @param[in] newSize       New size of the memory block in bytes.  Must be > 0 and <= original size.
     *
     * @returns boolean
     * @retval true     The trim was successful.
     * @retval false    The bufferHandle or newSize was invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_STATE if buffer is not the last allocated from the pool
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT if bufferHandle or newSize is invalid
     *
     * @pre The `bufferHandle` must be the last one returned from a call to `alloc()`.
     * 
     * @see alloc()
     */
    boolean trimSize(in long bufferHandle, in int newSize);
 
    /**
     * Frees a memory buffer previously allocated through `alloc()` or privately allocated by HAL services
     * from the video frame pool or audio frame pool.
     *
     * @param[in] bufferHandle        Memory buffer handle.
     *
     * @returns boolean
     * @retval true     The free was successful.
     * @retval false    The bufferHandle was invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see alloc()
     */
    boolean free(in long bufferHandle);

    /**
     * Check if a given buffer handle is a valid allocated handle.
     * 
     * @param[in] bufferHandle        Memory buffer handle.
     * 
     * @returns boolean
     * @retval true     The handle is valid.
     * @retval false    The handle is invalid.
     *
     * @exception binder::Status::Exception::EX_NONE for success.
     *
     * @see alloc(), free()
     */
    boolean isValid(in long bufferHandle);

    /**
     * Gets the allocated list of memory buffers from a pool.
     * 
     * If the pool handle is invalid then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
     * 
     * This API is intended for debug purposes and not general use.
     *
     * @param[in] poolHandle    Pool handle.
     *
     * @returns long[] array of buffer handles.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT
     * 
     * @see alloc(), createVideoPool(), createAudioPool()
     */
    long[] getAllocList(in Pool poolHandle);

    /**
     * Calculates the SHA-1 for the data contained inside an AV buffer.
     * 
     * Note: This is only available in developer/debug/vbn builds and never in production builds.
     * This aids in testing the decrypted output from DRM/CDM.
     * 
     * If the `bufferHandle` passed is invalid, then the `binder::Status EX_ILLEGAL_ARGUMENT` exception status is returned.
     *
     * Implementing this function is optional and if not implemented the function must return
     * the `binder::Status EX_UNSUPPORTED_OPERATION` exception status if called.
     * 
     * @param[in] bufferHandle              Memory buffer handle.
     * 
     * @returns byte[] SHA-1 result buffer.
     *
     * @exception binder::Status::Exception::EX_NONE for success
     * @exception binder::Status::Exception::EX_ILLEGAL_ARGUMENT
     * @exception binder::Status::Exception::EX_UNSUPPORTED_OPERATION
     */
    byte[] calculateSHA1(in long bufferHandle);
}
