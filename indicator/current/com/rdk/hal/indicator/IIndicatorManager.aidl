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
package com.rdk.hal.indicator;
import com.rdk.hal.indicator.IIndicator;

/**
 * @brief Indicator Manager HAL interface.
 *
 * Provides management and discovery of indicator instances. This interface enables
 * multi-instance support, allowing platforms to expose multiple independent indicator
 * resources. For RDK reference implementations, typically a single global indicator
 * instance is provided that reflects the overall device state.
 *
 * Third-party vendors may extend this to support multiple indicators if their platform
 * architecture requires independent indicator control (e.g., per-zone indicators).
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */

@VintfStability
interface IIndicatorManager
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "indicator";

    /**
     * Gets the list of platform indicator IDs.
     *
     * For RDK reference implementations, this typically returns a single global indicator ID.
     * Third-party vendors may return multiple IDs if their platform supports independent
     * indicator instances.
     *
     * @returns IIndicator.Id[] array of available indicator instance IDs.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    IIndicator.Id[] getIndicatorIds();

    /**
     * Gets the indicator interface for a given ID.
     *
     * @param[in] indicatorId The ID of the indicator resource.
     * @returns IIndicator interface or null on invalid indicator ID.
     * @exception binder::Status::Exception::EX_NONE for success.
     */
    @nullable IIndicator getIndicator(in IIndicator.Id indicatorId);
}
