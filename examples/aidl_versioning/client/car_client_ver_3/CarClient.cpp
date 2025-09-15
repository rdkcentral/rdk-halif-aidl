#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/demo/hal/car/ICar.h>
#include <com/demo/hal/car/CarSpecs.h>
#include <com/demo/hal/car/CarStatus.h>
#include <com/demo/hal/car/BnCarStatusListener.h>
#include <iostream>
#include <android/log.h>

#define LOG_TAG "CarClient"

using namespace android;
using namespace com::demo::hal::car;

sp<ICar> getCarService(){
    ALOGI("Request for Car Service");

    sp<IServiceManager> serviceManager =
        android::defaultServiceManager();

    sp<IBinder> carBinder =
        serviceManager->checkService(String16("CarService"));
    if(!carBinder) {
        ALOGE("Cannot find Car Service");
        return nullptr;
    }

    sp<ICar> carService = interface_cast<ICar>(carBinder);
    if(!carService){
        ALOGE("the CarService service is not an ICar type");
        return nullptr;
    }

    return carService;
}


class CarStatusListener : public BnCarStatusListener {
public:
    virtual android::binder::Status onCarStatusChanged(const CarStatus& newStatus) override {
        ALOGI("Car Status Changed: %s", newStatus.toString().c_str());
        return android::binder::Status::ok();
    }
};

int main() {
    sp<ICar> carService = getCarService();
    android::binder::Status status;

    if (carService == nullptr) {
        ALOGE("Failed to get car service");
        return -1;
    }

    int32_t client_ver = ICar::VERSION;
    int32_t service_ver = carService->getInterfaceVersion();

    char* client_hash = ICar::HASHVALUE;
    std::string service_hash = carService->getInterfaceHash();

    ALOGI("Versions, Client: %d Service: %d", client_ver, service_ver);
    ALOGI("Hashes, Client: %s Service: %s", client_hash, service_hash.c_str());

    // Register car status listener
    sp<CarStatusListener> listener = new CarStatusListener();
    status = carService->registerCarStatusListener(listener);
    if (status.isOk()) {
        ALOGI("Car status listener registered");
    } else {
        ALOGE("Failed to register car status listener: %s", status.toString8().c_str());
    }

    // Get car specs
    CarSpecs specs;
    status = carService->getCarSpecs(&specs);
    if (status.isOk()) {
        ALOGI("Car Specs: %s", specs.toString().c_str());
    } else {
        ALOGE("Failed to get car specs: %s", status.toString8().c_str());
    }

    // Get car status
    CarStatus carStatus;
    status = carService->getCarStatus(&carStatus);
    if (status.isOk()) {
        ALOGI("Car Status: %s", carStatus.toString().c_str());
    } else {
        ALOGE("Failed to get car status: %s", status.toString8().c_str());
    }

    // Start car engine
    status = carService->startCarEngine();
    if (status.isOk()) {
        ALOGI("Car engine started");
    } else {
        ALOGE("Failed to start car engine: %s", status.toString8().c_str());
    }

    // Stop car engine
    status = carService->stopCarEngine();
    if (status.isOk()) {
        ALOGI("Car engine stopped");
    } else {
        ALOGE("Failed to stop car engine: %s", status.toString8().c_str());
    }

    // Unregister car status listener
    status = carService->unregisterCarStatusListener(listener);
    if (status.isOk()) {
        ALOGI("Car status listener unregistered");
    } else {
        ALOGE("Failed to unregister car status listener: %s", status.toString8().c_str());
    }

    // Lock Car
    status = carService->lockCar();
    if (status.isOk()) {
        ALOGI("Car Locked");
    } else {
        ALOGE("Failed to Lock the Car: %s", status.toString8().c_str());
    }

    // Unlock Car
    status = carService->unlockCar();
    if (status.isOk()) {
        ALOGI("Car Unlocked");
    } else {
        ALOGE("Failed to unlock the car: %s", status.toString8().c_str());
    }

    // Reset Car Dashboard
    status = carService->resetCarDashboard();
    if (status.isOk()) {
        ALOGI("Car Dashboard reset");
    } else {
        ALOGE("Failed to reset the car Dashboard: %s", status.toString8().c_str());
    }

    return 0;
}

