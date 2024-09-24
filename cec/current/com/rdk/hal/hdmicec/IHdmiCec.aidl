package com.rdk.hal.hdmicec;
import com.rdk.hal.hdmicec.IHdmiCecController;
import com.rdk.hal.hdmicec.IHdmiCecControllerListener;
import com.rdk.hal.hdmicec.IHdmiCecEventListener;
import com.rdk.hal.hdmicec.Property;
import com.rdk.hal.PropertyValue;
import com.rdk.hal.State;

/** 
 *  @brief     HDMI CEC HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */

@VintfStability
interface IHdmiCec 
{
    /** The service name to publish. To be returned by getServiceName() in the derived class. */
    const @utf8InCpp String serviceName = "HdmiCec";


    /**
	 * @brief Gets the current state of the HDMI CEC interface.
     *
     * The HDMI CEC follows the standard HAL-E AV Session State Management.
     * Only CLOSED and STARTED are reported.
     *
     * @returns State enum value.
	 *
     * @see IHdmiCecEventListener.onStateChanged().
     */  
    State getState();

    /**
     * @brief Gets a property.
     *
     * @param[in] property              The key of a property from the Property enum.
     *
     * @returns PropertyValue or null if the property key is unknown.
     * 
     * @see setProperty()
     */
    @nullable PropertyValue getProperty(in Property property);

    /**
     * @brief Gets the logical addresses that have been set for filtering.
     * 
     * The broadcast address 0xF is always implied as being filtered as a logical address and
     * not returned in this array.
     *
     * @returns int[] - an array of addresses. The size of the array will be zero if no additional addresses have been set.
     * 
     * @see addLogicalAddress(), removeLogicalAddress()
     */
    int[] getLogicalAddresses();

    /**
	 * @brief Opens the HDMI CEC interface for control.
     * 
     * If successful the HDMI CEC interface transitions directly to the STARTED state.
     * Before logical addresses are added all broadcast messages will be processed and callbacks generated. 
     * The returned IHdmiCecController interface is used by the client to set a logical addresses and 
     * send CEC message buffers over the CEC bus.
     * An IHdmiCecControllerListener must be provided to receive incoming CEC message and state change events.
     * 
     * Only a single instance can be opened. Attempts to open again, by this or another process will fail with EX_ILLEGAL_STATE.
     * On opening all necessary logical addresses will be required to be added by the client.
     *
     * For a source HDMI device; on detecting the de-assertion of HPD, the Controller Client must close an opened 
     * IHdmiCecController interface, or remove all previously added logical addresses.
     * It is not considered an error for a client to open the HDMI device while HPD is not asserted.
     *
     * If the client that opened the `IHdmiCecController` crashes,
     * then close() is implicitly called to perform clean up.
     *
     * @param[in] cecControllerListener         A IHdmiCecControllerListener for the Controller Client to receive callbacks through.
     *
     * @exception binder::Status EX_ILLEGAL_STATE 
     * 
     * @returns IHdmiCecController or null on error.
     * 
     * @pre Resource is in State::CLOSED state.
     * 
     * @see close()
     */
    @nullable IHdmiCecController open(in IHdmiCecControllerListener cecControllerListener);

    /**
     * @brief Closes the HDMI CEC interface.
     *
     * The HDMI CEC interface must be in a STARTED state before it can be closed.
     * If successful the HDMI CEC interface transition to the CLOSED state.
     * The IHdmiCecController instance must not be used after it has been closed.
     * On closing the HDMI CEC interface, all added logical addresses are removed.
     * On the return of close() no more callbacks will occur to the IHdmiCecControllerListener
     * passed in the open() call.
     * 
     * @param[in] hdmiCecController     Instance of IHdmiCecController.
     *
     * @return boolean
     * @retval true     Successfully closed.
     * @retval false    Invalid state or unrecognised parameter.
     *
     * @pre Resource is in State::STARTED state.
     *
     * @see open()
     */
    boolean close(in IHdmiCecController hdmiCecController);


    /**
	 * Registers a CEC event listener.
     * 
     * This allows a client, other than the Controlling client, to receive messages and monitor the state for diagnostic purposes.
     * 
     * An `IHdmiCecEventListener` can only be registered once and will fail on subsequent
     * registration attempts.
     *
     * @param[in] cecEventListener	    Listener object for event callbacks.
     * 
     * @return boolean
     * @retval true     The event listener was registered.
     * @retval false    The event listener is already registered.
     *
     * @see unregisterEventListener()
     */
    boolean registerEventListener(in IHdmiCecEventListener cecEventListener);

    /**
	 * Unregisters a CEC event listener.
     * 
     * @param[in] cecEventListener	    Listener object for event callbacks.
     *
     * @return boolean
     * @retval true     The event listener was unregistered.
     * @retval false    The event listener was not found registered.
     *
     * @see registerEventListener()
     */
    boolean  unregisterEventListener(in IHdmiCecEventListener cecEventListener);
}
