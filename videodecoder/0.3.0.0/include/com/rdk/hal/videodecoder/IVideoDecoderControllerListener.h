#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/FrameMetadata.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Controller callbacks listener interface from video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IVideoDecoderControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderControllerListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ff9b64beb2c3c9a1fe1277a0c2d0e8080dfc4d0d";
  static constexpr char* HASHVALUE = "ff9b64beb2c3c9a1fe1277a0c2d0e8080dfc4d0d";
  // @aidl-doc
  /**
   * Callback when a full video frame has been decoded or the frame metadata needs to be notified.
   * The metadata must be non-null on the first frame after start() or flush() call or
   * when the metadata changes in the stream.
   * It can only be null if the contents have not changed since the last callback.
   *
   * Ownership semantics for `frameAVBufferHandle`:
   * - The client receives ownership of the AVBuffer handle when this callback is invoked.
   * - The client is responsible for managing the handle's lifecycle: either passing it to the next
   *   module (e.g., video sink) or explicitly freeing it via IAVBuffer.free() when no longer needed.
   *
   * End-of-stream is NOT delivered on this callback. Client-signalled EOS
   * is a discrete event - see `onEndOfStream()`, which the HAL fires exactly
   * once after the final `onFrameOutput()` of a drained session. The
   * advisory in-bitstream marker is carried per-frame by
   * `FrameMetadata.bitstreamEOS` and triggers no callback.
   *
   * @param[in] nsPresentationTime	The presentation time or -1 if only metadata is being returned.
   * @param[in] frameAVBufferHandle	AVBuffer handle to the decoded 2D video frame buffer. Valid handle in
   *                                   non-tunnelled mode; -1 in tunnelled mode.
   * @param[in] metadata				A FrameMetadata parcelable of metadata related to the frame.
   *                                  Nullable on routine callbacks per the rule above.
   *
   * @see IVideoDecoderController.decodeBufferWithMetadata(), IAVBuffer.free(),
   *      onEndOfStream()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onFrameOutput(int64_t nsPresentationTime, int64_t frameAVBufferHandle, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& metadata) = 0;
  // @aidl-doc
  /**
   * Callback signalling client-signalled end-of-stream.
   *
   * Fired exactly once per decode session, after the final `onFrameOutput()`
   * of a session drained by `IVideoDecoderController.signalEndOfStream()`.
   * It is delivered on this same listener and is ordered in-band - it
   * follows the last frame on the same ordered callback channel.
   *
   * Only the discrete EOS signal fires this callback. The advisory
   * in-bitstream marker (`FrameMetadata.bitstreamEOS`) never does - it may
   * denote a splice boundary rather than authoritative end-of-presentation.
   *
   * After this callback the decoder remains in `State::STARTED` but is
   * drained; no further `onFrameOutput()` is delivered until `flush()` or
   * `stop()` + `start()`.
   *
   * @see IVideoDecoderController.signalEndOfStream()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onEndOfStream() = 0;
  // @aidl-doc
  /**
   * Callback which delivers the picture user data from a frame.
   * The userData byte array starts from (and includes) the user_identifier field (typically 'GA94').
   * The output video frame can be delivered before or after the onUserDataOutput().
   * The user data must be delivered in the same frame presentation order as the output frames.
   *
   * The userData byte array contains SEI NAL data, typically conforming to the "user_data_registered_itu_t_t35"
   * structure, used for captioning:
   * - Begins with the ITU-T T.35 country_code (0xB5 for USA)
   * - Followed by provider_code (0x0031 for ATSC)
   * - Includes a user_identifier string (usually 'GA94')
   * - Contains a user_data_type_code (0x03 for CEA-608/708)
   * - Followed by one or more CC data packets (cc_valid, cc_type, and data bytes)
   *
   * The RDK media pipeline must parse this data to extract embedded CEA-608 or CEA-708 caption packets.
   * Each `onUserDataOutput()` call corresponds to a single decoded video frame and maintains AV sync for captions.
   * This approach standardises the delivery of caption-related data across all platforms supporting embedded SEI in
   * compressed video streams.
   *
   * @param[in] nsPresentationTime  The presentation time.
   * @param[in] userData            Array of bytes containing the SEI user data (e.g., ATSC A/72 caption payload).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onUserDataOutput(int64_t nsPresentationTime, const ::std::vector<uint8_t>& userData) = 0;
  // @aidl-doc
  /**
   * Callback that signals the video decoder input buffer queue has space again.
   *
   * Fired exactly once per back-pressure episode: when the internal queue transitions
   * from full to has-space after `IVideoDecoderController.decodeBufferWithMetadata()`
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
   * @see IVideoDecoderController.decodeBufferWithMetadata()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDecodeBufferAvailable() = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderControllerListener

class IVideoDecoderControllerListenerDefault : public IVideoDecoderControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onFrameOutput(int64_t /*nsPresentationTime*/, int64_t /*frameAVBufferHandle*/, const ::std::optional<::com::rdk::hal::videodecoder::FrameMetadata>& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onEndOfStream() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onUserDataOutput(int64_t /*nsPresentationTime*/, const ::std::vector<uint8_t>& /*userData*/) override {
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
};  // class IVideoDecoderControllerListenerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
