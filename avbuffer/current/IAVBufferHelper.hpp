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

#ifndef _IAVBUFFERHELPER_H_
#define _IAVBUFFERHELPER_H_

#include <stdint.h>

using namespace com::rdk::hal;
using namespace com::rdk::hal::avbuffer;

/**
 * @class IAVBufferHelper
 * @brief Pure virtual interface for AV buffer helpers.
 *
 * This interface defines the API contract for managing buffer handles
 * in AV pipelines where memory is shared between processes.
 * It is typically used in pipelines where pipeline elements
 * are implemented as AIDL HAL components communicating across process boundaries.
 *
 * Implementations of this interface are responsible for:
 *   - Mapping a memory handle into process address space
 *   - Unmapping a previously mapped handle
 *   - Writing data into secure buffers
 *   - Copying data between secure buffers
 *
 * Vendors must provide an implementation of this interface appropriate
 * to their platform. Depending on the architecture, this may involve:
 *   - Interacting with a buffer manager service (via AIDL, sockets, or vendor-specific transport)
 *   - Using platform-specific buffer types (DMABUF, ION, TEE-secure buffers)
 *   - Enforcing security / DRM constraints when writing or copying buffers
 *
 * A default implementation (`AVBufferHelper`) is typically provided as reference.
 * Vendors can choose to subclass `AVBufferHelper` or provide a fully custom
 * implementation of `IAVBufferHelper`.
 *
 * NOTE ON SINGLETON ACCESS:
 *   - The interface itself does not provide a static getInstance().
 *   - The default implementation (`AVBufferHelper`) provides a static getInstance()
 *     to simplify usage in typical pipeline nodes.
 *   - If a vendor supplies a custom implementation, they should provide their own
 *     singleton access mechanism or factory registration as appropriate.
 */
class IAVBufferHelper
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
     * @brief Destroys the `IAVBufferHelper` object.
     */
    virtual ~IAVBufferHelper() {}

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
    virtual void *mapHandle(uint64_t handle, uint32_t *size) = 0;

    /**
     * @brief Unmaps memory from a given handle.
     *
     * @param[in] handle The handle to unmap memory from.
     *
     * @retval true If the memory was successfully unmapped.
     * @retval false If the memory could not be unmapped (e.g., invalid handle).
     */
    virtual bool unmapHandle(uint64_t handle) = 0;

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
    virtual bool writeSecureHandle(uint64_t handle, void *data, uint32_t size) = 0;

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
    virtual bool copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, CopyMap map, uint32_t mapSize) = 0;
};

#endif // _IAVBUFFERHELPER_H_
