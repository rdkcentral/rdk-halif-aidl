package com.demo.hal.common;

/**
 * Parcelable representing the status of a vehicle's tire.
 * - pressure: Tire pressure (in psi).
 * - isPunctured: Indicates if the tire is punctured.
 */
@VintfStability
parcelable TireStatus {
    float pressure;     // Tire pressure in psi
    boolean isPunctured; // Whether the tire is punctured
}
