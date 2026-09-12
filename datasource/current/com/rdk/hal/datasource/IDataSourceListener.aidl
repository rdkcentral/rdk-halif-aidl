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
 * @brief    Consumer callback interface for IDataSource.
 * @author   Gerald Weatherup
 *
 * Proposed data-source interface. See issue #668 and data_source.md for rationale.
 *
 * A wake-up channel so a consumer need not poll acquire(). Implementations may
 * coalesce onDataAvailable across several ready buffers. The callbacks report
 * readiness only; buffers are collected through IDataSource.acquire().
 */
@VintfStability
oneway interface IDataSourceListener {
    /**
     * Data is available to acquire.
     *
     * After this callback, the next acquire() with a size / count up to the
     * reported amount will not block.
     *
     * @param[in] available  STREAM: bytes ready to read. FRAMED: buffers ready.
     */
    void onDataAvailable(in long available);

    /**
     * The stream has ended; no further data will be produced.
     */
    void onEndOfStream();

    /**
     * An error occurred on the source.
     *
     * @param[in] code     Implementation-defined error code.
     * @param[in] message  Human-readable detail.
     */
    void onError(in int code, in String message);
}
