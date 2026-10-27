#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/IAudioMixer.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Audio Mixer Manager HAL interface.
 *
 * Provides enumeration and access to available system audio mixers.
 * Each mixer represents a logical or physical audio mixing resource
 * on the platform, such as the system mixer or dedicated MS12/DTS instances.
 * This interface is implemented by the vendor layer and allows the RDK
 * middleware to discover and control available mixer resources.
 */
class IAudioMixerManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixerManager)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /** The service name for registration with Binder Service Manager. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * @brief Returns a list of available audio mixer instance IDs.
   *
   * This function can be called at any time. The returned set must
   * be stable for the lifetime of the process.
   *
   * @param[out] _aidl_return Array of IAudioMixer.Id values representing available mixers.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Acquires a specific audio mixer interface by ID.
   *
   * Callers should discover mounted mixer identifiers via
   * `getAudioMixerIds()` rather than probe-by-ID. Identifiers that are
   * not a defined value of `IAudioMixer.Id` raise EX_ILLEGAL_ARGUMENT;
   * a defined enum value for which no mixer is currently mounted on
   * this platform returns `null`.
   *
   * @param[in] id  Mixer resource identifier.
   *
   * @param[out] _aidl_return IAudioMixer interface for controlling the mixer, or
   *                          `null` if @c id is a defined enum value but no mixer
   *                          with that ID is mounted on this platform.
   *
   * @see getAudioMixerIds()
   * @see IAudioMixer
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if @c id
   *         is not a defined value of `IAudioMixer.Id`.
   */
  virtual ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id id, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixerManager

class IAudioMixerManagerDefault : public IAudioMixerManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioMixerIds(::std::vector<::com::rdk::hal::audiomixer::IAudioMixer::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioMixer(::com::rdk::hal::audiomixer::IAudioMixer::Id /*id*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixer>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerManagerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
