#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/OperationalMode.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiodecoder/Capabilities.h>
#include <com/rdk/hal/audiodecoder/Codec.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderController.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderControllerListener.h>
#include <com/rdk/hal/audiodecoder/IAudioDecoderEventListener.h>
#include <com/rdk/hal/audiodecoder/Property.h>
#include <com/rdk/hal/audiodecoder/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiodecoder {
// @aidl-doc
/**
 *  @brief     Audio Decoder HAL interface.
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
class IAudioDecoder : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioDecoder)
  static const int32_t VERSION = 3000;
  const std::string HASH = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  static constexpr char* HASHVALUE = "6a70aa94326e83560aef5c047cc0ff454b158a6e";
  // @aidl-doc
  /** Audio Decoder resource ID type */
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
    // @aidl-doc
    /** Sentinel indicating the sink source is an external non-HAL component rather than a HAL Audio Decoder. */
    enum : int32_t { EXTERNAL = -2 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.audiodecoder.IAudioDecoder.Id");
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
   * Gets the audio decoder capabilities.
   *
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiodecoder::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown.
   *
   * @see setProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid property value.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::audiodecoder::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current state of the audio decoder resource.
   *
   * @param[out] _aidl_return State enum value.
   *
   * @see IAudioDecoderListener.onStateChanged().
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::audiodecoder::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the specified audio decoder resource index to decode the specified codec.
   *
   * If successful the audio decoder transitions to an `OPENING` state and then a `READY` state
   * which is notified to any registered `IAudioDecoderEventListener` interfaces.
   *
   * Controller related callbacks are made through the `IAudioDecoderControllerListener`
   * passed into the call.
   *
   * The returned `IAudioDecoderController` interface is used by the client to feed data buffers
   * for decode and manage the decoding flow.
   *
   * If `secure` is requested (true) and the `Capabilties.supportsSecure` is false then the `open()`
   * fails with a null return.
   *
   * If the client that opened the `IAudioDecoderController` crashes,
   * then the `IAudioDecoderController` has `stop()` and `close()` implicitly called to perform clean up.
   *
   * @param[in] codec					            The codec to configure the audio decoder for.
   * @param[in] secure                            The audio decoder secure audio path mode.
   * @param[in] audioDecoderControllerListener    Listener object for controller callbacks.
   *
   * @param[out] _aidl_return IAudioDecoderController or null if the codec or secure is not supported if requested.
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see IAudioDecoderController, IAudioDecoderController.close(), registerEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If instance is not in CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status open(::com::rdk::hal::audiodecoder::Codec codec, bool secure, const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderControllerListener>& audioDecoderControllerListener, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the audio decoder.
   *
   * The audio decoder must be in a `READY` state before it can be closed.
   * If successful the audio decoder transitions to a `CLOSING` state and then a `CLOSED` state.
   * `onStateChanged(CLOSING, CLOSED)` will be notified on any registered listener interfaces.
   *
   * @param[in] audioDecoderController     Instance of the IAudioDecoderController.
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
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>& audioDecoderController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers an audio decoder event listener.
   *
   * An `IAudioDecoderEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] audioDecoderEventListener	    Listener object for callbacks.
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
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters an audio decoder event listener.
   *
   * @param[in] audioDecoderEventListener	    Listener object for callbacks.
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
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& audioDecoderEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the output mode currently selected by the vendor for this decoder.
   *
   * The mode is implementation-selected and is not configurable through
   * the Audio Decoder HAL.
   *
   * @param[out] _aidl_return Current operational output mode.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the resource is not in the STARTED state.
   */
  virtual ::android::binder::Status getCurrentOperationalMode(::com::rdk::hal::OperationalMode* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioDecoder

class IAudioDecoderDefault : public IAudioDecoder {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiodecoder::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::audiodecoder::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::audiodecoder::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(::com::rdk::hal::audiodecoder::Codec /*codec*/, bool /*secure*/, const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderControllerListener>& /*audioDecoderControllerListener*/, ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderController>& /*audioDecoderController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& /*audioDecoderEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::audiodecoder::IAudioDecoderEventListener>& /*audioDecoderEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentOperationalMode(::com::rdk::hal::OperationalMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioDecoderDefault
}  // namespace audiodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
