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

import com.rdk.hal.AVSource;
import com.rdk.hal.datasource.BufferDescriptor;
import com.rdk.hal.datasource.DeliveryMode;
import com.rdk.hal.datasource.MemoryType;
import com.rdk.hal.datasource.MemoryStats;
import com.rdk.hal.datasource.IDataSourceListener;

/**
 * @brief    Common consumer contract for reading from a data source.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * One interface that a file source, a broadcast demux filter, a software
 * injector, a capture ring or a decoder output can all present, so consumer
 * code reads any of them through the same acquire / release lifecycle over a
 * negotiated, typed BufferDescriptor.
 *
 * Lifecycle: configure() -> start() -> (acquire() / release())* -> stop().
 *
 * Negotiation resolves the memory type and delivery mode both ends support, so
 * the same consumer code accepts a dma-buf on a target platform and a mappable
 * segment on a reference host. An implementation is free to pass the backing
 * fd once at configure() and run the steady acquire / release loop as shared
 * index updates, keeping the per-buffer path off binder.
 *
 * Prior art: PipeWire node output port, Android BufferQueue consumer, GStreamer
 * source pad.
 */
@VintfStability
interface IDataSource {
    /**
     * Declares the memory types this consumer can accept, as a bitmask of
     * (1 << MemoryType). The source intersects it with what it can produce and
     * fixes the choice for the session.
     *
     * @param[in] acceptedMemoryTypeMask  OR of (1 << MemoryType) values.
     * @param[in] mode                    Requested delivery mode.
     * @param[in] listener                Readiness / error callbacks.
     * @return    The MemoryType selected for the session.
     */
    MemoryType configure(in int acceptedMemoryTypeMask, in DeliveryMode mode, in IDataSourceListener listener);

    /**
     * Classifies where the stream originates (IP, TUNER, SYSTEM, HDMI, ...).
     *
     * @return  The AVSource of this data source.
     */
    AVSource getSource();

    /**
     * Begins production. After start(), the source delivers data and raises
     * IDataSourceListener.onDataAvailable().
     */
    void start();

    /**
     * Stops production. Outstanding acquired buffers must be released. A stopped
     * source may be started again.
     */
    void stop();

    /**
     * Acquires the next available data.
     *
     * STREAM: returns a descriptor whose single plane addresses up to `size`
     * bytes at the current read position.
     * FRAMED: `size` is ignored; returns the next ready buffer (planes + meta).
     *
     * Blocks until data is available, or returns a null descriptor immediately
     * when the source is configured non-blocking and nothing is ready.
     *
     * @param[in] size  STREAM: requested byte count. FRAMED: ignored.
     * @return          The acquired buffer, or null when nothing is ready.
     */
    @nullable BufferDescriptor acquire(in long size);

    /**
     * Releases a previously acquired buffer back to the source.
     *
     * STREAM: `size` may be less than the acquired size to release a prefix and
     * advance the read position by that amount.
     * FRAMED: `size` is ignored; the whole slot is returned for reuse.
     *
     * @param[in] descriptor  A descriptor returned by acquire().
     * @param[in] size        STREAM: bytes to release. FRAMED: ignored.
     */
    void release(in BufferDescriptor descriptor, in long size);

    /**
     * Unblocks a thread waiting in acquire() (e.g. during teardown). Has no
     * effect when no call is blocked or the source is non-blocking.
     */
    void abortAcquire();

    /**
     * Returns the current memory accounting for this source's buffer pool.
     *
     * Because each consumer holds its own IDataSource, the snapshot is
     * attributable to one consumer — enough to make pipeline memory usage
     * visible and a leak (buffers reserved but never released) traceable to
     * its owner. Callable in any state; before configure() the pool is empty
     * and all counts are 0.
     *
     * @return  A MemoryStats snapshot of the pool.
     */
    MemoryStats getMemoryStats();
}
