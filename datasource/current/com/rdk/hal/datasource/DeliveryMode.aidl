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
 * @brief    How a data source delivers regions to its consumer.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * The one field that distinguishes a byte-stream ring from a framed buffer pool
 * — the difference between IRingBuffer and ICapture — without a separate
 * interface for each.
 */
@VintfStability
@Backing(type="int")
enum DeliveryMode {
    /**
     * Byte-window delivery over a contiguous backing. acquire() returns a region
     * of the requested size; release() may release a prefix of it, advancing the
     * read position. Buffers carry no meta. This is the IRingBuffer shape.
     */
    STREAM = 0,

    /**
     * Whole-buffer delivery from a set of slots. acquire() returns one complete,
     * self-describing buffer (planes + meta); release() returns that slot for
     * reuse. This is the ICapture / decoder-output shape.
     */
    FRAMED = 1,
}
