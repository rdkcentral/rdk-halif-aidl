/**
 *  If not stated otherwise in this file or this component's LICENSE
 *  file the following copyright and licenses apply:
 *
 *  Copyright 2025 RDK Management
 *
 *  Licensed under the Apache License, Version 2.0 (the License);
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an AS IS BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _AVBUFFERHELPER_H_
#define _AVBUFFERHELPER_H_

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#include <cstdint>

using namespace std;

/**
 * @brief Vendors shall provide the AV Buffer Helper implementation as libavbufferhelper.so.
 *
 * The middleware uses this predefined library name for dynamic loading, eliminating the need for
 * vendor-specific handling and avoiding build-time dependencies.
 */

class IAVBufferHelper
{
public:
    struct CopyMap {
        uint32_t src_offset;
        uint32_t dst_offset;
        uint32_t size;
    };


    // helper functions for mapping and unmapping memory from handles
    // used in the client code outside of the LinearBufferMgr class
    /**
     * @brief Map memory from the given handle.
     * @param handle The handle to map memory from.
     * @param[out] size The size of the mapped data
     */
    virtual void* mapHandle(uint64_t handle, uint32_t * size) = 0;

    /**
     * @brief Unmap memory from the given handle.
     * @param handle The handle to unmap memory from.
     * @return True if the memory was successfully unmapped, false otherwise.
     */
    virtual bool unmapHandle(uint64_t handle) = 0;

    /**
     * @brief Get the size of the memory mapped to the given handle.
     * @param handle The handle to get the size from.
     * @return The size of the memory mapped to the handle.
     */
    virtual uint32_t getAllocationSize(uint64_t handle) = 0;

    /**
     * @brief Write data from unsecure memory into a secure buffer.
     * @param handle The handle to write data into.
     * @param data The data to write.
     * @param size The size of the data to write.
     *
     * @return True if the data was successfully written, false otherwise.
     */
    virtual bool writeSecureHandle(uint64_t handle, void* data, uint32_t size) { return false; }

    /**
     * @brief Copy data from one secure buffer to another.
     * @param handleTo The handle to copy data to.
     * @param handleFrom The handle to copy data from.
     * @param CopyMap The map of offsets and sizes to copy.
     * @param mapSize The number if indexes in the map.
     *
     * @return True if the data was successfully copied, false otherwise.
     */
    virtual bool copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, CopyMap map, uint32_t mapSize) { return false; }
};

#ifdef __cplusplus
extern "C" {
#endif

// Factory function to acquire the AVBufferHelper singleton instance.
// This API returns the singleton AVBufferHelper instance and increments
// the internal reference count. The caller must invoke
// releaseAVBufferHelperInstance() when the instance is no longer needed.
IAVBufferHelper* getAVBufferHelperInstance();

// Factory function to release the AVBufferHelper singleton instance.
// This API decrements the internal reference count. The singleton instance
// shall be destroyed only when the reference count reaches zero.
// The caller must not directly delete the returned IAVBufferHelper instance.
void releaseAVBufferHelperInstance(IAVBufferHelper* instance);

#ifdef __cplusplus
}
#endif

#endif //_AVBUFFERHELPER_H_
