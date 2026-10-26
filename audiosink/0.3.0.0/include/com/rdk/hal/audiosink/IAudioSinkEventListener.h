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
 *  @brief     Callbacks listener interface from audio sink.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAudioSinkEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkEventListener)
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
   * The behaviour is the same for tunnelled and non-tunnelled audio.
   * This occurs once consumption of the last queued frame in the session
   * completes on the attached clock, whether or not a mixer input is
   * routed. With a mixer input routed, the audio may not immediately be
   * heard due to audio mixer and output latencies.
   *
   * @param[in] nsPresentationTime	The presentation time of the final audio frame in nanoseconds, or
   * `IAVClock.UNDEFINED_TIME` if no frames were queued.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback to indicate a audio frame buffer underflow condition.
   *
   * This occurs if the frame queue is empty at the AV sync clock based presentation time.
   * The callback occurs only once when the queue becomes empty.
   * The onAudioResumed() callback informs the client when video playback restarts,
   * which allows the onAudioUnderflow() to occur again.
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
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkEventListener

class IAudioSinkEventListenerDefault : public IAudioSinkEventListener {
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
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkEventListenerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
