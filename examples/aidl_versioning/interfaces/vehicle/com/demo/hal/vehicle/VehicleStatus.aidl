package com.demo.hal.vehicle;

/**
 * Parcelable representing the status of a vehicle.
 * - isMoving: Indicates if the vehicle is currently in motion.
 * - isLocked: Indicates if the vehicle is locked.
 * - engineOn: Indicates if the vehicle's engine is running.
 */
@VintfStability
parcelable VehicleStatus {
    boolean isMoving;  // Whether the vehicle is in motion
    boolean engineOn;  // Whether the engine is running
    boolean isLocked;  // Whether the vehicle is locked
}
