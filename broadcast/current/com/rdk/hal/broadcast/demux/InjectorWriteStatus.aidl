/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2025 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */
package com.rdk.hal.broadcast.demux;

/**
 * Result status of a software injector write operation.
 *
 * @see IDataFromSoftwareInjector.write()
 */
@VintfStability
@Backing(type = "int")
enum InjectorWriteStatus {
    /** Default initialisation value. */
    UNDEFINED = 0,
    /** All supplied data was written successfully. */
    SUCCESS,
    /** Buffer had insufficient space; only a partial write occurred. */
    NOT_ENOUGH_SPACE,
    /**
       The timeout elapsed before all data could be written; only a partial write
       may have occurred.
     */
    TIMEOUT,
    /**
       The write was aborted via abort(); only a partial write may have occurred.
     */
    ABORTED,
    /** Another thread is already blocked in write(). No data was written. */
    BUSY,
    /**
       An unexpected internal error occurred. Only a partial write may have
       occurred.
     */
    ERROR,
}
