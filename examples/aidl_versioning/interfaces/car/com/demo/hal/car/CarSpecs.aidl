package com.demo.hal.car;

import com.demo.hal.vehicle.VehicleSpecs;

/**
 * Parcelable defining car-specific specifications.
 * - vehicleSpecs: General vehicle specifications.
 * - numberOfDoors: Number of doors in the car.
 * - hasSunroof: Indicates if the car has a sunroof.
 * - isElectric: Specifies if the car is an electric vehicle.
 */
@VintfStability
parcelable CarSpecs {
    VehicleSpecs vehicleSpecs;  // General vehicle specifications
    int numberOfDoors;          // Number of doors in the car
    boolean hasSunroof;         // Indicates if a sunroof is available
    boolean isElectric;         // Specifies if the car is electric
}
