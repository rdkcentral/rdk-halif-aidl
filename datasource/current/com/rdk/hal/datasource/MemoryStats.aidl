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
 * @brief    Memory accounting for the buffers a data source has allocated.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * A snapshot of the backing memory reserved for this source's buffer pool,
 * read via IDataSource.getMemoryStats(). Because each consumer holds its own
 * IDataSource, the snapshot is per-source and therefore attributable to one
 * consumer — the unit needed to make pipeline memory usage visible and a leak
 * (buffers reserved but never released) traceable to its owner.
 *
 * Counts are steady-state pool figures, not per-acquire deltas: they cover the
 * backings exchanged at configure() plus any grown since, independent of how
 * many buffers are currently acquired.
 *
 * Prior art: PipeWire node buffer accounting, Android gralloc allocation
 * counters exposed through dumpsys meminfo.
 */
@VintfStability
parcelable MemoryStats {
    /**
     * Total backing memory reserved for this source's buffer pool, in bytes —
     * the sum across all `fds` / `handles` backings, mappable and secure alike.
     */
    long allocatedBytes;

    /**
     * Subset of `allocatedBytes` currently mapped into the consumer process,
     * in bytes. 0 for a SECURE_OPAQUE session, which is never mapped into an
     * unprivileged process (HAL.DSRC.4).
     */
    long mappedBytes;

    /** Number of buffers in the pool. */
    int bufferCount;

    /** Number of those buffers currently acquired by the consumer. */
    int acquiredCount;
}
