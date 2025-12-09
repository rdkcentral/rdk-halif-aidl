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

@VintfStability
@Backing(type="int")
enum Property 
{
    /**
     * CEC version supported by the HAL and HW.
     *
     * A byte value representing the CEC version supported by the HW and SW HAL implementation.
     * The value complies with the encoding used by the [CEC Version] CEC operand described in the appropriate HDMI specification.
     *
     * Please note that this value is NOT transmitted or obtained over the CEC bus. It is statically defined by the implementation.
     *
     * Type: Byte - 8-bit integer value.
     * Access: Read-only.
     */
    HAL_CEC_VERSION = 0,

    /**
     * Returns the total number of Directed CEC messages sent since open.
     * -1 means this metric is not yet implemented by the vendor.
     * 
     * If this property is read in the CLOSED state it will report 0.
     *
     * Type: Int - 32-bit signed integer value.
     * Access: Read-only.
     *
     */
    METRIC_DIRECTED_MESSAGES_SENT = 1000,

    /**
     * Returns the number of Broadcast CEC messages sent since open.
     * -1 means this metric is not yet implemented by the vendor.
     * 
     * If this property is read in the CLOSED state it will report 0.
     *
     * Type: Int - 32-bit signed integer value.
     * Access: Read-only.
     *
     */
    METRIC_BROADCAST_MESSAGES_SENT = 1001,

    /**
     * Returns the total number of Directed CEC messages sent and acknowledged since open.
     * -1 means this metric is not yet implemented by the vendor.
     * 
     * If this property is read in the CLOSED state it will report 0.
     *
     * Type: Int - 32-bit signed integer value.
     * Access: Read-only.
     *
     */
    METRIC_DIRECTED_MESSAGES_SENT_AND_ACKED = 1002,

    /**
     * Returns the total number of Broadcast CEC messages sent and acknowledged since open.
     * An acknowledgement implies a NACK in accordance with the inverted sense described in CEC specification.
     * -1 means this metric is not yet implemented by the vendor.
     * 
     * If this property is read in the CLOSED state it will report 0.
     *
     * Type: Int - 32-bit signed integer value.
     * Access: Read-only.
     *
     */
    METRIC_BROADCAST_MESSAGE_SENT_AND_ACKED = 1003,

    /**
     * Returns the total number of arbitration failures since open.
     * -1 means this metric is not yet implemented by the vendor.
     * 
     * If this property is read in the CLOSED state it will report 0.
     *
     * Type: Int - 32-bit signed integer value.
     * Access: Read-only.
     *
     */
    METRIC_ARBITRATION_FAILURES = 1004
}
