#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiodecoder/ErrorCode.h>
#include <com/rdk/hal/audiodecoder/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Events callbacks listener interface from audio decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IAudioDecoderEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoderEventListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  static constexpr char* HASHVALUE = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  // @aidl-doc
  /**
   * Callback when the decoder has raised an error.
   *
   * @param[in] errorCode 		    An ErrorCode enum value.
   * @param[in] vendorErrorCode  	    A vendor specific error code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode errorCode, int32_t vendorErrorCode) = 0;
  // @aidl-doc
  /**
   * Callback when the decoder has transitioned to a new state.
   *
   * @param[in] oldState	            The state that the decoder has transitioned from.
   * @param[in] newState              The new state that the decoder has transitioned to.
   *
   * @see getState()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State oldState, ::com::rdk::hal::audiodecoder::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoderEventListener

class IAudioDecoderEventListenerDefault : public IAudioDecoderEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDecodeError(::com::rdk::hal::audiodecoder::ErrorCode /*errorCode*/, int32_t /*vendorErrorCode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::audiodecoder::State /*oldState*/, ::com::rdk::hal::audiodecoder::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderEventListenerDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
