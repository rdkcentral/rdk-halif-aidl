#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmioutput/IHDMIOutputController.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class BpHDMIOutputController : public ::android::BpInterface<IHDMIOutputController> {
public:
  explicit BpHDMIOutputController(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIOutputController() = default;
  ::android::binder::Status start() override;
  ::android::binder::Status stop() override;
  ::android::binder::Status getHotPlugDetectState(bool* _aidl_return) override;
  ::android::binder::Status setProperty(::com::rdk::hal::hdmioutput::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) override;
  ::android::binder::Status setPropertyMulti(const ::std::vector<::com::rdk::hal::hdmioutput::PropertyKVPair>& propertyKVList, bool* _aidl_return) override;
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) override;
  ::android::binder::Status getHDCPReceiverVersion(::com::rdk::hal::hdmioutput::HDCPProtocolVersion* _aidl_return) override;
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmioutput::HDCPStatus* _aidl_return) override;
  ::android::binder::Status setSPDInfoFrame(const ::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>& spdInfoFrame) override;
  ::android::binder::Status getSPDInfoFrame(::std::optional<::com::rdk::hal::hdmioutput::SPDInfoFrame>* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIOutputController
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
