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
 *  @brief     Declared metric names and their contract ids.
 *
 *  GENERATED from av-field-dictionary.yaml by scripts/dictionary-ids.py. Do not hand-edit.
 *  Add the field to the HFD and re-run --generate.
 *
 *  A name constant spares a client a string literal it can mistype; the
 *  matching `_ID` is what it compares against `MetricFieldInfo.id` to confirm
 *  the product means the same thing by that name. A name that still matches
 *  while the unit or kind changed underneath is the failure these ids exist
 *  to catch.
 *
 *  These are the three-segment `<domain>.<element>.<field>` forms. A runtime
 *  name carries the instance too - `av.video_decoder.0.frames_decoded` - so a
 *  client composes the instance in, or matches on the trailing segments.
 *
 *  Constants only; this interface publishes no service and declares no methods.
 */
@VintfStability
interface MetricNames
{

    /* ---- av.video_decoder ---- */

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_DECODER_FRAMES_DECODED = "av.video_decoder.frames_decoded";
    const long AV_VIDEO_DECODER_FRAMES_DECODED_ID = 7190028136814733123;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_DECODER_FRAMES_DROPPED = "av.video_decoder.frames_dropped";
    const long AV_VIDEO_DECODER_FRAMES_DROPPED_ID = 3199765258934579127;

    /** events - counter */
    const @utf8InCpp String AV_VIDEO_DECODER_DECODE_ERRORS = "av.video_decoder.decode_errors";
    const long AV_VIDEO_DECODER_DECODE_ERRORS_ID = 507699468656658811;

    /** us - counter */
    const @utf8InCpp String AV_VIDEO_DECODER_DECODE_LATENCY_SUM_US = "av.video_decoder.decode_latency_sum_us";
    const long AV_VIDEO_DECODER_DECODE_LATENCY_SUM_US_ID = 5650252581706219703;

    /** ms - current */
    const @utf8InCpp String AV_VIDEO_DECODER_LAST_DECODE_ERROR_PTS_MS = "av.video_decoder.last_decode_error_pts_ms";
    const long AV_VIDEO_DECODER_LAST_DECODE_ERROR_PTS_MS_ID = 1503848029790550548;

    /** none - current */
    const @utf8InCpp String AV_VIDEO_DECODER_LAST_DECODE_ERROR_REASON = "av.video_decoder.last_decode_error_reason";
    const long AV_VIDEO_DECODER_LAST_DECODE_ERROR_REASON_ID = 5753957915196644361;

    /** none - current */
    const @utf8InCpp String AV_VIDEO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE = "av.video_decoder.last_decode_error_vendor_code";
    const long AV_VIDEO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE_ID = 2797173010128363476;


    /* ---- av.video_sink ---- */

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_RECEIVED = "av.video_sink.frames_received";
    const long AV_VIDEO_SINK_FRAMES_RECEIVED_ID = 5930257673774174338;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_PRESENTED = "av.video_sink.frames_presented";
    const long AV_VIDEO_SINK_FRAMES_PRESENTED_ID = 9166715668128979770;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_DROPPED_LATE = "av.video_sink.frames_dropped_late";
    const long AV_VIDEO_SINK_FRAMES_DROPPED_LATE_ID = 8539598620879275221;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_DROPPED_FRC = "av.video_sink.frames_dropped_frc";
    const long AV_VIDEO_SINK_FRAMES_DROPPED_FRC_ID = 7801355324249750808;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_REPEATED_FRC = "av.video_sink.frames_repeated_frc";
    const long AV_VIDEO_SINK_FRAMES_REPEATED_FRC_ID = 8266879710427280043;

    /** frames - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FRAMES_REPEATED_MISSING_FRAME = "av.video_sink.frames_repeated_missing_frame";
    const long AV_VIDEO_SINK_FRAMES_REPEATED_MISSING_FRAME_ID = 6513661011326852780;

    /** episodes - counter */
    const @utf8InCpp String AV_VIDEO_SINK_UNDERFLOWED = "av.video_sink.underflowed";
    const long AV_VIDEO_SINK_UNDERFLOWED_ID = 7495327176495149441;

    /** ms - counter */
    const @utf8InCpp String AV_VIDEO_SINK_UNDERFLOW_DURATION_MS = "av.video_sink.underflow_duration_ms";
    const long AV_VIDEO_SINK_UNDERFLOW_DURATION_MS_ID = 2586573105278991764;

    /** ms - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FREEZE_DURATION_MS = "av.video_sink.freeze_duration_ms";
    const long AV_VIDEO_SINK_FREEZE_DURATION_MS_ID = 2055547844275425544;

    /** events - counter */
    const @utf8InCpp String AV_VIDEO_SINK_FREEZE_EVENT_COUNT = "av.video_sink.freeze_event_count";
    const long AV_VIDEO_SINK_FREEZE_EVENT_COUNT_ID = 5879157403639982081;

    /** ms - high_water */
    const @utf8InCpp String AV_VIDEO_SINK_MAX_FREEZE_DURATION_MS = "av.video_sink.max_freeze_duration_ms";
    const long AV_VIDEO_SINK_MAX_FREEZE_DURATION_MS_ID = 616256046675117369;

    /** us - counter */
    const @utf8InCpp String AV_VIDEO_SINK_RENDER_LATENCY_SUM_US = "av.video_sink.render_latency_sum_us";
    const long AV_VIDEO_SINK_RENDER_LATENCY_SUM_US_ID = 8500652570172502029;

    /** ms - current */
    const @utf8InCpp String AV_VIDEO_SINK_BUFFER_DEPTH_MS = "av.video_sink.buffer_depth_ms";
    const long AV_VIDEO_SINK_BUFFER_DEPTH_MS_ID = 1233285642918160019;

    /** none - current */
    const @utf8InCpp String AV_VIDEO_SINK_LAST_UNDERFLOW_TRIGGER = "av.video_sink.last_underflow_trigger";
    const long AV_VIDEO_SINK_LAST_UNDERFLOW_TRIGGER_ID = 225476305547188054;

    /** ms - current */
    const @utf8InCpp String AV_VIDEO_SINK_LAST_UNDERFLOW_DURATION_MS = "av.video_sink.last_underflow_duration_ms";
    const long AV_VIDEO_SINK_LAST_UNDERFLOW_DURATION_MS_ID = 8871762138430500635;

    /** ms - current */
    const @utf8InCpp String AV_VIDEO_SINK_LAST_DROPPED_FRAME_PTS_MS = "av.video_sink.last_dropped_frame_pts_ms";
    const long AV_VIDEO_SINK_LAST_DROPPED_FRAME_PTS_MS_ID = 1039496017913387229;

    /** ms - current */
    const @utf8InCpp String AV_VIDEO_SINK_FIRST_FRAME_PRESENTED_PTS_MS = "av.video_sink.first_frame_presented_pts_ms";
    const long AV_VIDEO_SINK_FIRST_FRAME_PRESENTED_PTS_MS_ID = 6263076687653359064;


    /* ---- av.audio_decoder ---- */

    /** frames - counter */
    const @utf8InCpp String AV_AUDIO_DECODER_FRAMES_DECODED = "av.audio_decoder.frames_decoded";
    const long AV_AUDIO_DECODER_FRAMES_DECODED_ID = 2578674205185167365;

    /** frames - counter */
    const @utf8InCpp String AV_AUDIO_DECODER_FRAMES_DROPPED = "av.audio_decoder.frames_dropped";
    const long AV_AUDIO_DECODER_FRAMES_DROPPED_ID = 8398227945244922781;

    /** events - counter */
    const @utf8InCpp String AV_AUDIO_DECODER_DECODE_ERRORS = "av.audio_decoder.decode_errors";
    const long AV_AUDIO_DECODER_DECODE_ERRORS_ID = 6304448083405003412;

    /** us - counter */
    const @utf8InCpp String AV_AUDIO_DECODER_DECODE_LATENCY_SUM_US = "av.audio_decoder.decode_latency_sum_us";
    const long AV_AUDIO_DECODER_DECODE_LATENCY_SUM_US_ID = 1963176479211944050;

    /** ms - current */
    const @utf8InCpp String AV_AUDIO_DECODER_LAST_DECODE_ERROR_PTS_MS = "av.audio_decoder.last_decode_error_pts_ms";
    const long AV_AUDIO_DECODER_LAST_DECODE_ERROR_PTS_MS_ID = 6722215681813695422;

    /** none - current */
    const @utf8InCpp String AV_AUDIO_DECODER_LAST_DECODE_ERROR_REASON = "av.audio_decoder.last_decode_error_reason";
    const long AV_AUDIO_DECODER_LAST_DECODE_ERROR_REASON_ID = 1178095613798319143;

    /** none - current */
    const @utf8InCpp String AV_AUDIO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE = "av.audio_decoder.last_decode_error_vendor_code";
    const long AV_AUDIO_DECODER_LAST_DECODE_ERROR_VENDOR_CODE_ID = 8154299594531677909;


    /* ---- av.audio_sink ---- */

    /** episodes - counter */
    const @utf8InCpp String AV_AUDIO_SINK_UNDERFLOWED = "av.audio_sink.underflowed";
    const long AV_AUDIO_SINK_UNDERFLOWED_ID = 1454532482434647209;

    /** ms - counter */
    const @utf8InCpp String AV_AUDIO_SINK_UNDERFLOW_DURATION_MS = "av.audio_sink.underflow_duration_ms";
    const long AV_AUDIO_SINK_UNDERFLOW_DURATION_MS_ID = 5541259915310371762;

    /** ms - counter */
    const @utf8InCpp String AV_AUDIO_SINK_SILENCE_DURATION_MS = "av.audio_sink.silence_duration_ms";
    const long AV_AUDIO_SINK_SILENCE_DURATION_MS_ID = 719957973796843592;

    /** events - counter */
    const @utf8InCpp String AV_AUDIO_SINK_SILENCE_EVENT_COUNT = "av.audio_sink.silence_event_count";
    const long AV_AUDIO_SINK_SILENCE_EVENT_COUNT_ID = 3853488905361899822;

    /** ms - current */
    const @utf8InCpp String AV_AUDIO_SINK_BUFFER_DEPTH_MS = "av.audio_sink.buffer_depth_ms";
    const long AV_AUDIO_SINK_BUFFER_DEPTH_MS_ID = 1939450312673878711;

    /** none - current */
    const @utf8InCpp String AV_AUDIO_SINK_LAST_UNDERFLOW_TRIGGER = "av.audio_sink.last_underflow_trigger";
    const long AV_AUDIO_SINK_LAST_UNDERFLOW_TRIGGER_ID = 4645210446510350471;

    /** ms - current */
    const @utf8InCpp String AV_AUDIO_SINK_LAST_UNDERFLOW_DURATION_MS = "av.audio_sink.last_underflow_duration_ms";
    const long AV_AUDIO_SINK_LAST_UNDERFLOW_DURATION_MS_ID = 7174024267432445221;

    /** ms - current */
    const @utf8InCpp String AV_AUDIO_SINK_LAST_SILENCE_DURATION_MS = "av.audio_sink.last_silence_duration_ms";
    const long AV_AUDIO_SINK_LAST_SILENCE_DURATION_MS_ID = 2087572991653260931;


    /* ---- av.clock ---- */

    /** ms - current */
    const @utf8InCpp String AV_CLOCK_SYNC_OFFSET_MS = "av.clock.sync_offset_ms";
    const long AV_CLOCK_SYNC_OFFSET_MS_ID = 600075541413833688;

    /** ms - high_water */
    const @utf8InCpp String AV_CLOCK_SYNC_MAX_ABS_OFFSET_MS = "av.clock.sync_max_abs_offset_ms";
    const long AV_CLOCK_SYNC_MAX_ABS_OFFSET_MS_ID = 2364547409182921257;

    /** ms - counter */
    const @utf8InCpp String AV_CLOCK_SYNC_TIME_OVER_THRESHOLD_MS = "av.clock.sync_time_over_threshold_ms";
    const long AV_CLOCK_SYNC_TIME_OVER_THRESHOLD_MS_ID = 3619829115112350604;

    /** ms - config, writable */
    const @utf8InCpp String AV_CLOCK_SYNC_THRESHOLD_MS = "av.clock.sync_threshold_ms";
    const long AV_CLOCK_SYNC_THRESHOLD_MS_ID = 5519190410972100983;

    /** events - counter */
    const @utf8InCpp String AV_CLOCK_RESYNC_COUNT = "av.clock.resync_count";
    const long AV_CLOCK_RESYNC_COUNT_ID = 2166707080359975513;

    /** ms - counter */
    const @utf8InCpp String AV_CLOCK_RESYNC_MAGNITUDE_SUM_MS = "av.clock.resync_magnitude_sum_ms";
    const long AV_CLOCK_RESYNC_MAGNITUDE_SUM_MS_ID = 8927572216676754297;

}
