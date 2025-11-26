# RDK HAL Aidl Interface

**RDK-HALIF-AIDL** is an open-source framework that standardizes hardware abstraction layers using Android AIDL. It provides a structured, IPC-driven interface for seamless communication between system components and hardware devices. 

Designed for embedded platforms, **RDK-HALIF-AIDL** ensures efficient hardware interaction, modular development, and interoperability with Android-based ecosystems.

## Documentation

All documentation and build instructions for **RDK Hardware Porting Kit** can be found here: [Documentation](https://rdkcentral.github.io/rdk-halif-aidl/)
To build the interface please follow this [link](https://rdkcentral.github.io/rdk-halif-aidl/introduction/interface_generation/)

## Usage Steps

```bash
# 1. Initial build (will fail initially as .cpp files are not generated)
./build_interfaces.sh

# 2. Source your bashrc, so that linux binder repo path is updated in $PATH
source ~/.bashrc

# 3. Activate Python virtual environment
source docs/python_venv/bin/activate

# 4. Modify AIDL files if needed
# (Make necessary changes before proceeding)

# 5. Update and freeze APIs
./update_and_freeze_apis.sh --dry-run=false

# 6. Final build (libraries will be created in targets/out)
./build_interfaces.sh
```

## Copyright and License

**RDK-HALIF-AIDL** is Copyright 2024 RDK Management and licensed under the Apache License, Version 2.0. See the LICENSE and NOTICE files in the top-level directory for further details.
