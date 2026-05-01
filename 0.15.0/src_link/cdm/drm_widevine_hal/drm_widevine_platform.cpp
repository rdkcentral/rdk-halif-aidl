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

#include "drm_widevine_platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hal_utils.h"


// Private prototype for the AV Buffer Manager HAL implementation
void* avbConvertHandleToSecurePointer(int32_t handle);

// Widevine platform constructor
WidevinePlatformDRM::WidevinePlatformDRM(widevine::Cdm* cdm)
{
    LOG(eWarning, "WidevinePlatformDRM Constructor\n");

    // Initialize the widevine platform

}

// Widevine platform destructor
WidevinePlatformDRM::~WidevinePlatformDRM()
{
    LOG(eWarning, "WidevinePlatform Destructor\n");

    // Deinitialize the widevine platform

}

// Decrypt Proxy
widevine::Cdm::Status WidevinePlatformDRM::decryptWithHandle(int32_t handle, const widevine::Cdm::DecryptionBatch& batch)
{
    LOG(eTrace, "WidevinePlatformDRM::decryptWithHandle\n");

    // Convert Handle to SoC specific secure memory pointer
    void* secure_memory = avbConvertHandleToSecurePointer(handle);
    if(secure_memory == NULL) {
        LOG(eError, "WidevinePlatformDRM::decryptWithHandle - Error converting handle to secure memory\n");
        return widevine::Cdm::kTypeError;
    }

    batch.samples[0].output.data = secure_memory;
    batch.samples[0].output.data_length = batch.samples[0].input.data_length;
    batch.samples[0].output.data_offset = 0;

    // Decrypt the data using the widevine platform
    return _cdm->decrypt(batch);
}

// Decrypt Proxy
widevine::Cdm::Status WidevinePlatformDRM::decryptWithHandle(int32_t handle, const std::string& session_id, const widevine::Cdm::DecryptionBatch& batch)
{
    LOG(eTrace, "WidevinePlatformDRM::decryptWithHandle(2)\n");
    
    // Convert Handle to SoC specific secure memory pointer
    void* secure_memory = avbConvertHandleToSecurePointer(handle);
    if(secure_memory == NULL) {
        LOG(eError, "WidevinePlatformDRM::decryptWithHandle(session_id) - Error converting handle to secure memory\n");
        return widevine::Cdm::kTypeError;
    }

    batch.samples[0].output.data = secure_memory;
    batch.samples[0].output.data_length = batch.samples[0].input.data_length;
    batch.samples[0].output.data_offset = 0;
    
    // Decrypt the data using the widevine platform
    return _cdm->decrypt(session_id, batch);
}