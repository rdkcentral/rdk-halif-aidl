#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/ImplementationVersion.h>
#include <com/rdk/hal/broadcast/ca/ICaSlot.h>
#include <com/rdk/hal/broadcast/demux/IDemux.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
// @aidl-doc
/**
 * @brief BroadcastManager HAL interface.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IBroadcastManager : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BroadcastManager)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /**
   * The service name to publish.
   *
   * To be returned by getServiceName() in the derived class.
   */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * @brief Gets the service implementation version.
   *
   * This is not the same as the interface version, which is defined for the AIDL interface itself. The same
   * implementation version may implement multiple versions of the interface, and multiple implementations versions
   * may implement the same interface version (for example following internal bug fixes).
   *
   * @param[out] _aidl_return The implementation name and semantic version of the service.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the platform list of frontend IDs.
   *
   * @param[out] _aidl_return Array of IFrontend.Id values for all frontends on this platform.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the frontend interface for the given ID.
   *
   * @param[in] frontendId An ID obtained from getFrontendIds().
   *
   * @param[out] _aidl_return The frontend interface for the given ID.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
   */
  virtual ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& frontendId, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the list of demux IDs available on this platform.
   *
   * @param[out] _aidl_return Array of IDemux.Id values for all demuxes on this platform.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the demux interface for the given ID.
   *
   * @param[in] demuxId An ID obtained from getDemuxIds().
   *
   * @param[out] _aidl_return The demux interface for the given ID.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
   */
  virtual ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& demuxId, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the list of CA slot IDs available on this platform.
   *
   * @param[out] _aidl_return Array of ICaSlot.Id values for all CA slots on this platform.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the CA slot interface for the given ID.
   *
   * @param[in] slotId An ID obtained from getCaSlotIds().
   *
   * @param[out] _aidl_return The CA slot interface for the given ID.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if the ID is invalid.
   */
  virtual ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& slotId, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBroadcastManager

class IBroadcastManagerDefault : public IBroadcastManager {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getImplementationVersion(::com::rdk::hal::broadcast::ImplementationVersion* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontendIds(::std::vector<::com::rdk::hal::broadcast::frontend::IFrontend::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontend(const ::com::rdk::hal::broadcast::frontend::IFrontend::Id& /*frontendId*/, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontend>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDemuxIds(::std::vector<::com::rdk::hal::broadcast::demux::IDemux::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDemux(const ::com::rdk::hal::broadcast::demux::IDemux::Id& /*demuxId*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemux>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCaSlotIds(::std::vector<::com::rdk::hal::broadcast::ca::ICaSlot::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCaSlot(const ::com::rdk::hal::broadcast::ca::ICaSlot::Id& /*slotId*/, ::android::sp<::com::rdk::hal::broadcast::ca::ICaSlot>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBroadcastManagerDefault
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
