#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/drm/Mode.h>
#include <com/rdk/hal/drm/Pattern.h>
#include <com/rdk/hal/drm/SubSample.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace drm {
// @aidl-doc
/** Arguments to ICryptoPlugin decrypt */
class DecryptArgs : public ::android::Parcelable {
public:
  // @aidl-doc
  /**
   * A flag to indicate if a secure decoder is being used.
   *
   * This enables the plugin to configure buffer modes to work consistently
   * with a secure decoder.
   *
   */
  bool secure = false;
  // @aidl-doc
  /**
   * The keyId for the key that is used to do the decryption.
   *
   * The keyId refers to a key in the associated MediaDrm instance.
   */
  ::std::vector<uint8_t> keyId;
  // @aidl-doc
  /** The initialization vector */
  ::std::vector<uint8_t> iv;
  // @aidl-doc
  /** Crypto mode */
  ::com::rdk::hal::drm::Mode mode = ::com::rdk::hal::drm::Mode(0);
  // @aidl-doc
  /** Crypto pattern */
  ::com::rdk::hal::drm::Pattern pattern;
  // @aidl-doc
  /**
   * A vector of subsamples indicating the number of clear and encrypted
   * bytes to process.
   *
   * This allows the decrypt call to operate on a range of subsamples in a
   * single call
   */
  ::std::vector<::com::rdk::hal::drm::SubSample> subSamples;
  // @aidl-doc
  /**
   * Input AVBuffer handle for the encrypted data.
   *
   * It is the responsibility of the caller to recycle/free the allocated AVBuffer after the call to decrypt returns.
   */
  int64_t sourceBufferHandle = 0L;
  // @aidl-doc
  /** Output AVBuffer handle for the decrypted data. */
  int64_t destinationBufferHandle = 0L;
  inline bool operator!=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) != std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator<(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) < std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator<=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) <= std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator==(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) == std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator>(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) > std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }
  inline bool operator>=(const DecryptArgs& rhs) const {
    return std::tie(secure, keyId, iv, mode, pattern, subSamples, sourceBufferHandle, destinationBufferHandle) >= std::tie(rhs.secure, rhs.keyId, rhs.iv, rhs.mode, rhs.pattern, rhs.subSamples, rhs.sourceBufferHandle, rhs.destinationBufferHandle);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DecryptArgs");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DecryptArgs{";
    os << "secure: " << ::android::internal::ToString(secure);
    os << ", keyId: " << ::android::internal::ToString(keyId);
    os << ", iv: " << ::android::internal::ToString(iv);
    os << ", mode: " << ::android::internal::ToString(mode);
    os << ", pattern: " << ::android::internal::ToString(pattern);
    os << ", subSamples: " << ::android::internal::ToString(subSamples);
    os << ", sourceBufferHandle: " << ::android::internal::ToString(sourceBufferHandle);
    os << ", destinationBufferHandle: " << ::android::internal::ToString(destinationBufferHandle);
    os << "}";
    return os.str();
  }
};  // class DecryptArgs
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
