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
package com.rdk.hal.metrics;


/**
 *  @brief     Every metric this interface can serve, keyed by group block.
 *
 *  GENERATED from docs/av_field_dictionary.md by scripts/dictionary-ids.py.
 *  Do not hand-edit - add the field to the dictionary and re-run --emit-aidl.
 *
 *  The name is a direct transliteration of the declared name, so
 *  AV_VIDEO_DECODER_FRAMES_DECODED and `av.video_decoder.frames_decoded` are
 *  visibly the same thing.
 *
 *  Values are banded by group: `metricId / 1000` is the MetricGroup ordinal.
 *  Extending is appending inside a band; an existing value never moves,
 *  because a consumer that cached the mapping would otherwise read a
 *  different field under the value it already knows.
 *
 *  A value's presence here says the interface can carry it. Whether a given
 *  product serves it is `getGroupMetrics()` at runtime - a product that cannot
 *  measure a figure omits it rather than returning 0.
 */
@VintfStability
@Backing(type="int")
enum MetricId {

    /* ---- av.video_decoder ---- */

    /** frames - counter. `av.video_decoder.frames_decoded` */
    AV_VIDEO_DECODER_FRAMES_DECODED = 0,

    /** frames - counter. `av.video_decoder.frames_dropped` */
    AV_VIDEO_DECODER_FRAMES_DROPPED = 1,

    /** events - counter. `av.video_decoder.decode_errors` */
    AV_VIDEO_DECODER_DECODE_ERRORS = 2,

    /** us - counter. `av.video_decoder.decode_latency_sum_us` */
    AV_VIDEO_DECODER_DECODE_LATENCY_SUM_US = 3,

    /** ms - current. `av.video_decoder.last_decode_error_pts_ms` */
    AV_VIDEO_DECODER_LAST_DECODE_ERROR_PTS_MS = 4,

    /** none - current. `av.video_decoder.last_decode_error_reason` */
    AV_VIDEO_DECODER_LAST_DECODE_ERROR_REASON = 5,

    /** none - current. `av.video_decoder.last_decode_error_vendor_code` */
    AV_VIDEO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE = 6,

    /* ---- av.video_sink ---- */

    /** frames - counter. `av.video_sink.frames_received` */
    AV_VIDEO_SINK_FRAMES_RECEIVED = 1000,

    /** frames - counter. `av.video_sink.frames_presented` */
    AV_VIDEO_SINK_FRAMES_PRESENTED = 1001,

    /** frames - counter. `av.video_sink.frames_dropped_late` */
    AV_VIDEO_SINK_FRAMES_DROPPED_LATE = 1002,

    /** frames - counter. `av.video_sink.frames_dropped_frc` */
    AV_VIDEO_SINK_FRAMES_DROPPED_FRC = 1003,

    /** frames - counter. `av.video_sink.frames_repeated_frc` */
    AV_VIDEO_SINK_FRAMES_REPEATED_FRC = 1004,

    /** frames - counter. `av.video_sink.frames_repeated_missing_frame` */
    AV_VIDEO_SINK_FRAMES_REPEATED_MISSING_FRAME = 1005,

    /** episodes - counter. `av.video_sink.underflowed` */
    AV_VIDEO_SINK_UNDERFLOWED = 1006,

    /** ms - counter. `av.video_sink.underflow_duration_ms` */
    AV_VIDEO_SINK_UNDERFLOW_DURATION_MS = 1007,

    /** ms - counter. `av.video_sink.freeze_duration_ms` */
    AV_VIDEO_SINK_FREEZE_DURATION_MS = 1008,

    /** events - counter. `av.video_sink.freeze_event_count` */
    AV_VIDEO_SINK_FREEZE_EVENT_COUNT = 1009,

    /** ms - high_water. `av.video_sink.max_freeze_duration_ms` */
    AV_VIDEO_SINK_MAX_FREEZE_DURATION_MS = 1010,

    /** us - counter. `av.video_sink.render_latency_sum_us` */
    AV_VIDEO_SINK_RENDER_LATENCY_SUM_US = 1011,

    /** ms - current. `av.video_sink.buffer_depth_ms` */
    AV_VIDEO_SINK_BUFFER_DEPTH_MS = 1012,

    /** none - current. `av.video_sink.last_underflow_trigger` */
    AV_VIDEO_SINK_LAST_UNDERFLOW_TRIGGER = 1013,

    /** ms - current. `av.video_sink.last_underflow_duration_ms` */
    AV_VIDEO_SINK_LAST_UNDERFLOW_DURATION_MS = 1014,

    /** ms - current. `av.video_sink.last_dropped_frame_pts_ms` */
    AV_VIDEO_SINK_LAST_DROPPED_FRAME_PTS_MS = 1015,

    /** ms - current. `av.video_sink.first_frame_presented_pts_ms` */
    AV_VIDEO_SINK_FIRST_FRAME_PRESENTED_PTS_MS = 1016,

    /* ---- av.audio_decoder ---- */

    /** frames - counter. `av.audio_decoder.frames_decoded` */
    AV_AUDIO_DECODER_FRAMES_DECODED = 2000,

    /** frames - counter. `av.audio_decoder.frames_dropped` */
    AV_AUDIO_DECODER_FRAMES_DROPPED = 2001,

    /** events - counter. `av.audio_decoder.decode_errors` */
    AV_AUDIO_DECODER_DECODE_ERRORS = 2002,

    /** us - counter. `av.audio_decoder.decode_latency_sum_us` */
    AV_AUDIO_DECODER_DECODE_LATENCY_SUM_US = 2003,

    /** ms - current. `av.audio_decoder.last_decode_error_pts_ms` */
    AV_AUDIO_DECODER_LAST_DECODE_ERROR_PTS_MS = 2004,

    /** none - current. `av.audio_decoder.last_decode_error_reason` */
    AV_AUDIO_DECODER_LAST_DECODE_ERROR_REASON = 2005,

    /** none - current. `av.audio_decoder.last_decode_error_vendor_code` */
    AV_AUDIO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE = 2006,

    /* ---- av.audio_sink ---- */

    /** episodes - counter. `av.audio_sink.underflowed` */
    AV_AUDIO_SINK_UNDERFLOWED = 3000,

    /** ms - counter. `av.audio_sink.underflow_duration_ms` */
    AV_AUDIO_SINK_UNDERFLOW_DURATION_MS = 3001,

    /** ms - counter. `av.audio_sink.silence_duration_ms` */
    AV_AUDIO_SINK_SILENCE_DURATION_MS = 3002,

    /** events - counter. `av.audio_sink.silence_event_count` */
    AV_AUDIO_SINK_SILENCE_EVENT_COUNT = 3003,

    /** ms - current. `av.audio_sink.buffer_depth_ms` */
    AV_AUDIO_SINK_BUFFER_DEPTH_MS = 3004,

    /** none - current. `av.audio_sink.last_underflow_trigger` */
    AV_AUDIO_SINK_LAST_UNDERFLOW_TRIGGER = 3005,

    /** ms - current. `av.audio_sink.last_underflow_duration_ms` */
    AV_AUDIO_SINK_LAST_UNDERFLOW_DURATION_MS = 3006,

    /** ms - current. `av.audio_sink.last_silence_duration_ms` */
    AV_AUDIO_SINK_LAST_SILENCE_DURATION_MS = 3007,

    /* ---- av.clock ---- */

    /** ms - current. `av.clock.sync_offset_ms` */
    AV_CLOCK_SYNC_OFFSET_MS = 4000,

    /** ms - high_water. `av.clock.sync_max_abs_offset_ms` */
    AV_CLOCK_SYNC_MAX_ABS_OFFSET_MS = 4001,

    /** ms - counter. `av.clock.sync_time_over_threshold_ms` */
    AV_CLOCK_SYNC_TIME_OVER_THRESHOLD_MS = 4002,

    /** ms - config, writable. `av.clock.sync_threshold_ms` */
    AV_CLOCK_SYNC_THRESHOLD_MS = 4003,

    /** events - counter. `av.clock.resync_count` */
    AV_CLOCK_RESYNC_COUNT = 4004,

    /** ms - counter. `av.clock.resync_magnitude_sum_ms` */
    AV_CLOCK_RESYNC_MAGNITUDE_SUM_MS = 4005,

    /* ---- av.session ---- */

    /** ms - counter. `av.session.time_playing_ms` */
    AV_SESSION_TIME_PLAYING_MS = 5000,

    /** ms - counter. `av.session.time_buffering_ms` */
    AV_SESSION_TIME_BUFFERING_MS = 5001,

    /** ms - current. `av.session.preroll_ms` */
    AV_SESSION_PREROLL_MS = 5002,

    /** events - counter. `av.session.seek_count` */
    AV_SESSION_SEEK_COUNT = 5003,

    /* ---- av.admission ---- */

    /** events - counter. `av.admission.denied_count` */
    AV_ADMISSION_DENIED_COUNT = 6000,

    /** events - counter. `av.admission.reclaim_count` */
    AV_ADMISSION_RECLAIM_COUNT = 6001,

    /* ---- health.poll ---- */

    /** ms - current. `health.poll.poll_period_ms` */
    HEALTH_POLL_POLL_PERIOD_MS = 7000,

    /** events - counter. `health.poll.poll_overrun_count` */
    HEALTH_POLL_POLL_OVERRUN_COUNT = 7001,

    /** ms - current. `health.poll.state_age_ms` */
    HEALTH_POLL_STATE_AGE_MS = 7002,
}