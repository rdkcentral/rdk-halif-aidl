#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutput.h>
#include <com/rdk/hal/hdmioutput/PlatformCapabilities.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class IHDMIOutputManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputManager)
  static const int32_t VERSION = 1;
  const std::string HASH = "1e04b7a2abd81e9534138733782be7e186590068";
  static constexpr char* HASHVALUE = "1e04b7a2abd81e9534138733782be7e186590068";
  static const ::std::string& serviceName();
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* _aidl_return) = 0;
  virtual ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& hdmiOutputId, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputManager

class IHDMIOutputManagerDefault : public IHDMIOutputManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmioutput::PlatformCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIOutputIds(::std::vector<::com::rdk::hal::hdmioutput::IHDMIOutput::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getHDMIOutput(const ::com::rdk::hal::hdmioutput::IHDMIOutput::Id& /*hdmiOutputId*/, ::android::sp<::com::rdk::hal::hdmioutput::IHDMIOutput>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputManagerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
