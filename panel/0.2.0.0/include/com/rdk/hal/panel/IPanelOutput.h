#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/Capabilities.h>
#include <com/rdk/hal/panel/IPanelOutputController.h>
#include <com/rdk/hal/panel/IPanelOutputControllerListener.h>
#include <com/rdk/hal/panel/IPanelOutputEventListener.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
// @aidl-doc
/**
 *  @brief     Display Panel Output HAL interface.
 *  @authors   Luc Kennedy-Lamb, Peter Stieglitz, Douglas Adler, Ramkumar Pattabiraman
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 *  - <b>Boolean / ErrorCode results</b>: A returned boolean `false` or a non-success `ErrorCode`
 *    indicates that the call was accepted and processed but could not complete successfully for the
 *    documented reasons. Input validation and invalid controller state are still reported via Binder
 *    exceptions unless a method explicitly documents otherwise.
 */
class IPanelOutput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutput)
  static const int32_t VERSION = 2000;
  const std::string HASH = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  static constexpr char* HASHVALUE = "4479c03b862f1fd8020fb7ad2d043139bb832d75";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the capabilities of the panel service.
   *
   * This function can be called at any time and the returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::panel::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Open this panel output for exclusive control.
   *
   * On success this returns the exclusive IPanelOutputController for the
   * panel output. The controller may already be in any retained lifecycle
   * state, so the client must call `getState()` before deciding whether to
   * start, wait for an in-progress transition, continue with STARTED-state
   * operations, or recover from ERROR.
   *
   * Only one controller may exist at a time. If the owning client crashes,
   * the HAL releases exclusive ownership of the controller but retains the
   * current panel state and the latest stored configuration so a later client
   * can reopen the panel and continue from the existing state.
   *
   * @param listener Listener for exclusive controller callbacks.
   *
   * A client that reopens the panel after the previous controller owner died
   * must call `getState()` on the returned controller and continue from that
   * state rather than assuming the panel has been stopped or reset.
   *
   * @param[out] _aidl_return IPanelOutputController, or null if the panel output cannot be opened.
   *
   * @see close(), IPanelOutputController, registerListener()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if panel output is already open.
   * @retval ::android::binder::Status::EX_NULL_POINTER if listener is null.
   *
   *          Lifecycle state changes are reported through registered
   *          `IPanelOutputEventListener` instances.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::panel::IPanelOutputControllerListener>& listener, ::android::sp<::com::rdk::hal::panel::IPanelOutputController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Close this panel output and release the controller.
   *
   * Accepted from STOPPED or ERROR. From STOPPED this is the normal close
   * path. From ERROR this is the recovery path: after a start() failure
   * (which transitions the panel output to ERROR), the client calls close()
   * to release the controller and the panel output returns to a state where
   * it can be opened again. On success the controller is invalidated and
   * another client may `open()` the panel output.
   *
   * If the panel remains in ERROR after a close()/open()/start() recovery
   * attempt, the platform may require a full device reboot or power cycle to
   * clear latched display hardware. Treat that as a last resort and a
   * platform-specific recovery action rather than a normal API flow.
   *
   * Client death is handled separately from `close()`: the HAL releases the
   * controller ownership automatically, but it does not force the panel back
   * to STOPPED or discard the last stored configuration.
   *
   * If the panel output is in STARTED, STARTING, or STOPPING the call fails
   * with EX_ILLEGAL_STATE - the client must call stop() first (or, from
   * ERROR, close() directly).
   *
   * @param controller The IPanelOutputController instance returned by open().
   *
   * @param[out] _aidl_return Success flag.
   *   - true: Successfully closed.
   *   - false: The supplied controller is not the instance returned by open().
   * @see open(), IPanelOutputController.start()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if panel output is not in STOPPED or ERROR state.
   * @retval ::android::binder::Status::EX_NULL_POINTER if controller is null.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::panel::IPanelOutputController>& controller, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a callback listener for events generated by the panel output.
   *
   * An `IPanelOutputEventListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * Listener registration is independent of open()/close() and does not require
   * exclusive control of the panel output.
   *
   * @param[in] listener      IPanelOutputEventListener interface.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterListener(), IPanelOutputEventListener
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for a null object.
   */
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& listener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a callback listener for events generated by the panel output.
   *
   * @param[in] listener      Reference to a previously registered IPanelOutputEventListener interface.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerListener(), IPanelOutputEventListener
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for a null object.
   */
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& listener, bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutput

class IPanelOutputDefault : public IPanelOutput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::panel::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::panel::IPanelOutputControllerListener>& /*listener*/, ::android::sp<::com::rdk::hal::panel::IPanelOutputController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::panel::IPanelOutputController>& /*controller*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::panel::IPanelOutputEventListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
