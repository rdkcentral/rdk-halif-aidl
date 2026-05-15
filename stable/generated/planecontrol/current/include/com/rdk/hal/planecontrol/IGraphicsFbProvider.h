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
  static const int32_t VERSION = 1;
  const std::string HASH = "78a76d308d6d3f298f0283e8962a4a88719c93f0";
  static constexpr char* HASHVALUE = "78a76d308d6d3f298f0283e8962a4a88719c93f0";
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* _aidl_return) = 0;
  virtual ::android::binder::Status commitGraphicsFb(int32_t graphicsFbId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status createGraphicsFb(int32_t width, int32_t height, ::com::rdk::hal::planecontrol::GraphicsFbInfo* outInfo, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  virtual ::android::binder::Status destroyGraphicsFb(int32_t graphicsFbId) = 0;
  virtual ::android::binder::Status getNativeDisplayHandle(int64_t* _aidl_return) = 0;
  virtual ::android::binder::Status getEGLPlatformType(int32_t* _aidl_return) = 0;
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
  ::android::binder::Status getNativeDisplayHandle(int64_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getEGLPlatformType(int32_t* /*_aidl_return*/) override {
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
