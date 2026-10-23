#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiodecoder/CSDAudioFormat.h>
#include <com/rdk/hal/audiodecoder/InputBufferMetadata.h>
#include <com/rdk/hal/audiodecoder/Property.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Audio Decoder Controller HAL interface.
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
class IAudioDecoderController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderController)
  static const int32_t VERSION = 3000;
  const std::string HASH = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  static constexpr char* HASHVALUE = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
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
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid property and propertyValue.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiodecoder::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts the audio decoder.
   *
   * The audio decoder must be in a ready state before it can be started.
   * If successful the audio decoder transitions to a `STARTING` state and then a `STARTED` state.
   *
   * @pre The resource must be in State::READY.
   *
   * @see open(), stop()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the audio decoder.
   *
   * The decoder enters the `STOPPING` state and then any input data buffers that have been passed for decode but have
   * not yet been decoded are freed automatically.  This is effectively the same as a flush.
   * Once buffers are freed and the internal audio decoder state is reset, the decoder enters the `READY` state.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see start()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Pass an encoded buffer of audio elementary stream data to the audio decoder
   * with per-buffer metadata.
   *
   * The audio decoder must be in a `STARTED` state.
   * Buffers can be either non-secure or secure to support SAP (Secure Audio Path).
   * Each call shall reference a single audio frame with a presentation timestamp
   * carried in `metadata.nsPresentationTime`.
   *
   * Buffer Ownership: Ownership of the buffer transfers to the Audio Decoder HAL
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
   * `InputBufferMetadata` (including `trimStartNs`/`trimEndNs`) across calls.
   *
   * A PTS discontinuity is signalled by calling `signalDiscontinuity()`
   * before the first buffer that follows the discontinuity.
   *
   * @param[in] bufferHandle  A handle to the AV buffer containing the encoded
   *                          audio frame. MUST be a valid handle.
   * @param[in] metadata      Per-buffer metadata. See `InputBufferMetadata`.
   *
   * @param[out] _aidl_return boolean
   *   - true: Buffer successfully queued for decoding. Buffer ownership transfers to HAL.
   *   - false: Internal decode buffer queue is full. Buffer ownership remains with caller.
   *     The client SHOULD wait for `IAudioDecoderControllerListener.onDecodeBufferAvailable()`
   *     before retrying, to avoid wasted binder transactions. Continuing to call this
   *     method while the queue is full is permitted but will return `false` repeatedly
   *     until space is available.
   * @pre The resource must be in State::STARTED.
   *
   * @see InputBufferMetadata
   * @see signalDiscontinuity()
   * @see IAudioDecoderControllerListener.onFrameOutput()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if `bufferHandle` is
   *         invalid.
   */
  virtual ::android::binder::Status decodeBufferWithMetadata(int64_t bufferHandle, const ::com::rdk::hal::audiodecoder::InputBufferMetadata& metadata, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts a flush operation on the decoder.
   *
   * The audio decoder must be in a state of `STARTED`.
   * Any input data buffers that have been passed for decode but have
   * not yet been decoded are automatically freed.
   * The internal audio decoder state is optionally reset.
   *
   * @param[in] reset     When true, the internal audio decoder state is fully reset back to its opened READY state.
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
   * Signals a discontinuity in the audio stream.
   *
   * This is the sole PTS discontinuity signal on the input side. The client
   * calls it between the last buffer before the discontinuity and the first
   * buffer after it: buffers passed to `decodeBufferWithMetadata()` after
   * this call returns are PTS discontinuous with every buffer passed before it.
   *
   * The decoder MUST reset its PTS tracking and interpolation state before
   * decoding the first buffer passed after this call, and MUST NOT
   * interpolate timestamps across the discontinuity. Buffers passed before
   * this call are decoded and output as normal.
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
   * no per-buffer EOS flag. Audio EOS is always client-signalled: no
   * supported audio elementary stream carries an in-bitstream EOS marker.
   *
   * On this call the HAL MUST decode and emit every held frame in
   * presentation order via `IAudioDecoderControllerListener.onFrameOutput()`
   * (each with its `FrameMetadata`), and then fire
   * `IAudioDecoderControllerListener.onEndOfStream()` exactly once after the
   * final frame. No held frame may be dropped on EOS.
   *
   * This is distinct from `stop()` and `flush()`, which abruptly discard any
   * held frames rather than draining them.
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
   * @see IAudioDecoderControllerListener.onEndOfStream()
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
   * Sends codec-specific data to initialise the audio decoder.
   *
   * Some audio formats require out-of-band codec-specific data describing the audio stream,
   * which has been filtered from the container or provided by the application.
   * This must be invoked before any audio frame buffers are passed to `decodeBufferWithMetadata()`.
   *
   * For example, MPEG-4 Audio requires the AudioSpecificConfig, beginning with the audio object type.
   *
   * The accepted `CSDAudioFormat` values align with DVB, ISDB, HLS, and DASH broadcast/streaming standards.
   *
   * @see ISO/IEC 14496-3:2019
   * @see https://www.iso.org/standard/76383.html
   *
   * @param[in] csdAudioFormat   Codec-specific data format enum.
   * @param[in] codecData        Byte array containing the codec-specific data.
   *
   * @param[out] _aidl_return boolean
   *   - true: The codec data was successfully set.
   *   - false: Invalid parameter or empty codec data array.
   * @pre The decoder resource must be in State::STARTED.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   *
   *        Thrown if the resource is not in State::STARTED.
   */
  virtual ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::audiodecoder::CSDAudioFormat csdAudioFormat, const ::std::vector<uint8_t>& codecData, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the audio stream format hint before decoding begins.
   *
   * Provides the channel count and sample rate sourced from container
   * or demuxer metadata (e.g. GStreamer caps). Required for codecs
   * such as AC3/EAC3 where this information is not carried in
   * codec-specific data but is needed by the decoder and downstream
   * audio sink pipeline.
   *
   * For codecs that do carry format info in codec-specific data
   * (e.g. AAC AudioSpecificConfig), this method is optional - the
   * decoder will use the CSD values. If both are provided, the CSD
   * values take precedence.
   *
   * @param[in] channels    Number of audio channels.
   *                        Common values: 1 (mono), 2 (stereo),
   *                        6 (5.1 surround), 8 (7.1 surround).
   * @param[in] sampleRate  Sample rate in Hz.
   *                        Common values: 8000, 16000, 32000,
   *                        44100, 48000, 96000, 192000.
   *
   * @pre The resource must be in State::READY.
   *
   * @see PCMMetadata.numChannels, PCMMetadata.sampleRate
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource is not in the READY state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if channels or sampleRate is <= 0.
   */
  virtual ::android::binder::Status setAudioFormat(int32_t channels, int32_t sampleRate) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderController

class IAudioDecoderControllerDefault : public IAudioDecoderController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiodecoder::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status decodeBufferWithMetadata(int64_t /*bufferHandle*/, const ::com::rdk::hal::audiodecoder::InputBufferMetadata& /*metadata*/, bool* /*_aidl_return*/) override {
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
  ::android::binder::Status parseCodecSpecificData(::com::rdk::hal::audiodecoder::CSDAudioFormat /*csdAudioFormat*/, const ::std::vector<uint8_t>& /*codecData*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAudioFormat(int32_t /*channels*/, int32_t /*sampleRate*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderControllerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
