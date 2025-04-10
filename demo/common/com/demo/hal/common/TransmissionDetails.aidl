package com.demo.hal.common;

import com.demo.hal.common.TransmissionType;

/**
 * Parcelable representing the details of a vehicle's transmission.
 * - transmissionType: Type of transmission (Manual, Automatic, Semi-Automatic).
 * - transmissionMode: Transmission mode, such as "Drive", "Reverse".
 * - numberOfGears: Number of gears in the transmission.
 */
@VintfStability
parcelable TransmissionDetails {
    TransmissionType transmissionType; // Type of transmission
    int numberOfGears;                 // Number of gears
    @nullable
    String transmissionMode;           // Transmission mode (e.g., Drive, Reverse)
}
