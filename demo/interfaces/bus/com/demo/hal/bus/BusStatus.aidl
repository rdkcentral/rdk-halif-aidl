package com.demo.hal.bus;

import com.demo.hal.vehicle.VehicleStatus;
import com.demo.hal.common.SpeedStatus;
import com.demo.hal.common.FuelStatus;
import com.demo.hal.common.TireStatus;
import com.demo.hal.dashboard.DashboardInfo;
import com.demo.hal.dashboard.DashboardWarning;

/**
 * Parcelable defining the current status of a bus.
 * - vehicleStatus: General vehicle status.
 * - speedStatus: Current speed details.
 * - fuelStatus: Current fuel level and consumption.
 * - tireStatuses: Array representing the status of all tires.
 * - dashboardInfo: Current dashboard display information.
 * - activeWarnings: Active warnings displayed on the dashboard.
 */
@VintfStability
parcelable BusStatus {
    VehicleStatus vehicleStatus;   // General vehicle status
    @nullable
    SpeedStatus speedStatus;       // Current speed details
    @nullable
    FuelStatus fuelStatus;         // Current fuel level and consumption
    @nullable
    TireStatus[] tireStatuses;     // Array representing the status of all tires
    @nullable
    DashboardInfo dashboardInfo;   // Current dashboard display information
    @nullable
    DashboardWarning[] activeWarnings; // Active warnings displayed on the dashboard
}
