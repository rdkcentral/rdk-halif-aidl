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
package com.rdk.hal.videosink;

/**
 * @brief     The figures videosink measures.
 * @author    Gerald Weatherup
 */

/**
 * @brief The figures videosink measures.
 *
 * Each member states its unit and kind. `MetricValue.id` carries the member's
 * value, which is scoped to this component. Values are append-only.
 */

@VintfStability
@Backing(type="long")
enum Metric
{

    /**
     * Unit: frames. Kind: counter. Decoded frames received from the decoder to
     * be presented.
     */
    FRAMES_RECEIVED = 0,

    /**
     * Unit: frames. Kind: counter. Frames handed to display scanout for
     * presentation, one per successful render.
     */
    FRAMES_PRESENTED = 1,

    /**
     * Unit: frames. Kind: counter. Frames dropped because their PTS deadline
     * against the render clock had passed by more than one display frame
     * interval at the sink render check — too late to show. Sink
     * render-decision internal.
     */
    FRAMES_DROPPED_LATE = 2,

    /**
     * Unit: frames. Kind: counter. Frames dropped by frame-rate conversion
     * when the source rate exceeds the display rate, which is cadence
     * decimation rather than lateness.
     */
    FRAMES_DROPPED_FRC = 3,

    /**
     * Unit: frames. Kind: counter. Frames held for more than one display
     * interval by frame-rate conversion when the source rate is below the
     * display rate. Normal content cadence, and not a freeze.
     */
    FRAMES_REPEATED_FRC = 4,

    /**
     * Unit: frames. Kind: counter. Frames repeated to cover a missing next
     * frame — the sink had no new decoded frame ready at render time. This is
     * starvation cover, and it is what FREEZE_DURATION_MS integrates.
     */
    FRAMES_REPEATED_MISSING_FRAME = 5,

    /**
     * Unit: episodes. Kind: counter. Count of video buffer-underflow episodes.
     * One per episode start, where an episode starts when there is no frame to
     * present at render time and ends when a new frame is presented.
     */
    UNDERFLOWED = 6,

    /**
     * Unit: ms. Kind: counter. Cumulative wall-clock time across all video
     * underflow episodes. Paired with underflowed, so the mean episode length
     * is this divided by that. An underflow episode manifests on screen as a
     * freeze.
     */
    UNDERFLOW_DURATION_MS = 7,

    /**
     * Unit: ms. Kind: counter. Cumulative on-screen time the same frame was
     * held to cover a missing frame, which is the customer-visible freeze —
     * the time integral of FRAMES_REPEATED_MISSING_FRAME. Excludes
     * frame-rate-conversion cadence repeats, which are not freezes.
     */
    FREEZE_DURATION_MS = 8,

    /**
     * Unit: events. Kind: counter. Count of freeze episodes, one per episode
     * start. Paired with FREEZE_DURATION_MS, so the mean freeze length is that
     * divided by this.
     */
    FREEZE_EVENT_COUNT = 9,

    /**
     * Unit: ms. Kind: high_water. Longest single freeze episode observed. A
     * monotone non-decreasing high-water mark over the life of the resource,
     * and read-only: a maximum cannot be recovered by differencing two maxima,
     * so a consumer wanting the worst freeze within its own reporting window
     * tracks that itself from LAST_FREEZE_DURATION_MS rather than resetting a
     * figure other readers share.
     */
    MAX_FREEZE_DURATION_MS = 10,

    /**
     * Unit: us. Kind: counter. Running sum of per-frame render latency, from a
     * frame arriving at the sink input to being presented to scanout. Paired
     * with FRAMES_PRESENTED.
     */
    RENDER_LATENCY_SUM_US = 11,

    /**
     * Unit: ms. Kind: current. Buffered decoded media ahead of the present
     * position now — the sum of presentation durations of frames queued but
     * not yet presented. A live sample re-read each capture rather than a
     * cumulative figure. This is SoC- and use-case-specific, so compare it
     * against itself over time rather than across products.
     */
    BUFFER_DEPTH_MS = 12,

    /**
     * Unit: none. Kind: current. Cause of the most recent underflow episode,
     * which is what distinguishes an expected starvation from a defect.
     *
     * The value is a `MetricUnderflowTrigger`.
     */
    LAST_UNDERFLOW_TRIGGER = 13,

    /**
     * Unit: ms. Kind: current. Length of the most recent completed underflow
     * episode. Read with underflowed and UNDERFLOW_DURATION_MS, which give the
     * count and the total.
     */
    LAST_UNDERFLOW_DURATION_MS = 14,

    /**
     * Unit: ms. Kind: current. Stream PTS of the most recently dropped frame,
     * within one frame interval, whichever drop axis it fell on. This is what
     * turns a drop count into a locatable defect. Left undeclared where no PTS
     * is derivable.
     */
    LAST_DROPPED_FRAME_PTS_MS = 15,

    /**
     * Unit: ms. Kind: current. Stream PTS at which the most recent freeze
     * episode began, within one frame interval. Does for a freeze what
     * LAST_DROPPED_FRAME_PTS_MS does for a drop. Left undeclared where no PTS
     * is derivable.
     */
    LAST_FREEZE_PTS_MS = 16,

    /**
     * Unit: ms. Kind: current. Length of the most recent completed freeze
     * episode. Read with FREEZE_EVENT_COUNT and FREEZE_DURATION_MS for the
     * count and the total, and with MAX_FREEZE_DURATION_MS for the worst.
     */
    LAST_FREEZE_DURATION_MS = 17,

    /**
     * Unit: ms. Kind: current. PTS of the first frame to reach presentation,
     * set at session start and re-set after each seek or flush. This is the
     * hardware's contribution to time-to-first-frame; whatever elapsed above
     * the HAL before decode began is observed by the party that started the
     * session.
     */
    FIRST_FRAME_PRESENTED_PTS_MS = 18,
}
