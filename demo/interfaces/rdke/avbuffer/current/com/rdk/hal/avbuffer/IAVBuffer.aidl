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
 */

@VintfStability
interface IAVBuffer
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "AVBuffer";

    /** Invalid handle for buffers. */
    const long INVALID_HANDLE = -1;

    /**
     * Gets the number of used/total bytes in a memory heap.
     *
     * @param[in] secureHeap        Specifies the secure heap when true or non-secure heap when false.
     * 
     * @returns HeapMetrics
     *
     * @see createVideoPool(), createAudioPool(), destroyPool()
     */  
    HeapMetrics getHeapMetrics(in boolean secureHeap);

    /**
     * Creates a video memory buffer pool of a secure or non-secure type from which allocations can be made.
     * 
     * The size must be a multiple of 8 bytes.
     * 
     * If the `videoDecoderId` is invalid then the `EX_ILLEGAL_ARGUMENT` exception status is returned.
     * 
     * It the platform has exhausted all available memory from the requested heap then the exception status
     * `EX_SERVICE_SPECIFIC` with `HALError::OUT_OF_MEMORY` is returned.
     *
     * @param[in] secureHeap            Indicates if the pool is secure.
     * @param[in] videoDecoderIndex     The index of the video decoder resource.
     * 
     * @returns Pool
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
     * @exception binder::Status EX_SERVICE_SPECIFIC, HALError::OUT_OF_MEMORY
     * 
     * @pre The IVideoDecoder.Id must have been obtained from IVideoDecoderManager.getVideoDecoderIds()
     * 
     * @see destroyPool()
     */
    Pool createVideoPool(in boolean secureHeap, in IVideoDecoder.Id videoDecoderId, in IAVBufferSpaceListener listener);

    /**
     * Creates a audio memory buffer pool of a secure or non-secure type from which allocations can be made.
     * 
     * If the audio pool is for audio data not destinated for a vendor audio decoder
     * (e.g. system audio PCM) then the ID must be IAudioDecoder.Id.UNDEFINED.
     * 
     * It the platform has exhausted all available memory from the requested heap then the exception status
     * `EX_SERVICE_SPECIFIC` with `HALError::OUT_OF_MEMORY` is returned.
     * 
     * The size must be a multiple of 8 bytes.
     * 
     * If the `audioDecoderId` is invalid then the `EX_ILLEGAL_ARGUMENT` exception status is returned.
     *
     * @param[in] secureHeap            Indicates if the pool is secure.
     * @param[in] audioDecoderId        The ID of the audio decoder resource.
     * 
     * @returns Pool
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
     * @exception binder::Status EX_SERVICE_SPECIFIC, HALError::OUT_OF_MEMORY
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
     * If any buffer allocations are outstanding then the exception status `EX_SERVICE_SPECIFIC` with `HALError::NOT_EMPTY`
     * is returned.
     *
     * @param[in] poolHandle      Pool handle.
     *
     * @returns boolean
     * @retval true     The pool handle is valid.
     * @retval false    The pool handle is invalid.
     *
     * @exception binder::Status EX_SERVICE_SPECIFIC, HALError::NOT_EMPTY
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
     * If the pool handle is invalid then the `EX_ILLEGAL_ARGUMENT` exception status is returned.
     * 
     * @param[in] poolHandle        Pool handle.
     * 
     * @returns PoolMetrics
     *
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
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
     * @see alloc(), free(), createVideoPool(), createAudioPool()
     */
    PoolMetrics[] getAllPoolMetrics(in boolean secureHeap);
 
    /**
     * Allocates a memory buffer from a given buffer pool.
     * 
     * The allocation will be satisfied immediately or fail if a memory buffer of the given size is not available.
     * The output handle is valid when the returned result is >= 0.
     * The handle must eventually be used in a call to `free()` to release the memory block.
     * 
     * If the allocation fails due to an out of memory condition then `EX_SERVICE_SPECIFIC` with `HALError::OUT_OF_MEMORY`
     * is returned and the client can call `notifyWhenSpaceAvailable()` to be notified when space becomes available.
     *
     * @param[in] poolHandle    Pool handle.
     * @param[in] size          Size of the memory block allocation in bytes. Must be > 0.
     *
     * @returns long            The handle of the new buffer allocation.
     * @retval INVALID_HANDLE   The pool handle is invalid or the size is > the pool size.
     * 
     * @exception binder::Status EX_SERVICE_SPECIFIC, HALError::OUT_OF_MEMORY
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
     * If the buffer handle passed is not the last allocated from a pool then EX_ILLEGAL_STATE is returned.
     *
     * @param[in] bufferHandle  Memory buffer handle.
     * @param[in] newSize       New size of the memory block in bytes.  Must be > 0 and <= original size.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @returns boolean
     * @retval true     The trim was successful.
     * @retval false    The bufferHandle or newSize was invalid.
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
     * @see alloc(), free()
     */
    boolean isValid(in long bufferHandle);

    /**
     * Gets the allocated list of memory buffers from a pool.
     * 
     * If the pool handle is invalid then the `EX_ILLEGAL_ARGUMENT` exception status is returned.
     * 
     * This API is intended for debug purposes and not general use.
     *
     * @param[in] poolHandle    Pool handle.
     *
     * @returns long[] array of buffer handles.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
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
     * If the `bufferHandle` passed is invalid, then the `EX_ILLEGAL_ARGUMENT` exception status is returned.
     *
     * Implementing this function is optional and if not implemented the function must return
     * the `EX_UNSUPPORTED_OPERATION` exception status if called.
     * 
     * @param[in] bufferHandle              Memory buffer handle.
     * 
     * @returns byte[] SHA-1 result buffer.
     * 
     * @exception binder::Status EX_ILLEGAL_ARGUMENT
     * @exception binder::Status EX_UNSUPPORTED_OPERATION
     */
    byte[] calculateSHA1(in long bufferHandle);
}
