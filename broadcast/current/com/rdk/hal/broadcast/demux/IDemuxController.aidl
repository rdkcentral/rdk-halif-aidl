/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast.demux;

import com.rdk.hal.broadcast.demux.Filter;
import com.rdk.hal.broadcast.demux.FilterParameters;

/**
 * Interface for an opened demux.
 *
 * Grants exclusive access to the demux and allows opening and closing of filters. See IFrontendController for the
 * details on what this means in terms of synchronization requirements.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IDemuxController {
    /**
     * Open a filter for the given filter type.
     *
     * The returned union contains exactly one active member, representing the concrete type-specific filter interface.
     *
     * @exception ::android::binder::Status::EX_UNSUPPORTED_OPERATION The demux does not support the given filter type.
     * @exception ::android::binder::Status::EX_ILLEGAL_STATE The demux can not provide any more filters of the given
     *                                                        filter type.
     *
     * @param[in] parameters The parameters of the filter to create. The actual filter type to be returned is determined
     *                       by the type of the filter parameters.
     */
    @nullable Filter openFilter(in FilterParameters parameters);

    /**
     * Closes the given filter.
     *
     * The filter object will be invalidated. The call to closeFilter() will stop the filter.
     *
     * @exception ::android::binder::Status::EX_ILLEGAL_ARGUMENT The filter was not opened on this demux.
     */
    void closeFilter(in Filter filter);
}
