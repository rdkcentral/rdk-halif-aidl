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
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.hdmioutput;

import com.rdk.hal.hdmioutput.PlatformCapabilities;
import com.rdk.hal.hdmioutput.IHDMIOutput;

/**
 *  @brief     HDMI Output Manager HAL interface.
 *
 *  Responsible for HDMI output resource discovery and platform-wide feature exposure.
 *  The manager serves as the entry point for clients to enumerate and obtain handles
 *  to HDMI output ports and retrieve static platform-level capabilities.
 *
 *  This interface must remain stable and query-safe regardless of runtime HDMI activity.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
@VintfStability
interface IHDMIOutputManager
{
    /**
     * The systemd/Binder service name for this HAL service.
     *
     * Returned by the implementation via `getServiceName()` and used for
     * registration and discovery in the AIDL Binder service manager.
     */
    const @utf8InCpp String serviceName = "HDMIOutputManager";

    /**
     * Gets the static platform capabilities for HDMI outputs.
     *
     * This describes global support across all HDMI ports, such as max resolution,
     * HDR formats, and FreeSync tiers. The result is immutable and cached.
     *
     * This can be safely called before any HDMI output instance is opened.
     *
     * @returns PlatformCapabilities
     */
    PlatformCapabilities getCapabilities();

    /**
     * Enumerates available HDMI output IDs on the platform.
     *
     * This list provides the logical identifiers needed to call `getHDMIOutput()`.
     * Each returned ID is guaranteed to be valid unless the underlying resource
     * becomes unavailable (e.g., hot-removed HDMI transmitters in some systems).
     *
     * @returns IHDMIOutput.Id[]  Array of valid HDMI output identifiers.
     */
    IHDMIOutput.Id[] getHDMIOutputIds();

    /**
     * Retrieves a HDMI output instance associated with a given ID.
     *
     * The returned interface represents a client-specific connection to a port.
     * The output must be explicitly opened using `IHDMIOutput.open()` before it
     * enters an active state. Multiple clients may query the same ID, but only
     * one may successfully open a session at a time.
     *
     * @param[in] hdmiOutputId  ID of the HDMI output to access.
     *
     * @returns IHDMIOutput
     * @retval null  The ID was invalid or the resource is unavailable.
     *
     * @see IHDMIOutput
     */
    @nullable IHDMIOutput getHDMIOutput(in IHDMIOutput.Id hdmiOutputId);
}
