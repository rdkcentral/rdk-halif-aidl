package com.demo.hal.dashboard;

import com.demo.hal.common.WarningLevel;

/**
 * Parcelable representing an active warning on the dashboard.
 * - warningType: Type of warning (e.g., "Engine", "Tire Pressure").
 * - description: Detailed description of the warning.
 * - warningLevel: Severity level of the warning.
 */
@VintfStability
parcelable DashboardWarning {
    String warningType;       // Type of warning (e.g., "Engine", "Tire Pressure")
    String description;       // Description of the warning
    WarningLevel warningLevel; // Severity level of the warning
}
