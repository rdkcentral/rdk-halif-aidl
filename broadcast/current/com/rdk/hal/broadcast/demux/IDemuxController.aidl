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
package com.rdk.hal.broadcast.demux;
import com.rdk.hal.broadcast.demux.FilterType;
import com.rdk.hal.broadcast.demux.IFilter;

/**
 * @brief Interface for demux controller
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IDemuxController {
    /**
     * Get a filter for the given filter type.
     *
     * The returned filters are not active by default. The filter has to be configured with
     * one or more PIDs to enable it.
     *
     * @param[in] filterType    The type of filter to create.
     *
     * @returns IFilter or null on error (e.g. no filter available for the given type).
     */
    @nullable IFilter openFilter(in FilterType filterType);

    /**
     * Closes the given filter. The Filter object will be invalidated.
     *
     * @param[in] filter    The filter to close.
     *
     * @exception binder::Status EX_ILLEGAL_STATE if the filter has not been stopped.
     *
     * @pre The filter must have been stopped by calling IFilter.stop() before calling this method.
     *
     * @see IFilter.stop()
     */
    void closeFilter(in IFilter filter);
}
