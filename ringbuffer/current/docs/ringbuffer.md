# Generic Ring Buffer Interface

## References

!!! info References
    |||
    |-|-|
    |**Interface Definition**|[ringbuffer/current](https://github.com/rdkcentral/rdk-halif-aidl/tree/main/ringbuffer/current)|
    |**Interface Version**|`current`|
    |**API Documentation**|_TBD - Doxygen_|
    |**HAL Interface Type**|[AIDL and Binder](../introduction/aidl_and_binder.md)|
    |**VTS Tests**|TBC|
    |**Reference Implementation - vComponent**|**TBD**|

## Related Pages

!!! tip "Related Pages"
    - [Broadcast](../broadcast/broadcast.md)

## Overview

The Ring Buffer HAL moves bulk opaque data between two processes without sending that data over Binder. Binder carries
only control operations — registration, acquire and release, notifications — while the payload lives in memory shared
between the producer and the consumer.

The interface is deliberately content-agnostic. It carries bytes, not frames, packets or samples. A demultiplexer uses
it for filtered transport-stream data; a software input uses it in the opposite direction to feed a demultiplexer. The
interface imposes no structure on the bytes and no ownership of their meaning.

Three interfaces make up the API. `IRingBuffer` owns the buffer and its configuration. `IRingBufferSink` is the
producer endpoint and `IRingBufferSource` is the consumer endpoint. Each endpoint has a matching listener interface,
implemented by the client, through which the implementation delivers notifications.

`IRingBuffer` is implementation-internal by design. It is never registered with the service manager, has no
`serviceName` constant, and is never returned to a producer or a consumer. Only the owning HAL component holds one, so
buffer size and overflow behaviour are decided by that component rather than negotiated by its clients. This is why
`setSize()` and `setOverflowing()` have no client-facing equivalent.

In the consumers that exist today, the owning HAL creates and configures the buffer and publishes only the endpoint the
client needs: `IDemuxSoftwareInput.openForWriting()` returns a sink, and `IMpeg2TsDataFilter.registerConsumer()`
returns a source.

## Implementation Requirements

Requirements a conforming implementation must satisfy. Each is intended to be independently verifiable; the Comments
column names the interface element against which it is checked.

### Configuration

| #                 | Requirement                                                                                                                                                                                        | Comments                                                        |
| ----------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- | --------------------------------------------------------------- |
| **HAL.RINGBUF.1** | `setSize()` shall reject a size less than or equal to zero with `EX_ILLEGAL_ARGUMENT`.                                                                                                             |                                                                 |
| **HAL.RINGBUF.2** | `setSize()` shall reject a size above the implementation maximum with `EX_UNSUPPORTED_OPERATION`.                                                                                                  |                                                                 |
| **HAL.RINGBUF.3** | `setSize()` and `setOverflowing()` shall throw `EX_ILLEGAL_STATE` while a producer or a consumer is registered.                                                                                    | Configuration is permitted only while the buffer is idle.       |
| **HAL.RINGBUF.4** | Overflow behaviour is a capability of the implementation; one supporting only a single behaviour shall reject the other with `EX_UNSUPPORTED_OPERATION` rather than silently ignoring the request. | No default is defined; `getInfo()` reports the value in effect. |
| **HAL.RINGBUF.5** | Sizes and offsets shall be treated as 32-bit; a ring buffer is bounded at 2 GiB.                                                                                                                   | Deliberate limit; recorded on `setSize()`.                      |

### Registration

| #                 | Requirement                                                                                                                                     | Comments                                          |
| ----------------- | ----------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------- |
| **HAL.RINGBUF.6** | At most one producer and one consumer shall be registered at a time; a second registration shall throw `EX_ILLEGAL_STATE`.                      |                                                   |
| **HAL.RINGBUF.7** | `unregisterProducer()` / `unregisterConsumer()` shall throw `EX_ILLEGAL_ARGUMENT` when passed an endpoint that is not the registered one.       | Provenance checking.                              |
| **HAL.RINGBUF.8** | The implementation shall deliver `onSpaceAvailable()` to a newly registered producer, so that it learns the buffer size without a further call. | Stated on `registerProducer()`.                   |
| **HAL.RINGBUF.9** | An endpoint interface and its file descriptor shall be invalidated by the matching unregister call.                                             | The descriptor is caller-owned and caller-closed. |

### Acquire and Release

| #                  | Requirement                                                                                                                       | Comments                                 |
| ------------------ | --------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------- |
| **HAL.RINGBUF.10** | `acquire()` shall reject a request less than or equal to zero, or larger than the buffer size, with `EX_ILLEGAL_ARGUMENT`.        | Both endpoints.                          |
| **HAL.RINGBUF.11** | `acquire()` shall return a contiguous region; `bytes` may be smaller than requested where the region would otherwise wrap.        | `remaining` reports what lies beyond it. |
| **HAL.RINGBUF.12** | The producer shall hold at most one outstanding acquire; a second `acquire()` before `release()` shall throw `EX_ILLEGAL_STATE`.  | Guarantees a contiguous write region.    |
| **HAL.RINGBUF.13** | `release()` shall throw `EX_ILLEGAL_ARGUMENT` for an ID that does not correspond to an outstanding acquire on that endpoint.      |                                          |
| **HAL.RINGBUF.14** | `IRingBufferSink.release()` shall reject a byte count that is negative or larger than the count acquired.                         |                                          |
| **HAL.RINGBUF.15** | Bytes acquired but not released by the producer shall not be made readable, and shall remain available to a later acquire.        | Short writes are permitted.              |
| **HAL.RINGBUF.16** | After `release()` returns, the releasing side shall not access the released region, and the opposite side becomes entitled to it. |                                          |
| **HAL.RINGBUF.17** | A non-overflowing buffer with no free space shall return `null` from the producer's `acquire()` rather than blocking or throwing. |                                          |
| **HAL.RINGBUF.18** | A buffer with no readable data shall return `null` from the consumer's `acquire()`.                                               |                                          |

### Overflow

| #                  | Requirement                                                                                                                                     | Comments                                                           |
| ------------------ | ----------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------ |
| **HAL.RINGBUF.19** | On an overflowing buffer the producer's `acquire()` shall succeed even when the buffer is full, overwriting data the consumer has not yet read. | Data loss is the documented trade for never blocking the producer. |
| **HAL.RINGBUF.20** | An overflow shall be reported through `onError()` with `RingBufferErrorCode.OVERFLOW`.                                                          | Lets the consumer discard data it can no longer trust.             |
| **HAL.RINGBUF.21** | An overflow shall not corrupt a region the consumer currently holds through an outstanding acquire.                                             | A held region stays valid until released.                          |

### Notification

| #                  | Requirement                                                                                                                                                         | Comments                        |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------------------- | ------------------------------- |
| **HAL.RINGBUF.22** | `setNotificationThreshold()` shall reject a threshold below zero or above the buffer size with `EX_ILLEGAL_ARGUMENT`.                                               | Zero disables notifications.    |
| **HAL.RINGBUF.23** | Notifications shall be edge-triggered: after firing, no further notification shall be delivered until the level falls below the threshold and rises above it again. | Prevents notification flooding. |
| **HAL.RINGBUF.24** | `setNotificationThreshold()` shall deliver a notification immediately when the threshold is already met at the time of the call.                                    | Avoids a lost-wakeup race.      |
| **HAL.RINGBUF.25** | Listener callbacks shall be `oneway`, so that a slow or unresponsive client cannot block the implementation.                                                        |                                 |

### Flush and Disconnection

| #                  | Requirement                                                                                                                                        | Comments                                                   |
| ------------------ | -------------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------- |
| **HAL.RINGBUF.26** | `requestFlush()` shall reset the read and write positions and deliver `onFlushRequested()` to the producer.                                        |                                                            |
| **HAL.RINGBUF.27** | `requestFlush()` shall return without waiting for the producer to act; the producer's response is best-effort.                                     | Asynchronous by contract.                                  |
| **HAL.RINGBUF.28** | The implementation shall report peer loss through `onError()` with `PRODUCER_DISCONNECTED` or `CONSUMER_DISCONNECTED`.                             |                                                            |
| **HAL.RINGBUF.29** | On peer loss the implementation shall release that peer's registration and any outstanding acquires, returning the slot to its unregistered state. | A crashed peer must not permanently block re-registration. |
| **HAL.RINGBUF.30** | An `onError()` call shall carry a human-readable message; `IMPLEMENTATION_ERROR` shall always do so.                                               |                                                            |

### Ownership and Access

| #                  | Requirement                                                                                                                             | Comments                                     |
| ------------------ | --------------------------------------------------------------------------------------------------------------------------------------- | -------------------------------------------- |
| **HAL.RINGBUF.31** | `IRingBuffer` shall not be registered with the service manager and shall not be returned to a producer or a consumer.                   | Implementation-internal by design.           |
| **HAL.RINGBUF.32** | The owning HAL component shall publish only the endpoint a client needs — an `IRingBufferSink` or an `IRingBufferSource`.               | Clients never configure the buffer.          |
| **HAL.RINGBUF.33** | `IRingBuffer.getInfo()` shall return the current size, readable byte count and overflow setting, including before any client registers. | Lets the owner read back what it configured. |

### Peer Death

| #                  | Requirement                                                                                                                     | Comments                                   |
| ------------------ | ------------------------------------------------------------------------------------------------------------------------------- | ------------------------------------------ |
| **HAL.RINGBUF.34** | The implementation shall register a death recipient on each listener passed to `registerProducer()` / `registerConsumer()`.     | The listener is the client-hosted binder.  |
| **HAL.RINGBUF.35** | On producer death the implementation shall discard any acquire result the producer held, since it was never released.           | Uncommitted bytes must not become visible. |
| **HAL.RINGBUF.36** | On consumer death the implementation shall release any acquire results the consumer held, returning that space to the producer. |                                            |
| **HAL.RINGBUF.37** | Cleanup on peer death shall require no call from the surviving client; the slot shall be reusable without an unregister call.   | Recovery must not depend on the dead peer. |

---

## Design Principles

### Bytes Are Shared, Control Is Not

Payload never travels over Binder. Both sides map the same memory using the file descriptor obtained from
`getFileDescriptor()`, and read or write at the offsets returned by `acquire()`. Binder carries only the control
operations and the notifications.

The expected implementation is Linux shared memory, mappable with `mmap(2)` by both parties. That is not mandatory. An
implementation may instead back the buffer with a custom driver and DMA buffers, or with any descriptor supporting the
required access pattern — a device node or a socket, using the acquire offsets as seek positions. What matters is that
both sides agree on the semantics described here, not on the mechanism. No out-of-band synchronisation is permitted:
the AIDL interface is the only coordination channel.

The descriptor returned by `getFileDescriptor()` is a duplicate belonging to the caller, which must close it; calling
the method twice yields two descriptors and two obligations. Closing it is not the same as giving up the role, and
holding it is not the same as keeping one: the descriptor stays open as long as the caller leaves it open, but the
memory behind it is only meaningful while that client is registered. Once the registration ends — by unregistering, or
because the implementation reclaimed it after the client died — the mapping must not be read or written again, since
the region may already belong to a replacement. Unmap and close as part of unregistering.

### Control Belongs to the Owning Component

`IRingBuffer` is not part of the client-facing surface. It is held only by the HAL component that creates the buffer,
is never registered with the service manager, and is never returned to a producer or a consumer. Its absence of a
`serviceName` constant is deliberate, not an oversight.

This is why there is no client-facing way to set a size or an overflow policy. A client asks the owning HAL for a
stream of bytes; how much buffering that takes, and what happens when it fills, are properties of the component
providing the data, not of the client reading it. A client that needs different behaviour is asking for a different
configuration of the owning component, not of the buffer.

The owner can read back what it configured through `IRingBuffer.getInfo()`, which is available before any client has
registered.

### One Producer, One Consumer

A buffer has at most one registered producer and one registered consumer. Registration returns the corresponding
endpoint interface, and that endpoint is the client's claim on the role. The buffer does not multiplex: fan-out to
several consumers is the responsibility of whoever owns the buffer, not of this interface.

Size and overflow behaviour are fixed while either role is registered. Both `setSize()` and `setOverflowing()` throw
`EX_ILLEGAL_STATE` once a producer or consumer exists, so configuration belongs to the idle buffer, before any endpoint
is handed out.

A newly registered producer receives `onSpaceAvailable()` without having asked for it. This is deliberate: it tells the
producer how much room the buffer has, so it needs no separate query before its first write.

### Acquire and Release Bracket Every Access

Neither side touches the mapped memory except between a successful `acquire()` and its matching `release()`. The
acquire result carries four fields, and all four matter:

- `id` correlates the release with the acquire;
- `offset` is where in the mapping the region begins;
- `bytes` is how much was actually granted, which may be less than requested;
- `remaining` is what is left beyond the granted region.

`bytes` can fall short of the request because a region is always contiguous. Where the free or readable span wraps
around the end of the buffer, the acquire stops at the boundary and `remaining` reports the part at the beginning; a
second acquire collects it. This is why `remaining` can be non-zero even when `bytes` is less than requested, and why
neither side should read a short acquire as "the buffer is nearly empty".

The two sides have deliberately different rules:

- **The producer may hold only one outstanding acquire.** A second `acquire()` before `release()` throws
  `EX_ILLEGAL_STATE`. This keeps the write region contiguous and avoids fragmenting the buffer.
- **The consumer may hold several.** Calling `acquire()` again before releasing a previous result is allowed and does
  not throw. Each result carries its own ID, and results may be released **in any order** — the consumer is not
  required to release them in the order it acquired them. Space returns to the producer as each result is released.

The producer's `release()` takes a byte count as well as an ID, because a producer may write less than it acquired. The
unwritten remainder is not published to the consumer and stays available for a later acquire. The consumer's
`release()` takes only an ID: a reader consumes what it was given.

Once `release()` returns, the releasing side must not touch that region again. The opposite side is now entitled to it.

### Overflow Is a Per-Implementation Capability

`setOverflowing()` selects what happens when the producer outruns the consumer:

- **Overflowing.** The producer is never refused. `acquire()` succeeds even when the buffer is full, overwriting data
  the consumer has not yet read. The producer never stalls; data is lost instead.
- **Non-overflowing.** The producer's `acquire()` returns `null` when there is no space. No data is lost, but the
  producer must cope with being unable to write — by retrying after `onSpaceAvailable()`, or by dropping at source.

**The interface defines no default.** Which behaviours a ring buffer offers, and which one it starts in, are properties
of that implementation — a buffer backed by a driver ring may be physically incapable of blocking its producer, while
one backed by shared memory may support either. An implementation that offers only one behaviour rejects the other
with `EX_UNSUPPORTED_OPERATION` rather than silently ignoring the request.

The owning component must therefore set the behaviour it needs rather than assume one, and read back what it got
through `getInfo()`. Code that relies on an unstated default is relying on the platform it happened to be tested on.

An overflow is reported to the consumer through `onError()` with `RingBufferErrorCode.OVERFLOW`. The consumer should
treat data acquired around an overflow with suspicion: after an overwrite the readable span can mix newer and older
bytes, so it is contiguous neither in time nor in order. The error tells the consumer it may discard what it holds.

### Notification Is Edge-Triggered

Each endpoint sets a threshold with `setNotificationThreshold()`. The producer is notified through `onSpaceAvailable()`
when free space reaches its threshold; the consumer through `onDataAvailable()` when readable data reaches its. A
threshold of zero disables notification; the default is one byte.

Notifications are **edge-triggered**. After a notification fires, no further one is delivered until the level drops
back below the threshold and rises above it again. Without this rule a full buffer would notify continuously while the
client was unable to act.

Setting a threshold that is already satisfied delivers a notification immediately. This closes the race where a client
sets a threshold just after the level rose, and would otherwise wait for an edge that has already passed.

Both listener interfaces are `oneway`. Delivery is asynchronous and the implementation does not wait for the client to
return. A client must not call back into the endpoint from within the callback body; it may make those calls once the
callback has returned.

### Flush Resets Both Ends

`requestFlush()` is issued by the consumer. It resets the read and write positions and asks the producer, through
`onFlushRequested()`, to discard anything staged upstream so that no stale data arrives afterwards.

The call is asynchronous and returns before the producer has acted. The producer's response is best-effort — it may
have no internal buffers to discard, or may be unable to discard them. A consumer needing a hard discontinuity boundary
cannot rely on the flush alone.

The consumer should release any acquire results it holds before calling `requestFlush()`. A region acquired before the
flush refers to positions the flush has reset, so reading it afterwards yields arbitrary bytes.

### Disconnection Is an Error, Not Silence

`PRODUCER_DISCONNECTED` and `CONSUMER_DISCONNECTED` report that the peer has gone — a crash, or termination by the
system — rather than leaving the survivor to infer it from a buffer that has stopped moving.

The implementation must also act on it, not merely report it. When a peer is lost, its registration is released and
the slot returns to its unregistered state so that a replacement can register. A crashed producer must not leave a
buffer permanently unusable.

The mechanism is a death recipient. Each listener passed to `registerProducer()` or `registerConsumer()` is implemented
by the client, so from the implementation's side it is a remote proxy and supports `linkToDeath()`. The implementation
registers a death recipient on it at registration time and performs the cleanup when it fires. No extra interface or
token is needed — the listener already crosses the boundary in the right direction.

The two directions differ in what happens to the abandoned region. A producer's outstanding acquire is **discarded**:
it was never released, so it was never committed, and the consumer must not see it. A consumer's outstanding acquires
are **released**, returning that space to the producer, because the bytes were already committed and the consumer has
simply stopped reading them.

Cleanup requires nothing from the surviving client. It must not need an `unregisterProducer()` or
`unregisterConsumer()` call, since the only party that could pass the matching endpoint is the one that died.

`IMPLEMENTATION_ERROR` covers everything else, and carries detail in the message parameter.

### Information Is a Snapshot

`getInfo()` returns the buffer size, the currently readable byte count and the overflow setting. It is available on all
three interfaces, so the owning component can read back what it configured without waiting for a client to register.
The size and the overflow flag are stable while a client is registered; `availableForReading` is a snapshot that may be
stale before the call returns, because the other side runs concurrently.

Treat `availableForReading` as advisory — useful for metrics or coarse decisions. `acquire()` is the authoritative
operation, and its `bytes` field is the only trustworthy statement of what the caller may access.

`RingBufferInfo` deliberately omits the space available for writing, because it can be derived from the size and the
readable count.

## Concurrency

The implementation serialises its own state; clients do not need to lock around individual calls. A client that shares
an endpoint between its own threads owns that synchronisation, including the producer's single-outstanding-acquire
rule.

Callbacks arrive on a Binder thread, not on the caller's thread. An `OVERFLOW` error in particular can be raised as a
consequence of an acquire that is in progress, so a client must not hold a lock during `acquire()` that its callback
handler also needs.
