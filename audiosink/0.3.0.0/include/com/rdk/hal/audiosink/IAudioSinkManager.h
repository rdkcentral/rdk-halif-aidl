#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiosink/IAudioSink.h>
#include <com/rdk/hal/audiosink/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Audio Sink Manager HAL interface.
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
class IAudioSinkManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSinkManager)
  static const int32_t VERSION = 3000;
  const std::string HASH = "217303eaf0f0e7ddd5a52b527b23759e877e9dcd";
  static constexpr char* HASHVALUE = "217303eaf0f0e7ddd5a52b527b23759e877e9dcd";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the list of platform audio sink IDs.
   *
   * @param[out] _aidl_return IAudioSink.Id[] array.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the platform wide capabilities for audio sinks.
   *
   * This includes the system mixer native PCM formats and sample rate that an audio sink
   * has to deliver for mixing.
   * The platform capabilities are determined at build time and cannot change.
   *
   * @param[out] _aidl_return PlatformCapabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the audio sink interface for a given ID.
   *
   * @param[in] audioSinkId       The ID of the audio sink resource.
   *
   * @param[out] _aidl_return IAudioSink or null on invalid audio sink ID.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& audioSinkId, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSinkManager

class IAudioSinkManagerDefault : public IAudioSinkManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioSinkIds(::std::vector<::com::rdk::hal::audiosink::IAudioSink::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPlatformCapabilities(::com::rdk::hal::audiosink::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioSink(const ::com::rdk::hal::audiosink::IAudioSink::Id& /*audioSinkId*/, ::android::sp<::com::rdk::hal::audiosink::IAudioSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkManagerDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
