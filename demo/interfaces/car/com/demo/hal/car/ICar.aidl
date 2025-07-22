package com.demo.hal.car;

import com.demo.hal.car.CarSpecs;
import com.demo.hal.car.CarStatus;
import com.demo.hal.car.ICarStatusListener;

/**
 * Interface for car-related operations.
 */
@VintfStability
interface ICar {

    /**
     * Retrieves the specifications of the car.
     * @return CarSpecs object with car-specific details.
     */
    CarSpecs getCarSpecs();

    /**
     * Retrieves the current status of the car.
     * @return CarStatus object containing various status indicators.
     */
    CarStatus getCarStatus();

    /**
     * Starts the car engine.
     */
    void startCarEngine();

    /**
     * Stops the car engine.
     */
    void stopCarEngine();

    /**
     * Registers a listener for car status updates.
     * @param listener A reference to the ICarStatusListener interface.
     */
    void registerCarStatusListener(ICarStatusListener listener);

    /**
     * Unregisters a previously registered car status listener.
     * @param listener A reference to the ICarStatusListener interface.
     */
    void unregisterCarStatusListener(ICarStatusListener listener);

    /**
     * Locks the car.
     */
    void lockCar();

    /**
     * Unlocks the car.
     */
    void unlockCar();

    /**
     * Resets the dashboard of the car.
     */
    void resetCarDashboard();

}
