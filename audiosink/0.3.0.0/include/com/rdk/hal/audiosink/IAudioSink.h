#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiosink/Capabilities.h>
#include <com/rdk/hal/audiosink/ContentType.h>
#include <com/rdk/hal/audiosink/IAudioSinkController.h>
#include <com/rdk/hal/audiosink/IAudioSinkControllerListener.h>
#include <com/rdk/hal/audiosink/IAudioSinkEventListener.h>
#include <com/rdk/hal/audiosink/Property.h>
#include <com/rdk/hal/audiosink/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiosink {
// @aidl-doc
/**
 *  @brief     Audio Sink HAL interface.
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
class IAudioSink : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioSink)
  static const int32_t VERSION = 3000;
  const std::string HASH = "250b70f29eb723ed19aef2f8ff2401d7f3b80297";
  static constexpr char* HASHVALUE = "250b70f29eb723ed19aef2f8ff2401d7f3b80297";
  // @aidl-doc
  /** Audio Sink resource ID type */
  class Id : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The actual resource ID */
    int32_t value = 0;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    // @aidl-doc
    /** The undefined ID value. */
    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiosink.IAudioSink.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  // @aidl-doc
  /**
   * Gets the capabilities for this audio sink.
   *
   * This function can be called at any time and is not dependant on any audio sink state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiosink::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown.
   *
   * @see IAudioSinkController.setProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid property value.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiosink::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current audio sink state.
   *
   * @param[out] _aidl_return State enum value.
   *
   * @see IAudioSinkEventListener.onStateChanged().
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::audiosink::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the audio sink.
   *
   * If successful, the audio sink transitions to an OPENING state and then a READY state.
   * The following guarantees are made for an opened audio sink:
   *  - Volume is set to the default of 1.0 and unmuted.
   *  - The linked Audio Decoder is set to IAudioDecoder.Id.UNDEFINED.
   *  - All `Property` values are set to their defaults.
   *
   * If the client that opened the `IAudioSinkController` crashes,
   * then `stop()` and `close()` are implicitly called on the `IAudioSinkController` to perform cleanup.
   *
   * @param[in] contentType                     The content type of the audio sink.
   * @param[in] audioSinkControllerListener     Callback listener for controller events.
   *
   * @param[out] _aidl_return IAudioSinkController or null On error
   *
   * @pre The resource must be in the CLOSED state.
   *
   * @see close()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status open(::com::rdk::hal::audiosink::ContentType contentType, const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkControllerListener>& audioSinkControllerListener, ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the audio sink.
   *
   * The audio sink must be in a READY state before it can be closed.
   * If successful the audio sink transitions to a CLOSING state and then a CLOSED state.
   * onStateChanged(CLOSING, CLOSED) will be notified on any registered IAudioSinkListener interfaces.
   *
   * @param[in] audioSinkController     Instance of the IAudioSinkController.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or unrecognised parameter.
   * @pre The resource must be in State::READY.
   *
   * @see open()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If instance is not in OPENED State.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>& audioSinkController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an audio sink event listener.
   *
   * An `IAudioSinkEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] audioSinkEventListener	    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters an audio sink event listener.
   *
   * @param[in] audioSinkEventListener	    Listener object for event callbacks.
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
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& audioSinkEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioSink

class IAudioSinkDefault : public IAudioSink {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiosink::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiosink::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::audiosink::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(::com::rdk::hal::audiosink::ContentType /*contentType*/, const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkControllerListener>& /*audioSinkControllerListener*/, ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkController>& /*audioSinkController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& /*audioSinkEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiosink::IAudioSinkEventListener>& /*audioSinkEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioSinkDefault
}  // namespace audiosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
