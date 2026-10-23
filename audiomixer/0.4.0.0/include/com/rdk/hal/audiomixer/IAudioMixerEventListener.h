#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/ContentType.h>
#include <com/rdk/hal/audiomixer/State.h>
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
 * @brief     Listener interface for asynchronous Audio Mixer events.
 * Provides callbacks for runtime events such as input codec changes, error notifications,
 *            resource state changes, and other dynamic mixer events.
 *            Intended to be registered with the IAudioMixer.
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 */
class IAudioMixerEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerEventListener)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief     Called when the codec or content type changes on any audio mixer input.
   * @param[in] audioMixerInputIndex  The input index affected.
   * @param[in] codec                 The new codec detected on the input.
   * @param[in] contentType           The content type (e.g., STREAM, CLIP, TTS).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onInputCodecChanged(int32_t audioMixerInputIndex, ::com::rdk::hal::audiodecoder::Codec codec, ::com::rdk::hal::audiomixer::ContentType contentType) = 0;
  // @aidl-doc
  /**
   * @brief     Called when a runtime error occurs on the mixer instance.
   * @param[in] errorCode  An implementation-defined or HAL-standard error code.
   * @param[in] message    Human-readable error message, may be empty.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onError(int32_t errorCode, const ::std::string& message) = 0;
  // @aidl-doc
  /**
   * @brief     Called when the mixer state changes (e.g., READY, STARTED, STOPPING).
   * @param[in] oldState  The previous state.
   * @param[in] newState  The new state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State oldState, ::com::rdk::hal::audiomixer::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerEventListener

class IAudioMixerEventListenerDefault : public IAudioMixerEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onInputCodecChanged(int32_t /*audioMixerInputIndex*/, ::com::rdk::hal::audiodecoder::Codec /*codec*/, ::com::rdk::hal::audiomixer::ContentType /*contentType*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onError(int32_t /*errorCode*/, const ::std::string& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiomixer::State /*oldState*/, ::com::rdk::hal::audiomixer::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerEventListenerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
