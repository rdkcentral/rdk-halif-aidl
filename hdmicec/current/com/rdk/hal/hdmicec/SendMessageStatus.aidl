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
package com.rdk.hal.hdmicec;
 
/** 
 * @brief       Message status definitions returned from IHdmiCecController.sendMessage()
 * @author      Luc Kennedy-Lamb
 * @author      Peter Stieglitz
 * @author      Douglas Adler
 */
 
@VintfStability
@Backing(type="int")
enum SendMessageStatus 
{
    /**
     * The SendMessageStatus indicates the state of the message transmission by reporting
     * CEC line arbitration and, if successful, the state of the ACK bit for last header/data block transmission.
     * To understand the meaning of the SendMessageStatus values, please refer to
     * HDMI Specification 1.4b, Section CEC 6.1.2 "ACK (Acknowledge)".
     */

    /**
     * Directly Addressed Message: The message was sucessfully acknowledged by the directly addressed follower.
     * Broadcast Message: One or more devices rejected the message.
     *                    At least one retransmission was attempted.
     */
    ACK_STATE_0 = 0, 

    /**
     * Directly Addressed Message: The message was not acknowledged by the directly addressed follower.
     *                             At least one retransmission was attempted.
     * Broadcast Message: The message was sent and not rejected by any device.
     */  
    ACK_STATE_1 = 1,

    /**
     * CEC line arbitration, after two attempts, failed. The message was not sent.
     */  
    BUSY = 2
}
