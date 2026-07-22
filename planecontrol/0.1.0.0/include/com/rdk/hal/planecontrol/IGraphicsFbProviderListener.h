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
  static const int32_t VERSION = 1000;
  const std::string HASH = "11e8e5b5f7dc1340849d654caa7a1444056272b6";
  static constexpr char* HASHVALUE = "11e8e5b5f7dc1340849d654caa7a1444056272b6";
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
