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
class IPlaneControlListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PlaneControlListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "bed7512d891c70602f0bd173dd855823d7382423";
  static constexpr char* HASHVALUE = "bed7512d891c70602f0bd173dd855823d7382423";
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPlaneControlListener

class IPlaneControlListenerDefault : public IPlaneControlListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPlaneControlListenerDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
