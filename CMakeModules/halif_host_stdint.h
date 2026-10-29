/*
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
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * Force-included (-include) into native host C++ builds by dev_env_guard.sh.
 *
 * The pinned Binder SDK's AOSP sources use uint8_t / uintptr_t without
 * including <cstdint> (libbase/hex.cpp, utils/StrongPointer.h). libstdc++
 * before 13 pulled it in transitively; gcc 13+ and clang on libstdc++ 13+
 * do not. Target builds use the Kirkstone toolchain and never see this file.
 *
 * It includes nothing: a forced <cstdint> would load glibc's features.h
 * before libbase/posix_strerror_r.cpp undefines _GNU_SOURCE, selecting the
 * wrong strerror_r. The types come from the compiler's own predefined
 * macros, so a later <stdint.h> redeclares exactly the same typedefs.
 */
#ifndef HALIF_HOST_STDINT_H
#define HALIF_HOST_STDINT_H

typedef __INT8_TYPE__    int8_t;
typedef __INT16_TYPE__   int16_t;
typedef __INT32_TYPE__   int32_t;
typedef __INT64_TYPE__   int64_t;
typedef __UINT8_TYPE__   uint8_t;
typedef __UINT16_TYPE__  uint16_t;
typedef __UINT32_TYPE__  uint32_t;
typedef __UINT64_TYPE__  uint64_t;
typedef __INTPTR_TYPE__  intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

#endif /* HALIF_HOST_STDINT_H */
