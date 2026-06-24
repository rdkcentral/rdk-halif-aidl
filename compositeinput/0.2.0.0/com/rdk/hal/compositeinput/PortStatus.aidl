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
 */

package com.rdk.hal.compositeinput;

import com.rdk.hal.compositeinput.Port;
import com.rdk.hal.compositeinput.SignalStatus;
import com.rdk.hal.compositeinput.VideoResolution;

/**
 * @brief Current status of a composite input port.
 *
 * Lean polled snapshot of the basic connectivity, signal, and video mode
 * state. Returned by ICompositeInputPort.getStatus() in a single IPC call.
 *
 * Extended status (signal quality, signal strength) and telemetry metrics
 * are accessed via ICompositeInputPort.getProperty() using PortProperty
 * keys — this avoids duplicating data across two read paths.
 */
@VintfStability
parcelable PortStatus
{
    /** Port ID (0 to maxPorts-1). */
    int portId;

    /** True if a physical cable/source is connected to this port. */
    boolean connected;

    /** True if this port is currently active for presentation. */
    boolean active;

    /** Current signal status. */
    SignalStatus signalStatus;

    /** Detected video resolution and format, or null if no signal. */
    @nullable VideoResolution detectedResolution;
}
