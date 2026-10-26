#pragma once

#include <array>
#include <binder/Enums.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiomixer/Capabilities.h>
#include <com/rdk/hal/audiomixer/IAudioMixerController.h>
#include <com/rdk/hal/audiomixer/IAudioMixerEventListener.h>
#include <com/rdk/hal/audiomixer/IAudioOutputPort.h>
#include <com/rdk/hal/audiomixer/InputRouting.h>
#include <com/rdk/hal/audiomixer/Property.h>
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
 * @brief Audio Mixer HAL interface.
 *
 * Exposes all mixer functions for the identified resource,
 * including audio routing, output port enumeration, and audio
 * quality (AQ) processor management. Supports both secure and
 * non-secure audio paths. Each instance represents a single mixer.
 *
 * @author    Luc Kennedy-Lamb
 * @author    Peter Stieglitz
 * @author    Douglas Adler
 * @author    Gerald Weatherup
 */
class IAudioMixer : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioMixer)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief Mixer resource IDs.
   *
   * MIXER_SYSTEM is always present; additional IDs are vendor/platform defined.
   */
  enum class Id : int32_t {
    // @aidl-doc
    /** The system mixer. Always present. */
    MIXER_SYSTEM = 0,
    // @aidl-doc
    /** Mixer 1. Vendor/platform defined. */
    MIX1 = 1,
    // @aidl-doc
    /** Mixer 2. Vendor/platform defined. */
    MIX2 = 2,
    // @aidl-doc
    /** Mixer 3. Vendor/platform defined. */
    MIX3 = 3,
    // @aidl-doc
    /** Mixer 4. Vendor/platform defined. */
    MIX4 = 4,
    // @aidl-doc
    /** Mixer 5. Vendor/platform defined. */
    MIX5 = 5,
  };
  // @aidl-doc
  /**
   * @brief Returns the list of audio output port IDs on this mixer.
   *
   * @param[out] _aidl_return Array of int values representing port IDs.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets an audio output port interface by ID.
   *
   * Callers should discover valid port identifiers via
   * `getAudioOutputPortIds()` rather than probe-by-ID. Negative or
   * otherwise structurally invalid identifiers raise
   * `EX_ILLEGAL_ARGUMENT`; an identifier that is plausible but not
   * currently mounted on this mixer instance returns `null`.
   *
   * @param[in] id Output port identifier (as int).
   * @param[out] _aidl_return IAudioOutputPort interface, or null if no port with the
   *                          given ID is mounted on this mixer instance.
   *
   * @see getAudioOutputPortIds()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if @c id is negative or
   *                     structurally invalid for this platform.
   */
  virtual ::android::binder::Status getAudioOutputPort(int32_t id, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the capabilities of this mixer instance.
   *
   * Capabilities include secure path, number/types of supported inputs,
   * and supported content types/codecs per input.
   *
   * @param[out] _aidl_return Capabilities description for the mixer.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Gets a property value from the mixer instance.
   * @param[in] property      The property key (from Property enum).
   * @param[out] _aidl_return The current property value.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if property not supported.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property property, ::com::rdk::hal::PropertyValue* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Opens this mixer instance for runtime control.
   *
   * If successful, the mixer transitions from CLOSED to OPENING and then READY.
   * The returned controller is used to start/stop/flush and manage mixer runtime behaviour.
   *
   * If `secure` is requested (true) and `Capabilities.supportsSecure` is false, open fails
   * with a null return.
   *
   * If the client that opened the controller crashes, `stop()` and `close()` are implicitly
   * called to perform cleanup.
   *
   * @param[in] secure                  The mixer secure audio path mode.
   * @param[in] audioMixerEventListener Listener for state/error/runtime mixer callbacks.
   * @param[out] _aidl_return IAudioMixerController interface, or null on internal/open failure.
   * @see close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if mixer is not in CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if parameters are invalid.
   * @retval ::android::binder::Status::EX_NULL_POINTER if listener is null.
   */
  virtual ::android::binder::Status open(bool secure, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Closes this mixer instance.
   *
   * The mixer must be in READY state before it can be closed. On success it transitions
   * to CLOSING and then CLOSED.
   *
   * @param[in] audioMixerController Instance returned by open().
   * @param[out] _aidl_return true on successful close, false for invalid state or unknown controller.
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if mixer is not in READY state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if controller is null.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& audioMixerController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an audio mixer event listener.
   *
   * An `IAudioMixerEventListener` can only be registered once and will
   * fail on subsequent registration attempts with the same instance.
   * Registration does not require ownership of the mixer controller —
   * observers can attach without holding the IAudioMixerController.
   *
   * @param[in] audioMixerEventListener Listener object for callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   * @see IAudioMixerEventListener
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters an audio mixer event listener.
   *
   * @param[in] audioMixerEventListener Listener object for callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& audioMixerEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the list of currently active source codecs being mixed.
   *
   * Useful for clients to discover what input formats are currently processed
   * by the mixer for debugging, display, or selection logic.
   *
   * The length and order of the returned array correspond to the current
   * active mixer inputs; each entry matches the input at the same index
   * as returned by capability or enumeration APIs.
   *
   * Callable independent of open()/close(), like `getCapabilities()` —
   * does not require holding the IAudioMixerController and does not gate
   * on the mixer lifecycle state.
   *
   * @param[out] _aidl_return List of codecs for active sources.
   *
   * @see IAudioMixer.getCapabilities()
   * @see Codec
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief     Gets the current audio source routing for all mixer inputs.
   *
   *            Returns an array with one element for each mixer input (as
   *            declared in `Capabilities.inputs`). If a mixer input has no
   *            source connected, `AudioSourceType.NONE` is indicated.
   *
   *            Callable independent of open()/close(), like
   *            `getCapabilities()` — does not require holding the
   *            IAudioMixerController and does not gate on the mixer
   *            lifecycle state.
   *
   * @param[out] _aidl_return Array of audio source to mixer tree input routing
   *                          configurations.
   *
   * @see       IAudioMixer.getCapabilities()
   * @see       IAudioMixerController.setInputRouting()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioMixer

class IAudioMixerDefault : public IAudioMixer {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getAudioOutputPortIds(::std::vector<int32_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioOutputPort(int32_t /*id*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioOutputPort>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiomixer::Property /*property*/, ::com::rdk::hal::PropertyValue* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(bool /*secure*/, const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*audioMixerEventListener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerController>& /*audioMixerController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*audioMixerEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiomixer::IAudioMixerEventListener>& /*audioMixerEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentSourceCodecs(::std::vector<::com::rdk::hal::audiodecoder::Codec>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getInputRouting(::std::vector<::com::rdk::hal::audiomixer::InputRouting>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioMixerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
[[nodiscard]] static inline std::string toString(IAudioMixer::Id val) {
  switch(val) {
  case IAudioMixer::Id::MIXER_SYSTEM:
    return "MIXER_SYSTEM";
  case IAudioMixer::Id::MIX1:
    return "MIX1";
  case IAudioMixer::Id::MIX2:
    return "MIX2";
  case IAudioMixer::Id::MIX3:
    return "MIX3";
  case IAudioMixer::Id::MIX4:
    return "MIX4";
  case IAudioMixer::Id::MIX5:
    return "MIX5";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::audiomixer::IAudioMixer::Id, 6> enum_values<::com::rdk::hal::audiomixer::IAudioMixer::Id> = {
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIXER_SYSTEM,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX1,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX2,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX3,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX4,
  ::com::rdk::hal::audiomixer::IAudioMixer::Id::MIX5,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
