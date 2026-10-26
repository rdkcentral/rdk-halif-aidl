#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/Capabilities.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
// @aidl-doc
/**
 * @brief Indicator HAL interface.
 *
 * Defines the Hardware Abstraction Layer (HAL) interface for indicator services.
 * Each indicator instance represents a hardware-controlled visual indicator
 * (e.g., LED, panel display) that can be set to different states.
 *
 * For RDK reference implementations, a single global indicator is typically used
 * to reflect the overall device state. Third-party vendors may implement multiple
 * independent indicator instances if required by their platform architecture.
 *
 * States are represented as strings to provide flexibility and extensibility.
 * Standard state names include:
 * - "BOOT": Initial bootloader-defined state
 * - "ACTIVE": System is fully operational
 * - "STANDBY": Low-power idle state
 * - "OFF": All indicators are off
 * - "DEEP_SLEEP": Deep sleep mode
 * - "WPS_CONNECTING": Wi-Fi Protected Setup is active
 * - "WPS_CONNECTED": WPS connection successful
 * - "WPS_ERROR": WPS session failed
 * - "WPS_SES_OVERLAP": Multiple WPS sessions detected
 * - "WIFI_ERROR": Wi-Fi hardware or configuration fault
 * - "IP_ACQUIRED": IP address successfully assigned
 * - "NO_IP": IP assignment failed
 * - "FULL_SYSTEM_RESET": Factory reset in progress
 * - "USB_UPGRADE": Firmware upgrade via USB
 * - "SOFTWARE_DOWNLOAD_ERROR": Software update failed
 * - "PSU_FAILURE": Power supply fault detected
 *
 * On system boot, the implementation shall set the indicator to the first state
 * defined in the platform's HFP file until changed by the set() function.
 *
 * Vendors may define additional custom states as needed.
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IIndicator : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Indicator)
  static const int32_t VERSION = 2000;
  const std::string HASH = "c42e2138000a28ce8688e053ade6b9dc24856de7";
  static constexpr char* HASHVALUE = "c42e2138000a28ce8688e053ade6b9dc24856de7";
  // @aidl-doc
  /** Indicator resource ID type */
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

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.indicator.IIndicator.Id");
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
   * Gets the capabilities of this indicator instance.
   *
   * This function can be called at any time and returns the set of states
   * supported by this specific indicator instance. The returned value must
   * not change between calls.
   *
   * @param[out] _aidl_return Capabilities parcelable containing supported state strings.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::indicator::Capabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets a new indicator state.
   *
   * The state string must be one of the states listed in the capabilities
   * returned by getCapabilities(). Setting an unsupported state will fail.
   *
   * @param[in] state An indicator state string to be set.
   * @param[out] _aidl_return Success flag indicating whether state was set.
   *   - true: State was set successfully.
   *   - false: State is not supported or setting failed.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid state string.
   */
  virtual ::android::binder::Status set(const ::std::string& state, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the current indicator state.
   *
   * Returns the currently active state as a string.
   *
   * @param[out] _aidl_return Current indicator state string.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status get(::std::string* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IIndicator

class IIndicatorDefault : public IIndicator {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::indicator::Capabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status set(const ::std::string& /*state*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status get(::std::string* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IIndicatorDefault
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
