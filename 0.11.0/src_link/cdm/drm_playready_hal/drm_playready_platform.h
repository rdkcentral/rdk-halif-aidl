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


// Header file for DRM Platform library to initialize and terminate the 
// specific DRM implementation (Widevine, PlayReady, etc.) and to provide
// a decrypt interface that converts RDK secure handles into platform specific
// secure memory pointers
#include <stdlib.h>

#if !(defined (__x86_64__) || defined (__i386__))
#include <drmmanager.h>    // Playready header file
#else 

typedef unsigned char           DRM_BYTE;               /* 1 byte  */
typedef unsigned short          DRM_WORD;               /* 2 bytes */
typedef unsigned long           DRM_DWORD;              /* 4 bytes */
typedef unsigned long           DRM_INT32;              /* 4 bytes */
typedef unsigned long long      DRM_UINT64;             /* 8 bytes */
typedef long long               DRM_INT64;              /* 8 bytes */
typedef long                    DRM_LONG;               /* 4 bytes */
typedef void                    DRM_VOID;               /* void    */

#define __in
#define __in_ecount(x)
#define __in_bcount(x)
#define __out
#define __deref_out_bcount(x)


#ifndef DRM_RESULT_DEFINED
#define DRM_RESULT_DEFINED
typedef DRM_LONG  DRM_RESULT;
#endif /*DRM_RESULT_DEFINED*/

#define DRM_SUCCESS                      ((DRM_RESULT)0x00000000L)
#define DRM_S_FALSE                      ((DRM_RESULT)0x00000001L)

#define DRM_FAILED(Status)               ((DRM_RESULT)(Status)<0)
#define DRM_SUCCEEDED(Status)            ((DRM_RESULT)(Status) >= 0)

typedef struct __tagDRM_CIPHER_CONTEXT
{
    // Fake structure definition to allow compilation
    DRM_VOID                *pFuncTbl;
} DRM_CIPHER_CONTEXT;

typedef struct
{
    DRM_BYTE rgbBuffer[ sizeof( DRM_CIPHER_CONTEXT ) ];
} DRM_DECRYPT_CONTEXT;

DRM_RESULT Drm_Reader_DecryptOpaque(
    __in                                            DRM_DECRYPT_CONTEXT      *f_pDecryptContext,
    __in                                            DRM_DWORD                 f_cEncryptedRegionMappings,
    __in_ecount( f_cEncryptedRegionMappings ) const DRM_DWORD                *f_pdwEncryptedRegionMappings,
    __in                                            DRM_UINT64                f_ui64InitializationVector,
    __in                                            DRM_DWORD                 f_cbEncryptedContent,
    __in_bcount( f_cbEncryptedContent )       const DRM_BYTE                 *f_pbEncryptedContent,
    __out                                           DRM_DWORD                *f_pcbOpaqueClearContent,
    __deref_out_bcount( *f_pcbOpaqueClearContent )  DRM_BYTE                **f_ppbOpaqueClearContent
    );


// Stub Implementation of the Playready Decrypt function
DRM_RESULT Drm_Reader_DecryptOpaque(
    __in                                            DRM_DECRYPT_CONTEXT      *f_pDecryptContext,
    __in                                            DRM_DWORD                 f_cEncryptedRegionMappings,
    __in_ecount( f_cEncryptedRegionMappings ) const DRM_DWORD                *f_pdwEncryptedRegionMappings,
    __in                                            DRM_UINT64                f_ui64InitializationVector,
    __in                                            DRM_DWORD                 f_cbEncryptedContent,
    __in_bcount( f_cbEncryptedContent )       const DRM_BYTE                 *f_pbEncryptedContent,
    __out                                           DRM_DWORD                *f_pcbOpaqueClearContent,
    __deref_out_bcount( *f_pcbOpaqueClearContent )  DRM_BYTE                **f_ppbOpaqueClearContent
    )
{
    *f_pcbOpaqueClearContent = 0;
    *f_ppbOpaqueClearContent = (DRM_BYTE*)NULL;

    // Stub implementation of the Playready Decrypt function
    return DRM_SUCCESS;
}
#endif

// Initialize the DRM platform library
// Returns DRM_SUCCESS on success, DRM_E_FAIL on failure
DRM_RESULT drm_playready_platform_init();

// Terminate the DRM platform library
// Returns DRM_SUCCESS on success, DRM_E_FAIL on failure
DRM_RESULT drm_playready_platform_term();

// Convert RDK secure handle to platform specific secure memory pointer and
// call the DRM specific decrypt function

// This function mimics the decrypt function in the Playready CDM API and converts
// the RDK secure handle to a platform specific secure memory pointer before
// calling the Playready decrypt function
DRM_RESULT Drm_Reader_DecryptOpaque_Handle(
    __in                                            DRM_DECRYPT_CONTEXT      *f_pDecryptContext,
    __in                                            DRM_DWORD                 f_cEncryptedRegionMappings,
    __in_ecount( f_cEncryptedRegionMappings ) const DRM_DWORD                *f_pdwEncryptedRegionMappings,
    __in                                            DRM_UINT64                f_ui64InitializationVector,
    __in                                            DRM_DWORD                 f_cbEncryptedContent,
    __in_bcount( f_cbEncryptedContent )       const DRM_BYTE                 *f_pbEncryptedContent,
    __out                                           DRM_DWORD                *f_pcbOpaqueClearContent,
    __out                                           DRM_INT32                *f_pHandle             // RDK secure handle
    );