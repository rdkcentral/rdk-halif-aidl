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
#ifndef AVBUFFERHELPER_H
#define AVBUFFERHELPER_H
#include <stdint.h>
#include "../h/com/rdk/hal/HALError.h"

namespace com {
namespace rdk {
namespace hal {
namespace avbuffer {

/**********************************************************************************/
/**********************************************************************************/
/**********************************************************************************/

/**
 * Map a non-secure AV buffer handle to a process-local pointer for read/write access.
 *
 * @param handle  Buffer handle.
 * @param pptr    Double pointer that receives the mapped memory address on success.
 *
 * @returns HALError::SUCCESS               Memory buffer was mapped to process at ptr location.
 * @returns HALError::INVALID_ARGUMENT      Invalid buffer handle, secure buffer handle or NULL pptr.
 */
com::rdk::hal::HALError mapHandle(int64_t handle, void** pptr);

/**
 * Unmap a memory AV buffer pointer previously mapped by a call to mapHandle().
 *
 * @param handle Pointer to Handle structure.
 * @param ptr    Pointer that was previously mapped.
 * 
 * @returns HALError::SUCCESS               Memory buffer was unmapped.
 * @returns HALError::INVALID_ARGUMENT      Invalid buffer handle or pointer.
 */
com::rdk::hal::HALError unmapHandle(int64_t handle, void* ptr);

/**********************************************************************************/
/**********************************************************************************/
/**********************************************************************************/

/**
 * Writes a block of data to a memory block at a given offset.
 *
 * @param handle                Memory buffer handle.
 * @param targetBufferOffset    Byte offset into the memory buffer.
 * @param sourceData            Pointer to source data.
 * @param sourceDataBytes       Number of bytes to write.
 *
 * @retval HALError::SUCCESS            The write was successful.
 * @retval HALError::INVALID_ARGUMENT   Invalid memory buffer handle.
 * @retval HALError::OUT_OF_BOUNDS      The offset and/or data array size are out of bounds of the memory buffer.
 */
com::rdk::hal::HALError write(int64_t handle, size_t targetBufferOffset, void* sourceData, size_t sourceDataBytes);

/**
 * AV buffer offset and length range description structure type.
 */
typedef struct {
    size_t offset;
    size_t length;
} BufferRange_t;

/**
 * Copies one or more ranges of bytes between memory buffers.
 *
 * @param destinationHandle     Memory buffer handle.
 * @param sourceHandle          Memory buffer handle.
 * @param pBufferRanges         Pointer to array of offset and length range description objects.
 * @param arrSize               Array size.
 *
 * @retval HALError::SUCCESS            The copy was successful.
 * @retval HALError::INVALID_ARGUMENT   One or more invalid memory buffer handles.
 * @retval HALError::OUT_OF_BOUNDS      The offset and/or size are out of bounds of a memory buffer.
 */
com::rdk::hal::HALError copyWithMap(int64_t destinationHandle, int64_t sourceHandle, BufferRange_t* pBufferRanges, size_t arrSize);

}  // namespace avbuffer
}  // namespace hal
}  // namespace rdk
}  // namespace com

#endif // AVBUFFERHELPER_H
