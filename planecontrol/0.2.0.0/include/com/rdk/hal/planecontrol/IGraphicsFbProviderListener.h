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
  static const int32_t VERSION = 2000;
  const std::string HASH = "1aa55452f48fe34e5b7e10c7dddc2ea772f337a2";
  static constexpr char* HASHVALUE = "1aa55452f48fe34e5b7e10c7dddc2ea772f337a2";
  virtual ::android::binder::Status onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t timestampNs) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IGraphicsFbProviderListener

class IGraphicsFbProviderListenerDefault : public IGraphicsFbProviderListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onGraphicsFbReleased(int32_t /*oldGraphicsFbId*/, int64_t /*timestampNs*/) override {
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
