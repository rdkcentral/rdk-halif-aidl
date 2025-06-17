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
// AVBufferHelper.hpp
#ifndef _AVBUFFERHELPER_HPP_
#define _AVBUFFERHELPER_HPP_

#include <cstdint>

/**
 * @class AVBufferHelper
 * @brief Singleton class to manage vendor-specific AV buffer operations.
 *
 * This class provides high-level APIs for buffer mapping, unmapping,
 * secure data writing, and secure buffer-to-buffer copying.
 * It delegates all low-level memory operations to a vendor-supplied
 * implementation.
 *
 * Usage:
 * --------
 * AVBufferHelper& helper = AVBufferHelper::getInstance();
 * uint32_t size;
 * void* ptr = helper.mapHandle(handle, &size);
 * if (ptr) { ... }
 * helper.unmapHandle(handle);
 *
 * CopyMap map = {0, 0, size};
 * helper.copySecureHandleWithMap(destHandle, srcHandle, map);
 */
class AVBufferHelper
{
public:
    /**
     * @struct CopyMap
     * @brief Structure for describing source and destination offsets for secure copy.
     */
    struct CopyMap
    {
        uint32_t src_offset; /**< Offset in source buffer */
        uint32_t dst_offset; /**< Offset in destination buffer */
        uint32_t size;       /**< Size in bytes to copy */
    };

    /**
     * @brief Returns the singleton instance of AVBufferHelper.
     * @return Reference to singleton instance.
     */
    static AVBufferHelper &getInstance()
    {
        static AVBufferHelper instance;
        return instance;
    }

    /**
     * @brief Maps a buffer handle to virtual memory.
     * @param handle Buffer handle.
     * @param size Pointer to store the mapped size.
     * @return Pointer to mapped memory or nullptr on failure.
     */
    void *mapHandle(uint64_t handle, uint32_t *size);

    /**
     * @brief Unmaps a previously mapped buffer handle.
     * @param handle Buffer handle to unmap.
     * @return True if successful, false otherwise.
     */
    bool unmapHandle(uint64_t handle);

    /**
     * @brief Securely writes data to a buffer handle.
     * @param handle Destination buffer handle.
     * @param data Pointer to source data.
     * @param size Size of data in bytes.
     * @return True if successful, false otherwise.
     */
    bool writeSecureHandle(uint64_t handle, const void *data, uint32_t size);

    /**
     * @brief Securely copies data from one buffer to another.
     * @param handleTo Destination buffer handle.
     * @param handleFrom Source buffer handle.
     * @param map Copy parameters (offsets and size).
     * @return True if successful, false otherwise.
     */
    bool copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, const CopyMap &map);

private:
    /**
     * @brief Private constructor.
     */
    AVBufferHelper();

    /**
     * @brief Destructor.
     */
    ~AVBufferHelper();

    AVBufferHelper(const AVBufferHelper &) = delete;            ///< Copy constructor deleted.
    AVBufferHelper &operator=(const AVBufferHelper &) = delete; ///< Assignment operator deleted.

    class VendorPlatformBufferOps *ops_; ///< Pointer to vendor-specific operations implementation.
};

#endif // _AVBUFFERHELPER_HPP_
