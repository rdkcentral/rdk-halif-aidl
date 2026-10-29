/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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

/*
 * Force-included (-include) into native host C++ builds by dev_env_guard.sh.
 *
 * The pinned Binder SDK's AOSP sources name uint8_t (libbase/hex.cpp) and
 * uintptr_t (utils/StrongPointer.h) without including <cstdint>. libstdc++
 * before 13 pulled it in transitively; gcc 13+ and clang on libstdc++ 13+
 * do not. Target builds use the Kirkstone toolchain and never see this file.
 *
 * It includes nothing: a forced <cstdint> would load glibc's features.h
 * before libbase/posix_strerror_r.cpp undefines _GNU_SOURCE, selecting the
 * wrong strerror_r. The aliases name the compiler's predefined types, so the
 * later <cstdint> declarations of the same names are valid redeclarations.
 */
#ifndef HALIF_HOST_STDINT_H
#define HALIF_HOST_STDINT_H

#ifdef __cplusplus
using uint8_t   = __UINT8_TYPE__;
using uintptr_t = __UINTPTR_TYPE__;
#endif

#endif /* HALIF_HOST_STDINT_H */
