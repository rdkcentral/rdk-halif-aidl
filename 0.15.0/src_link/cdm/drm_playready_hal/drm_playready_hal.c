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

#include "drm_playready_platform.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "hal_utils.h"

// Private prototype for the AV Buffer Manager HAL implementation
int32_t avbConvertSecurePointerToHandle(void* f_ppbOpaqueClearContent);

// Initialize the DRM platform library
// Returns DRM_SUCCESS on success, DRM_E_FAIL on failure
DRM_RESULT drm_playready_platform_init()
{
    // PlayReady Platform Init
    LOG(eWarning, "PlayReady Platform Init\n");
    return DRM_SUCCESS;
}

// Deinitialize the DRM platform library
// Returns DRM_SUCCESS on success, DRM_E_FAIL on failure
DRM_RESULT drm_playready_platform_deinit()
{
    // PlayReady Platform Deinit
    LOG(eWarning, "PlayReady Platform Deinit\n");
    return DRM_SUCCESS;
}

// Proxy the DRM decrypt call
DRM_RESULT Drm_Reader_DecryptOpaque_Handle(DRM_DECRYPT_CONTEXT      *f_pDecryptContext,
                                           DRM_DWORD                 f_cEncryptedRegionMappings,
                                     const DRM_DWORD                *f_pdwEncryptedRegionMappings,
                                           DRM_UINT64                f_ui64InitializationVector,
                                           DRM_DWORD                 f_cbEncryptedContent,
                                     const DRM_BYTE                 *f_pbEncryptedContent,
                                           DRM_DWORD                *f_pcbOpaqueClearContent,
                                           DRM_INT32                *f_pHandle)
{
    DRM_RESULT              dr                          = DRM_SUCCESS;
    DRM_BYTE                **f_ppbOpaqueClearContent   = NULL;
    
    // PlayReady Decrypt Opaque Handle
    LOG(eTrace, "PlayReady Decrypt Opaque Handle\n");

    // Call the DRM decrypt method, the returned data will be in f_pbDecryptedData as a secure pointer
    dr = Drm_Reader_DecryptOpaque(f_pDecryptContext,
                                  f_cEncryptedRegionMappings,
                                  f_pdwEncryptedRegionMappings,
                                  f_ui64InitializationVector,
                                  f_cbEncryptedContent,
                                  f_pbEncryptedContent,
                                  f_pcbOpaqueClearContent,
                                  f_ppbOpaqueClearContent);

    // Convert the f_ppbOpaqueClearContent from a SoC implemenation of a 
    // secure pointer to a RDK AV buffer manager handle using this private function
    // avbConvertSecurePointerToHandle(f_ppbOpaqueClearContent);
    if(DRM_SUCCEEDED(dr) && f_ppbOpaqueClearContent != NULL) {
        *f_pHandle = avbConvertSecurePointerToHandle((void*)f_ppbOpaqueClearContent);
        if(*f_pHandle == -1) {
            LOG(eError, "avbConvertSecurePointerToHandle Failed\n");
            dr = DRM_S_FALSE;
        }
    }
    else {
        LOG(eError, "Drm_Reader_DecryptOpaque Failed\n");
        // Set the handle to -1 if the conversion fails
        *f_pHandle = -1;
    }

    return dr;
}
