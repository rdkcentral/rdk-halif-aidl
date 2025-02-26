# HAL `setProperty` and `getProperty`

This document provides a concise overview of the `setProperty` and `getProperty` methods within **RDK-AIDL-HAL**. These methods offer a flexible mechanism for interacting with services, encompassing both metadata management and functional control.

## **Core Functionality:**

`setProperty(String key, String value)`:  Sets a property associated with the service.  The `key` identifies the property, and the `value` provides the data to be stored or used.

`getProperty(String key)`: Retrieves the value of a specified property. The `key` identifies the property to retrieve.

## **Key Considerations:**

* **Implementation-Defined Behavior:**  The *meaning and effect* of any given `key` and `value` are entirely determined by the service implementing the AIDL interface.  The AIDL itself *only* defines the communication mechanism, not the semantics.

* **Beyond Metadata:** While `setProperty` and `getProperty` can be used for storing and retrieving metadata (e.g., object names, versions), they are *not limited* to this purpose.  

They can be used to:

- **Control Service Behavior:** Setting a property might trigger an action, change a service's state, or modify its operational parameters.
- **Retrieve Service State:** Getting a property might return the current state of a component, a calculated value, or any other information the service chooses to expose.

- **General-Purpose Communication:** Think of these methods as a generic communication channel. The AIDL defines the channel (key-value pairs), but the service defines the "language" spoken over that channel (the meaning of each key).

### Example Use Cases:

- **Configuration:** `setProperty("logLevel", "DEBUG")` could set the logging verbosity.
- **State Management:** `getProperty("connectionStatus")` might return the current connection state.
- **Command Execution:** `setProperty("reboot", "true")` could trigger a reboot.
- **Data Retrieval:** `getProperty("sensorData")` might return sensor readings.

- **No Inherent Semantics:**  The AIDL interface itself imposes no restrictions on the types of data that can be stored or retrieved, nor does it define what any particular key should represent.  The service is solely responsible for defining and managing these.

### Best Practices:

- **Documentation is Crucial:** Service developers should clearly document the available properties, their meanings, valid value ranges, and any side effects.  This is essential for clients to use the interface correctly.
- **Consistent Key Naming:** Employ a consistent naming convention for properties to improve readability and maintainability.
- **Error Handling:** Services should handle invalid property keys or values gracefully, possibly by returning error codes or throwing exceptions.

**In summary:** `setProperty()` and `getProperty()` are powerful and flexible tools.  They can be used for metadata, configuration, state management, and more.  However, their true potential is realized when service developers thoroughly document and carefully design the properties they expose, ensuring clear communication and predictable behavior for clients.