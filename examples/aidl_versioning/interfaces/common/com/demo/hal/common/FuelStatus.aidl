package com.demo.hal.common;

import com.demo.hal.common.FuelType;

/**
 * Parcelable representing the fuel status of a vehicle.
 * - fuelType: Type of fuel being used by the vehicle (Petrol, Diesel, Electric, Hydrogen).
 * - fuelLevel: The current fuel level (in percentage).
 * - fuelConsumptionRate: Rate at which fuel is consumed (in liters per hour).
 */
@VintfStability
parcelable FuelStatus {
    FuelType fuelType;           // Type of fuel
    float fuelLevel;             // Fuel level as a percentage
    float fuelConsumptionRate;   // Fuel consumption rate (liters per hour)
}
