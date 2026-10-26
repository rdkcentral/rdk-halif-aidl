#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/hdmicec/SendMessageStatus.h>
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
 *  @brief     HDMI CEC Controller HAL interface.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 *
 *  <h3>Exception Handling</h3>
 *  Unless otherwise specified, this interface follows standard Android Binder semantics:
 *  - <b>Success</b>: The method returns `binder::Status::Exception::EX_NONE` and all output parameters/return values
 * are valid.
 *  - <b>Failure (Exception)</b>: The method returns a service-specific exception (e.g., `EX_SERVICE_SPECIFIC`,
 * `EX_ILLEGAL_ARGUMENT`). In this case, output parameters and return values contain undefined (garbage) memory and must
 * not be used. The caller must ignore any output variables.
 */
class IHdmiCecController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(HdmiCecController)
  static const int32_t VERSION = 2000;
  const std::string HASH = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  static constexpr char* HASHVALUE = "e6856e41e56df2162e16424bd2e6cd2c38d8697a";
  // @aidl-doc
  /**
   * @brief Adds one or more Logical Addresses to be message filtered by the host device.
   *
   * This function adds the specified Logical Addresses such that directly addressed CEC messages with a matching
   * destination address will be received by this device.
   * The HAL will immediately ACK and produce callbacks for all received messages.
   *
   * The Client must first acquire a logical address using the CEC Logical Address Allocation method
   * (ref <HDMI Specification 2-0> Section <CEC 11.3.3>) before adding the logical address.
   * A physical device may add at most two logical addresses. Multiple logical addresses
   * are permitted only for the device-type combinations explicitly defined in HDMI
   * Specification 2-0, Section 11.3.2, Table 11-8. The client can add permitted
   * logical addresses in one call or add them one by one.
   *
   * All addresses must be in the directly addressable range of 0 to 14 (0x0 ~ 0xE) or the function will return false.
   * If any addresses passed in are already added then the function will return false.
   *
   * @param[in] logicalAddresses   An array of logical address to be added.
   *
   * @param[out] _aidl_return
   *                     true  - if successfully added
   *                     false - if the logical addresses cannot be added, including when:
   *                              - more than two logical addresses are supplied;
   *                              - any address is outside the directly addressable range of 0 to 14 (0x0 ~ 0xE);
   *                              - any address has already been added; or
   *                              - the logical address combination is not permitted by HDMI Specification 2-0,
   *                                Section 11.3.2, Table 11-8.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @see IHdmiCec.getLogicalAddresses(), removeLogicalAddresses(), IHdmiCecEventListener.onMessageReceived()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Removes Logical Addresses that have been previously added.
   *
   * The HAL will not produce callbacks for received messages where the destination logical address is removed.
   * The HAL will not ACK messages where the logical address is removed.
   * All addresses must be in the directly addressable range of 0 to 14 (0x0 ~ 0xE) or the function will return false.
   * If any addresses passed in are not added then the function will return false.
   *
   * @param[in] logicalAddresses   An array of logical addresses to be removed.
   *
   * @pre The resource must be in State::STARTED.
   *
   * @param[out] _aidl_return true on successfully removing and false if one or more logical addresses have not been previously added.
   *
   *
   * @see IHdmiCec.getLogicalAddresses(), addLogicalAddresses()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& logicalAddresses, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Synchronously send a CEC message.
   *
   * This function writes a complete CEC frame onto the bus and waits for an ACK.
   *
   * The packet contained in the message buffer will follow this format
   *     (ref <HDMI Specification 2-0> Section <CEC 11.1>) :
   *
   * complete frame  = header block + data block@n
   * header block    = destination logical address (4-bit) + source address (4-bit)@n
   * data block      = opcode block (8-bit) + operand block (N-bytes)
   *
   * The maximum message size (Header Block plus opcode block plus operand blocks) is 16 * 8 bits (16bytes).
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
   * The HAL implementation MUST add the EOM and ACK bits in the message in compliance with <HDMI Specification 2-0>
   * Section <CEC 11>. The HAL implementation MUST comply with all Signalling and Bit Timings described in <HDMI
   * Specification 2-0> Section <CEC 11.9.2>. The HAL implementation MUST comply with <HDMI Specification 2-0> Section
   * <CEC 11.9.3> on Frame Re-transmissions.
   *
   * For a source HDMI device, while HPD is not asserted all sent messages will timeout.
   * It is not considered an error for a message to be sent while HPD is not asserted.
   *
   * @param[in] message The message to be sent.
   *
   * @pre The HDMI CEC interface is in State::STARTED
   *
   * @param[out] _aidl_return SendMessageStatus
   *
   *
   * @see IHdmiCec.open()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE
   */
  virtual ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& message, ::com::rdk::hal::hdmicec::SendMessageStatus* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IHdmiCecController

class IHdmiCecControllerDefault : public IHdmiCecController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status addLogicalAddresses(const ::std::vector<int32_t>& /*logicalAddresses*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status removeLogicalAddresses(const ::std::vector<int32_t>& /*logicalAddresses*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sendMessage(const ::std::vector<uint8_t>& /*message*/, ::com::rdk::hal::hdmicec::SendMessageStatus* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IHdmiCecControllerDefault
}  // namespace hdmicec
}  // namespace hal
}  // namespace rdk
}  // namespace com
