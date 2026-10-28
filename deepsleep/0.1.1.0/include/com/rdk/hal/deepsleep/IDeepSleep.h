#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/deepsleep/Capabilities.h>
#include <com/rdk/hal/deepsleep/KeyCode.h>
#include <com/rdk/hal/deepsleep/WakeUpTrigger.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace deepsleep {
// @aidl-doc
/**
 *  @brief     Deep Sleep HAL interface.
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
class IDeepSleep : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DeepSleep)
  static const int32_t VERSION = 1010;
  const std::string HASH = "6411d7fcfa82f9364bc617dffc8858ce799a9c73";
  static constexpr char* HASHVALUE = "6411d7fcfa82f9364bc617dffc8858ce799a9c73";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the capabilities of the deep sleep service.
   *
   * @param[out] _aidl_return Capabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Places the device into deep sleep which is configured to wake on a set of trigger types.
   *
   * The function will block until it resumes from standby and then returns the triggers that occured to wake up the
   * device. Upon return, the system clock has been adjusted to closely represent the actual elapsed time spent in
   * deep sleep.
   *
   * The `preconfiguredTriggers[]` reported in the `Capabilities` are always enabled as trigger sources.
   * If they are not explicitly specified in the `triggersToWakeUpon[]` array then they are implicitly added.
   *
   * `WakeUpTrigger.TIMER` is armed only when `setWakeUpTimer()` has set a period greater than 0.
   * With a period of 0 the HAL does not program the timer, even if `WakeUpTrigger.TIMER` is in
   * `preconfiguredTriggers[]` or `triggersToWakeUpon[]`.
   *
   * If the timer expires before the device has entered deep sleep, the HAL abandons deep sleep and
   * returns true with `WakeUpTrigger.TIMER` in `wokeUpByTriggers[]`.
   *
   * After the device exits deep sleep, whichever trigger woke it, the HAL resets the timer period to 0.
   *
   * @param[in] triggersToWakeUpon    Array of wake up trigger events to wake upon after entering deep sleep.
   * @param[out] wokeUpByTriggers     Array of wake up trigger events that occurred when waking the device from deep
   * sleep.
   * @param[out] keyCode              If one of the `wokeUpByTriggers[]` is an RCU based trigger, then keyCode
   * contains the Linux key code. `null` if not applicable.
   *
   * @param[out] _aidl_return boolean - true on success or false if any of the triggers are not supported on the device.
   *   - true: - the deep sleep was successful and woke up on one of the explicit or implicit triggers.
   *   - false: - deep sleep could not be entered.
   * @see setWakeUpTimer()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& triggersToWakeUpon, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* wokeUpByTriggers, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* keyCode, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the timer period to wake the device from deep sleep.
   *
   * The timer starts when `enterDeepSleep()` is called and `WakeUpTrigger.TIMER` is listed in the
   * `triggersToWakeUpon[]` array. The timer must support at least 7 days.
   *
   * The period is 0 until this is called, and is reset to 0 after every wake, so the middleware sets it
   * before each `enterDeepSleep()`. The middleware calculates the period from real time, for example the
   * seconds until the product's scheduled wake time. The HAL programs the period exactly as requested: a
   * period shorter than the time the device takes to enter deep sleep wakes it straight away.
   *
   * The platform is expected to wake the device within ±/- 5 seconds of the programmed period.
   * The actual wake time could be adjusted for clock drift and resume latency where applicable.
   *
   * @param[in] seconds   The timer period in seconds which must be >= 0. Negative values are invalid.
   *                      0 disables the timer: the HAL does not program the timer and `WakeUpTrigger.TIMER`
   *                      is not armed, even if it is in `Capabilities.preconfiguredTriggers[]`.
   *
   * @param[out] _aidl_return boolean
   *   - true: - if the wake up timer period was valid.
   *   - false: - the period was invalid.
   * @pre The WakeUpTrigger.TIMER must be listed in the Capabilities.supportedTriggers array.
   *
   * @see getWakeUpTimer(), enterDeepSleep()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setWakeUpTimer(int32_t seconds, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the timer period set by `setWakeUpTimer()`.
   *
   * If no period has been set since the last wake, 0 is returned, meaning no timer.
   *
   * @param[out] _aidl_return int     The period of the wake up timer in seconds.
   *
   *
   * @pre The WakeUpTrigger.TIMER must be listed in the Capabilities.supportedTriggers array.
   *
   * @see setWakeUpTimer()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getWakeUpTimer(int32_t* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDeepSleep

class IDeepSleepDefault : public IDeepSleep {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::deepsleep::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status enterDeepSleep(const ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>& /*triggersToWakeUpon*/, ::std::vector<::com::rdk::hal::deepsleep::WakeUpTrigger>* /*wokeUpByTriggers*/, ::std::optional<::com::rdk::hal::deepsleep::KeyCode>* /*keyCode*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setWakeUpTimer(int32_t /*seconds*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getWakeUpTimer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDeepSleepDefault
}  // namespace deepsleep
}  // namespace hal
}  // namespace rdk
}  // namespace com
