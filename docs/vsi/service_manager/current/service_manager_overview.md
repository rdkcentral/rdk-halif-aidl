# Overview

The **Service Manager** is a crucial **Binder service** included in the vendor layer. It is launched early in system initialization and serves as a **registry** for Binder service interfaces.

- As each **HAL service** starts, it registers its **public Binder interface** with the **Service Manager**.
- Registered interfaces are added to the Service Manager’s list, making them discoverable by clients.
- Clients can retrieve a registered service interface by calling `getService()` with the corresponding service name.
