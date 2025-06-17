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
#include "VendorPlatformBufferOps.hpp"

/**
 * @file VendorPlatformBufferOps.cpp
 * @brief Stub file for vendor-specific buffer operations implementation.
 *
 * This file provides stub implementations of the VendorPlatformBufferOps methods.
 * VENDORS ARE EXPECTED TO REPLACE THESE WITH ACTUAL HARDWARE-SPECIFIC LOGIC.
 *
 * These functions define how memory handles are mapped, unmapped, and managed
 * in a secure and platform-specific way, often involving DRM or secure memory.
 */

void *VendorPlatformBufferOps::mapHandle(uint64_t handle, uint32_t *size)
{
    *size = 0;
    return nullptr; // Vendor must implement actual memory mapping.
}

int VendorPlatformBufferOps::unmapHandle(uint64_t handle)
{
    return 0; // Vendor must implement unmapping logic.
}

int VendorPlatformBufferOps::writeSecure(uint64_t handle, const void *data, uint32_t size)
{
    return 0; // Vendor must implement secure write.
}

int VendorPlatformBufferOps::copySecure(uint64_t to, uint64_t from, uint32_t srcOff, uint32_t dstOff, uint32_t size)
{
    return 0; // Vendor must implement secure copy logic.
}
