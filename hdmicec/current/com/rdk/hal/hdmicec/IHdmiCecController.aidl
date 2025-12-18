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
import com.rdk.hal.hdmicec.SendMessageStatus;

/** 
 *  @brief     HDMI CEC Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */

@VintfStability
interface IHdmiCecController 
{
    /**
    * @brief Adds one or more Logical Addresses to be message filtered by the host device.
    *
    * This function adds the specified Logical Addresses such that directly addressed CEC messages with a matching 
    * destination address will be received by this device. 
    * The HAL will immediately ACK and produce callbacks for all received messages.
    *
    * The Client must first aquire a logical address using CEC Logical Address Allocation method 
    * (ref <HDMI Specification 1-4> Section <CEC 10.2.1>) before adding the logical address. 
    * The client can add all the logical addresses in one call or add them one by one.
    * 
    * All addresses must be in the directly addressable range of 0 to 14 (0x0 ~ 0xE) or the function will return false.
    * If any addresses passed in are already added then the function will return false.
    *
    * @param[in] logicalAddresses   An array of logical address to be added.
    *
    * @returns true if successfully added or false if the logical addresses have not been added.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHdmiCecController}} for exception handling behavior).
    * 
    * @pre The resource must be in State::STARTED.
    *
    * @see IHdmiCec.getLogicalAddresses(), removeLogicalAddresses(), IHdmiCecEventListener.onMessageReceived()
    */
    boolean addLogicalAddresses(in int[] logicalAddresses);

    /**
    * @brief Removes Logical Addresses that have been previously added.
    *
    * The HAL will not produce callbacks for received messages where the destination logical address is removed.
    * The HAL will not ACK messages where the logical address is removed.
    * All addresses must be in the directly addressable range of 0 to 14 (0x0 ~ 0xE) or the function will return false.
    * If any addresses passed in are not added then the function will return false.
    * 
    * @param[in] logicalAddresses   An array of logical addresses to be removed.
    *
    * @pre The resource must be in State::STARTED.
    *
    * @returns true on successfully removing and false if one or more logical addresses have not been previously added.
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHdmiCecController}} for exception handling behavior).
    * 
    * @see IHdmiCec.getLogicalAddresses(), addLogicalAddresses()
    */
    boolean removeLogicalAddresses(in int[] logicalAddresses);

    /**
     * @brief Synchronously send a CEC message.
     *
     * This function writes a complete CEC frame onto the bus and waits for an ACK.
     *
     * The packet contained in the message buffer will follow this format 
     *     (ref <HDMI Specification 1-4> Section <CEC 6.1>) :
     * 
     * complete frame  = header block + data block@n
     * header block    = destination logical address (4-bit) + source address (4-bit)@n
     * data block      = opcode block (8-bit) + operand block (N-bytes)
     *
     * The maximum message size (Header Block plus opcode block plus operand blocks) is 16 * 8 bits (16bytes).
     *
     * @code
     * |------------------------------------------------
     * | header block  |          data blocks          |
     * |------------------------------------------------
     * |3|2|1|0|3|2|1|0|7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|  
     * |------------------------------------------------
     * | Dest  |  src  |  opcode block | operand block |
     * |------------------------------------------------
     * @endcode
     *
     * The HAL implementation MUST add the EOM and ACK bits in the message in compliance with HDMI Specification 1-4> Section <CEC 6>.
     * The HAL implementation MUST comply with all Signalling and Bit Timings described in HDMI Specification 1-4> Section <CEC 5>.
     * The HAL implementation MUST comply with HDMI Specification 1-4> Section <CEC 7.1> on Frame Re-transmissions.
     * 
     * For a source HDMI device, while HPD is not asserted all sent messages will timeout.
     * It is not considered an error for a message to be sent while HPD is not asserted.
     *
     * @param[in] message The message to be sent.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @pre The HDMI CEC interface is in State::STARTED
     *
     * @returns SendMessageStatus
     *
     * @note On exception, output parameters/return values are undefined and must not be used. (See {{@link IHdmiCecController}} for exception handling behavior).
     *
     * @see IHdmiCec.open()
     */
    SendMessageStatus sendMessage(in byte[] message);

}
