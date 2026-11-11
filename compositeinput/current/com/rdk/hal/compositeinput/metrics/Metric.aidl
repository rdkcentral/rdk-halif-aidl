/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
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
 */
package com.rdk.hal.compositeinput.metrics;

/**
 * @brief Metrics served by the composite input port.
 *
 * Read with ICompositeInputPort.getMetrics() or getMetric(). Values are
 * append-only: a member is never renumbered or reused. Each counter starts
 * at zero when the service initialises, only rises, and is kept per
 * resource instance.
 */
@VintfStability
@Backing(type = "int")
enum Metric {
    /**
     * @brief Signal locks acquired.
     *
     * Measures: successful acquisitions of signal lock on the port,
     * counted when lock is gained.
     *
     * Excludes: acquisitions that end without lock.
     *
     * Used for: judging how often the input has to find its signal.
     *
     * How to use: difference two snapshots. Divide the difference of
     * LOCK_ACQUISITION_TIME_NS by it for the mean time to lock.
     *
     * Unit: locks. Kind: counter. Support: optional.
     */
    SIGNAL_LOCKS = 0,

    /**
     * @brief Signal locks lost.
     *
     * Measures: losses of an acquired lock while the port is STARTED,
     * counted when lock is lost; one per Episode::SIGNAL_LOSS episode.
     *
     * Excludes: lock released by stop() or close().
     *
     * Used for: measuring the stability of the incoming signal.
     *
     * How to use: difference two snapshots and divide by the
     * difference of STARTED_DURATION_NS for drops per unit time.
     *
     * Unit: drops. Kind: counter. Support: optional.
     */
    SIGNAL_DROPS = 1,

    /**
     * @brief Total time spent acquiring signal lock.
     *
     * Measures: time from the start of each acquisition, at start() or
     * when a signal appears, to lock being gained, summed over the
     * acquisitions counted by SIGNAL_LOCKS.
     *
     * Excludes: acquisitions that end without lock.
     *
     * Used for: measuring how long the viewer waits for a picture.
     *
     * How to use: mean time to lock = delta LOCK_ACQUISITION_TIME_NS /
     * delta SIGNAL_LOCKS between two snapshots.
     *
     * Unit: nanoseconds. Kind: counter. Support: optional.
     */
    LOCK_ACQUISITION_TIME_NS = 2,

    /**
     * @brief Time the most recent signal lock took to acquire.
     *
     * Measures: the acquisition time, as counted in
     * LOCK_ACQUISITION_TIME_NS, of the most recent acquisition that
     * gained lock.
     *
     * Excludes: acquisitions still in progress; before the first lock
     * the metric has no value and is left out of the snapshot.
     *
     * Used for: checking the time to lock after a source change.
     *
     * How to use: read it after a lock; it is a level, so do not
     * difference it.
     *
     * Unit: nanoseconds. Kind: gauge. Support: optional.
     */
    LAST_LOCK_ACQUISITION_TIME_NS = 3,

    /**
     * @brief Total time the port has been STARTED.
     *
     * Measures: time the port spent in the STARTED state, summed over
     * every session and including the elapsed part of a session still
     * running at the latch.
     *
     * Excludes: time in any other state.
     *
     * Used for: normalising drops and locks to the time the input was
     * in use.
     *
     * How to use: difference two snapshots and use it as the
     * denominator of per-time rates.
     *
     * Unit: nanoseconds. Kind: counter. Support: optional.
     */
    STARTED_DURATION_NS = 4,
}
