#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <com/rdk/hal/planecontrol/GraphicsFbCapabilities.h>
#include <com/rdk/hal/planecontrol/GraphicsFbInfo.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class IGraphicsFbProvider : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsFbProvider)
  static const int32_t VERSION = 2000;
  const std::string HASH = "1aa55452f48fe34e5b7e10c7dddc2ea772f337a2";
  static constexpr char* HASHVALUE = "1aa55452f48fe34e5b7e10c7dddc2ea772f337a2";
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status commitGraphicsFb(int32_t graphicsFbId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status createGraphicsFb(int32_t width, int32_t height, ::com::rdk::hal::planecontrol::GraphicsFbInfo* outInfo, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status destroyGraphicsFb(int32_t graphicsFbId) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IGraphicsFbProvider

class IGraphicsFbProviderDefault : public IGraphicsFbProvider {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status commitGraphicsFb(int32_t /*graphicsFbId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createGraphicsFb(int32_t /*width*/, int32_t /*height*/, ::com::rdk::hal::planecontrol::GraphicsFbInfo* /*outInfo*/, ::android::os::ParcelFileDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status destroyGraphicsFb(int32_t /*graphicsFbId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IGraphicsFbProviderDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
