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

#ifndef _AVBUFFERHELPER_CWRAPPER_H_
#define _AVBUFFERHELPER_CWRAPPER_H_

#include "IAVBufferHelper.hpp" // Inherits from this interface

/**
 * @class AVBufferHelperCWrapper
 * @brief Concrete C++ implementation of IAVBufferHelper that wraps a C API.
 *
 * This class provides the default implementation for IAVBufferHelper by delegating
 * all calls to the underlying C functions defined in avbuffer_c_api.h.
 * It is implemented as a C++ singleton to provide a single point of access
 * to the C-based buffer helper functionality.
 */
class AVBufferHelperCWrapper : public IAVBufferHelper
{
public:
    /**
     * @brief Provides access to the singleton instance of AVBufferHelperCWrapper.
     *
     * This is the standard way to get the single instance of this concrete class.
     *
     * @return A reference to the singleton AVBufferHelperCWrapper instance.
     */
    static AVBufferHelperCWrapper& getInstance();

    // Implementations of the pure virtual methods from IAVBufferHelper
    // These methods will call the corresponding C functions.

    void *mapHandle(uint64_t handle, uint32_t *size) override;
    bool unmapHandle(uint64_t handle) override;
    bool writeSecureHandle(uint64_t handle, const void *data, uint32_t size) override;
    bool copySecureHandleWithMap(uint64_t handleTo, uint64_t handleFrom, const CopyMap& map) override;

private:
    // Private constructor, copy constructor, and assignment operator
    // to enforce the singleton pattern.
    AVBufferHelperCWrapper() = default;
    ~AVBufferHelperCWrapper() = default;
    AVBufferHelperCWrapper(const AVBufferHelperCWrapper&) = delete;
    AVBufferHelperCWrapper& operator=(const AVBufferHelperCWrapper&) = delete;
};

#endif // _AVBUFFERHELPER_CWRAPPER_H_