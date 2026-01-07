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

/**
 *  @brief     DataPacket 
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/** Struct representing data to be read in shared memory */
@VintfStability
parcelable DataPacket {
    /** Plain ID type */
    @VintfStability
    parcelable Id {
        /** The actual ID */
        long value;
    }

    /**
     * Packet ID
     *
     * This will eventually wrap. But so seldom that it should pose no problem.
     */
    Id id;
    /** The offset of the data into the shared memory in bytes */
    long offset;
    /** The length of the data in bytes */
    long size;
}
