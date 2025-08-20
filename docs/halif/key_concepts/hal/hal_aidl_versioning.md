# RDK AIDL HAL Interface Versioning

## 1. Introduction

This document is a **technical specification** for the RDK AIDL HAL interface versioning mechanism. It defines normative requirements—metadata formats, runtime behaviors, and implementation obligations—that implementers must follow to ensure safe, compatible evolution of AIDL interfaces.

Below are the steps must be followed to write versioned aidl interfaces
1. Define the AIDL interface in the prescribed format. (See [Interface Definition](#3-interface-definition) section)
2. Write interface definition purely in AIDL.
3. Perform [**Update API**](#1-update-api) on the defined interface.
4. Review and Test the interface
5. Perform [**Freeze API**](#2-freeze-api) on the defined interface.
6. Repeat steps 3, 4, and 6 for next versions.

## 2. Versioning Metadata

Each AIDL interface carries two metadata fields embedded in the generated stub classes:

- **Version Number** (`int INTERFACE_VERSION`)
    - Incremented **every time** the AIDL file is modified (method added/modified, annotation changed).
    - Exposed at runtime as a constant field.

- **Interface Hash** (`String INTERFACE_HASH`)
    - SHA‑256 digest computed over the **canonical form** of the AIDL (see Section 3).
    - Ignores formatting/comments so that only signature changes affect the hash.

### Freeze Version vs. Current Version

- **Frozen Versions**:
  - The list version numbers recorded in the [interface definition](#3-interface-definition);
  - It represents the last published interface states.
  - Location of the Interface: `stable/aidl/<interface-name>/<stable-version>`
  - Each frozen version has it's hash associated with it stored at `stable/aidl/<interface-name>/<stable-version>/.hash`
- **Current/Next Version**:
  - The version for the AIDL interface under development.
  - The version value will be the `last frozen version + 1`
  - Location of the Interface: `stable/aidl/<interface-name>/current`
  - As this version is under development, it won't have the corresponding hash value. 

Both values ensure that any new change starts from a known, immutable baseline and that the code version aligns with the published snapshot.

## 3. Interface Validation
The versioning mechanism validates the given AIDL interfaces before it performs any operation on it. It checks for the valid interface definition, backward-compatibility, integrity etc.

The validation of the interface will be done by the versioning mechanism on its owm. Implementors don't have to do it explicitly. In case required, running update api will carry out the interface validation.

1. **Valid Interface Definition**:
    - Check if the syntax of interface definition is correct
    - All the imports are defined
    - Essential at the time of update api
2. **Integrity**:
    - Check if the frozen interfaces has not been modified after they were frozen.
    - Compute the hash value and compare it with the hash value from the file(.hash, captured along with frozen API)
    - Must be checked whenever interface is being modifed and used.
3. **Compatibility**:
    - Check if the all the versions(current/next and frozen) of interface are backward compatible
    - Each version will be checked agains the previouse version
    - Must be checked whenever interface is being modifed and used.
4. **Equality**:
    - Checks if the interface from the top of tree(ToT), i.e. the workspace where implementers write interface definition, is eual to the updated one.
    - Must be checked at the time of freeze api
5. **Updated**:
    - Checks if the interface from the current/next version is updated after the last frozen version
    - Must be checked at the time of freeze api

All or few of the above checks will be done as per the requirement whenever the interface validation is carried out

## 4. Interface Definition

Each interface must be defined in the YAML or JSON format. The name of the file should be **interface.yaml** or **interface.json**.

* **Fields in the AIDL Definition:**
    - **aidl_interface**: Defines the definition of the AIDL Interface.
    - **name**: Unique name of the AIDL Interface.
    - **srcs**: A list of AIDL sources for the Interface.
    - **stability**: Stability of the AIDL Interface. Currently, only vintf is supported.
    - **dump_api**: Enables gated APIs location for the AIDL Interface.
        -   It creates a separate directory, aidl_api, to store the current and frozen APIS.
    - **imports**: a list of imports on which the defined AIDL Interface is dependent.
    - **version_with_info**: a list of frozen versions associated with the list of dependent interfaces and their versions.
        - **Only the versioning framework should update this field**.

* **Example Definition of AIDL interface in YAML**
    ```yaml
    aidl_interface:
      name: car
      srcs:
        - com/demo/hal/car/*.aidl
      imports:
        - common
        - vehicle
        - dashboard
      dump_api: enabled
      stability: vintf
      versions_with_info:
        - version: "1"
          imports:
            - vehicle-V1
        - version: "2"
          imports:
            - common-V2
            - vehicle-V1
        - version: "3"
          imports:
            - common-V4
            - vehicle-V3
            - dashboard-V1    
    ```
* **Example Definition of AIDL interface in JSON**
    ```json
    {
      "aidl_interface": {
        "name": "car",
        "srcs": [
          "com/demo/hal/car/*.aidl"
        ],
        "imports": [
          "common",
          "vehicle",
          "dashboard"
        ],
        "dump_api": "enabled",
        "stability": "vintf",
        "versions_with_info": [
          {
            "version": "1",
            "imports": [
              "vehicle-V1"
            ]
          },
          {
            "version": "2",

            "imports": [
              "common-V2",
              "vehicle-V1"
            ]
          },
          {
            "version": "3",
            "imports": [
              "common-V4",
              "vehicle-V3",
              "dashboard-V1"
            ]
          }
        ]
      }
    }    
    ```

## **5. Versioning AIDL Interface**
The versioning of an AIDL interface is done in two steps, [Update API](#1-update-api) and [Freeze API](#2-freeze-api). These steps are essential while writing/defining the AIDL interface only.
### **1. Update API**
* Update API must be performed on the interface whenever it is modified.
* **Command:** `aidl_ops -u <interface-name>`
  ```bash
  ./build-tools/linux_binder_idl/host/aidl_ops –u car
  ```
* **Actions carried out:**
  * Validates Interface Definition from the workspace ([Check 1](#3-interface-validation)) and Updates `stable/aidl/<interface-name>/current` with the modified interface.
  * Validates the interface for [integrity and compatibility](#3-interface-validation).
  * The updated interface (i.e. `stable/aidl/<interface-name>/current`) must be reviewed and finzalized for freezing
* **Notes:**
    1. Imported interfaces must be updated first in case those are also modified.
    2. The backward compatibilty will be checked after updating the interface. If the modified API is not backward compatible, it won't be reverted.

### **2. Freeze API**
* Freeze API must be performed on the interface while freezing the API.
* Freeze Version will be `Last frozen/stable version + 1`
* **Command** `aidl_ops -f <interface-name>`
    ```bash
    ./build-tools/linux_binder_idl/host/aidl_ops –f car
    ```
* **Actions carried out:**
  * Validates the interface for [Equality, Integrity, Compatibility and updated](#3-interface-validation)
  * If all checks are passed the updated API from current location (`stable/aidl/<interface-name>/current`) will be copied to the freeze location (`stable/aidl/<interface-name>/<next-version>`).
  * Computes hash by considering AIDL files and version and stores in `stable/aidl/<interface-name>/<next-version>/.hash` file
  *  Updates the  field `version_with_info` in the [interface definition](#4-interface-definition)
* **Notes:**
  1. Imported interfaces must be freezed first in case those are also updated.
  2. The `version_with_info` field in the interface definition will be updated by the versioning tool only and it must not be updated manually. 

## **6. Generating Sources**

As per the section, [CMake Configuration to handle Interface library generation](#6-cmake-configuration-to-handle-interface-library-generation), the versioning framework provides support to generate interface libraries. In case the requirment is only to generate the sources of stubs and proxies of the interface, the below command can be used,

  ```bash
  ./build-tools/linux_binder_idl/host/aidl_ops –g -v 2 car
  ```

The generated sources can be used in your code directly or can be used to generate the library. Note that, it won't generate sourced for imported interfaces and it needs to be done seperately.

## **7. Directory Structure of AIDL interfaces

Once AIDL interfaces are stabilized, the following directory structure is adopted:

* Manually modified interfaces are placed in separate directories, either within a dedicated subdirectory like `interfaces/`, or directly in the main project directory.
* The `stable/` directory contains all finalized (or soon-to-be finalized) AIDL API interfaces. It also includes the generated source code for associated stubs and proxies corresponding to each AIDL interface.

```bash
.
├── interfaces
│   ├── car
│   │   ├── com/demo/hal/car/*.aidl
│   │   └── interface.yaml
│   └── common
│       ├── com/demo/hal/common/*.aidl
│       └── interface.json
└── stable
    ├── aidl
    │   ├── car
    │   │   ├── 1
    │   │   │   └── com/demo/hal/car/*.aidl
    │   │   └── current
    │   │       └── com/demo/hal/car/*.aidl
    │   └── common
    │       ├── 1
    │       │   └── com/demo/hal/common/*.aidl
    │       ├── 2
    │       │   └── com/demo/hal/common/*.aidl
    │       │       └── demo
    │       └── current
    │           └── com
    │               └── demo
    └── generated
        ├── car
        │   ├── include
        │   │   ├── 1
        │   │   │   └── com/demo/hal/car/*.h
        │   │   └── 2
        │   │       └── com/demo/hal/car/*.h
        │   └── src
        │       ├── 1
        │       │   └── com/demo/hal/car/*.cpp
        │       └── 2
        │           └── com/demo/hal/car/*.cpp
        └── common
            ├── include
            │   ├── 1
            │   │   └── com/demo/hal/common/*.h
            │   ├── 2
            │   │   └── com/demo/hal/common/*.h
            │   └── 3
            │       └── com/demo/hal/common/*.h
            └── src
                ├── 1
                │   └── com/demo/hal/common/*.cpp
                ├── 2
                │   └── com/demo/hal/common/*.cpp
                └── 3
                    └── com/demo/hal/common/*.cpp
```

## **8. CMake Configuration to handle Interface library generation**

CMake configuration is provided along with the versioning framework to handle the interface linking with the HAL service or the client. It adds the Interface library targets along with their dependencies in the build system as required by the particular module.

It Provides seamless integration of the AIDL Interfaces as developers don’t have to consider, 
* The Interface Dependencies and Imports
* Different versions of these imports
* AIDL Sources and their Locations in the build system
* Managing the source code of the generated stubs and proxies

It can be integrate with Yocto, and CMake based build systems. (Support for the Make build system will also be provided)

### Steps to include the CMake Configuration and link the interface libraries

1. **Define the `INTFS_ROOT_DIR`:**
    *  This variable is used get the location root directory where all interfaces are located.
    * If this variable is not set, the versioning framework considers the directory from where the cmake is executed as the root directory.
2. **Include Versioning Framework's CMake configuration include file:**
    ```cmake
    include(${LINUX_BINDER_AIDL_ROOT}/CMakeLists.inc)
    ```
    The variable, `LINUX_BINDER_AIDL_ROOT`, is the directory location where `linux-binder-aidl` repository is checked out.
3. **Link the Interface Library:**
    ```cmake
    target_link_intfs_libraries(CarClientVer3
        car-V3-cpp
    )
    ```
    It creates the target library of stubs and proxies of the interface, `car`, version 3 and it's imported interfaces as per the frozen versions. These libraries will be linked against the module.
4. **Configure the Include directory**
    ```cmake
    target_include_directories(CarServiceVer2
        PRIVATE
        ${INTFS_ROOT_DIR}/stable/generated/car/include/
    )
    ```

### **Example:**
  ```cmake
    cmake_minimum_required(VERSION 3.8)

    # Set the aidl interfaces root directory where all interfaces are
    # located along with stable versions.  
    set(INTFS_ROOT_DIR path/to/interfaces_root_directory)

    # Include the versioning Framework's CMake
    set(LINUX_BINDER_AIDL_ROOT path/to/linux_binder_aidl)
    include(${LINUX_BINDER_AIDL_ROOT}/CMakeLists.inc)
    
    set(CarClient_Sources CarClient.cpp)
    
    add_executable(CarClientVer3 ${CarClient_Sources})
    
    # Link the aidl interface stubs & proxies library
    target_link_intfs_libraries(CarClientVer3
        car-V3-cpp
        )
  
    # Configure the include directory
    target_include_directories(CarServiceVer2
        PRIVATE
        ${INTFS_ROOT_DIR}/stable/generated/car/include/
    )
    
    target_link_libraries(CarClientVer3 PRIVATE log)
    
    install(TARGETS CarClientVer3
    
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
  ```

## **9. The Server and the client Implementation**
### **1. Service Implementation**
1. Provide an implementation for the Interface.

    Example of a class definition which implements the ICar Interface
    ```c++
    #include <3/com/demo/hal/car/BnCar.h>
    #include <binder/Status.h>

    using namespace com::demo::hal::car;

    class CarService : public BnCar {
      public:
        CarService();
        ~CarService();

        // Interface Methods Implementation
        ...
      private:
        // Private methods and 
    }
    ```
2. Write a server to create the service using the Interface Class. The server has to register the the service with a unique service identifier.
    ```c++
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
        android::status_t status = sm->addService(String16("CarService"),
                                        carService, true /* allowIsolated */);
    }
    
    void JoinThreadPool() {
        sp<ProcessState> ps = ProcessState::self();
        IPCThreadState::self()->joinThreadPool();  // should not return
    }
    
    
    int main() {
        CreateAndRegisterService();
        JoinThreadPool();
        std::abort();  // unreachable
    }
    ```

### 2. **Client Implementation**
Client has to acquire the specific service from service manager. It has to make use of the unique identifier to get the service.

If required, it has to implement the listner class from the interface.

Once the required service is acquired, the version and hash value of the server can be inquired using `getInterfaceVersion()` and `getInterfaceHash()` respectively. The version can be used by the client to tweak it's implementation as per the server's version.

Below is the example of the client.
```c++
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <3/com/demo/hal/car/ICar.h>
#include <3/com/demo/hal/car/BnCarStatusListener.h>
#include <iostream>

using namespace android;
using namespace com::demo::hal::car;

// Get the Car Service
sp<ICar> getCarService(){
    sp<IServiceManager> serviceManager =
        android::defaultServiceManager();

    sp<IBinder> carBinder =
        serviceManager->checkService(String16("CarService"));
    if(!carBinder) {
        return nullptr;
    }   

    sp<ICar> carService = interface_cast<ICar>(carBinder);
    if(!carService){
        return nullptr;
    }   

    return carService;
}

// Listner Implementation
class CarStatusListener : public BnCarStatusListener {
public:
    virtual android::binder::Status onCarStatusChanged(const CarStatus& newStatus) override {
        return android::binder::Status::ok();
    }   
};

int main() {
    sp<ICar> carService = getCarService();
    android::binder::Status status;

    if (carService == nullptr) {
        return -1; 
    }

    // The Interface version and hash value on the client side
    int32_t client_ver = ICar::VERSION;
    char* client_hash = ICar::HASHVALUE;

    // The Interface version and hash value on the server side
    int32_t service_ver = carService->getInterfaceVersion();
    std::string service_hash = carService->getInterfaceHash();

    // Register car status listener
    sp<CarStatusListener> listener = new CarStatusListener();
    status = carService->registerCarStatusListener(listener);
    if (status.isOk()) {
        ALOGI("Car status listener registered");
    } else {
        ALOGE("Failed to register car status listener: %s", status.toString8().c_str());
    }
}
```

## 10. Testing & Validation Strategy

All AIDL changes **must** be updated locally **before** opening a pull request:

- **Interface Validation**:
    ```bash
    ./build-tools/linux_binder_idl/host/aidl_ops –u car
    ```
    - Verifies that the value in `.hash` matches with the hash computed using the current state of aidl files
    - Verifies that all the frozen versions are backward compatible
    - See [Interface Validation](#3-interface-validation) for more details.

- **Simulates**:
    - Older client vs. newer server
    - Newer client vs. older server
    - Exact-version match
    - Reports pass/fail per method.

- **Pull Request Validation**:
    - When creating a PR, attach logs from both scripts demonstrating successful verification and compatibility checks.
    - The PR reviewer will ensure these results are present and all tests pass before merging.

## 11. Developer Guidelines

### **When modifying AIDL**

1. In case of the new Interface Definition: Define the AIDL interface in the prescribed format. (See [Interface Definition](#4-interface-definition) section)
2. Perform [Update API](#1-update-api) on the interface.
3. Create a PR and  perform required testing of the interface
4. At the time of publishing new version: Perform [Freeze API](#2-freeze-api) on the defined/updated interface.

### **Removing or renaming methods**

- Removing or Renaming of the method is not allowed if the method is already published in the previous method.
- Method signature can be changed provided that the backward compatibility is not broken(This will be validated while updating or freezing the API).

### **Review Checklist**

- [ ] Version incremented correctly in the interface definition.
- [ ] `.hash` is created for the frozen api.
- [ ] All local tests pass (hash + compatibility).
