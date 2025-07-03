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
import com.rdk.hal.State;

/** 
 *  @brief     HDMI CEC Event Listener HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
oneway interface IHdmiCecEventListener {
 
    /**
     * Callback to be invoked for each frame sent by the Controller through IHdmiCecController.sendMessage().
     *
     * When registered the HAL invokes this callback after sending, or attempting to send a message.
     * The message's send status allows the listener to know the result of the message transmission.
     *
     * The intention of this listener is to allow diagnostic tools to monitor CEC traffic between the CEC Controller Client
     * and the HAL.
     *
     * The frame contained in the buffer will follow this format
     *     (ref <HDMI Specification 1-4> Section <CEC 6.1>) :
     *
     * complete frame  = header block + data block@n
     * header block    = destination logical address (4-bit) + source address (4-bit)@n
     * data block      = opcode block (8-bit) + operand block (N-bytes)
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
     * The message buffer should be identical to the IHdmiCecController.sendMessage() call.
     *
     * @param[in] message	A variable length message conforming to format described above.
     * @param[in] status    The status of the sent message
     *
     * @see IHdmiCecController.sendMessage()
     */
    void onMessageReceived(in byte[] message);

    /**
	 * Callback when the CEC interface has transitioned to a new state.
     *
     * @param[in] oldState	            The state transitioned from.
     * @param[in] newState              The new state transitioned to.
     * 
     * @see IHdmiCec.getState()
     */
    void onStateChanged(in State oldState, in State newState);

}
