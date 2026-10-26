#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/CryptoSchemes.h>
#include <com/rdk/hal/drm/ICryptoPlugin.h>
#include <com/rdk/hal/drm/IDrmPlugin.h>
#include <com/rdk/hal/drm/Uuid.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/**
 * IDrmFactory is the main entry point for interacting with a vendor's
 * drm HAL to create drm plugin instances. A drm plugin instance
 * creates drm sessions which are used to obtain keys for a crypto
 * session so it can decrypt protected video content.
 */
class IDrmFactory : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DrmFactory)
  static const int32_t VERSION = 2000;
  const std::string HASH = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  static constexpr char* HASHVALUE = "ef9f0fd6c9a0c25f700ad00f124132011c6de297";
  // @aidl-doc
  /**
   * Create a drm plugin instance for the specified uuid and
   * scheme-specific initialization data.
   *
   * @param uuid uniquely identifies the drm scheme. See
   *     http://dashif.org/identifiers/protection for uuid assignments
   * @param appPackageName identifies the package name of the calling
   *     application.
   *
   * @param[out] _aidl_return A DRM plugin instance if successful, or null if not created.
   *                      Implicit error codes:
   *                        + ERROR_DRM_CANNOT_HANDLE if the plugin cannot be created.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::std::string& appPackageName, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Create a crypto plugin for the specified uuid and scheme-specific
   * initialization data.
   *
   * @param uuid uniquely identifies the drm scheme. See
   *     http://dashif.org/identifiers/protection for uuid assignments
   *
   * @param initData scheme-specific init data.
   *        The initData can (if known) contain the SessionId created by DRMPlugin::openSession(), else a byte array
   * of zero length.
   *
   * @param[out] _aidl_return A crypto plugin instance if successful, or null if not created.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& uuid, const ::std::vector<uint8_t>& initData, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Return vector of uuids identifying crypto schemes supported by
   * this HAL.
   *
   * @param[out] _aidl_return List of uuids for which isCryptoSchemeSupported is true;
   *                       each uuid can be used as input to createPlugin.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDrmFactory

class IDrmFactoryDefault : public IDrmFactory {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status createDrmPlugin(const ::com::rdk::hal::drm::Uuid& /*uuid*/, const ::std::string& /*appPackageName*/, ::android::sp<::com::rdk::hal::drm::IDrmPlugin>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createCryptoPlugin(const ::com::rdk::hal::drm::Uuid& /*uuid*/, const ::std::vector<uint8_t>& /*initData*/, ::android::sp<::com::rdk::hal::drm::ICryptoPlugin>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSupportedCryptoSchemes(::com::rdk::hal::drm::CryptoSchemes* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDrmFactoryDefault
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
