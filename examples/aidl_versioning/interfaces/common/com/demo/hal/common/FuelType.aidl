package com.demo.hal.common;

import com.demo.hal.common.FuelType;

/**
 * Enum representing the different types of fuel a vehicle can use.
 * - PETROL: Petrol fuel type.
 * - DIESEL: Diesel fuel type.
 * - ELECTRIC: Electric (Battery) fuel type.
 */
@VintfStability
@Backing(type="int")
enum FuelType {
    PETROL = 0,    // Petrol fuel
    DIESEL = 1,    // Diesel fuel
    ELECTRIC = 2   // Electric fuel
}
