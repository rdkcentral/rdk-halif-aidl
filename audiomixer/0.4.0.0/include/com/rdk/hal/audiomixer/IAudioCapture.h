#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
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
 * @brief Audio capture interface for output ports.
 *
 * Provides stateful control over audio capture sessions on an output port.
 * Clients obtain shared memory, call start() to begin streaming, receive async callbacks via IAudioCaptureListener,
 * acknowledge consumed data with releaseData(), then call stop() to end the session.
 *
 * Example lifecycle:
 * @code
 *   long[] ringBufferSizeBytes = new long[1];
 *   ParcelFileDescriptor pfd = capture.getSharedMemory(ringBufferSizeBytes);
 *   capture.start();
 *   // Listener receives onDataAvailable(offset, length, metadata) callbacks.
 *   // Client reads from shared memory then calls releaseData(offset, length).
 *   capture.stop();
 * @endcode
 *
 * The data format captured is that of the output port.
 * Where an output port is physical, the capture interface captures the data format currently being output.
 * Where the output port is a dedicated capture port setting the OUTPUT_FORMAT directly controls the format of captured
 * data.
 */
class IAudioCapture : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioCapture)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief Returns the shared-memory ring buffer descriptor for zero-copy capture.
   *
   * This method must be called before capturing of audio data has been started with a call to start().
   *
   * @param[out] sharedMemorySizeBytes Single-element array receiving the
   *                                   total ring buffer size in bytes.
   *                                   AIDL primitives cannot be `out`
   *                                   parameters, so a length-1 long array
   *                                   is used to return the size alongside
   *                                   the ParcelFileDescriptor.
   * @param[out] _aidl_return ParcelFileDescriptor identifying the shared-memory ring buffer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if capture already started.
   */
  virtual ::android::binder::Status getSharedMemory(::std::vector<int64_t>* sharedMemorySizeBytes, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Release the shared-memory ring buffer
   *
   * This method may be called only when capturing of audio data has not been started
   * yet, or after a previous capture session has been stopped.
   * Calling releaseSharedMemory() before getSharedMemory() is not an error and has
   * no effect.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if capture is started.
   */
  virtual ::android::binder::Status releaseSharedMemory() = 0;
  // @aidl-doc
  /**
   * @brief Start audio capture stream using the configured format.
   *
   * Transitions capture interface from stopped to started state. Listener will receive
   * onStarted() callback, followed by repeated onDataAvailable() callbacks as audio
   * frames become available. Call stop() to end the stream.
   *
   * Ring buffer state is reset on every start() following a stop() transition.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if start is called when capture is not stopped
   *          or if the shared memory ring buffer has not been acquired by the client.
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * @brief Stop audio capture stream.
   *
   * Transitions capture interface from started to stopped state. Listener will receive
   * onStopped() callback after this method returns. No further onDataAvailable() callbacks
   * will be delivered.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if stop is called when not started.
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * @brief Acknowledges that previously signalled data has been consumed by the client.
   *
   * The offset and length must match a previously received onDataAvailable() callback.
   *
   * @param[in] offsetBytes Byte offset previously received from onDataAvailable().
   * @param[in] lengthBytes Length in bytes previously received from onDataAvailable().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if capture not started.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid region.
   */
  virtual ::android::binder::Status releaseData(int64_t offsetBytes, int32_t lengthBytes) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioCapture

class IAudioCaptureDefault : public IAudioCapture {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getSharedMemory(::std::vector<int64_t>* /*sharedMemorySizeBytes*/, ::android::os::ParcelFileDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseSharedMemory() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseData(int64_t /*offsetBytes*/, int32_t /*lengthBytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioCaptureDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
