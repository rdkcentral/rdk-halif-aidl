#pragma once
#include <mutex>

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>
#include <com/rdk/hal/hdmiinput/IHDMIInput.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmiinput {
class BpHDMIInput : public ::android::BpInterface<IHDMIInput> {
public:
  explicit BpHDMIInput(const ::android::sp<::android::IBinder>& _aidl_impl);
  virtual ~BpHDMIInput() = default;
  ::android::binder::Status getCapabilities(::com::rdk::hal::hdmiinput::Capabilities* _aidl_return) override;
  ::android::binder::Status getProperty(::com::rdk::hal::hdmiinput::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) override;
  ::android::binder::Status getState(::com::rdk::hal::hdmiinput::State* _aidl_return) override;
  ::android::binder::Status getEDID(::std::vector<uint8_t>* edid, bool* _aidl_return) override;
  ::android::binder::Status getDefaultEDID(::com::rdk::hal::hdmiinput::HDMIVersion version, ::std::vector<uint8_t>* edid, bool* _aidl_return) override;
  ::android::binder::Status getHDCPCurrentVersion(::com::rdk::hal::hdmiinput::HDCPProtocolVersion* _aidl_return) override;
  ::android::binder::Status getHDCPStatus(::com::rdk::hal::hdmiinput::HDCPStatus* _aidl_return) override;
  ::android::binder::Status getSPDInfoFrame(::std::vector<uint8_t>* _aidl_return) override;
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputControllerListener>& hdmiInputControllerListener, ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>* _aidl_return) override;
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputController>& hdmiInputController, bool* _aidl_return) override;
  ::android::binder::Status registerEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) override;
  ::android::binder::Status unregisterEventListener(const ::android::sp<::com::rdk::hal::hdmiinput::IHDMIInputEventListener>& hdmiInputEventListener, bool* _aidl_return) override;
  int32_t getInterfaceVersion() override;
  std::string getInterfaceHash() override;
private:
  int32_t cached_version_ = -1;
  std::string cached_hash_ = "-1";
  std::mutex cached_hash_mutex_;
};  // class BpHDMIInput
}  // namespace hdmiinput
}  // namespace hal
}  // namespace rdk
}  // namespace com
