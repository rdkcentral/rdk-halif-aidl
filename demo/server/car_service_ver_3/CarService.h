#ifndef CAR_IMPL_H
#define CAR_IMPL_H

#include <com/demo/hal/car/BnCar.h>
#include <com/demo/hal/car/CarSpecs.h>
#include <com/demo/hal/car/CarStatus.h>
#include <com/demo/hal/car/ICarStatusListener.h>
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

