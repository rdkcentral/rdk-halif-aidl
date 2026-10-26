#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/avclock/ClockMode.h>
#include <com/rdk/hal/avclock/ClockTime.h>
#include <com/rdk/hal/avclock/Property.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace avclock {
// @aidl-doc
/**
 *  @brief     AV Clock Controller HAL interface.
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
class IAVClockController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AVClockController)
  static const int32_t VERSION = 2010;
  const std::string HASH = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  static constexpr char* HASHVALUE = "d0becf05cd55f7eea5b57014b844635eeee1214a";
  // @aidl-doc
  /**
   * Sets a property.
   *
   * Mutator — lives on the controller because property writes require the
   * single-writer ownership established by `IAVClock.open()`. Read access
   * (`getProperty()`) remains on `IAVClock` so identity properties can be
   * discovered before opening.
   *
   * Validation pattern:
   *  - `EX_ILLEGAL_ARGUMENT` indicates a caller bug — the `property` key is
   *    not a member of the Property enum. The caller should fix the call;
   *    retrying with the same arguments will keep failing.
   *  - `false` indicates a runtime rejection — the key is valid and the
   *    value is well-formed, but the write could not be applied (value out
   *    of range for this clock instance, property is read-only on this
   *    platform, hardware busy, etc.). The caller can retry or pick a
   *    different value.
   *
   * @param[in] property              The key of a property from the Property enum.
   * @param[in] propertyValue         Holds the value to set.
   *
   * @param[out] _aidl_return boolean
   *   - true: Property was successfully set.
   *   - false: Runtime rejection (value out of range, property
   *     read-only on this platform, etc.).
   * @see IAVClock.getProperty()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT when `property`
   *         is not a member of the Property enum (caller bug).
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::avclock::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Starts the AV Clock.
   *
   * The AV Clock must be in a `READY` state before it can be started.
   * If successful the AV Clock transitions to the `STARTING` state and then to the `STARTED` state.
   *
   * @pre AV Clock is in State::READY state.
   *
   * @see stop(), close()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status start() = 0;
  // @aidl-doc
  /**
   * Stops the AV Clock.
   *
   * The AV Clock enters the `STOPPING` state and then the enters the `READY` state.
   *
   * @pre AV Clock is in State::STARTED state.
   *
   * @see start()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status stop() = 0;
  // @aidl-doc
  /**
   * Sets the mode of the AV Clock.
   *
   * The default mode is `ClockMode::AUTO` and can only be changed in the `READY` state.
   *
   * @param[in] clockMode		        The AV Clock mode.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully set the clock mode.
   *   - false: The clock mode is invalid.
   * @pre AV Clock is in State::READY state.
   *
   * @see getClockMode()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode clockMode, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the mode of the AV Clock.
   *
   * @param[out] _aidl_return ClockMode
   *
   * @pre AV Clock is in State::READY or State::STARTED state.
   *
   * @see setClockMode()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Notifies the AV Clock of a new PCR sample filtered from the broadcast stream.
   *
   * When the AV Clock source is set to `ClockMode::PCR` then the client must deliver PCR samples
   * filtered from the broadcast stream through calls to `notifyPCRSample()`.
   *
   * It is important that the sampleTimestamp is recorded as soon as possible when the PCR
   * is seen in the broadcast stream to reduce sample jitter.
   *
   * If the AV clock is not `STARTED` or not in `PCR` clock mode then the `binder::Status EX_ILLEGAL_STATE` exception
   * is returned.
   *
   * @param[in] pcrTimeNs			    The PCR time converted to nanoseconds.
   * @param[in] sampleTimestampNs	    CLOCK_MONOTONIC_RAW timestamp in nanoseconds when the PCR sample was
   * received.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully notified the PCR sample.
   *   - false: One or more invalid parameters.
   * @pre AV Clock is in State::STARTED state and in PCR clock mode.
   *
   * @see setClockMode()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status notifyPCRSample(int64_t pcrTimeNs, int64_t sampleTimestampNs, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current AV Clock time.
   *
   * For `ClockMode::PCR` driven clocks this returns the equivalent of the MPEG system time clock (STC) in nanoseconds
   * units.
   *
   * For other clock modes this returns the clock used for presentation of AV frames in the system.
   *
   * Priming: the AV Clock has a primed/unprimed sub-state inside `STARTED`.
   * Until the clock receives its first priming event for the configured
   * `ClockMode`, it is `STARTED` but unprimed and `getCurrentClockTime()`
   * returns `null`. Once primed, it returns a valid `ClockTime`. Clients
   * that need to react to the priming transition without polling can
   * register for the `IAVClockControllerListener.onPrimed()` callback.
   *
   * Priming source per `ClockMode`:
   * - `ClockMode::PCR`          → first call to `notifyPCRSample()`
   * - `ClockMode::AUDIO_MASTER` → first audio frame PTS received by the linked audio sink
   * - `ClockMode::VIDEO_MASTER` → first video frame PTS received by the linked video sink
   * - `ClockMode::AUTO`         → whichever of the above arrives first, given the configured sources
   *
   * The unprimed → primed transition is one-way per started session;
   * re-priming requires `stop()` followed by `start()`.
   *
   * @param[out] _aidl_return ClockTime, or `null` if the clock is `STARTED` but not yet primed.
   *
   * @pre AV Clock is in State::STARTED state.
   *
   * @see IAVClockControllerListener.onPrimed()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the clock is not in `STARTED`.
   */
  virtual ::android::binder::Status getCurrentClockTime(::std::optional<::com::rdk::hal::avclock::ClockTime>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the playback rate for the AV Clock.
   *
   * Not available when `ClockMode::PCR` mode is used.
   *
   * When the rate is set between 0.5 and 2.0, the AV presentation has audio pitch correction.
   *
   * The rate 0.0 will pause the playback.
   *
   * @param[in] rate      The playback rate.  Default is 1.0 for normal play forward speed.
   *
   * @param[out] _aidl_return boolean
   *   - true: Successfully set the playback state.
   *   - false: Invalid rate parameter.
   * @pre AV Clock is in State::READY or State::STARTED state and clock mode is not ClockMode::PCR.
   *
   * @see getPlaybackRate()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status setPlaybackRate(double rate, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the playback rate.
   *
   * Not valid for `ClockMode::PCR` mode driven clocks, which shall return `binder::Status EX_ILLEGAL_STATE`.
   *
   * @param[out] _aidl_return double representing the playback rate where 1.0 is normal speed.
   *
   * @pre AV Clock is in State::READY or State::STARTED state and mode is not ClockMode::PCR.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status getPlaybackRate(double* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAVClockController

class IAVClockControllerDefault : public IAVClockController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::avclock::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setClockMode(::com::rdk::hal::avclock::ClockMode /*clockMode*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getClockMode(::com::rdk::hal::avclock::ClockMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status notifyPCRSample(int64_t /*pcrTimeNs*/, int64_t /*sampleTimestampNs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCurrentClockTime(::std::optional<::com::rdk::hal::avclock::ClockTime>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPlaybackRate(double /*rate*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPlaybackRate(double* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAVClockControllerDefault
}  // namespace avclock
}  // namespace hal
}  // namespace rdk
}  // namespace com
