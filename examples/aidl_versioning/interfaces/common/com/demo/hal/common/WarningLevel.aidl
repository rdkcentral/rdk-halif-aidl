package com.demo.hal.common;

import com.demo.hal.common.WarningLevel;

/**
 * Enum representing the severity levels of warnings in the vehicle's dashboard.
 * - LOW: Low-level warning.
 * - MEDIUM: Medium-level warning.
 * - HIGH: High-level warning.
 * - CRITICAL: Critical-level warning.
 */
@VintfStability
@Backing(type="int")
enum WarningLevel {
    LOW = 0,       // Low-level warning
    MEDIUM = 1,    // Medium-level warning
    HIGH = 2,      // High-level warning
    CRITICAL = 3   // Critical-level warning
}
