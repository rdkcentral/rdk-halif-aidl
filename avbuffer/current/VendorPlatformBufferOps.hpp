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
#ifndef _VENDORPLATFORMBUFFEROPS_HPP_
#define _VENDORPLATFORMBUFFEROPS_HPP_

#include <cstdint>

/**
 * @class VendorPlatformBufferOps
 * @brief Interface to be implemented by vendors for buffer operations.
 *
 * This class defines platform-specific buffer operations required for
 * mapping, unmapping, and managing secure AV buffers.
 *
 * VENDORS MUST IMPLEMENT THIS INTERFACE according to their platform's
 * memory handling, security, and performance characteristics.
 */
class VendorPlatformBufferOps
{
public:
    /**
     * @brief Maps a buffer handle.
     * @param handle Handle to map.
     * @param size Output size.
     * @return Pointer to mapped memory or nullptr.
     */
    void *mapHandle(uint64_t handle, uint32_t *size);

    /**
     * @brief Unmaps a buffer handle.
     * @param handle Buffer handle.
     * @return 0 on success, non-zero on failure.
     */
    int unmapHandle(uint64_t handle);

    /**
     * @brief Writes data securely to a buffer.
     * @param handle Buffer handle.
     * @param data Data pointer.
     * @param size Data size.
     * @return 0 on success, non-zero on failure.
     */
    int writeSecure(uint64_t handle, const void *data, uint32_t size);

    /**
     * @brief Copies data between two secure buffers.
     * @param to Destination handle.
     * @param from Source handle.
     * @param srcOff Source offset.
     * @param dstOff Destination offset.
     * @param size Number of bytes.
     * @return 0 on success, non-zero on failure.
     */
    int copySecure(uint64_t to, uint64_t from, uint32_t srcOff, uint32_t dstOff, uint32_t size);
};

#endif // _VENDORPLATFORMBUFFEROPS_HPP_
