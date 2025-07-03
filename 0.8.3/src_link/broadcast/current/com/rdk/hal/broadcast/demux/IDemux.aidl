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
import com.rdk.hal.broadcast.demux.SoftwareSource;
import com.rdk.hal.broadcast.frontend.IFrontend;

/**
 *  @brief     Interface for a demux. 
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */


@VintfStability
interface IDemux {
    /**
     * The IDemux interface shall be a light-weight wrapper for a demux. Either connected to a hardware
     * frontend or a demux for software write.
     *
     * Before this can be operational a source must be set by calling @ref IDemux::setSource().
     */ 
    
    @VintfStability
    union SourceType {
        /** A vendor-layer frontend as the source */
        IFrontend frontendSource;
        /** A pure software source, fed by the userspace code */
        SoftwareSource softwareSource;
    }

    /** Set the specified source type as the source for this demux */
    void setSource(in SourceType sourceType);

    /** Create a filter of the specified type */
    IFilter openFilter(in FilterType filterType);

    /**
     * Close the demux
     *
     * After calling this the demux is no longer valid.
     */
    void close();
}
