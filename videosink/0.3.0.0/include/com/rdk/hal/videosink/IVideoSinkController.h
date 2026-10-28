#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/avclock/IAVClock.h>
#include <com/rdk/hal/videodecoder/FrameMetadata.h>
#include <com/rdk/hal/videodecoder/IVideoDecoder.h>
#include <com/rdk/hal/videosink/Property.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
// @aidl-doc
/**
 *  @brief     Video Sink Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>AVClock association and video output</h3>
 *  A video sink presents output only when an AVClock is attached and started.
 *  The clock association is owned by the sink — clients call `attachClock()` /
 *  `detachClock()` / `getClock()` on this controller to manage it. The AVClock
 *  itself does not need to be made aware of which sinks present against it.
 *  <ul>
 *  <li><b>No AVClock attached</b> (the default after `open()`, or after
 *      `detachClock()`): the sink does NOT consume frames and does NOT
 *      present output. Frames passed to `queueVideoFrame()` accumulate in the
 *      internal queue until the queue fills, after which `queueVideoFrame()`
 *      returns `false` until queue space becomes available again. Frames
 *      remain in the queue across the no-clock period.</li>
 *  <li><b>AVClock attached and started</b>: the sink consumes queued frames
 *      at the rate dictated by the clock, rendering them when a video plane
 *      is mapped — AV synchronisation is in effect (lip-synced with any audio
 *      sink presenting against the same clock) whether or not a plane is
 *      mapped. If the clock is paused, consumption pauses with it and the
 *      queue will eventually fill.</li>
 *  </ul>
 *  `attachClock()` / `detachClock()` are callable in `READY` or `STARTED` and
 *  do not change the sink's state-machine state. Detaching during `STARTED`
 *  suspends consumption but does not flush the queue or stop the sink.
 *
 *  <h3>Video plane mapping and rendering</h3>
 *  The attached clock gates frame consumption; the mapped video plane gates
 *  visibility. The plane mapping is owned by Plane Control rather than by this
 *  controller — it is set for `SourceType::VIDEO_SINK` at this sink's
 *  `RESOURCE_ID` through
 *  `IPlaneControl.setVideoSourceDestinationPlaneMapping()`, where a
 *  `destinationPlaneIndex` of -1 means the sink has no plane.
 *  <ul>
 *  <li><b>Plane mapped</b>: queued frames are consumed at their presentation
 *      times on the attached clock and rendered on that plane.</li>
 *  <li><b>No plane mapped</b>: queued frames are consumed at their
 *      presentation times and their buffers freed via `IAVBuffer.free()` at
 *      exactly the same points as when a plane is mapped, and nothing is
 *      displayed. The queue drains at clock rate, so the sink stays in sync
 *      with any audio sink presenting against the same clock and video is
 *      lip-synced from the moment a plane is mapped.</li>
 *  </ul>
 *  `Property.RENDER_FIRST_FRAME` is independent of this contract: it only
 *  governs whether a single first frame may be displayed ahead of the
 *  attached clock, and does not change when frames are consumed, freed, or
 *  when `onEndOfStream()` fires.
 * The mapping may be set or cleared at any point in the session, including
 * while `STARTED`. A successful mapping change leaves the sink's state-machine
 * state unchanged and does not flush the queue. On becoming
 *  mapped, the sink renders from the first queued frame whose presentation
 *  time is at or after the current clock time; queued frames whose
 *  presentation time has already passed are discarded rather than displayed
 *  late.
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IVideoSinkController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkController)
  static const int32_t VERSION = 3000;
  const std::string HASH = "da350441651184f9632c4dbf59d960ce6767f0bf";
  static constexpr char* HASHVALUE = "da350441651184f9632c4dbf59d960ce6767f0bf";
  // @aidl-doc
  /**
   * Sets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   * @param[in] propertyValue         Holds the value to set.
   *
   * @param[out] _aidl_return boolean
   *   - true: The property was successfully set.
   *   - false: Invalid property key or value.
   * @see getProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the Video Decoder ID linked to this Video Sink.
   *
   * `IVideoDecoder.Id.UNDEFINED` means that no Video Decoder source is
   * associated. It is the default when the Video Sink is opened and may be
   * passed here to clear an existing association, equivalent in effect to
   * the state at `open()`.
   *
   * `IVideoDecoder.Id.EXTERNAL` indicates that the Video Sink is fed by an
   * external non-HAL component rather than a HAL Video Decoder. A session
   * associated with `EXTERNAL` may be started.
   *
   * A valid Video Decoder ID is one returned by
   * `IVideoDecoderManager.getVideoDecoderIds()`. A valid association, or
   * `IVideoDecoder.Id.EXTERNAL`, is required before the pipeline is started
   * in both tunnelled and non-tunnelled modes.
   *
   * @param[in] videoDecoderId
   *      The ID of the Video Decoder source, `IVideoDecoder.Id.EXTERNAL`
   *      for an external non-HAL source, or `IVideoDecoder.Id.UNDEFINED`
   *      to clear the association.
   *
   * @param[out] _aidl_return boolean
   *   - true:
   *     The Video Decoder ID was set, the source was set to
   *     `IVideoDecoder.Id.EXTERNAL`, or the association was cleared with
   *     `IVideoDecoder.Id.UNDEFINED`.
   *   - false:
   *     The ID is not `IVideoDecoder.Id.EXTERNAL` and not one returned by
   *     `IVideoDecoderManager.getVideoDecoderIds()`.
   * @pre The resource must be in State::READY.
   *
   * @see getVideoDecoder(), IVideoDecoderManager.getVideoDecoderIds()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE
   *   Operation completed successfully.
   *
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   *   The resource is not in State::READY.
   */
  virtual ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& videoDecoderId, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the Video Decoder ID linked to this Video Sink.
   *
   * Returns the currently associated `IVideoDecoder.Id` in both tunnelled
   * and non-tunnelled modes.
   *
   * @param[out] _aidl_return IVideoDecoder.Id which can be `IVideoDecoder.Id.UNDEFINED` or
   *                          `IVideoDecoder.Id.EXTERNAL`.
   *
   * @pre The resource must be in State::READY or State::STARTED.
   *
   * @see setVideoDecoder()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource
   *         is not in State::READY or State::STARTED.
   */
  virtual ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Attaches an AVClock to this video sink for AV synchronisation.
   *
   * The sink consumes queued frames and renders them on the mapped video
   * plane only while the attached clock is started. With no clock attached,
   * frames queued via `queueVideoFrame()` accumulate but are not consumed
   * or rendered. See the interface @brief for the full AVClock-association
   * contract.
   *
   * The same AVClock may be attached to multiple sinks (typically one audio
   * sink and one video sink for AV-synchronised playback). The sink owns its
   * clock relationship; the AVClock does not need to be made aware.
   *
   * If a different clock is already attached, this call replaces the
   * attachment. Calling with `IAVClock.Id.UNDEFINED` is equivalent to
   * `detachClock()`.
   *
   * Can be called in `READY` or `STARTED` state. Attaching during `STARTED`
   * causes the sink to begin clock-paced presentation from the next frame
   * once the clock is started; the call does not change the sink's
   * state-machine state.
   *
   * @param[in] clockId   The ID of the AVClock to attach, or
   *                      `IAVClock.Id.UNDEFINED` to detach.
   *
   * @pre The resource must be in State::READY or State::STARTED.
   *
   * @see detachClock(), getClock(), IAVClockManager.getAVClockIds()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if `clockId`
   *         does not refer to an existing AVClock instance.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the sink is
   *         not in `READY` or `STARTED`.
   */
  virtual ::android::binder::Status attachClock(const ::com::rdk::hal::avclock::IAVClock::Id& clockId) = 0;
  // @aidl-doc
  /**
   * Detaches the currently attached AVClock from this video sink.
   *
   * After this call the sink does NOT consume or render further frames
   * until a clock is attached again. Equivalent to calling
   * `attachClock(IAVClock.Id.UNDEFINED)`. See the interface @brief for the
   * full AVClock-association contract.
   *
   * Idempotent: calling when no clock is attached is a no-op.
   *
   * Does not change the sink's state-machine state and does not flush the
   * internal queue — frames already queued remain queued and will be
   * presented once a clock is attached and started.
   *
   * @pre The resource must be in State::READY or State::STARTED.
   *
   * @see attachClock(), getClock()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the sink is
   *         not in `READY` or `STARTED`.
   */
  virtual ::android::binder::Status detachClock() = 0;
  // @aidl-doc
  /**
   * Gets the AVClock ID currently attached to this video sink.
   *
   * @param[out] _aidl_return IAVClock.Id, which is `IAVClock.Id.UNDEFINED` when no clock is
   *                          attached. With no clock attached the sink does not consume or
   *                          render output — see the interface @brief.
   *
   * @pre The resource must be in State::READY or State::STARTED.
   *
   * @see attachClock(), detachClock()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the sink is
   *         not in `READY` or `STARTED`.
   */
  virtual ::android::binder::Status getClock(::com::rdk::hal::avclock::IAVClock::Id* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts the Video Sink.
   *
   * The Video Sink must be in a READY state before it can be started.
   * If successful the Video Sink transitions to a `STARTING` state and then
   * a `STARTED` state.
   *
   * The client must call `setVideoDecoder()` with a valid decoder ID, or
   * `IVideoDecoder.Id.EXTERNAL` for an external non-HAL source, before
   * calling this method in both tunnelled and non-tunnelled modes. Starting
   * a Video Sink while the associated decoder ID is
   * `IVideoDecoder.Id.UNDEFINED` shall fail.
   *
   * The Video Decoder association is the only association this call
   * requires. The AVClock attachment and the video plane mapping are
   * independent of it: a sink started with no plane mapped runs normally
   * and displays nothing until a plane is mapped — see the interface
   * @brief.
   *
   * @pre The resource must be in State::READY.
   * @pre The associated Video Decoder ID must not be
   *      `IVideoDecoder.Id.UNDEFINED`; set a valid decoder ID or
   *      `IVideoDecoder.Id.EXTERNAL` using `setVideoDecoder()`.
   *
   * @see stop(), IVideoSink.open(), setVideoDecoder()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   *
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   *   The resource is not in State::READY, or the associated Video
   *   Decoder ID is `IVideoDecoder.Id.UNDEFINED`.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the Video Sink.
   *
   * The sink enters the `STOPPING` state and then the sink enters the `READY` state.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see start(), IVideoSink.close()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Queues a video frame for display.
   *
   * When the presentation time occurs for the video frame the current mapped video plane is used
   * to render the video frame. With no plane mapped the frame is consumed
   * and freed at that same presentation time and nothing is displayed — see
   * the interface @brief.
   *
   * Consumption is gated by the AVClock attachment — see the interface
   * @brief for the full contract. Summary: the sink consumes queued frames
   * and renders them on the mapped video plane only while an AVClock
   * attached via `attachClock()` is started. With no clock attached (default
   * after `open()` or after `detachClock()`), or with the clock paused, this
   * method accepts frames into the internal queue but the sink does NOT
   * consume or render them; once the queue fills, the method returns `false`
   * until queue space becomes available again.
   *
   * When an AVClock is attached and started, the presentation time of the
   * video frame is controlled by the clock and will be lip-synced with an
   * audio sink presenting against the same clock.
   *
   *
   * Buffer Ownership: Ownership of the buffer transfers to the Video Sink HAL only
   * when `queueVideoFrame()` accepts the buffer (returns true). Once accepted, the HAL is
   * responsible for freeing the buffer after processing. The caller must not modify or
   * access the buffer after a successful call. If the call returns false or throws an
   * exception, ownership remains with the caller.
   *
   *
   * End-of-stream signalling: this method only queues frames - it carries
   * no end-of-stream flag. After queuing its final frame the client calls
   * `signalEndOfStream()`, which tells the sink no more frames will be
   * queued.
   *
   * Throws `binder::Status::Exception::EX_ILLEGAL_STATE` if called after
   * `signalEndOfStream()` has been invoked on this session.
   *
   * Throws `binder::Status::Exception::EX_UNSUPPORTED_OPERATION` when the
   * controller is configured for tunnel mode - this API is not part of the
   * data path in tunnel; the sink is fed by the decoder internally and the
   * vendor is responsible for the internal EOS propagation. See
   * [Discussion #492](https://github.com/rdkcentral/rdk-halif-aidl/discussions/492).
   *
   *
   * @param[in] nsPresentationTime    The presentation time of the video frame in nanoseconds.
   * @param[in] frameBufferHandle     A handle to the video frame buffer.
   * @param[in] metadata              A FrameMetadata object with metadata relating to the video frame.
   *
   * @param[out] _aidl_return boolean
   *   - true: Frame successfully queued for display. Buffer ownership transfers to HAL.
   *   - false: Video sink queue is full. Buffer ownership remains with caller.
   *     The client SHOULD wait for `IVideoSinkControllerListener.onFrameBufferAvailable()`
   *     before retrying, to avoid wasted binder transactions. Continuing to call this
   *     method while the queue is full is permitted but will return `false` repeatedly
   *     until space is available.
   * @pre The resource must be in State::STARTED.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource is not in `STARTED`, or if a video frame
   * is passed after `signalEndOfStream()`.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if the controller is configured for tunnel mode.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT
   */
  virtual ::android::binder::Status queueVideoFrame(int64_t nsPresentationTime, int64_t frameBufferHandle, const ::com::rdk::hal::videodecoder::FrameMetadata& metadata, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Signals end-of-stream to the video sink.
   *
   * Asserts that no further frames will be queued via `queueVideoFrame()`.
   * The sink consumes every already-queued frame at its presentation time
   * — and, where a plane is mapped, renders it — in the usual way, then
   * fires `IVideoSinkControllerListener.onEndOfStream(nsPresentationTime)`
   * with the presentation time of the final queued frame.
   *
   * The callback is keyed on that presentation time passing on the attached
   * clock, so it fires whether or not a video plane is mapped.
   *
   * If no frames are queued when this is called, the sink fires
   * `onEndOfStream()` with an undefined-time sentinel
   * (`IAVClock.UNDEFINED_TIME`) so the client sees the same callback in all
   * cases.
   *
   * A second call is a no-op. After this call `queueVideoFrame()` throws
   * `EX_ILLEGAL_STATE` until the sink is flushed or stopped and restarted.
   *
   * Behaviour is identical in tunnelled and non-tunnelled modes - the MW calls this
   * method the same way. In tunnelled mode the decoder->sink data flow is
   * vendor-internal; the vendor must implement the EOS signal propagation
   * from decoder to sink so the sink can fire
   * `onEndOfStream(nsPresentationTime)` with the correct presentation
   * timing. The MW observes the same sequencing in both modes:
   * `decoder.onEndOfStream()` (decode complete) followed by
   * `sink.onEndOfStream(nsPresentationTime)` (presentation complete).
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see IVideoSinkControllerListener.onEndOfStream()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource
   *         is not in State::STARTED.
   */
  virtual ::android::binder::Status signalEndOfStream() = 0;
  // @aidl-doc
  /**
   * Flushes the internal queue of video frames.
   *
   * Once the flush operation has completed the `onFlushComplete()` callback is made to the client.
   *
   * When `holdLastFrame` is set true, the current displayed video frame is held on the display
   * until either a new video frame is presented, a new `flush()` call with `holdLastFrame` set to false is made
   * or the video sink is closed.
   *
   * @param[in] holdLastFrame         If true then the current displayed video frame is held.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see discardFramesUntil(), IVideoSinkControllerListener.onFlushComplete()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status flush(bool holdLastFrame) = 0;
  // @aidl-doc
  /**
   * Sets the earliest presentation time stamp for the Video Sink to display its next frame.
   *
   * The next video frame to display shall be >= `nsPresentationTime` after this call.
   * Any frames in tunnelled or non-tunnelled operational mode which are before this time
   * shall be freed and not displayed.
   *
   * If there is a frame already displayed then it remains displayed until a new frame arrives.
   * The `discardFramesUntil()` function is often used to perform accurate seek operations to a specific presentation
   * time inside a video stream and called after `flush()` with `holdLastFrame` set to true.
   *
   * @param[in] nsPresentationTime    The earliest presentation time of a video frame to display.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see flush()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status discardFramesUntil(int64_t nsPresentationTime) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkController

class IVideoSinkControllerDefault : public IVideoSinkController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::videosink::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoDecoder(const ::com::rdk::hal::videodecoder::IVideoDecoder::Id& /*videoDecoderId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoDecoder(::com::rdk::hal::videodecoder::IVideoDecoder::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status attachClock(const ::com::rdk::hal::avclock::IAVClock::Id& /*clockId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status detachClock() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getClock(::com::rdk::hal::avclock::IAVClock::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status queueVideoFrame(int64_t /*nsPresentationTime*/, int64_t /*frameBufferHandle*/, const ::com::rdk::hal::videodecoder::FrameMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status signalEndOfStream() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status flush(bool /*holdLastFrame*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status discardFramesUntil(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkControllerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
