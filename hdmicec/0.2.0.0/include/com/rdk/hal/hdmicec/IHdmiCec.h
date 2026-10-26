#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/hdmicec/IHdmiCecController.h>
#include <com/rdk/hal/hdmicec/IHdmiCecEventListener.h>
#include <com/rdk/hal/hdmicec/Property.h>
#include <com/rdk/hal/hdmicec/State.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
// @aidl-doc
/**
 *  @brief     HDMI CEC HAL interface.
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
class IHdmiCec : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiCec)
  static const int32_t VERSION = 2000;
  const std::string HASH = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  static constexpr char* HASHVALUE = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * @brief Gets the current state of the HDMI CEC interface.
   *
   * The HDMI CEC follows the standard HAL-E AV Session State Management.
   * Only CLOSED and STARTED are reported.
   *
   * @param[out] _aidl_return State enum value.
   *
   *
   * @see IHdmiCecEventListener.onStateChanged().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getState(::com::rdk::hal::hdmicec::State* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets a property.
   *
   * @param[in] property              The key of a property from the Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null if the property key is unknown.
   *
   *
   * @see setProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getProperty(::com::rdk::hal::hdmicec::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the logical addresses that have been set for filtering.
   *
   * The broadcast address 0xF is always implied as being filtered as a logical address and
   * not returned in this array.
   *
   * @param[out] _aidl_return int[] - an array of addresses. The size of the array will be zero if no additional addresses have been
   *                     set.
   *
   *
   * @see addLogicalAddress(), removeLogicalAddress()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getLogicalAddresses(::std::vector<int32_t>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Opens the HDMI CEC interface for control.
   *
   * If successful the HDMI CEC interface transitions directly to the STARTED state.
   * Before logical addresses are added all broadcast messages will be processed and callbacks generated.
   * The returned IHdmiCecController interface is used by the client to set a logical addresses and
   * send CEC message buffers over the CEC bus.
   * An IHdmiCecEventListener must be provided to receive incoming CEC message and state change events.
   *
   * Only a single instance can be opened. Attempts to open again, by this or another process will fail with
   * `binder::Status EX_ILLEGAL_STATE`. On opening all necessary logical addresses will be required to be added by the
   * client.
   *
   * For a source HDMI device; on detecting the de-assertion of HPD, the Controller Client must close an opened
   * IHdmiCecController interface, or remove all previously added logical addresses.
   * It is not considered an error for a client to open the HDMI device while HPD is not asserted.
   *
   * If the client that opened the `IHdmiCecController` crashes,
   * then close() is implicitly called to perform clean up.
   *
   * @param[in] cecControllerListener         A IHdmiCecEventListener for the Controller Client to receive callbacks
   * through.
   *
   * @param[out] _aidl_return IHdmiCecController or null on error.
   *
   *
   * @pre The resource must be in State::CLOSED.
   *
   * @see close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecControllerListener, ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Closes the HDMI CEC interface.
   *
   * The HDMI CEC interface must be in a STARTED state before it can be closed.
   * If successful the HDMI CEC interface transition to the CLOSED state.
   * The IHdmiCecController instance must not be used after it has been closed.
   * On closing the HDMI CEC interface, all added logical addresses are removed.
   * On the return of close() no more callbacks will occur to the IHdmiCecEventListener
   * passed in the open() call.
   *
   * @param[in] hdmiCecController     Instance of IHdmiCecController.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully closed.
   *   - false: Invalid state or unrecognised parameter.
   * @pre The resource must be in State::STARTED.
   *
   * @see open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>& hdmiCecController, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a CEC event listener.
   *
   * This allows a client, other than the Controlling client, to receive messages and monitor the state for diagnostic
   * purposes.
   *
   * @param[in] cecEventListener    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a CEC event listener.
   *
   * @param[in] cecEventListener    Listener object for event callbacks.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerEventListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& cecEventListener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHdmiCec

class IHdmiCecDefault : public IHdmiCec {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getState(::com::rdk::hal::hdmicec::State* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(::com::rdk::hal::hdmicec::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getLogicalAddresses(::std::vector<int32_t>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& /*cecControllerListener*/, ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecController>& /*hdmiCecController*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& /*cecEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmicec::IHdmiCecEventListener>& /*cecEventListener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHdmiCecDefault
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
