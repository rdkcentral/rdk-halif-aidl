package com.demo.hal.car;

import com.demo.hal.car.CarStatus;

/**
 * Listener interface for receiving car status updates.
 */
@VintfStability
interface ICarStatusListener {

    /**
     * Callback method triggered when the car status changes.
     * @param newStatus The updated status of the car.
     */
    void onCarStatusChanged(in CarStatus newStatus);
}
