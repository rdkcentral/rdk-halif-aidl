#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/SecurityLevel.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class VaultCapabilities : public ::android::Parcelable {
public:
  ::std::string vaultName;
  ::std::string halVersion;
  ::com::rdk::hal::cryptoengine::SecurityLevel securityLevel = ::com::rdk::hal::cryptoengine::SecurityLevel::SOFTWARE;
  int32_t maxKeys = 0;
  ::std::vector<int32_t> keySizes = {};
  bool persistsAcrossSleep = false;
  int64_t storageCapacityBytes = 0L;
  int64_t storageUsedBytes = 0L;
  inline bool operator!=(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) != std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }
  inline bool operator<(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) < std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }
  inline bool operator<=(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) <= std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }
  inline bool operator==(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) == std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }
  inline bool operator>(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) > std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }
  inline bool operator>=(const VaultCapabilities& rhs) const {
    return std::tie(vaultName, halVersion, securityLevel, maxKeys, keySizes, persistsAcrossSleep, storageCapacityBytes, storageUsedBytes) >= std::tie(rhs.vaultName, rhs.halVersion, rhs.securityLevel, rhs.maxKeys, rhs.keySizes, rhs.persistsAcrossSleep, rhs.storageCapacityBytes, rhs.storageUsedBytes);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.keyvault.VaultCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "VaultCapabilities{";
    os << "vaultName: " << ::android::internal::ToString(vaultName);
    os << ", halVersion: " << ::android::internal::ToString(halVersion);
    os << ", securityLevel: " << ::android::internal::ToString(securityLevel);
    os << ", maxKeys: " << ::android::internal::ToString(maxKeys);
    os << ", keySizes: " << ::android::internal::ToString(keySizes);
    os << ", persistsAcrossSleep: " << ::android::internal::ToString(persistsAcrossSleep);
    os << ", storageCapacityBytes: " << ::android::internal::ToString(storageCapacityBytes);
    os << ", storageUsedBytes: " << ::android::internal::ToString(storageUsedBytes);
    os << "}";
    return os.str();
  }
};  // class VaultCapabilities
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
