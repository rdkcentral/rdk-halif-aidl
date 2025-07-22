package com.demo.hal.bus;

import com.demo.hal.bus.BusStatus;

/**
 * Listener interface for receiving bus status updates.
 */
@VintfStability
interface IBusStatusListener {

    /**
     * Callback method triggered when the bus status changes.
     * @param newStatus The updated status of the bus.
     */
    void onBusStatusChanged(in BusStatus newStatus);
}
