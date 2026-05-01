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

#if !(defined (__x86_64__) || defined (__i386__))
#include <cdm.h>    // Widevine CDM header file
#else
#include <string>
namespace widevine {
    class Cdm {
    public:
        enum Status {
            kSuccess = 0,
            kTypeError = 1,
        };

        struct InputBuffer {
        public:
            InputBuffer() : data(nullptr), data_length(0) {}
        
            const uint8_t* data;
            uint32_t data_length;

        };

        struct OutputBuffer {
        public:
            OutputBuffer() : data(nullptr), data_offset(0), data_length(0) {}

            void* data;
            uint32_t data_offset;
            uint32_t data_length;
        };

        struct Sample {
        public:
            Sample() : input(), output() {}

            // These structs describe the protected input data of the sample and the
            // output buffer that decrypted data should be written to.
            InputBuffer input;
            OutputBuffer output;
        };

        struct DecryptionBatch {
            // Fake structure definition to allow compilation
            public:
            DecryptionBatch() 
            : samples(nullptr)
            , samples_length(0)
            {
            }

            Sample* samples;
            uint32_t samples_length;
        };

        Cdm() {}
        virtual ~Cdm() {}

        virtual Status decrypt(const DecryptionBatch& batch) {
            return kSuccess;
        };
        virtual Status decrypt(const std::string& session_id,
                               const DecryptionBatch& batch) {
            return kSuccess;
        };

    };
}; // namespace widevine


#endif


class WidevinePlatformDRM {
public:
    // Initialize the DRM platform library
    WidevinePlatformDRM(widevine::Cdm* cdm);

    // Terminate the DRM platform library
    ~WidevinePlatformDRM();


    // Convert RDK secure handle to platform specific secure memory pointer and
    // call the DRM specific decrypt function

    // This function mimics the decrypt function in the Widevine CDM API and converts
    // the RDK secure handle to a platform specific secure memory pointer before
    // calling the Widevine CDM decrypt function
    widevine::Cdm::Status decryptWithHandle(int32_t handle, const widevine::Cdm::DecryptionBatch& batch);

    // This function mimics the decrypt function in the Widevine CDM API and converts
    // the RDK secure handle to a platform specific secure memory pointer before
    // calling the Widevine CDM decrypt function
    widevine::Cdm::Status decryptWithHandle(int32_t handle, const std::string& session_id, const widevine::Cdm::DecryptionBatch& batch);

private:
    widevine::Cdm* _cdm;

};