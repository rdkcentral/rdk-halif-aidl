#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiosink/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Controller callbacks listener interface from audio sink.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAudioSinkControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "250b70f29eb723ed19aef2f8ff2401d7f3b80297";
  static constexpr char* HASHVALUE = "250b70f29eb723ed19aef2f8ff2401d7f3b80297";
  // @aidl-doc
  /**
   * Callback when the sink has transitioned to a new state.
   *
   * @param[in] oldState	            The state transitioned from.
   * @param[in] newState              The new state transitioned to.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiosink::State oldState, ::com::rdk::hal::audiosink::State newState) = 0;
  // @aidl-doc
  /**
   * Callback when the first audio frame has started to be mixed.
   *
   * The behaviour is the same for tunnelled and non-tunnelled audio.
   * This occurs on the first audio frame in the session or after a flush() call.
   * Mixing requires a routed mixer input, so for a sink running with no
   * mixer input routed this reports the first frame mixed once a mixer
   * input becomes routed.
   * The frame may not immediately be heard due to the audio pipeline output latency.
   *
   * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback when consumption of the session's final queued audio frame
   * has completed on the attached clock.
   *
   * Triggered after the client called `IAudioSinkController.signalEndOfStream()`
   * to assert that no further frames will be queued. Fires exactly once per
   * session, ordered strictly after consumption of the final queued frame
   * completes on the attached clock. It is keyed on that completion
   * rather than on mixing, so it fires whether or not a mixer input is
   * routed. If no frames were queued, `nsPresentationTime` is the
   * undefined-time sentinel (`IAVClock.UNDEFINED_TIME`).
   *
   * The behaviour is the same for tunnelled and non-tunnelled audio.
   * With a mixer input routed, the audio may not immediately be heard due
   * to audio mixer and output latencies.
   *
   * @param[in] nsPresentationTime	The presentation time of the final audio frame in nanoseconds,
   *                                  or `IAVClock.UNDEFINED_TIME` if no frames were queued.
   *
   * @see IAudioSinkController.signalEndOfStream()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback to indicate an audio frame buffer underflow condition.
   *
   * This occurs when the frame queue is empty, or when buffers are present but none
   * are available for presentation at the AV sync clock based presentation time.
   *
   * The callback occurs only once when this condition is met.
   *
   * The `onAudioResumed()` callback informs the client when audio playback restarts,
   * which allows the `onAudioUnderflow()` callback to occur again if a subsequent
   * underflow occurs.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onAudioUnderflow() = 0;
  // @aidl-doc
  /**
   * Callback to indicate that audio has resumed after an audio underflow event.
   *
   * The onAudioUnderflow() can occur again after onAudioResumed() has been called.
   *
   * @param[in] nsPresentationTime	The presentation time of the audio frame in nanoseconds.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onAudioResumed(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback when a requested flush() operation has completed.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFlushComplete() = 0;
  // @aidl-doc
  /**
   * Callback that signals the audio sink input frame buffer queue has space again.
   *
   * Fired exactly once per back-pressure episode: when the internal queue transitions
   * from full to has-space after `IAudioSinkController.queueAudioFrame()` returned `false`.
   * If the client continues to call `queueAudioFrame()` during back-pressure (receiving
   * `false` repeatedly), only one callback is delivered per transition, regardless of
   * the number of intermediate `false` returns.
   *
   * The client SHOULD wait for this callback before retrying `queueAudioFrame()` to avoid
   * wasted binder transactions. Continuing to call `queueAudioFrame()` while the queue is
   * full is permitted but will return `false` repeatedly until space is available.
   *
   * Not fired in steady-state operation - only after a refused frame.
   *
   * @see IAudioSinkController.queueAudioFrame()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFrameBufferAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkControllerListener

class IAudioSinkControllerListenerDefault : public IAudioSinkControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiosink::State /*oldState*/, ::com::rdk::hal::audiosink::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFirstFrameRendered(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioUnderflow() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onAudioResumed(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFlushComplete() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFrameBufferAvailable() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkControllerListenerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
