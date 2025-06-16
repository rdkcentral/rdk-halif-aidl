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
 * [http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "avbuffer_helper.h"  // C API functions
#include "AVBufferHelperCWrapper.hpp" // Header for this class
#include <iostream>                // For basic logging/error reporting (replace with proper logging framework in production)

// This namespace is intentionally left out in headers but can be used here for convenience
// using namespace com::rdk::hal::avbuffer; // Example if you had specific RDK namespaces

/**
 * @brief Provides access to the singleton instance of AVBufferHelperCWrapper.
 *
 * This function uses the "Meyers' Singleton" pattern (static local variable)
 * which ensures thread-safe initialization in C++11 and later.
 *
 * @return A reference to the singleton AVBufferHelperCWrapper instance.
 */
AVBufferHelperCWrapper& AVBufferHelperCWrapper::getInstance()
{
    static AVBufferHelperCWrapper instance;
    return instance;
}

/**
 * @brief Maps memory from a given handle by calling the C API.
 *
 * Delegates the call to avbuffer_map_handle from the C API.
 *
 * @param[in] handle The handle to map memory from.
 * @param[out] size A pointer to a uint32_t that will be populated with the size of the mapped data.
 *
 * @returns A pointer to the mapped memory address, or nullptr if the mapping fails.
 */
void *AVBufferHelperCWrapper::mapHandle(uint64_t handle, uint32_t *size)
{
    // Validate input pointer for size
    if (size == nullptr) {
        std::cerr << "AVBufferHelperCWrapper: Error - 'size' pointer is nullptr in mapHandle." << std::endl;
        return nullptr;
    }

    void* mapped_ptr = avbuffer_map_handle(handle, size);

    // Basic error logging
    if (mapped_ptr == nullptr) {
        std::cerr << "AVBufferHelperCWrapper: Failed to map handle 0x"
                  << std::hex << handle << std::dec << ". Check C API implementation." << std::endl;
    }

    return mapped_ptr;
}

/**
 * @brief Unmaps memory from a given handle by calling the C API.
 *
 * Delegates the call to avbuffer_unmap_handle from the C API.
 *
 * @param[in] handle The handle to unmap memory from.
 *
 * @retval true If the memory was successfully unmapped.
 * @retval false If the memory could not be unmapped (e.g., invalid handle, C API error).
 */
bool AVBufferHelperCWrapper::unmapHandle(uint64_t handle)
{
    int result = avbuffer_unmap_handle(handle);

    // C functions typically return 0 for success, non-zero for failure
    if (result != 0) {
        std::cerr << "AVBufferHelperCWrapper: Failed to unmap handle 0x"
                  << std::hex << handle << std::dec << ". C API returned error code: "
                  << result << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Writes data from unsecure memory into a secure buffer by calling the C API.
 *
 * Delegates the call to avbuffer_write_secure_handle from the C API.
 *
 * @param[in] handle The handle of the secure buffer to write data into.
 * @param[in] data A pointer to the unsecure data to write.
 * @param[in] size The size of the data to write, in bytes.
 *
 * @retval true If the data was successfully written.
 * @retval false If the data could not be written (e.g., invalid handle, insufficient space, C API error).
 */
bool AVBufferHelperCWrapper::writeSecureHandle(uint64_t handle, const void *data, uint32_t size)
{
    // Validate input pointers
    if (data == nullptr) {
        std::cerr << "AVBufferHelperCWrapper: Error - 'data' pointer is nullptr in writeSecureHandle." << std::endl;
        return false;
    }

    int result = avbuffer_write_secure_handle(handle, data, size);

    if (result != 0) {
        std::cerr << "AVBufferHelperCWrapper: Failed to write to secure handle 0x"
                  << std::hex << handle << std::dec << ". C API returned error code: "
                  << result << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Copies data from one secure buffer to another by calling the C API.
 *
 * Delegates the call to avbuffer_copy_secure_handle_with_map from the C API.
 * This method directly translates the C++ CopyMap struct to the C-style
 * AVBufferCopyMap_t struct before passing it to the C function.
 *
 * @param[in] handleTo The handle of the destination secure buffer.
 * @param[in] handleFrom The handle of the source secure buffer.
 * @param[in] map The IAVBufferHelper::CopyMap structure specifying the offsets and size.
 *
 * @retval true If the data was successfully copied.
 * @retval false If the data could not be copied (e.g., invalid handles, C API error).
 */
bool AVBufferHelperCWrapper::copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, const CopyMap& map)
{
    // Translate C++ CopyMap to C-style AVBufferCopyMap_t
    AVBufferCopyMap_t c_map = {
        .src_offset = map.src_offset,
        .dst_offset = map.dst_offset,
        .size = map.size
    };

    int result = avbuffer_copy_secure_handle_with_map(handleTo, handleFrom, c_map);

    if (result != 0) {
        std::cerr << "AVBufferHelperCWrapper: Failed to copy between secure handles (to 0x"
                  << std::hex << handleTo << ", from 0x" << handleFrom << std::dec
                  << "). C API returned error code: " << result << std::endl;
        return false;
    }

    return true;
}