package com.demo.hal.bus;

import com.demo.hal.bus.BusSpecs;
import com.demo.hal.bus.BusStatus;
import com.demo.hal.bus.IBusStatusListener;

/**
 * Interface for bus-related operations.
 */
@VintfStability
interface IBus {

    /**
     * Retrieves the specifications of the bus.
     * @return BusSpecs object with bus-specific details.
     */
    BusSpecs getBusSpecs();

    /**
     * Retrieves the current status of the bus.
     * @return BusStatus object containing various status indicators.
     */
    BusStatus getBusStatus();

    /**
     * Starts the bus engine.
     */
    void startBusEngine();

    /**
     * Stops the bus engine.
     */
    void stopBusEngine();

    /**
     * Locks the bus doors.
     */
    void lockBus();

    /**
     * Unlocks the bus doors.
     */
    void unlockBus();

    /**
     * Registers a listener for bus status updates.
     * @param listener A reference to the IBusStatusListener interface.
     */
    void registerBusStatusListener(IBusStatusListener listener);

    /**
     * Unregisters a previously registered bus status listener.
     * @param listener A reference to the IBusStatusListener interface.
     */
    void unregisterBusStatusListener(IBusStatusListener listener); 

    /**
     * Resets the dashboard of the bus.
     */
    void resetBusDashboard();

    /**
     * Opens the bus doors.
     */
    void openBusDoors();

    /**
     * Closes the bus doors.
     */
    void closeBusDoors();

}
