package com.demo.hal.common;

import com.demo.hal.common.EngineType;
import com.demo.hal.common.FuelType;

/**
 * Parcelable containing engine specifications.
 * - engineType: Type of the engine (Petrol, Diesel, Electric, Hybrid).
 * - horsepower: Engine horsepower.
 * - fuelType: Fuel Type of the Engine
 * - displacement: Engine displacement (in liters).
 */
@VintfStability
parcelable EngineSpecs {
    EngineType engineType;  // Type of the engine
    int horsepower;         // Engine horsepower
    FuelType fuelType;       // Fuel Type of the Engine
    float displacement;     // Engine displacement in liters
}
