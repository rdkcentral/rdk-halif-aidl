# AV Clock Overview

The AV Clock HAL service establishes synchronization between audio and video sinks, enabling lip-sync playback by driving them from a shared clock.

In broadcast scenarios, the Program Clock Reference (PCR) is provided to the AV Clock HAL. This allows the local System Time Clock (STC) to be synchronized with the broadcast encoder's timing, crucial for preventing buffer underflow or overflow.

For IP streaming, clients can manipulate the playback rate, facilitating pause functionality and fine-grained adjustments for clock synchronization with other devices or streams.

Audio and video sinks associated with a given AV Clock instance comprise a synchronization group.  Members of a sync group share a common presentation clock.  The AV Clock HAL provides an interface for the application to define the composition of these sync groups, specifying the video sink and the associated audio sink(s).
