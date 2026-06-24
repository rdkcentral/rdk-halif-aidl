package com.demo.hal.car;

import com.demo.hal.vehicle.VehicleStatus;
import com.demo.hal.common.FuelStatus;
import com.demo.hal.common.SpeedStatus;
import com.demo.hal.common.TireStatus;
import com.demo.hal.dashboard.DashboardInfo;
import com.demo.hal.dashboard.DashboardWarning;

/**
 * Parcelable defining the current status of a car.
 * - vehicleStatus: General vehicle status.
 * - fuelStatus: Current fuel level and consumption.
 * - speedStatus: Current speed details.
 * - tireStatuses: Array representing the status of all tires.
 * - dashboardInfo: Current dashboard display information.
 * - activeWarnings: Active warnings displayed on the dashboard.
 */
@VintfStability
parcelable CarStatus {
    VehicleStatus vehicleStatus;   // General vehicle status
    
    @nullable
    FuelStatus fuelStatus;         // Current fuel level and consumption
    @nullable
    SpeedStatus speedStatus;       // Current speed details
    @nullable
    TireStatus[] tireStatuses;     // Array representing the status of all tires
    @nullable
    DashboardInfo dashboardInfo;   // Current dashboard display information
    @nullable
    DashboardWarning[] activeWarnings; // Active warnings displayed on the dashboard
}
