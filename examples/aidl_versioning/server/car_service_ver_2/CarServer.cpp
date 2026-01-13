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
