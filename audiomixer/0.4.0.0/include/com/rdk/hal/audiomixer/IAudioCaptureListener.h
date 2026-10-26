#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/AudioCaptureData.h>
#include <com/rdk/hal/audiomixer/AudioCaptureError.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Audio capture event listener interface.
 * Asynchronous callback interface for receiving audio capture events from an output port.
 * All methods are one-way (fire-and-forget) to avoid blocking the capture thread.
 */
class IAudioCaptureListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioCaptureListener)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief Called when a new audio data frame is available in shared-memory ring buffer.
   *
   * Wrap-around semantics:
   * If (offsetBytes + lengthBytes) <= ringBufferSizeBytes, the frame is contiguous.
   * If (offsetBytes + lengthBytes) > ringBufferSizeBytes, the frame wraps and must be read
   * as two segments:
   * segment1: [offsetBytes, ringBufferSizeBytes)
   * segment2: [0, (offsetBytes + lengthBytes) - ringBufferSizeBytes)
   *
   * @param[in] offsetBytes Byte offset from the start of the ring buffer.
   * @param[in] lengthBytes Number of valid bytes for this frame.
   * @param[in] metadata Audio frame metadata (channels, sample rate, timestamp, format).
   *
   * The client must call IAudioCapture.releaseData(offsetBytes, lengthBytes) after reading.
   *
   * This is a one-way call; it does not wait for the callback to complete.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDataAvailable(int64_t offsetBytes, int32_t lengthBytes, const ::com::rdk::hal::audiomixer::AudioCaptureData& metadata) = 0;
  // @aidl-doc
  /**
   * @brief Called when audio capture stream has successfully started.
   *
   * Signals that the capture interface has transitioned to active/streaming state
   * and audio frames are being delivered via onDataAvailable() calls.
   *
   * This is a one-way call; it does not wait for the callback to complete.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStarted() = 0;
  // @aidl-doc
  /**
   * @brief Called when audio capture stream has stopped.
   *
   * Signals that the capture interface has transitioned to idle/stopped state.
   * No further onDataAvailable() callbacks will be delivered.
   *
   * This is a one-way call; it does not wait for the callback to complete.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStopped() = 0;
  // @aidl-doc
  /**
   * @brief Called when an error occurs during audio capture.
   * ERROR_OVERFLOW indicates new incoming data was dropped and is lost.
   *
   * @param[in] error Error code indicating the type of failure.
   * @param[in] message Human-readable error description.
   *
   * This is a one-way call; it does not wait for the callback to complete.
   *
   * @exception None (one-way interface never throws).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError error, const ::std::string& message) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioCaptureListener

class IAudioCaptureListenerDefault : public IAudioCaptureListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDataAvailable(int64_t /*offsetBytes*/, int32_t /*lengthBytes*/, const ::com::rdk::hal::audiomixer::AudioCaptureData& /*metadata*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStarted() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStopped() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(::com::rdk::hal::audiomixer::AudioCaptureError /*error*/, const ::std::string& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioCaptureListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
