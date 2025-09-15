package com.demo.hal.common;

import com.demo.hal.common.TransmissionType;

/**
 * Enum representing the different types of transmissions in a vehicle.
 * - MANUAL: Manual transmission.
 * - AUTOMATIC: Automatic transmission.
 * - SEMI_AUTOMATIC: Semi-automatic transmission.
 */
@VintfStability
@Backing(type="int")
enum TransmissionType {
    MANUAL = 0,        // Manual transmission
    AUTOMATIC = 1,     // Automatic transmission
    SEMI_AUTOMATIC = 2 // Semi-automatic transmission
}
