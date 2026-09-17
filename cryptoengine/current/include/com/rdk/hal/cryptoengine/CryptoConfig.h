#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/cryptoengine/Algorithm.h>
#include <com/rdk/hal/cryptoengine/BlockMode.h>
#include <com/rdk/hal/cryptoengine/Digest.h>
#include <com/rdk/hal/cryptoengine/EcCurve.h>
#include <com/rdk/hal/cryptoengine/KeyDerivation.h>
#include <com/rdk/hal/cryptoengine/PaddingMode.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace cryptoengine {
class CryptoConfig : public ::android::Parcelable {
public:
  ::com::rdk::hal::cryptoengine::Algorithm algorithm = ::com::rdk::hal::cryptoengine::Algorithm::UNSET;
  ::com::rdk::hal::cryptoengine::BlockMode blockMode = ::com::rdk::hal::cryptoengine::BlockMode::UNSET;
  ::com::rdk::hal::cryptoengine::PaddingMode paddingMode = ::com::rdk::hal::cryptoengine::PaddingMode::UNSET;
  int32_t keySizeBits = 0;
  ::std::vector<uint8_t> keyData = {};
  ::std::optional<::std::vector<uint8_t>> iv;
  ::std::optional<::std::vector<uint8_t>> aad;
  int32_t macLengthBits = 0;
  ::com::rdk::hal::cryptoengine::Digest digest = ::com::rdk::hal::cryptoengine::Digest::UNSET;
  ::com::rdk::hal::cryptoengine::EcCurve ecCurve = ::com::rdk::hal::cryptoengine::EcCurve::UNSET;
  ::com::rdk::hal::cryptoengine::KeyDerivation kdf = ::com::rdk::hal::cryptoengine::KeyDerivation::UNSET;
  ::std::optional<::std::vector<uint8_t>> salt;
  ::std::optional<::std::vector<uint8_t>> info;
  int32_t pbkdf2Iterations = 0;
  int32_t derivedKeyLengthBits = 0;
  int64_t rsaPublicExponent = 0L;
  ::std::optional<::std::vector<uint8_t>> wrappedKeyData;
  inline bool operator!=(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) != std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }
  inline bool operator<(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) < std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }
  inline bool operator<=(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) <= std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }
  inline bool operator==(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) == std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }
  inline bool operator>(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) > std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }
  inline bool operator>=(const CryptoConfig& rhs) const {
    return std::tie(algorithm, blockMode, paddingMode, keySizeBits, keyData, iv, aad, macLengthBits, digest, ecCurve, kdf, salt, info, pbkdf2Iterations, derivedKeyLengthBits, rsaPublicExponent, wrappedKeyData) >= std::tie(rhs.algorithm, rhs.blockMode, rhs.paddingMode, rhs.keySizeBits, rhs.keyData, rhs.iv, rhs.aad, rhs.macLengthBits, rhs.digest, rhs.ecCurve, rhs.kdf, rhs.salt, rhs.info, rhs.pbkdf2Iterations, rhs.derivedKeyLengthBits, rhs.rsaPublicExponent, rhs.wrappedKeyData);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.cryptoengine.CryptoConfig");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CryptoConfig{";
    os << "algorithm: " << ::android::internal::ToString(algorithm);
    os << ", blockMode: " << ::android::internal::ToString(blockMode);
    os << ", paddingMode: " << ::android::internal::ToString(paddingMode);
    os << ", keySizeBits: " << ::android::internal::ToString(keySizeBits);
    os << ", keyData: " << ::android::internal::ToString(keyData);
    os << ", iv: " << ::android::internal::ToString(iv);
    os << ", aad: " << ::android::internal::ToString(aad);
    os << ", macLengthBits: " << ::android::internal::ToString(macLengthBits);
    os << ", digest: " << ::android::internal::ToString(digest);
    os << ", ecCurve: " << ::android::internal::ToString(ecCurve);
    os << ", kdf: " << ::android::internal::ToString(kdf);
    os << ", salt: " << ::android::internal::ToString(salt);
    os << ", info: " << ::android::internal::ToString(info);
    os << ", pbkdf2Iterations: " << ::android::internal::ToString(pbkdf2Iterations);
    os << ", derivedKeyLengthBits: " << ::android::internal::ToString(derivedKeyLengthBits);
    os << ", rsaPublicExponent: " << ::android::internal::ToString(rsaPublicExponent);
    os << ", wrappedKeyData: " << ::android::internal::ToString(wrappedKeyData);
    os << "}";
    return os.str();
  }
};  // class CryptoConfig
}  // namespace cryptoengine
}  // namespace hal
}  // namespace rdk
}  // namespace com
