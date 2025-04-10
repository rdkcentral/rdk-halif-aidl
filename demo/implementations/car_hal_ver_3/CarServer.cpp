#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include "CarService.h"

using android::String16;
using android::sp;
using android::defaultServiceManager;
using android::ProcessState;
using android::IPCThreadState;


void CreateAndRegisterService() {
    sp<ProcessState> proc(ProcessState::self());
    sp<CarService> carService = new CarService();
    sp<android::IServiceManager> sm = defaultServiceManager();
    android::status_t status = sm->addService(String16("CarService"), carService,
                                        true /* allowIsolated */);
    if (status == android::OK) {
        ALOGI("%s():%d CarService added", __FUNCTION__, __LINE__);
    } else {
        ALOGE("%s():%d Failed to add service %d", __FUNCTION__, __LINE__, status);
    }
}


void JoinThreadPool() {
    sp<ProcessState> ps = ProcessState::self();
    IPCThreadState::self()->joinThreadPool();  // should not return
}


int main() {
    //android::com::CreateAndRegisterService();
    CreateAndRegisterService();
    //android::com::JoinThreadPool();
    JoinThreadPool();
    std::abort();  // unreachable
}
