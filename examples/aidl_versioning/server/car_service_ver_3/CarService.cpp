/**
 * Copyright 2024 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "CarService.h"

using namespace com::demo::hal::car;
using namespace com::demo::hal::vehicle;
using namespace com::demo::hal::common;
using namespace com::demo::hal::dashboard;

CarService::CarService()
    : carStatusListener(NULL) {
    
    ALOGI("%s(): %d Initializing Car Service Control", __FUNCTION__, __LINE__);
    
    carStatus = new CarStatus();
    carStatus->vehicleStatus = VehicleStatus();
    carStatus->fuelStatus = FuelStatus();
    carStatus->speedStatus = SpeedStatus();
    carStatus->dashboardInfo = DashboardInfo();

    std::vector<std::optional<TireStatus>> tires(4);
    for (auto& tire : tires) {
        tire = TireStatus();  // or pass constructor args if needed
    }
    carStatus->tireStatuses = tires;
    carStatus->activeWarnings = std::vector<std::optional<DashboardWarning>>{};

    carSpecs = new CarSpecs();
    carSpecs->vehicleSpecs = VehicleSpecs();
    carSpecs->numberOfDoors = 5;
    carSpecs->hasSunroof = false;
    carSpecs->isElectric = false;
}

CarService::~CarService() {}

android::binder::Status CarService::getCarSpecs(CarSpecs* specs) {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    *specs = *carSpecs;
    return android::binder::Status::ok();
}

android::binder::Status CarService::getCarStatus(CarStatus* status) {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    *status = *carStatus;
    return android::binder::Status::ok();
}

android::binder::Status CarService::startCarEngine() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    // Implementation to start the car engine
    carStatus->vehicleStatus.engineOn = true;
    notifyCarStatusListener();
    return android::binder::Status::ok();
}

android::binder::Status CarService::stopCarEngine() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    // Implementation to stop the car engine
    carStatus->vehicleStatus.engineOn = false;
    notifyCarStatusListener();
    return android::binder::Status::ok();
}

android::binder::Status CarService::registerCarStatusListener(const ::android::sp<ICarStatusListener>& listener) {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    carStatusListener = listener;
    return android::binder::Status::ok();
}

android::binder::Status CarService::unregisterCarStatusListener(const ::android::sp<ICarStatusListener>& listener) {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    if (carStatusListener == listener) {
        carStatusListener = nullptr;
    }
    return android::binder::Status::ok();
}

android::binder::Status CarService::lockCar() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    // Implementation to lock the car
    carStatus->vehicleStatus.isLocked = true;
    notifyCarStatusListener();
    return android::binder::Status::ok();
}

android::binder::Status CarService::unlockCar() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    // Implementation to unlock the car
    carStatus->vehicleStatus.isLocked = false;
    notifyCarStatusListener();
    return android::binder::Status::ok();
}

android::binder::Status CarService::resetCarDashboard() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    // Implementation to reset the car dashboard
    if (carStatus != nullptr) {
        carStatus->dashboardInfo->displayMessage = (android::String16) "";
        carStatus->dashboardInfo->warningActive = false;
    }
    notifyCarStatusListener();
    return android::binder::Status::ok();
}

void CarService::notifyCarStatusListener() {
    ALOGI("%s(): %d", __FUNCTION__, __LINE__);
    if (carStatusListener != nullptr) {
        carStatusListener->onCarStatusChanged(*carStatus);
    }
}

