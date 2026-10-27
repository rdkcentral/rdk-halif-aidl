#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmiinput/IHDMIInput.h>
#include <com/rdk/hal/hdmiinput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
// @aidl-doc
/**
 *  @brief     HDMI Input Manager HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Amit Patel
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IHDMIInputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIInputManager)
  static const int32_t VERSION = 2000;
  const std::string HASH = "b40c57ae7d1bc106df72be13a813813713acbae8";
  static constexpr char* HASHVALUE = "b40c57ae7d1bc106df72be13a813813713acbae8";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the platform capabilities for HDMI inputs.
   *
   * This function can be called at any time.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return PlatformCapabilities parcelable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the platform list of HDMI input IDs.
   *
   * @param[out] _aidl_return IHDMIInput.Id[]
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a HDMI input interface.
   *
   * @param[in] hdmiInputId  The HDMI input port ID, must be one of the values returned by getHDMIInputIds().
   *
   * @param[out] _aidl_return IHDMIInput or null if the ID is invalid.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& hdmiInputId, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIInputManager

class IHDMIInputManagerDefault : public IHDMIInputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIInputIds(::std::vector<::com::rdk::hal::hdmiinput::IHDMIInput::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIInput(const ::com::rdk::hal::hdmiinput::IHDMIInput::Id& /*hdmiInputId*/, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInput>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIInputManagerDefault
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
