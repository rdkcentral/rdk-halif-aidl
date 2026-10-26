#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videodecoder/ErrorCode.h>
#include <com/rdk/hal/videodecoder/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Event callbacks listener interface from video decoder.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IVideoDecoderEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoderEventListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  static constexpr char* HASHVALUE = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  // @aidl-doc
  /**
   * Callback when the decoder has raised an error.
   *
   * @param[in] errorCode 		    An ErrorCode enum value.
   * @param[in] vendorErrorCode  	    A vendor specific error code.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode errorCode, int32_t vendorErrorCode) = 0;
  // @aidl-doc
  /**
   * Callback when the decoder has transitioned to a new state.
   *
   * @param[in] oldState	            The state that the decoder has transitioned from.
   * @param[in] newState              The new state that the decoder has transitioned to.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::videodecoder::State oldState, ::com::rdk::hal::videodecoder::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoDecoderEventListener

class IVideoDecoderEventListenerDefault : public IVideoDecoderEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onDecodeError(::com::rdk::hal::videodecoder::ErrorCode /*errorCode*/, int32_t /*vendorErrorCode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::videodecoder::State /*oldState*/, ::com::rdk::hal::videodecoder::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoDecoderEventListenerDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
