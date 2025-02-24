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
package com.rdk.hal.hdmioutput;
 
/** 
 *  @brief     HDMI Input Signal State enumeration.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Amit Patel
 */
 
@VintfStability
@Backing(type = "int")
enum SignalState
{
    /**
     * Unknown
     */
    UNKNOWN = 0x00,

    /**
     * @brief This enumeration defines the type of HDMI signal status.
     */
    typedef enum _dsHdmiInSignalStatus_t
{
    dsHDMI_IN_SIGNAL_STATUS_NONE = -1,    /*!< HDMI input signal status NONE. Default state upon start up */
    dsHDMI_IN_SIGNAL_STATUS_NOSIGNAL,     /*!< HDMI input No signal signal status. No device connected */
    dsHDMI_IN_SIGNAL_STATUS_UNSTABLE,     /*!< HDMI input unstable signal status. This is normally a transitional state,  */
    /*!< but can remain here due to some faults on HDMI Source / Cable */
    dsHDMI_IN_SIGNAL_STATUS_NOTSUPPORTED, /*!< HDMI input not supported signal status */
    /*!< e.g. The sink device does not support the incoming HDMI In signal from source */
    dsHDMI_IN_SIGNAL_STATUS_STABLE,       /*!< HDMI input Stable signal status are presented on plane */
    dsHDMI_IN_SIGNAL_STATUS_MAX           /*!< Out of range  */
} dsHdmiInSignalStatus_t;
}
