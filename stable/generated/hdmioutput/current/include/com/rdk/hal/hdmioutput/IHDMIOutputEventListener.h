#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmioutput/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace hdmioutput {
class IHDMIOutputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputEventListener)
  static const int32_t VERSION = 1;
  const std::string HASH = "1e04b7a2abd81e9534138733782be7e186590068";
  static constexpr char* HASHVALUE = "1e04b7a2abd81e9534138733782be7e186590068";
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::hdmioutput::State oldState, ::com::rdk::hal::hdmioutput::State newState) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHDMIOutputEventListener

class IHDMIOutputEventListenerDefault : public IHDMIOutputEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmioutput::State /*oldState*/, ::com::rdk::hal::hdmioutput::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHDMIOutputEventListenerDefault
}  // namespace hdmioutput
}  // namespace hal
}  // namespace rdk
}  // namespace com
