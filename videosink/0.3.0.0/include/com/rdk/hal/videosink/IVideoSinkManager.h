#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/videosink/IVideoSink.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
// @aidl-doc
/**
 *  @brief     Video Sink Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`, `EX_ILLEGAL_ARGUMENT`).
 *    In this case, output parameters and return values contain undefined (garbage) memory and must not be used.
 *    The caller must ignore any output variables.
 */
class IVideoSinkManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSinkManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "670f95dc021cdc6aa9c40df7fd7ceaf53ec5ca6e";
  static constexpr char* HASHVALUE = "670f95dc021cdc6aa9c40df7fd7ceaf53ec5ca6e";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the list of platform Video Sink IDs.
   *
   * @param[out] _aidl_return IVideoSink.Id[]
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   */
  virtual ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a Video Sink interface.
   *
   * @param[in] videoSinkId	    The ID of the Video Sink.
   *
   * @param[out] _aidl_return IVideoSink or null if the ID is invalid.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   */
  virtual ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& videoSinkId, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSinkManager

class IVideoSinkManagerDefault : public IVideoSinkManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getVideoSinkIds(::std::vector<::com::rdk::hal::videosink::IVideoSink::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSink(const ::com::rdk::hal::videosink::IVideoSink::Id& /*videoSinkId*/, ::android::sp<::com::rdk::hal::videosink::IVideoSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkManagerDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
