package com.demo.hal.common;

import com.demo.hal.common.EngineType;

/**
 * Enum representing the different types of engine in a vehicle.
 * - PETROL: Petrol engine.
 * - DIESEL: Diesel engine.
 * - ELECTRIC: Electric engine.
 */
@VintfStability
@Backing(type="int")
enum EngineType {
    PETROL = 0,    // Petrol engine
    DIESEL = 1,    // Diesel engine
    ELECTRIC = 2   // Electric engine
}
