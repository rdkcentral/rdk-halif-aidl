package com.demo.hal.bus;

import com.demo.hal.vehicle.VehicleSpecs;

/**
 * Parcelable defining bus-specific specifications.
 * - vehicleSpecs: General vehicle specifications.
 * - passengerCapacity: Maximum number of passengers the bus can hold.
 * - hasLuggageCompartment: Indicates if the bus has a luggage compartment.
 * - hasDoubleDeck: Specifies if the bus is a double-decker.
 */
@VintfStability
parcelable BusSpecs {
    VehicleSpecs vehicleSpecs;  // General vehicle specifications
    int passengerCapacity;      // Maximum passenger capacity
    boolean hasLuggageCompartment; // Indicates if luggage compartment is available
    boolean hasDoubleDeck;      // Specifies if the bus is a double-decker
}
