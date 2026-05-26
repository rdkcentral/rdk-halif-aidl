package com.demo.hal.dashboard;

/**
 * Parcelable representing dashboard information.
 * - displayMessage: Text message displayed on the dashboard.
 * - warningActive: Boolean flag indicating if a warning is currently active.
 */
@VintfStability
parcelable DashboardInfo {
    String displayMessage;  // Dashboard display message
    boolean warningActive;  // Indicates if a warning is active
}
