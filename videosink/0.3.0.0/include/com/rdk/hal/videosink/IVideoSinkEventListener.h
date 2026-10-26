#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videosink/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
// @aidl-doc
/**
 *  @brief     Callbacks event listener interface for Video Sink.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IVideoSinkEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkEventListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "da350441651184f9632c4dbf59d960ce6767f0bf";
  static constexpr char* HASHVALUE = "da350441651184f9632c4dbf59d960ce6767f0bf";
  // @aidl-doc
  /**
   * Callback when the first video frame has been rendered.
   *
   * The behaviour is the same for tunnelled and non-tunnelled video operating modes.
   * This occurs on the first frame rendered after an `open()` or `flush()` call.
   * The frame may not immediately be visible due to video pipeline and compositor functions.
   * The associated plane `Capabilities.vsyncDisplayLatency` indicates the expected time between
   * this callback and actual display.
   *
   * Rendering requires a mapped video plane, so for a sink running with no
   * plane mapped this reports the first frame rendered once a plane becomes
   * mapped.
   *
   * @param[in] nsPresentationTime    The presentation time of the frame.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFirstFrameRendered(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback when the presentation time of the session's final queued frame
   * has passed on the attached clock.
   *
   * The behaviour is the same for tunnelled and non-tunnelled video operating modes.
   * This occurs once the presentation time of the last queued frame in the
   * session has passed on the attached clock. It is keyed on that
   * presentation time rather than on rendering, so it fires whether or not a
   * video plane is mapped.
   * The frame may not immediately be visible due to video pipeline and compositor functions.
   * With a plane mapped, the associated plane `Capabilities.vsyncDisplayLatency`
   * indicates the expected time between this callback and actual display.
   *
   * @param[in] nsPresentationTime    The presentation time of the final video frame,
   *                                  or `IAVClock.UNDEFINED_TIME` if no frames were queued.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEndOfStream(int64_t nsPresentationTime) = 0;
  // @aidl-doc
  /**
   * Callback to indicate a video frame buffer underflow condition.
   *
   * This occurs if the frame queue is empty at the next expected AV Clock based
   * presentation time for a video frame.
   * The callback occurs only once when the queue becomes empty.
   * The `onVideoResumed()` callback informs the client when video playback restarts,
   * which allows the `onVideoUnderflow()` to occur again.
   *
   * Underflow detection follows frame consumption, which the attached clock
   * gates, so this pair of callbacks applies whether or not a video plane is
   * mapped.
   *
   * @see onVideoResumed()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoUnderflow() = 0;
  // @aidl-doc
  /**
   * Callback to indicate that video has resumed presentation after a video underflow event.
   *
   * The `onVideoUnderflow()` can occur again after `onVideoResumed()` has been called.
   *
   * @see onVideoUnderflow()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onVideoResumed() = 0;
  // @aidl-doc
  /**
   * Callback when a requested `flush()` operation has completed.
   *
   * @see IVideoSinkController.flush()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFlushComplete() = 0;
  // @aidl-doc
  /**
   * Callback when the Video Sink has transitioned to a new state.
   *
   * @param[in] oldState	The state that the sink has transitioned from.
   * @param[in] newState  The new state that the sink has transitioned to.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::videosink::State oldState, ::com::rdk::hal::videosink::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkEventListener

class IVideoSinkEventListenerDefault : public IVideoSinkEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFirstFrameRendered(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream(int64_t /*nsPresentationTime*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoUnderflow() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onVideoResumed() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onFlushComplete() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::videosink::State /*oldState*/, ::com::rdk::hal::videosink::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkEventListenerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
