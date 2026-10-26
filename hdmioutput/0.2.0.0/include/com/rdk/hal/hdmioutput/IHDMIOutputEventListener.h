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
// @aidl-doc
/**
 *  @brief     Event callbacks listener interface from HDMI output.
 *
 *  This listener is notified of asynchronous lifecycle changes during the operation of
 *  the HDMI output port. It reflects changes to internal state caused by client operations
 *  such as `open()`, `start()`, `stop()`, and `close()`, or internal recovery actions.
 *
 *  Transitions always follow the legal state machine as defined in the HAL interface contract.
 *
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *  @author    Gerald Weatherup
 */
class IHDMIOutputEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HDMIOutputEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  static constexpr char* HASHVALUE = "da2bdb87e132357fe6f9e19ac44749eb9339f1b5";
  // @aidl-doc
  /**
   * Callback triggered when the HDMI output changes state.
   *
   * State transitions may be client-driven (e.g., via `open()`, `start()`, `close()`),
   * or HAL-driven (e.g., upon device loss or failure recovery).
   *
   * This callback is always invoked **after** the internal state transition is complete
   * and the resource is stable in its new state. Clients should interpret this as the
   * current, authoritative lifecycle state of the output port.
   *
   * It is valid for this callback to fire multiple times with the same `newState` in
   * the event of reentry or redundant transitions.
   *
   * @param[in] oldState  The state the HDMI output transitioned from.
   * @param[in] newState  The state the HDMI output transitioned to.
   *
   * @see State
   * @see IHDMIOutput.open(), IHDMIOutput.close()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
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
