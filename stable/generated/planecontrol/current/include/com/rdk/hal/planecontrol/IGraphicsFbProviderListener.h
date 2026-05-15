#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
class IGraphicsFbProviderListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsFbProviderListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "78a76d308d6d3f298f0283e8962a4a88719c93f0";
  static constexpr char* HASHVALUE = "78a76d308d6d3f298f0283e8962a4a88719c93f0";
  virtual ::android::binder::Status onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t elapsedRealtimeNanos) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IGraphicsFbProviderListener

class IGraphicsFbProviderListenerDefault : public IGraphicsFbProviderListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onGraphicsFbReleased(int32_t /*oldGraphicsFbId*/, int64_t /*elapsedRealtimeNanos*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IGraphicsFbProviderListenerDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
