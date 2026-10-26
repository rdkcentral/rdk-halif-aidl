#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmicec/SendMessageStatus.h>
#include <com/rdk/hal/hdmicec/State.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace hdmicec {
// @aidl-doc
/**
 *  @brief     HDMI CEC Event Listener HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IHdmiCecEventListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiCecEventListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  static constexpr char* HASHVALUE = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  // @aidl-doc
  /**
   * Callback to be invoked for each frame arrival.
   *
   * The frame contained in the buffer will follow this format
   *     (ref <HDMI Specification 1-4> Section <CEC 6.1>) :
   *
   * complete frame  = header block + data block@n
   * header block    = destination logical address (4-bit) + source address (4-bit)@n
   * data block      = opcode block (8-bit) + operand block (N-bytes)
   *
   * @code
   * |------------------------------------------------
   * | header block  |          data blocks          |
   * |------------------------------------------------
   * |3|2|1|0|3|2|1|0|7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|
   * |------------------------------------------------
   * | Dest  |  src  |  opcode block | operand block |
   * |------------------------------------------------
   * @endcode
   *
   * The HAL implementation must remove the EOM and ACK bits in the returned buffer.
   *
   * @param[in] message	A variable length message conforming to format described above.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& message) = 0;
  // @aidl-doc
  /**
   * Callback when the CEC interface has transitioned to a new state.
   *
   * @param[in] oldState	            The state transitioned from.
   * @param[in] newState              The new state transitioned to.
   *
   * @see IHdmiCec.getState()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State oldState, ::com::rdk::hal::hdmicec::State newState) = 0;
  // @aidl-doc
  /**
   * Callback to be invoked for each frame sent by the Controller through IHdmiCecController.sendMessage().
   *
   * When registered the HAL invokes this callback after sending, or attempting to send a message.
   * The message's send status allows the listener to know the result of the message transmission.
   *
   * The intention of this listener is to allow diagnostic tools to monitor CEC traffic between the CEC Controller
   * Client and the HAL.
   *
   * The frame contained in the buffer will follow this format
   *     (ref <HDMI Specification 1-4> Section <CEC 6.1>) :
   *
   * complete frame  = header block + data block@n
   * header block    = destination logical address (4-bit) + source address (4-bit)@n
   * data block      = opcode block (8-bit) + operand block (N-bytes)
   *
   * @code
   * |------------------------------------------------
   * | header block  |          data blocks          |
   * |------------------------------------------------
   * |3|2|1|0|3|2|1|0|7|6|5|4|3|2|1|0|7|6|5|4|3|2|1|0|
   * |------------------------------------------------
   * | Dest  |  src  |  opcode block | operand block |
   * |------------------------------------------------
   * @endcode
   *
   * The message buffer should be identical to the IHdmiCecController.sendMessage() call.
   *
   * @param[in] message	A variable length message conforming to format described above.
   * @param[in] status    The status of the sent message
   *
   * @see IHdmiCecController.sendMessage()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus status) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHdmiCecEventListener

class IHdmiCecEventListenerDefault : public IHdmiCecEventListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onMessageReceived(const ::std::vector<uint8_t>& /*message*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onStateChanged(::com::rdk::hal::hdmicec::State /*oldState*/, ::com::rdk::hal::hdmicec::State /*newState*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onMessageSent(const ::std::vector<uint8_t>& /*message*/, ::com::rdk::hal::hdmicec::SendMessageStatus /*status*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHdmiCecEventListenerDefault
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
