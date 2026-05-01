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
import android.hardware.common.fmq.MQDescriptor;
import android.hardware.common.fmq.SynchronizedReadWrite;
import com.rdk.hal.broadcast.demux.DataPacket;

/**
 *  @brief     Struct representing a software source
 *  @author    Jan Pedersen
 *  @author    Christian George
 *  @author    Philipp Trommler 
 */

/**
 * Upon receiving this struct, the software sink is supposed to duplicate and mmap the shared memory
 * file descriptor and to listen to the provided fast message queue. When the sink is closed or if
 * for any other reason the sink will no longer read from the filter, the file descriptor should be
 * closed, the memory unmapped and the message queue disposed.
 */
@VintfStability
parcelable SoftwareSink {
    /** Plain ID type */
    @VintfStability
    parcelable Id {
        /** The actual ID */
        long value;
    }

    /**
     * The software sink's ID
     *
     * This can be used to unregister the sink at the filter.
     */
    Id id;

    /**
     * The message queue
     *
     * Over this queue messages about data being available to read will be sent. Since the queue is
     * synchronized, it has to be read by the software sink in order to avoid blocking the filter.
     */
    MQDescriptor<DataPacket, SynchronizedReadWrite> mqDesc;

    /** File descriptor for the shared memory */
    ParcelFileDescriptor fd;
}
