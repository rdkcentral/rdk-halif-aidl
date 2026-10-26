#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/videosink/Capabilities.h>
#include <com/rdk/hal/videosink/IVideoSinkController.h>
#include <com/rdk/hal/videosink/IVideoSinkControllerListener.h>
#include <com/rdk/hal/videosink/IVideoSinkEventListener.h>
#include <com/rdk/hal/videosink/Property.h>
#include <com/rdk/hal/videosink/State.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace videosink {
// @aidl-doc
/**
 *  @brief     Video Sink HAL interface.
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
class IVideoSink : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(VideoSink)
  static const int32_t VERSION = 3000;
  const std::string HASH = "da350441651184f9632c4dbf59d960ce6767f0bf";
  static constexpr char* HASHVALUE = "da350441651184f9632c4dbf59d960ce6767f0bf";
  // @aidl-doc
  /** Video Sink resource ID type */
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.videosink.IVideoSink.Id");
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
   * Gets the capabilities for this Video Sink.
   *
   * This function can be called at any time and is not dependant on any Video Sink state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::videosink::Capabilities* _aidl_return) = 0;
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
  virtual ::android::binder::Status getProperty(::com::rdk::hal::videosink::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current Video Sink state.
   *
   * @param[out] _aidl_return State enum value.
   *
   * @see IVideoSinkListener.onStateChanged().
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::videosink::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Opens the Video Sink.
   *
   * If successful the Video Sink transitions to an OPENING state and then a READY state.
   *
   * If the client that opened the `IVideoSinkController` crashes,
   * then the `IVideoSinkController` has `stop()` and `close()` implicitly called to perform clean up.
   *
   * @param[in] videoSinkControllerListener       Callback listener for controller events.
   *
   * @param[out] _aidl_return IVideoSinkController or null on error.
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see close(), IVideoSinkController.start()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If the resource is not in the CLOSED state.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkControllerListener>& videoSinkControllerListener, ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Closes the Video Sink.
   *
   * The Video Sink must be in a `READY` state before it can be closed.
   * If successful the Video Sink transitions to a `CLOSING` state and then a `CLOSED` state.
   *
   * @param[in] videoSinkController     Instance of the IVideoSinkController.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or unrecognised parameter.
   * @see open()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE If instance is not in OPENED State.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>& videoSinkController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a Video Sink event listener.
   *
   * An `IVideoSinkEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] videoSinkEventListener	    Listener object for callbacks.
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
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& videoSinkEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a Video Sink event listener.
   *
   * @param[in] videoSinkEventListener	    Listener object for callbacks.
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
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& videoSinkEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IVideoSink

class IVideoSinkDefault : public IVideoSink {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::videosink::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::videosink::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getState(::com::rdk::hal::videosink::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkControllerListener>& /*videoSinkControllerListener*/, ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkController>& /*videoSinkController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& /*videoSinkEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::videosink::IVideoSinkEventListener>& /*videoSinkEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IVideoSinkDefault
}  // namespace videosink
}  // namespace hal
}  // namespace rdk
}  // namespace com
