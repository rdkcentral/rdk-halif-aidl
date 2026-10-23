#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/frontend/LnbTone.h>
#include <com/rdk/hal/broadcast/frontend/LnbVoltage.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief LNB controller interface.
 *
 * Handles control operations for a Low-Noise Block downconverter (LNB), including voltage control, tone control, and
 * DiSEqC signalling. Exclusively obtained through IFrontend.openLnb(), see IFrontendController for details.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 *
 * @see IFrontend.openLnb()
 */
class ILnbController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(LnbController)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /**
   * @brief Set the LNB voltage.
   *
   * Use LnbVoltage.NONE to turn off the LNB power.
   *
   * @param[in] voltage The LNB voltage to set.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage voltage) = 0;
  // @aidl-doc
  /**
   * @brief Set the LNB tone.
   *
   * @param[in] tone The LNB tone to set.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone tone) = 0;
  // @aidl-doc
  /**
   * @brief Get the overload state of the LNB controller.
   *
   * @param[out] _aidl_return Overload state of the LNB power line.
   *   - true: The LNB power line is overloaded (e.g. possible short circuit on the LNB voltage line).
   *   - false: The LNB power line is not overloaded.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status isOverloaded(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Send a DiSEqC (Digital Satellite Equipment Control) command.
   *
   * Sends a DiSEqC command to the connected LNB equipment as specified by the EUTELSAT Bus Functional Specification
   * Version 4.2. Blocks until the entire command has been transmitted.
   *
   * A DiSEqC message is at most 6 bytes (framing, address, command and up to three data bytes). An implementation
   * may reject anything longer with EX_ILLEGAL_ARGUMENT rather than forwarding it to the hardware.
   *
   * @param[in] command The DiSEqC command bytes to transmit.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the command is empty, malformed, or longer than
   *                                                        6 bytes.
   */
  virtual ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& command) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class ILnbController

class ILnbControllerDefault : public ILnbController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setVoltage(::com::rdk::hal::broadcast::frontend::LnbVoltage /*voltage*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setTone(::com::rdk::hal::broadcast::frontend::LnbTone /*tone*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isOverloaded(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status sendDiseqc(const ::std::vector<uint8_t>& /*command*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class ILnbControllerDefault
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
