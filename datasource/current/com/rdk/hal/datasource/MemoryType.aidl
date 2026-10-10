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
 *
 * SPDX-License-Identifier: Apache-2.0
 */
package com.rdk.hal.datasource;

/**
 * @brief    Backing and access discriminator for a data-source buffer.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * Selects how the bytes referenced by a BufferDescriptor are backed and how a
 * consumer may reach them. This is the single axis that lets one consumer path
 * accept a dma-buf on a target platform and a mappable segment on a reference
 * host without branching in consumer code.
 *
 * Prior art: Android BufferUsage flags, PipeWire spa_data.type
 * (MemFd/DmaBuf/MemId).
 */
@VintfStability
@Backing(type="int")
enum MemoryType {
    /**
     * POSIX shared memory / memfd. Any permitted process may mmap(2) the fd and
     * read/write the region directly at the plane offsets.
     */
    MAPPABLE = 0,

    /**
     * A dma-buf file descriptor. Imported by hardware / EGL / a downstream
     * device; the consumer may or may not CPU-map it depending on the negotiated
     * usage. Planes may share one fd at different offsets, or arrive as separate
     * fds.
     */
    DMABUF = 1,

    /**
     * A secure-opaque handle to memory that meets secure video / audio path
     * requirements. There is no mappable fd; the region is resolvable only by a
     * trusted entity (e.g. a trusted application or secure hardware peripheral).
     * The descriptor carries the handle, not a ParcelFileDescriptor.
     */
    SECURE_OPAQUE = 2,
}
