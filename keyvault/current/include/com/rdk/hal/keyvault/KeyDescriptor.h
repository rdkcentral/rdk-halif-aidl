#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/Algorithm.h>
#include <com/rdk/hal/cryptoengine/Digest.h>
#include <com/rdk/hal/cryptoengine/KeyType.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace keyvault {
class KeyDescriptor : public ::android::Parcelable {
public:
  ::std::string alias;
  ::com::rdk::hal::cryptoengine::Algorithm algorithm = ::com::rdk::hal::cryptoengine::Algorithm::UNSET;
  ::com::rdk::hal::cryptoengine::KeyType keyType = ::com::rdk::hal::cryptoengine::KeyType::SECRET;
  int32_t keySizeBits = 0;
  int32_t usages = 0;
  bool extractable = false;
  ::com::rdk::hal::cryptoengine::Digest digest = ::com::rdk::hal::cryptoengine::Digest::UNSET;
  int32_t keyVersion = 0;
  int64_t createdAtMs = 0L;
  int64_t expiresAtMs = 0L;
  inline bool operator!=(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) != std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }
  inline bool operator<(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) < std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }
  inline bool operator<=(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) <= std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }
  inline bool operator==(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) == std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }
  inline bool operator>(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) > std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }
  inline bool operator>=(const KeyDescriptor& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest, keyVersion, createdAtMs, expiresAtMs) >= std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest, rhs.keyVersion, rhs.createdAtMs, rhs.expiresAtMs);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.keyvault.KeyDescriptor");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "KeyDescriptor{";
    os << "alias: " << ::android::internal::ToString(alias);
    os << ", algorithm: " << ::android::internal::ToString(algorithm);
    os << ", keyType: " << ::android::internal::ToString(keyType);
    os << ", keySizeBits: " << ::android::internal::ToString(keySizeBits);
    os << ", usages: " << ::android::internal::ToString(usages);
    os << ", extractable: " << ::android::internal::ToString(extractable);
    os << ", digest: " << ::android::internal::ToString(digest);
    os << ", keyVersion: " << ::android::internal::ToString(keyVersion);
    os << ", createdAtMs: " << ::android::internal::ToString(createdAtMs);
    os << ", expiresAtMs: " << ::android::internal::ToString(expiresAtMs);
    os << "}";
    return os.str();
  }
};  // class KeyDescriptor
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
