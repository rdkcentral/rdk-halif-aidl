#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/indicator/IIndicator.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace indicator {
// @aidl-doc
/**
 * @brief Indicator Manager HAL interface.
 *
 * Provides management and discovery of indicator instances. This interface enables
 * multi-instance support, allowing platforms to expose multiple independent indicator
 * resources. For RDK reference implementations, typically a single global indicator
 * instance is provided that reflects the overall device state.
 *
 * Third-party vendors may extend this to support multiple indicators if their platform
 * architecture requires independent indicator control (e.g., per-zone indicators).
 *
 * @author Luc Kennedy-Lamb
 * @author Peter Stieglitz
 * @author Douglas Adler
 * @author Gerald Weatherup
 */
class IIndicatorManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(IndicatorManager)
  static const int32_t VERSION = 2000;
  const std::string HASH = "c42e2138000a28ce8688e053ade6b9dc24856de7";
  static constexpr char* HASHVALUE = "c42e2138000a28ce8688e053ade6b9dc24856de7";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the list of platform indicator IDs.
   *
   * For RDK reference implementations, this typically returns a single global indicator ID.
   * Third-party vendors may return multiple IDs if their platform supports independent
   * indicator instances.
   *
   * @param[out] _aidl_return IIndicator.Id[] array of available indicator instance IDs.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the indicator interface for a given ID.
   *
   * @param[in] indicatorId The ID of the indicator resource.
   * @param[out] _aidl_return IIndicator interface or null on invalid indicator ID.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& indicatorId, ::android::sp<::com::rdk::hal::indicator::IIndicator>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IIndicatorManager

class IIndicatorManagerDefault : public IIndicatorManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getIndicatorIds(::std::vector<::com::rdk::hal::indicator::IIndicator::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getIndicator(const ::com::rdk::hal::indicator::IIndicator::Id& /*indicatorId*/, ::android::sp<::com::rdk::hal::indicator::IIndicator>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IIndicatorManagerDefault
}  // namespace indicator
}  // namespace hal
}  // namespace rdk
}  // namespace com
