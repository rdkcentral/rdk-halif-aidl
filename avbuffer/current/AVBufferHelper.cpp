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
#include "AVBufferHelper.hpp"
#include "VendorPlatformBufferOps.hpp"

/**
 * @brief Constructs the AVBufferHelper singleton and initializes vendor ops.
 */
AVBufferHelper::AVBufferHelper()
{
    ops_ = new VendorPlatformBufferOps();
}

/**
 * @brief Destroys the AVBufferHelper singleton and cleans up vendor ops.
 */
AVBufferHelper::~AVBufferHelper()
{
    delete ops_;
}

/**
 * @brief Returns the singleton instance of AVBufferHelper.
 * @return Reference to the singleton instance.
 */
AVBufferHelper &AVBufferHelper::getInstance()
{
    static AVBufferHelper instance;
    return instance;
}

/**
 * @brief Maps a buffer handle into memory using vendor operations.
 * @param handle Buffer handle.
 * @param size Output pointer for mapped memory size.
 * @return Pointer to mapped memory, or nullptr on failure.
 */
void *AVBufferHelper::mapHandle(uint64_t handle, uint32_t *size)
{
    return ops_->mapHandle(handle, size);
}

/**
 * @brief Unmaps a previously mapped buffer handle using vendor operations.
 * @param handle Buffer handle to unmap.
 * @return True on success, false on failure.
 */
bool AVBufferHelper::unmapHandle(uint64_t handle)
{
    return ops_->unmapHandle(handle) == 0;
}

/**
 * @brief Writes data securely to a buffer using vendor operations.
 * @param handle Target buffer handle.
 * @param data Pointer to data to write.
 * @param size Size of data in bytes.
 * @return True on success, false otherwise.
 */
bool AVBufferHelper::writeSecureHandle(uint64_t handle, const void *data, uint32_t size)
{
    return ops_->writeSecure(handle, data, size) == 0;
}

/**
 * @brief Securely copies data between buffers using vendor operations.
 * @param handleTo Destination buffer handle.
 * @param handleFrom Source buffer handle.
 * @param map Struct containing copy offset and size information.
 * @return True on success, false otherwise.
 */
bool AVBufferHelper::copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, const CopyMap &map)
{
    return ops_->copySecure(handleTo, handleFrom, map.src_offset, map.dst_offset, map.size) == 0;
}
