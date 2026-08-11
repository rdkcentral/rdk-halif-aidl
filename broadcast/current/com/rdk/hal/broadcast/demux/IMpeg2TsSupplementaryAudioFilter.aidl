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

import com.rdk.hal.broadcast.demux.Pid;

/**
 * MPEG-2 TS supplementary audio filter interface for tunneled pipelines.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IMpeg2TsSupplementaryAudioFilter {
    /**
     * Set the PID containing the PCR values to be used for supplementary audio data.
     *
     * Setting a PID will activate the filter, i.e. it will potentially start outputting data instantly.
     *
     * @param pid The PID containing the PCR values.
     */
    void setPid(in Pid pid);

    /** Reset the PID containing the PCR values, effectively stopping the filter. */
    void clearPid();
}
