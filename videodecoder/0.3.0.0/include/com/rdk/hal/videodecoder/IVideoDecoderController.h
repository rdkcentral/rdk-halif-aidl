#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/videodecoder/CSDVideoFormat.h>
#include <com/rdk/hal/videodecoder/InputBufferMetadata.h>
#include <com/rdk/hal/videodecoder/Property.h>
#include <com/rdk/hal/videodecoder/VideoDecoderStreamConfig.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video Decoder Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IVideoDecoderController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderController)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ff9b64beb2c3c9a1fe1277a0c2d0e8080dfc4d0d";
  static constexpr char* HASHVALUE = "ff9b64beb2c3c9a1fe1277a0c2d0e8080dfc4d0d";
  // @aidl-doc
  /**
   * Starts the Video Decoder.
   *
   * The Video Decoder must be in a `READY` state before it can be started.
   * If successful the Video Decoder transitions to a `STARTING` state and then a `STARTED` state.
   *
   * @pre The resource must be in State::READY.
   *
   * @see IVideoDecoder.open(), IVideoDecoder.stop()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the Video Decoder.
   *
   * The decoder enters the `STOPPING` state and then any input data buffers that have been passed for decode but have
   * not yet been decoded are automatically freed.  This is effectively the same as a flush.
   * Once buffers are freed and the internal Video Decoder state is reset, the decoder enters the `READY` state.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see start()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status stop() = 0;
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
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::videodecoder::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Pass an encoded buffer of video elementary stream data to the Video Decoder
   * with per-buffer metadata.
   *
   * The Video Decoder must be in a `STARTED` state.
   * Buffers can be either non-secure or secure to support SVP (Secure Video Path).
   * Each call shall reference a single video frame with a presentation timestamp
   * carried in `metadata.nsPresentationTime`.
   *
   * Buffer Ownership: Ownership of the buffer transfers to the Video Decoder HAL
   * only when this call accepts the buffer (returns true). Once accepted, the HAL
   * is responsible for freeing the buffer after processing. The caller must not
   * modify or access the buffer after a successful call. If the call returns false
   * or throws an exception, ownership remains with the caller.
   *
   * `bufferHandle` MUST reference a valid encoded frame. This method only
   * submits data - it carries no end-of-stream signal. A client that has
   * submitted its final buffer ends the decode session out-of-band via
   * `signalEndOfStream()`, which drains the decoder.
   *
   * Throws `binder::Status::Exception::EX_ILLEGAL_STATE` if called after
   * `signalEndOfStream()` has been invoked on this session. This applies in
   * both tunnel and non-tunnel modes - the decoder input path is not
   * tunnelled.
   *
   * Each call is self-describing; the HAL MUST NOT carry any field of
   * `InputBufferMetadata` across calls.
   *
   * A PTS discontinuity is signalled by calling `signalDiscontinuity()`
   * before the first buffer that follows the discontinuity.
   *
   * @param[in] bufferHandle  A handle to the AV buffer containing the encoded
   *                          video frame. MUST be a valid handle.
   * @param[in] metadata      Per-buffer metadata. See `InputBufferMetadata`.
   *
   * @param[out] _aidl_return boolean
   *   - true: Buffer successfully queued for decoding. Buffer ownership transfers to HAL.
   *   - false: Internal decode buffer queue is full. Buffer ownership remains with caller.
   *     The client SHOULD wait for `IVideoDecoderControllerListener.onDecodeBufferAvailable()`
   *     before retrying, to avoid wasted binder transactions. Continuing to call this
   *     method while the queue is full is permitted but will return `false` repeatedly
   *     until space is available.
   * @pre The resource must be in State::STARTED.
   *
   * @see InputBufferMetadata
   * @see signalDiscontinuity()
   * @see IVideoDecoderControllerListener.onFrameOutput()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if `bufferHandle` is
   *         invalid.
   */
  virtual ::android::binder::Status decodeBufferWithMetadata(int64_t bufferHandle, const ::com::rdk::hal::videodecoder::InputBufferMetadata& metadata, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts a flush operation on the decoder.
   *
   * The Video Decoder must be in a `STARTED` state.
   * Any input data buffers that have been passed for decode but have
   * not yet been decoded are automatically freed.
   *
   * Any pending decoded video frames due for callback are returned to the video frame buffer pool.
   * The internal Video Decoder state is optionally reset.
   *
   * @param[in] reset - When true, the internal Video Decoder state is fully reset back to its opened `READY` state.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status flush(bool reset) = 0;
  // @aidl-doc
  /**
   * Signals a discontinuity in the video stream.
   *
   * This is the sole PTS discontinuity signal on the input side. The client
   * calls it between the last buffer before the discontinuity and the first
   * buffer after it: buffers passed to `decodeBufferWithMetadata()` after
   * this call returns are PTS discontinuous with every buffer passed before
   * it and with every frame already held in the Video Decoder.
   *
   * The decoder MUST reset its PTS tracking and interpolation state before
   * decoding the first buffer passed after this call, and MUST NOT
   * interpolate timestamps across the discontinuity. Buffers passed before
   * this call, and frames already held in the Video Decoder, are decoded
   * and output as normal.
   *
   * The first frame output from buffers passed after this call carries
   * `FrameMetadata.discontinuity = true`.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see FrameMetadata.discontinuity
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status signalDiscontinuity() = 0;
  // @aidl-doc
  /**
   * Signals client-driven end-of-stream and drains the decoder.
   *
   * This is the discrete, authoritative "I will submit no further buffers"
   * signal. It is the only end-of-stream path on the input side - there is
   * no per-buffer EOS flag. It serves the after-the-fact case where the
   * client discovers end-of-stream only after its final buffer was already
   * submitted (async demux, network EOF, pipelined I/O).
   *
   * On this call the HAL MUST decode and emit every held frame in
   * presentation order via `IVideoDecoderControllerListener.onFrameOutput()`
   * (each with its `FrameMetadata`, plus `onUserDataOutput()` for captions),
   * and then fire `IVideoDecoderControllerListener.onEndOfStream()` exactly
   * once after the final frame. No held frame may be dropped on EOS.
   *
   * This is distinct from `stop()` and `flush()`, which abruptly discard the
   * decoder's reorder/DPB tail rather than draining it.
   *
   * A second call is a no-op. After this call any `decodeBufferWithMetadata()`
   * throws `EX_ILLEGAL_STATE`. The decoder remains in `STARTED` (drained)
   * until `flush()` or `stop()` + `start()`.
   *
   * Behaviour is identical in tunnel and non-tunnel modes - the MW calls this
   * method the same way. In tunnel mode the decoder->sink data flow is
   * vendor-internal; the vendor must implement the EOS signal propagation
   * from decoder to sink so the sink can fire
   * `onEndOfStream(nsPresentationTime)` with the correct presentation
   * timing. The MW observes the same sequencing in both modes:
   * `decoder.onEndOfStream()` (decode complete) followed by
   * `sink.onEndOfStream(nsPresentationTime)` (presentation complete).
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see IVideoDecoderControllerListener.onEndOfStream()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource
   *         is not in State::STARTED, or if no buffers have ever been
   *         submitted on this session (no stream has started).
   */
  virtual ::android::binder::Status signalEndOfStream() = 0;
  // @aidl-doc
  /**
   * Sends codec specific data to initialise the Video Decoder.
   *
   * This function sends codec-specific data to the Video Decoder for initialisation.
   * The Video Decoder must be in the `STARTED` state before calling this function.
   *
   * Some video media requires out-of-band codec-specific data to describe the video stream.
   * This data is pre-filtered from the container or provided by the application. When
   * required, this function must be called before video frame buffers are passed to
   * `decodeBufferWithMetadata()`.
   *
   * The format of the `codecData` parameter depends on the `csdVideoFormat`:
   *
   * For `AVC_DECODER_CONFIGURATION_RECORD` (H.264/AVC), this is the
   * `AVCDecoderConfigurationRecord`, starting with the configuration version byte.
   * See ISO/IEC 14496-15:2022, 5.3.3.1.2 and
   * https://www.iso.org/standard/83336.html for more details.
   *
   * For `HEVC_DECODER_CONFIGURATION_RECORD` (H.265/HEVC), this is the
   * `HEVCDecoderConfigurationRecord`, starting with the configuration version byte.
   * See ISO/IEC 23008-2 and https://www.iso.org/standard/85457.html for
   * further information.
   *
   * For `AV1_DECODER_CONFIGURATION_RECORD` (AV1 video), this is the
   * `AV1CodecConfigurationRecord`, starting with the first configuration version byte.
   * See https://aomediacodec.github.io/av1-isobmff/#av1codecconfigurationbox-section
   * for more details.
   *
   * @param[in] csdVideoFormat The codec specific data format. This must match the codec specified in the `open()`
   * call.
   * @param[in] codecData      The byte array of codec data. This must not be empty.
   *
   * @param[out] _aidl_return boolean
   *   - true: The codec data was successfully set.
   *   - false: Invalid parameter or empty codec data array.
   * @pre The resource must be in the `STARTED` state.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource is not in the `STARTED` state.
   */
  virtual ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::videodecoder::CSDVideoFormat csdVideoFormat, const ::std::vector<uint8_t>& codecData, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Atomically applies a batch of container/manifest-derived
   * stream-configuration hints in a single binder transaction. This is
   * the canonical surface for setting all `VideoDecoderStreamConfig`
   * fields — there are no individual typed setters; every field is
   * configured through this call.
   *
   * <h4>Atomicity</h4>
   * Either every non-null field is applied or none are. If any field fails
   * validation, the call returns `EX_ILLEGAL_ARGUMENT` and the decoder
   * state is unchanged from before the call.
   *
   * <h4>Hint precedence and persistence</h4>
   * Bitstream-derived metadata wins over the hint when present; the hint
   * is the fallback used only when the bitstream is silent. The values the
   * decoder actually used are reported via `FrameMetadata`. Hints persist
   * across `flush()` and are cleared on `close()`.
   *
   * <h4>Per-field application</h4>
   * Each non-null field is applied to the decoder's stream-config state:
   * - `resolution`           — pre-allocation seed for frame buffers
   * - `frameRate`            — pipeline timing seed
   * - `pixelAspectRatio`     — PAR fallback when bitstream VUI omits it
   * - `colorimetry`          — colour primaries / matrix fallback
   * - `masteringDisplayInfo` — SMPTE ST 2086 fallback (HEVC SEI type 137)
   * - `contentLightLevel`    — CTA-861.3 MaxCLL/MaxFALL fallback (SEI 144)
   * - `dolbyVisionLayerFlags`— BL/EL presence; only meaningful for DOLBY_VISION
   *
   * @param[in] config  Stream-configuration batch. Fields set to `null`
   *                    are ignored (no change). Fields with values are
   *                    applied as hints; see `VideoDecoderStreamConfig`
   *                    for per-field validation rules.
   *
   * @pre The resource must be in State::READY.
   *
   * @see VideoDecoderStreamConfig, FrameMetadata
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource is not in the READY state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if any field fails validation
   *         (e.g. `resolution.width <= 0`, `frameRate.denominator == 0`
   *         while `numerator != 0`, exactly one of `pixelAspectRatio.numerator` /
   *         `denominator` is 0).
   */
  virtual ::android::binder::Status setStreamConfig(const ::com::rdk::hal::videodecoder::VideoDecoderStreamConfig& config) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderController

class IVideoDecoderControllerDefault : public IVideoDecoderController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(::com::rdk::hal::videodecoder::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decodeBufferWithMetadata(int64_t /*bufferHandle*/, const ::com::rdk::hal::videodecoder::InputBufferMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
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
  ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::videodecoder::CSDVideoFormat /*csdVideoFormat*/, const ::std::vector<uint8_t>& /*codecData*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setStreamConfig(const ::com::rdk::hal::videodecoder::VideoDecoderStreamConfig& /*config*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderControllerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
