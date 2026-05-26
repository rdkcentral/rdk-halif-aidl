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

#ifndef CAR_IMPL_H
#define CAR_IMPL_H

#include <3/com/demo/hal/car/BnCar.h>
#include <3/com/demo/hal/car/CarSpecs.h>
#include <3/com/demo/hal/car/CarStatus.h>
#include <3/com/demo/hal/car/ICarStatusListener.h>
#include <com/demo/hal/vehicle/VehicleStatus.h>
#include <com/demo/hal/vehicle/VehicleSpecs.h>
#include <com/demo/hal/common/FuelStatus.h>
#include <com/demo/hal/common/SpeedStatus.h>
#include <com/demo/hal/common/TireStatus.h>
#include <com/demo/hal/dashboard/DashboardInfo.h>
#include <com/demo/hal/dashboard/DashboardWarning.h>
#include <binder/Status.h>
#include <android/log.h>

using namespace com::demo::hal::car;

#define LOG_TAG "CarService"

class CarService : public BnCar {
public:
    CarService();
    //CarService(CarSpecs* specs, CarStatus* status);
    ~CarService();

    android::binder::Status getCarSpecs(CarSpecs* specs) override;
    android::binder::Status getCarStatus(CarStatus* status) override;
    android::binder::Status startCarEngine() override;
    android::binder::Status stopCarEngine() override;
    android::binder::Status registerCarStatusListener(const ::android::sp<ICarStatusListener>& listener) override;
    android::binder::Status unregisterCarStatusListener(const ::android::sp<ICarStatusListener>& listener) override;
    android::binder::Status lockCar() override;
    android::binder::Status unlockCar() override;
    android::binder::Status resetCarDashboard() override;

private:
    void notifyCarStatusListener();

    CarSpecs* carSpecs;
    CarStatus* carStatus;
    android::sp <ICarStatusListener> carStatusListener;
};

#endif // CAR_IMPL_H

