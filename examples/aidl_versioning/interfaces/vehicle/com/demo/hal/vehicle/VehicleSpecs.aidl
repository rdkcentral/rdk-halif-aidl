package com.demo.hal.vehicle;

import com.demo.hal.common.EngineSpecs;

/**
 * Parcelable representing basic vehicle specifications.
 * - engineSpecs: Specs of Engine used in the Vehicle
 * - numberOfWheels: Total number of wheels in the vehicle.
 * - length: Length of the vehicle (in meters).
 * - width: Width of the vehicle (in meters).
 * - height: Height of the vehicle (in meters).
 */
@VintfStability
parcelable VehicleSpecs {
    EngineSpecs engineSpecs; // Specs of Engine used in the Vehicle
    int numberOfWheels;      // Total wheels in the vehicle
    float length;            // Length of the vehicle in meters
    float width;             // Width of the vehicle in meters
    float height;            // Height of the vehicle in meters
}
