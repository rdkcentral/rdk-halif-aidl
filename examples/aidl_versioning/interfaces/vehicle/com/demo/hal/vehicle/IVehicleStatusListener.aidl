package com.demo.hal.vehicle;

import com.demo.hal.vehicle.VehicleStatus;

/**
 * Callback interface for vehicle status updates.
 */
@VintfStability
interface IVehicleStatusListener {

    /**
     * Callback triggered when the vehicle status is updated.
     * @param status The updated vehicle status.
     */
    void onVehicleStatusChanged(in VehicleStatus status);
}
