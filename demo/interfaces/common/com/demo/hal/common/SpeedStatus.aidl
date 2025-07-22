package com.demo.hal.common;

/**
 * Parcelable representing the speed status of a vehicle.
 * - currentSpeed: The current speed of the vehicle (in km/h).
 * - maxSpeed: The maximum speed the vehicle can achieve (in km/h).
 */
@VintfStability
parcelable SpeedStatus {
    float currentSpeed; // Current speed in km/h
    float maxSpeed;     // Maximum speed in km/h
}
