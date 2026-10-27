#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/InputRouting.h>
#include <com/rdk/hal/audiomixer/Property.h>
#include <com/rdk/hal/audiosink/VolumeRamp.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief     Audio Mixer Controller HAL interface.
 * Provides stateful and runtime control over a specific platform audio mixer resource.
 *            This includes lifecycle management (start/stop), flushing, signalling end-of-stream,
 *            routing configuration, and property configuration. Intended for use by the
 *            middleware audio server and platform integrators.
 *
 *            <h3>Mix policy and clipping</h3>
 *            The mixer guarantees the output signal will not clip. When the sum of active
 *            input contributions (per-input volume × input signal level) would exceed full
 *            scale, the HAL applies headroom management — typically a soft limiter on the
 *            master mix bus or master attenuation. The exact mechanism is a vendor
 *            implementation detail; what is guaranteed is that the output stays within
 *            full scale.
 *
 *            Per-input volumes set via setInputVolume() / setInputVolumeRamp() are the
 *            subjective gains the application requests. The HAL handles the math to keep
 *            the output safe. Applications do not need to compute their own normalisation
 *            budget.
 *
 *            For predictable mixes during overlapping audio events (e.g. system sound
 *            over main programme), applications should explicitly duck the main input via
 *            setInputVolumeRamp() rather than relying on the limiter — see the audio_mixer
 *            documentation "Use case 2 — Ducking a system sound over main audio".
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
class IAudioMixerController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerController)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief     Sets the audio source routing for one or more inputs on this mixer instance.
   * Allows multiple audio [source -> mixer input] mappings to be configured.
   *            This enables operations such as switching between decoders, routing
   *            HDMI input audio, or connecting application audio to mixer inputs.
   *
   *            The target mixer input is defined by the array position:
   *            - routing[0] configures mixer input 0
   *            - routing[1] configures mixer input 1
   *            - etc.
   *
   *            Each InputRouting element specifies sourceType/sourceIndex for that input.
   *
   *            To disconnect a source from a mixer input, set `sourceType` to `AudioSourceType.NONE`.
   *
   *            Validation:
   *            - If a source type and source index appear multiple times in the routing array, the call fails.
   *            - If a mixer input is already mapped to a different source, returns false.
   *
   * @param[in] routing   Array of audio source to mixer input routing configurations.
   * @param[out] _aidl_return Success status.
   *   - true: All routing mappings were successfully applied.
   *   - false: One or more routing configurations were invalid or conflicted.
   * @see       IAudioMixer.getInputRouting()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if routing array contains invalid values.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if mixer is in a state that prevents routing changes.
   */
  virtual ::android::binder::Status setInputRouting(const ::std::vector<::com::rdk::hal::audiomixer::InputRouting>& routing, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Sets a property on the controlled mixer instance.
   *
   *            The property must be writable in the current mixer state.
   *            Property writability is documented per-key in Property.aidl.
   *
   * @param[in] property      The property key (from Property enum).
   * @param[in] propertyValue The value to set (PropertyValue union; active
   *                          union field must match the property type).
   *
   * @param[out] _aidl_return true on successful write; false if the property is not
   *                          supported on this mixer or the value is rejected (e.g.
   *                          out of range for the property).
   *
   *   - true: The property was written and is now in effect.
   *   - false: The property is unsupported on this mixer instance
   *     or the value was rejected; mixer state is unchanged.
   * @see       IAudioMixer.getProperty()
   * @see       Property
   * @see       PropertyValue
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if @c property is unknown
   *                     or the PropertyValue union's active field does not match
   *                     the property's declared type.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the mixer is not in a
   *                     state that permits writing this property.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Starts audio mixing for this mixer instance.
   * The mixer transitions to the STARTED state and processes configured audio inputs and outputs.
   * @pre       The mixer must be in READY state.
   * @see       stop(), flush()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if already started or not ready.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * @brief     Stops audio mixing for this mixer instance.
   * The mixer transitions through STOPPING to READY state, ceasing output and freeing any buffered resources.
   * @pre       The mixer must be in STARTED state.
   * @see       start(), flush()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not started.
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * @brief     Flushes the mixer, discarding all buffered audio data.
   * @param[in] reset   When true, resets internal state to READY; when false, retains configuration but flushes data.
   * @pre       The mixer must be in STARTED state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not started.
   */
  virtual ::android::binder::Status flush(bool reset) = 0;
  // @aidl-doc
  /**
   * @brief     Signals a stream discontinuity in the mixer pipeline.
   * Used when a break or change in input PTS or format occurs, such as switching sources or seeking.
   * @pre       The mixer must be in STARTED state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not started.
   */
  virtual ::android::binder::Status signalDiscontinuity() = 0;
  // @aidl-doc
  /**
   * @brief     Signals end-of-stream for all active mixer inputs.
   * After all buffered frames are processed, the mixer drains remaining data
   *            and transitions through STOPPING to READY state.
   *            Named `signalEndOfStream()` for consistency with the decoder
   *            and sink controllers.
   * @pre       The mixer must be in STARTED state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if not started.
   */
  virtual ::android::binder::Status signalEndOfStream() = 0;
  // @aidl-doc
  /**
   * @brief     Sets the volume (attenuation) for a specific mixer input.
   * @details   Per-input attenuation lets clients balance multiple sources
   *            mixed into the same output (e.g., reduce main programme volume
   *            while a system sound plays). Value range is 0..100 where 100
   *            is unity gain (no attenuation) and 0 is silence.
   *
   *            Independent of the mixer-level FADER_LEVEL property which
   *            controls main/associated audio balance, and the output port
   *            VOLUME property which controls overall output volume.
   *
   *            <b>Mute behaviour:</b> setting volume to 0 removes that input's
   *            contribution from the mix budget. Remaining active inputs
   *            retain their requested levels (no auto-scale-up). Restoring
   *            the volume re-introduces the input at the new level.
   *
   *            <b>Mix policy:</b> the mixer prevents output clipping — see
   *            the interface header "Mix policy and clipping" notes. High
   *            per-input volumes across multiple active inputs will not
   *            cause output clipping; the HAL applies headroom management.
   *
   *            <b>Instant change:</b> this call applies the new volume
   *            immediately. For changes during active playback, prefer
   *            setInputVolumeRamp() to avoid audible clicks (zipper noise).
   *
   * @param[in] inputIndex  Mixer input index (0..Capabilities.inputs.length-1).
   * @param[in] volume      Volume level 0..100.
   *
   * @param[out] _aidl_return true on success, false if the input is unsupported on this
   *                          mixer (e.g. input is unrouted / has no source). Out-of-range
   *                          inputIndex or volume values throw EX_ILLEGAL_ARGUMENT.
   *
   * @see       getInputVolume(), setInputVolumeRamp()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if inputIndex is outside
   *                     [0, Capabilities.inputs.length-1] or volume is outside [0, 100].
   */
  virtual ::android::binder::Status setInputVolume(int32_t inputIndex, int32_t volume, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Gets the current volume for a specific mixer input.
   *
   * @param[in] inputIndex  Mixer input index (0..Capabilities.inputs.length-1).
   * @param[out] _aidl_return Current volume level 0..100. While a ramp is in progress
   *                          (setInputVolumeRamp), returns the instantaneous current
   *                          volume along the ramp, not the target.
   *
   * @see       setInputVolume(), setInputVolumeRamp()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if inputIndex is invalid.
   */
  virtual ::android::binder::Status getInputVolume(int32_t inputIndex, int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Smoothly ramps the volume of a specific mixer input.
   * @details   Walks the input's volume from its current value to
   *            targetVolume over overMs milliseconds, following the chosen
   *            VolumeRamp curve. Use this for any volume change that
   *            happens while audio is flowing — instantaneous changes
   *            cause audible clicks (zipper noise).
   *
   *            Typical durations are 50–500 ms — long enough to avoid
   *            clicks, short enough to feel responsive. Common ducking
   *            pattern: 200 ms attack to duck the main input, hold while
   *            the system sound plays, 300 ms release to restore.
   *
   *            If a ramp is already in progress on this input, it is
   *            stopped at its current instantaneous volume and replaced by
   *            this new ramp starting from that point.
   *
   *            Ducking with this API works uniformly across all input
   *            source types — sink-routed, tunnelled decoder, and direct
   *            (HDMI / Composite) inputs alike. This is the only API that
   *            does so; sink-side IAudioSinkController.setVolumeRamp()
   *            applies only to sink-routed sources.
   *
   * @param[in] inputIndex    Mixer input index (0..Capabilities.inputs.length-1).
   * @param[in] targetVolume  Target volume at end of ramp (0..100).
   * @param[in] overMs        Duration of the ramp in milliseconds. Must be > 0.
   *                          A value of 0 is rejected; use setInputVolume()
   *                          for instantaneous changes.
   * @param[in] curve         Ramp curve from VolumeRamp enum
   *                          (LINEAR, IN_CUBIC, OUT_CUBIC).
   *
   * @param[out] _aidl_return true on success, false if the input is unsupported on this
   *                          mixer (e.g. input is unrouted / has no source). Out-of-range
   *                          inputIndex, targetVolume, or overMs values throw
   *                          EX_ILLEGAL_ARGUMENT.
   *
   * @see       setInputVolume(), getInputVolume(), VolumeRamp
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if inputIndex is outside
   *                     [0, Capabilities.inputs.length-1], targetVolume is outside
   *                     [0, 100], or overMs is <= 0.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the mixer is not in
   *                     STARTED state.
   */
  virtual ::android::binder::Status setInputVolumeRamp(int32_t inputIndex, int32_t targetVolume, int32_t overMs, ::com::rdk::hal::audiosink::VolumeRamp curve, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerController

class IAudioMixerControllerDefault : public IAudioMixerController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setInputRouting(const ::std::vector<::com::rdk::hal::audiomixer::InputRouting>& /*routing*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*reset*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalDiscontinuity() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalEndOfStream() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setInputVolume(int32_t /*inputIndex*/, int32_t /*volume*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getInputVolume(int32_t /*inputIndex*/, int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setInputVolumeRamp(int32_t /*inputIndex*/, int32_t /*targetVolume*/, int32_t /*overMs*/, ::com::rdk::hal::audiosink::VolumeRamp /*curve*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerControllerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
