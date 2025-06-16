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

#ifndef _AVBUFFER_C_API_H_
#define _AVBUFFER_C_API_H_

#include <stdint.h> // For uint64_t, uint32_t

// Ensure C linkage for these functions so C++ compilers don't mangle their names.
// This is critical for vendors implementing in pure C.
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct AVBufferCopyMap_t
 * @brief C-style structure defining offsets and size for a memory copy operation.
 * This mirrors the C++ CopyMap struct but is for the C API.
 */
typedef struct {
    uint32_t src_offset; /**< The offset from the source handle where copying begins. */
    uint32_t dst_offset; /**< The offset in the destination handle where data will be copied. */
    uint32_t size;       /**< The amount of data to copy, in bytes. */
} AVBufferCopyMap_t;


/**
 * @brief Maps memory from a given handle into the process address space.
 *
 * This function is the C-level equivalent of IAVBufferHelper::mapHandle.
 *
 * @param[in] handle The handle to map memory from.
 * @param[out] size A pointer to a uint32_t that will be populated with the size of the mapped data.
 *
 * @returns A pointer to the mapped memory address, or NULL if the mapping fails.
 */
void* avbuffer_map_handle(uint64_t handle, uint32_t* size);

/**
 * @brief Unmaps memory from a previously mapped handle.
 *
 * This function is the C-level equivalent of IAVBufferHelper::unmapHandle.
 *
 * @param[in] handle The handle to unmap memory from.
 *
 * @retval 0 If the memory was successfully unmapped.
 * @retval non-zero If the memory could not be unmapped (e.g., invalid handle, error).
 */
int avbuffer_unmap_handle(uint64_t handle);

/**
 * @brief Writes data from unsecure memory into a secure buffer.
 *
 * This function is the C-level equivalent of IAVBufferHelper::writeSecureHandle.
 *
 * @param[in] handle The handle of the secure buffer to write data into.
 * @param[in] data A pointer to the unsecure data to write.
 * @param[in] size The size of the data to write, in bytes.
 *
 * @retval 0 If the data was successfully written.
 * @retval non-zero If the data could not be written (e.g., invalid handle, insufficient space).
 */
int avbuffer_write_secure_handle(uint64_t handle, const void* data, uint32_t size);

/**
 * @brief Copies data from one secure buffer to another based on a map.
 *
 * This function is the C-level equivalent of IAVBufferHelper::copySecureHandleWithMap.
 * Note: Assumes a single copy map for simplicity, matching the C++ interface.
 *
 * @param[in] handle_to The handle of the destination secure buffer.
 * @param[in] handle_from The handle of the source secure buffer.
 * @param[in] map The AVBufferCopyMap_t structure specifying the offsets and size for the copy operation.
 *
 * @retval 0 If the data was successfully copied.
 * @retval non-zero If the data could not be copied (e.g., invalid handles, overlapping regions).
 */
int avbuffer_copy_secure_handle_with_map(uint64_t handle_to, uint64_t handle_from, AVBufferCopyMap_t map);

#ifdef __cplusplus
} // extern "C"
#endif

#endif // _AVBUFFER_C_API_H_