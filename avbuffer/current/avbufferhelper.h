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

#ifndef _AVBUFFERHELPER_H_
#define _AVBUFFERHELPER_H_

#include <stdint.h>
#include <mutex>

using namespace std;
using namespace com::rdk::hal;
using namespace com::rdk::hal::avbuffer;

/**
 * @class RDKAVBufferHelper
 * @brief Provides helper functions for mapping and unmapping memory from handles,
 * and for writing and copying data within secure buffer regions.
 */
class RDKAVBufferHelper
{
public:
    /**
     * @struct CopyMap
     * @brief Defines the offsets and size for a memory copy operation.
     */
    struct CopyMap
    {
        uint32_t src_offset; /**< The offset from the source handle where copying begins. */
        uint32_t dst_offset; /**< The offset in the destination handle where data will be copied. */
        uint32_t size;       /**< The amount of data to copy, in bytes. */
    };

    /**
     * @brief Constructs an `RDKAVBufferHelper` object.
     */
    RDKAVBufferHelper();

    /**
     * @brief Destroys the `RDKAVBufferHelper` object.
     */
    virtual ~RDKAVBufferHelper();

    /**
     * @brief Retrieves the singleton instance of `RDKAVBufferHelper`.
     *
     * @returns A pointer to the `RDKAVBufferHelper` instance.
     */
    static RDKAVBufferHelper *getInstance();

    /**
     * @brief Maps memory from a given handle.
     *
     * This function is used by client code outside the `LinearBufferMgr` class to
     * map memory from a specified handle.
     *
     * @param[in] handle The handle to map memory from.
     * @param[out] size A pointer to a `uint32_t` that will be populated with the size of the mapped data.
     *
     * @returns A pointer to the mapped memory address, or `nullptr` if the mapping fails.
     */
    void *mapHandle(uint64_t handle, uint32_t *size);

    /**
     * @brief Unmaps memory from a given handle.
     *
     * @param[in] handle The handle to unmap memory from.
     *
     * @retval true If the memory was successfully unmapped.
     * @retval false If the memory could not be unmapped (e.g., invalid handle).
     */
    bool unmapHandle(uint64_t handle);

    /**
     * @brief Writes data from unsecure memory into a secure buffer.
     *
     * @param[in] handle The handle of the secure buffer to write data into.
     * @param[in] data A pointer to the unsecure data to write.
     * @param[in] size The size of the data to write, in bytes.
     *
     * @retval true If the data was successfully written.
     * @retval false If the data could not be written (e.g., invalid handle, insufficient space).
     */
    bool writeSecureHandle(uint64_t handle, void *data, uint32_t size);

    /**
     * @brief Copies data from one secure buffer to another.
     *
     * @param[in] handleTo The handle of the destination secure buffer.
     * @param[in] handleFrom The handle of the source secure buffer.
     * @param[in] map The `CopyMap` structure specifying the offsets and size for the copy operation.
     * @param[in] mapSize The number of indexes in the map.
     *
     * @retval true If the data was successfully copied.
     * @retval false If the data could not be copied (e.g., invalid handles, overlapping regions).
     */
    bool copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, CopyMap map, uint32_t mapSize);

private:
    /**
     * @brief Sends a request message over a socket.
     *
     * @param[in] sockfd The socket file descriptor.
     * @param[in] pMessage A pointer to the message to send.
     *
     * @retval true If the message was successfully sent.
     * @retval false If an error occurred during sending.
     */
    bool sendRequest(int sockfd, void *pMessage);

    /**
     * @brief Retrieves a response message from a socket.
     *
     * @param[in] sockfd The socket file descriptor.
     * @param[out] pMessage A pointer to the buffer to store the received message.
     *
     * @retval true If the response was successfully received.
     * @retval false If an error occurred during reception.
     */
    bool getResponse(int sockfd, void *pMessage);

    /**
     * @brief Retrieves the offset associated with a given handle.
     *
     * @param[in] handle The handle for which to retrieve the offset.
     *
     * @returns The offset of the handle, or `0` if the handle is invalid.
     */
    uint32_t getHandleOffset(uint64_t handle);

    /**
     * @brief Retrieves the size associated with a given handle.
     *
     * @param[in] handle The handle for which to retrieve the size.
     *
     * @returns The size of the handle, or `0` if the handle is invalid.
     */
    uint32_t getHandleSize(uint64_t handle);

    /**
     * @brief Retrieves the base address of the shared memory region.
     *
     * @returns A pointer to the base address of the shared memory region, or `nullptr` if
     * the region is not mapped.
     */
    void *getSharedMemoryRegionAddr();

    void *_shm_addr;            /**< @brief Stores the local address of the mapped shared memory region. */
    std::recursive_mutex m_mtx; /**< @brief Mutex to protect access to shared resources within the helper. */
};

#endif // _AVBUFFERHELPER_H_
