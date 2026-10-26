#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/OperationalMode.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/videodecoder/Capabilities.h>
#include <com/rdk/hal/videodecoder/Codec.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderController.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderControllerListener.h>
#include <com/rdk/hal/videodecoder/IVideoDecoderEventListener.h>
#include <com/rdk/hal/videodecoder/Property.h>
#include <com/rdk/hal/videodecoder/PropertyKVPair.h>
#include <com/rdk/hal/videodecoder/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace videodecoder {
// @aidl-doc
/**
 *  @brief     Video Decoder HAL interface.
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
class IVideoDecoder : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoDecoder)
  static const int32_t VERSION = 3000;
  const std::string HASH = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  static constexpr char* HASHVALUE = "922cc8ec92962ec7843061aae427af80fb4c37a1";
  // @aidl-doc
  /** Video decoder resource ID type */
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
    /** Sentinel indicating the sink source is an external non-HAL component rather than a HAL Video Decoder. */
    enum : int32_t { EXTERNAL = -2 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videodecoder.IVideoDecoder.Id");
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
   * Gets the capabilities for this Video Decoder.
   *
   * This function can be called at any time and is not dependant on any Video Decoder state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::videodecoder::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown.
   *
   * @see setProperty(), getPropertyMulti()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid property value.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::videodecoder::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets multiple properties.
   *
   * Retrieves values for a list of property keys.
   *
   * Input `properties` is a non-null array of `Property` keys. Each key must be a
   * valid enum value; unknown or out-of-range values are treated as invalid.
   *
   * Output `propertyKVList` returns one `PropertyKVPair` per requested key, with
   * the same ordering as `properties`. For each pair, the `property` field echoes
   * the requested key and `propertyValue` is populated on success.
   *
   * Error handling and return semantics:
   * - Passing an empty `properties` array fails with `EX_ILLEGAL_ARGUMENT`.
   * - If any key in `properties` is invalid, no values are populated and the
   *   call fails with `EX_ILLEGAL_ARGUMENT`.
   * - If a required out-parameter is null (e.g. `propertyKVList`), the call fails
   *   with `EX_NULL_POINTER`.
   * - When an exception is raised, no return value is transmitted.
   *
   * @param[in] properties      Non-empty list of property keys to query.
   * @param[out] propertyKVList Returned key/value pairs corresponding to `properties`.
   *
   * @param[out] _aidl_return boolean
   *   - true: All property values were retrieved successfully.
   *   - false: The property values could not be retrieved.
   * @see getProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid property key(s) or empty input list.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::videodecoder::Property>& properties, ::std::vector<::com::rdk::hal::videodecoder::PropertyKVPair>* propertyKVList, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current Video Decoder state.
   *
   * @param[out] _aidl_return State enum value.
   *
   * @see IVideoDecoderEventListener.onStateChanged().
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::videodecoder::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the Video Decoder to decode the specified codec.
   *
   * If successful the Video Decoder transitions to an `OPENING` state and then a `READY` state
   * which is notified to any registered `IVideoDecoderEventListener` interfaces.
   *
   * Controller related callbacks are made through the `IVideoDecoderControllerListener`
   * passed into the call.
   *
   * The returned `IVideoDecoderController` interface is used by the client to feed data buffers
   * for decode and manage the decoding flow.
   *
   * If the client that opened the `IVideoDecoderController` crashes,
   * then the `IVideoDecoderController` has `stop()` and `close()` implicitly called to perform clean up.
   *
   * The decoder will be opened expecting frames with a resolution up to the maximum specified in `CodecCapabilities`.
   *
   * @param[in] codec                             The codec to configure the Video Decoder for.
   * @param[in] secure                            The Video Decoder secure mode.
   * @param[in] videoDecoderControllerListener    Listener object for controller callbacks.
   *
   * @param[out] _aidl_return IVideoDecoderController or null if the codec or the requested secure mode is not supported.
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see IVideoDecoderController, IVideoDecoderController.close(), registerEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status open(::com::rdk::hal::videodecoder::Codec codec, bool secure, const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderControllerListener>& videoDecoderControllerListener, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the Video Decoder to decode the specified codec with a specified maximum resolution.
   *
   * If successful the Video Decoder transitions to an `OPENING` state and then a `READY` state
   * which is notified to any registered `IVideoDecoderEventListener` interfaces.
   *
   * Controller related callbacks are made through the `IVideoDecoderControllerListener`
   * passed into the call.
   *
   * The returned `IVideoDecoderController` interface is used by the client to feed data buffers
   * for decode and manage the decoding flow.
   *
   * If the client that opened the `IVideoDecoderController` crashes,
   * then the `IVideoDecoderController` has `stop()` and `close()` implicitly called to perform clean up.
   *
   * The decoder will be opened expecting frames up to a maximum of `maxWidth` and `maxHeight'.
   * If `maxWidth` and `maxHeight' exceed that specified in the `CodecCapabilities` then binder::Status::Exception::EX_ILLEGAL_ARGUMENT
   * will be returned.
   *
   * @param[in] codec                             The codec to configure the Video Decoder for.
   * @param[in] secure                            The Video Decoder secure mode.
   * @param[in] videoDecoderControllerListener    Listener object for controller callbacks.
   * @param[in] maxWidth                          maximum width of the decoded frame.
   * @param[in] maxHeight                         maximum height of the decoded frame.
   *
   * @param[out] _aidl_return IVideoDecoderController or null if the codec or the requested secure mode is not supported.
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see IVideoDecoderController, IVideoDecoderController.close(), registerEventListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status openWithResolution(::com::rdk::hal::videodecoder::Codec codec, bool secure, const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderControllerListener>& videoDecoderControllerListener, int32_t maxWidth, int32_t maxHeight, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the Video Decoder.
   *
   * The Video Decoder must be in a `READY` state before it can be closed.
   * If successful the video decoder transitions to a `CLOSING` state and then a `CLOSED` state.
   * Then `onStateChanged(CLOSING, CLOSED)` will be notified on any registered event listener interfaces.
   *
   * @param[in] videoDecoderController     Instance of the IVideoDecoderController.
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
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>& videoDecoderController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a Video Decoder event listener.
   *
   * An `IVideoDecoderEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] videoDecoderEventListener	    Listener object for event callbacks.
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
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderEventListener>& videoDecoderEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a Video Decoder event listener.
   *
   * @param[in] videoDecoderEventListener	    Listener object for event callbacks.
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
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderEventListener>& videoDecoderEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the output mode currently selected by the vendor for this decoder.
   *
   * The mode is implementation-selected and is not configurable through
   * the Video Decoder HAL. TUNNELLED output is consumed within the vendor
   * layer; NON_TUNNELLED output is returned through onFrameOutput().
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
};  // class IVideoDecoder

class IVideoDecoderDefault : public IVideoDecoder {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::videodecoder::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::videodecoder::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyMulti(const ::std::vector<::com::rdk::hal::videodecoder::Property>& /*properties*/, ::std::vector<::com::rdk::hal::videodecoder::PropertyKVPair>* /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::videodecoder::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(::com::rdk::hal::videodecoder::Codec /*codec*/, bool /*secure*/, const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderControllerListener>& /*videoDecoderControllerListener*/, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openWithResolution(::com::rdk::hal::videodecoder::Codec /*codec*/, bool /*secure*/, const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderControllerListener>& /*videoDecoderControllerListener*/, int32_t /*maxWidth*/, int32_t /*maxHeight*/, ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderController>& /*videoDecoderController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderEventListener>& /*videoDecoderEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::videodecoder::IVideoDecoderEventListener>& /*videoDecoderEventListener*/, bool* /*_aidl_return*/) override {
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
};  // class IVideoDecoderDefault
}  // namespace videodecoder
}  // namespace hal
}  // namespace rdk
}  // namespace com
