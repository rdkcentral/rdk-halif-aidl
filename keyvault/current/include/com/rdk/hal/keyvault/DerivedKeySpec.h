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
class DerivedKeySpec : public ::android::Parcelable {
public:
  ::std::string alias;
  ::com::rdk::hal::cryptoengine::Algorithm algorithm = ::com::rdk::hal::cryptoengine::Algorithm::UNSET;
  ::com::rdk::hal::cryptoengine::KeyType keyType = ::com::rdk::hal::cryptoengine::KeyType::SECRET;
  int32_t keySizeBits = 0;
  int32_t usages = 0;
  bool extractable = false;
  ::com::rdk::hal::cryptoengine::Digest digest = ::com::rdk::hal::cryptoengine::Digest::UNSET;
  inline bool operator!=(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) != std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }
  inline bool operator<(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) < std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }
  inline bool operator<=(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) <= std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }
  inline bool operator==(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) == std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }
  inline bool operator>(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) > std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }
  inline bool operator>=(const DerivedKeySpec& rhs) const {
    return std::tie(alias, algorithm, keyType, keySizeBits, usages, extractable, digest) >= std::tie(rhs.alias, rhs.algorithm, rhs.keyType, rhs.keySizeBits, rhs.usages, rhs.extractable, rhs.digest);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.keyvault.DerivedKeySpec");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DerivedKeySpec{";
    os << "alias: " << ::android::internal::ToString(alias);
    os << ", algorithm: " << ::android::internal::ToString(algorithm);
    os << ", keyType: " << ::android::internal::ToString(keyType);
    os << ", keySizeBits: " << ::android::internal::ToString(keySizeBits);
    os << ", usages: " << ::android::internal::ToString(usages);
    os << ", extractable: " << ::android::internal::ToString(extractable);
    os << ", digest: " << ::android::internal::ToString(digest);
    os << "}";
    return os.str();
  }
};  // class DerivedKeySpec
}  // namespace keyvault
}  // namespace hal
}  // namespace rdk
}  // namespace com
