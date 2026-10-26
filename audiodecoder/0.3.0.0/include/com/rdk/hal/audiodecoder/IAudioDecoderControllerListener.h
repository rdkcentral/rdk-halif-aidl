#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/FrameMetadata.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Callbacks listener interface from audio decoder controller.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAudioDecoderControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  static constexpr char* HASHVALUE = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  // @aidl-doc
  /**
   * Called when an audio frame has been decoded or when frame metadata needs notification.
   *
   * In tunnelled mode, audio data is consumed by the vendor layer, so no PCM buffer is returned.
   *
   * Otherwise, `frameAVBufferHandle` is a valid AVBuffer handle to a decoded PCM buffer,
   * and `metadata` is non-null for the first frame after `State::START` or `State::FLUSHING`,
   * or whenever stream metadata changes. Metadata may be null if unchanged since the last callback,
   * except that a frame with a non-zero trim always carries non-null metadata, even when the trim
   * repeats the previous frame's trim; a null metadata means zero trim for that frame.
   * See `FrameMetadata.trimStartNs`.
   *
   * Ownership semantics for `frameAVBufferHandle`:
   * - The client receives ownership of the AVBuffer handle when this callback is invoked.
   * - The client is responsible for managing the handle's lifecycle: either passing it to the next
   *   module (e.g., audio sink) or explicitly freeing it via IAVBuffer.free() when no longer needed.
   *
   * End-of-stream is NOT delivered on this callback. Client-signalled EOS
   * is a discrete event - see `onEndOfStream()`, which the HAL fires exactly
   * once after the final `onFrameOutput()` of a session drained by
   * `IAudioDecoderController.signalEndOfStream()`.
   *
   * @param[in] nsPresentationTime    The presentation timestamp in nanoseconds, or -1 if only metadata is being
   * returned.
   * @param[in] frameAVBufferHandle   AVBuffer handle to the decoded audio frame buffer. Valid handle in
   *                                   non-tunnelled mode; -1 in tunnelled mode.
   * @param[in] metadata              FrameMetadata for the audio frame. Nullable on routine
   *                                  callbacks (in tunnelled mode or when unchanged); always
   *                                  non-null in non-tunnelled mode for a frame with a non-zero trim.
   *
   * @see IAudioDecoderController.decodeBufferWithMetadata(), IAVBuffer.free(),
   *      onEndOfStream()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameAVBufferHandle, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& metadata) = 0;
  // @aidl-doc
  /**
   * Callback signalling client-signalled end-of-stream.
   *
   * Fired exactly once per decode session, after the final `onFrameOutput()`
   * of a session drained by `IAudioDecoderController.signalEndOfStream()`.
   * It is delivered on this same listener and is ordered in-band - it
   * follows the last frame on the same ordered callback channel.
   *
   * Audio EOS is always client-signalled, so this callback is the sole
   * end-of-stream event for the audio decoder.
   *
   * After this callback the decoder remains in `State::STARTED` but is
   * drained; no further `onFrameOutput()` is delivered until `flush()` or
   * `stop()` + `start()`.
   *
   * @see IAudioDecoderController.signalEndOfStream()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEndOfStream() = 0;
  // @aidl-doc
  /**
   * Callback that signals the audio decoder input buffer queue has space again.
   *
   * Fired exactly once per back-pressure episode: when the internal queue transitions
   * from full to has-space after `IAudioDecoderController.decodeBufferWithMetadata()`
   * returned `false`. If the client continues to call `decodeBufferWithMetadata()`
   * during back-pressure (receiving `false` repeatedly), only one callback is
   * delivered per transition, regardless of the number of intermediate `false` returns.
   *
   * The client SHOULD wait for this callback before retrying
   * `decodeBufferWithMetadata()` to avoid wasted binder transactions. Continuing
   * to call it while the queue is full is permitted but will return `false`
   * repeatedly until space is available.
   *
   * Not fired in steady-state operation - only after a refused buffer.
   *
   * @see IAudioDecoderController.decodeBufferWithMetadata()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDecodeBufferAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderControllerListener

class IAudioDecoderControllerListenerDefault : public IAudioDecoderControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFrameOutput(int64_t /*nsPresentationTime*/, int64_t /*frameAVBufferHandle*/, const ::std::optional<::com::rdk::hal::audiodecoder::FrameMetadata>& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onDecodeBufferAvailable() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderControllerListenerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
