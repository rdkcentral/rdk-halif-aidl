#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
class IAudioCapture : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioCapture)
  static const int32_t VERSION = 3000;
  const std::string HASH = "ff12e597d51955e239d709062d17dd73b32ddb56";
  static constexpr char* HASHVALUE = "ff12e597d51955e239d709062d17dd73b32ddb56";
  virtual ::android::binder::Status getSharedMemory(::std::vector<int64_t>* sharedMemorySizeBytes, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status releaseSharedMemory() = 0;
  virtual ::android::binder::Status start() = 0;
  virtual ::android::binder::Status stop() = 0;
  virtual ::android::binder::Status releaseData(int64_t offsetBytes, int32_t lengthBytes) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioCapture

class IAudioCaptureDefault : public IAudioCapture {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getSharedMemory(::std::vector<int64_t>* /*sharedMemorySizeBytes*/, ::android::os::ParcelFileDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseSharedMemory() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status start() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status stop() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseData(int64_t /*offsetBytes*/, int32_t /*lengthBytes*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioCaptureDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
