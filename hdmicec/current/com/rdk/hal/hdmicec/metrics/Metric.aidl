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
package com.rdk.hal.hdmicec.metrics;

/**
 * @brief Metrics served by the CEC service.
 *
 * Read with IHdmiCec.getMetrics() or getMetric(). Values are append-only:
 * a member is never renumbered or reused. Each counter starts at zero when
 * the service initialises, only rises, and is kept per resource instance.
 */
@VintfStability
@Backing(type = "int")
enum Metric {
    /**
     * @brief Directed messages sent.
     *
     * Measures: messages to one logical address passed to
     * sendMessage() and transmitted, counted once per message whatever
     * the retries.
     *
     * Excludes: broadcast messages (BROADCAST_MESSAGES_SENT) and
     * messages never transmitted because arbitration was lost on every
     * attempt.
     *
     * Used for: measuring CEC traffic sent by the device.
     *
     * How to use: difference two snapshots; compare with
     * DIRECTED_MESSAGES_ACKED for the delivery ratio.
     *
     * Unit: messages. Kind: counter.
     */
    DIRECTED_MESSAGES_SENT = 0,

    /**
     * @brief Broadcast messages sent.
     *
     * Measures: messages to the broadcast address passed to
     * sendMessage() and transmitted, counted once per message whatever
     * the retries.
     *
     * Excludes: directed messages (DIRECTED_MESSAGES_SENT) and
     * messages never transmitted because arbitration was lost on every
     * attempt.
     *
     * Used for: measuring CEC traffic sent by the device.
     *
     * How to use: difference two snapshots; compare with
     * BROADCAST_MESSAGES_ACKED for the delivery ratio.
     *
     * Unit: messages. Kind: counter.
     */
    BROADCAST_MESSAGES_SENT = 1,

    /**
     * @brief Directed messages acknowledged.
     *
     * Measures: directed messages counted by DIRECTED_MESSAGES_SENT
     * whose acknowledge bit was set by the follower.
     *
     * Excludes: messages not acknowledged after the last retry.
     *
     * Used for: finding a follower that does not answer.
     *
     * How to use: delivery ratio = delta DIRECTED_MESSAGES_ACKED /
     * delta DIRECTED_MESSAGES_SENT between two snapshots.
     *
     * Unit: messages. Kind: counter.
     */
    DIRECTED_MESSAGES_ACKED = 2,

    /**
     * @brief Broadcast messages not rejected.
     *
     * Measures: broadcast messages counted by BROADCAST_MESSAGES_SENT
     * that no follower rejected; the acknowledge bit of a broadcast
     * has the inverted sense of the CEC specification.
     *
     * Excludes: messages rejected by a follower after the last retry.
     *
     * Used for: finding a follower that rejects broadcasts.
     *
     * How to use: delivery ratio = delta BROADCAST_MESSAGES_ACKED /
     * delta BROADCAST_MESSAGES_SENT between two snapshots.
     *
     * Unit: messages. Kind: counter.
     */
    BROADCAST_MESSAGES_ACKED = 3,

    /**
     * @brief Bus arbitrations lost.
     *
     * Measures: transmission attempts that lost arbitration for the
     * CEC bus to another initiator, counted at each attempt, retries
     * included.
     *
     * Excludes: attempts that won arbitration and then failed for
     * another reason.
     *
     * Used for: measuring contention on the CEC bus.
     *
     * How to use: difference two snapshots and divide by the
     * difference in timestampNs for failures per unit time.
     *
     * Unit: attempts. Kind: counter.
     */
    ARBITRATION_FAILURES = 4,
}
