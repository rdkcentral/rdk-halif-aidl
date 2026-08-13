# Broadcast

## References

!!! info References
    |||
    |-|-|
    |**Interface Definition**|[broadcast/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/broadcast/current)|
    |**Interface Version**|`current`|
    |**API Documentation**| *TBD* |
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|
    |**VTS Tests**| TBC |
    |**Reference Implementation - vComponent**|**TBD**|

## Related Pages

!!! tip "Related Pages"
    - TBC

## 🚧 Document Under Construction

## General Design Principles

### The `IDemuxDataProvider` Interface

The `IDemuxDataProvider` interface can be confusing at first glance, because it's empty. The reason for this, though, is
that it's not meant to provide any functionality to the generic interface. Instead, it is meant to be used as an opaque
type for the service to implement any needed implementation-specific functionality, where a direct connection between a
specific front end and a specific demux is needed. An example for this can be hardware handles that need to be passed
from the front end to the demux in order to establish a connection between the two.

By it's nature, the details of such functionality should be hidden from the client, as the client is not meant to
include any implementation-specific details. Thus, the public interface is kept empty, and the service implementation is
free to implement any functionality it needs.

### Types and Type Safety

In order to avoid too much overhead in the Binder communication, custom types (in the form of AIDL parcelables) are
avoided for variables which are transferred frequently. Instead, primitive types are used for these variables. This is a
tradeoff between type safety and performance and requires careful implementation of both the service and the client. The
following rules have to be obeyed for all these variables using primitive types, even when not explicitly mentioned in
the documentation:

1. For variables which are semantically unsigned (e.g. `maxSymbolRate`), providing a negative value is considered an
   error. The service implementation is expected to return an `::android::binder::Status::EX_ILLEGAL_ARGUMENT` error in
   this case. The client should refrain from providing negative values for these variables.
2. For variables with a defined range (e.g. `pid` in the range of `0` to `0x1FFF`), providing a value outside of this
   range is considered an error. The service implementation is expected to return an
   `::android::binder::Status::EX_ILLEGAL_ARGUMENT` error in this case. The client should refrain from providing values
   outside of the defined range for these variables.
3. For variables with a range that can be queried through the API itself (e.g. `frequency`, which can be queried through
   `frontend.Capabilities.minFrequencyHz` and `frontend.Capabilities.maxFrequencyHz`), providing a value outside of this
   range is considered an error. The service implementation is expected to return an
   `::android::binder::Status::EX_ILLEGAL_ARGUMENT` error in this case. The client should refrain from providing values
   outside of the defined range for these variables.

For variables which are transferred infrequently, though, custom types are used to provide type safety (e.g.
`frontend.IFrontend.Id`).

Functions don't return `boolean`, because it adds additional overhead in form of another variable transferred over
Binder with no added gain. Instead, functions return `void` and throw a Binder exception in case of an error. The client
has to check the returned `::android::binder::Status` to determine if the function call was successful, anyway, thus
making the `boolean` return value redundant.

Strings are generally avoided both for arguments and return values, for obvious reasons.

### Passing Interfaces Directly

TODO: Write about that we pass interfaces directly instead of using IDs, and the pattern that we return interfaces to
their factories to destroy them.

### IDs

There are a couple of type-safe IDs defined in the broadcast API. These IDs are used to identify specific objects in the
system. They are opaque to the client and are only meaningful to the service implementation.
