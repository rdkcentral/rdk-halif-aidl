package com.demo.hal.vehicle;

import com.demo.hal.vehicle.VehicleSpecs;
import com.demo.hal.vehicle.VehicleStatus;
import com.demo.hal.vehicle.IVehicleStatusListener;

/**
 * Interface representing the vehicle control system.
 */
@VintfStability
interface IVehicle {

    /**
     * Retrieves the basic specifications of the vehicle.
     * @return VehicleSpecs object containing vehicle specifications.
     */
    VehicleSpecs getVehicleSpecs();

    /**
     * Retrieves the current status of the vehicle.
     * @return VehicleStatus object containing vehicle status details.
     */
    VehicleStatus getVehicleStatus();

    /**
     * Starts the vehicle's engine.
     */
    void startVehicleEngine();

    /**
     * Stops the vehicle's engine.
     */
    void stopVehicleEngine();

    /**
     * Starts moving the vehicle.
     */
    void startMoving();

    /**
     * Stops the vehicle.
     */
    void stopMoving();

    /**
     * Registers a status listener to monitor vehicle updates.
     * @param listener The listener interface to receive status updates.
     */
    void registerVehicleStatusListener(IVehicleStatusListener listener);

    /**
     * Unregisters the status listener.
     * @param listener The listener to be removed.
     */
    void unregisterVehicleStatusListener(IVehicleStatusListener listener);

    /** 
     * Locks the vehicle.
     */
    void lockVehicle();

    /** 
     * Unlocks the vehicle.
     */
    void unlockVehicle();

    /**
     * Sets the fuel level of the vehicle.
     * @param fuelLevel New fuel level percentage.
     */
    void setFuelLevel(float fuelLevel);

}
