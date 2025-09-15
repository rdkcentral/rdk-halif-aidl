package com.demo.hal.dashboard;

import com.demo.hal.dashboard.DashboardInfo;
import com.demo.hal.dashboard.DashboardWarning;

/**
 * Interface for dashboard-related operations.
 */
@VintfStability
interface IDashboard {

    /**
     * Retrieves the current dashboard information.
     * @return DashboardInfo object with current display messages and status.
     */
    DashboardInfo getDashboardInfo();

    /**
     * Retrieves the list of active dashboard warnings.
     * @return Array of DashboardWarning objects representing active warnings.
     */
    DashboardWarning[] getActiveWarnings();

    /**
     * Resets the dashboard, clearing messages and warnings.
     */
    void resetDashboard();
}
