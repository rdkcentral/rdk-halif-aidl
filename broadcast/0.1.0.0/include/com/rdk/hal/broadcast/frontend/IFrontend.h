#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/IBroadcastClientToken.h>
#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/frontend/FrontendCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/FrontendType.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>
#include <com/rdk/hal/broadcast/frontend/IFrontendController.h>
#include <com/rdk/hal/broadcast/frontend/ILnbController.h>
#include <cstdint>
#include <optional>
#include <tuple>
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
 * @brief Front end HAL interface.
 *
 * Non-exclusive access to the front end. Multiple clients can work on the same frontend at the same time and access
 * information about it through this interface. When a client wants to tune the frontend, it has to acquire exclusive
 * access through the IFrontendController interface obtained from open().
 *
 * Exclusive claims are released when the owning client drops its Binder reference, including on abnormal termination,
 * so a crashed client cannot hold the frontend indefinitely. See the design document for the mechanism.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IFrontend : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Frontend)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /** Frontend resource ID type. */
  class Id : public ::android::Parcelable {
  public:
    // @aidl-doc
    /** The actual resource ID. */
    int32_t value = -1;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    // @aidl-doc
    /** The undefined ID value. */
    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.IFrontend.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  // @aidl-doc
  /**
   * @brief Get the ID of this frontend.
   *
   * @param[out] _aidl_return The resource ID of this frontend.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Check whether the frontend is already opened.
   *
   * Be aware of possible TOCTOU issues when using this method, especially in connection with open().
   *
   * @param[out] _aidl_return Open state of the frontend.
   *   - true: The frontend is opened by a client.
   *   - false: The frontend is not opened.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status isOpen(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Gets the supported frontend types.
   *
   * @param[out] _aidl_return Array of frontend types supported by this frontend.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the supported capabilities for the given frontend type.
   *
   * The active member of FrontendCapabilities.specifics always matches the requested frontendType: ATSC selects
   * atsc, DVB_C selects dvbC, DVB_S selects dvbS and DVB_T selects dvbT. The client does not need to inspect the
   * union tag to know which member to read.
   *
   * @param[in] frontendType A type obtained from getFrontendTypes().
   *
   * @param[out] _aidl_return The capabilities of this frontend for the given frontend type.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The frontendType is not supported by this frontend.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType frontendType, ::com::rdk::hal::broadcast::frontend::FrontendCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Exclusively open the frontend for tuning.
   *
   * The returned IFrontendController interface is used by the client to facilitate all tune related operations.
   *
   * @param[in] token The caller's client token. The claim is released if the owning client terminates.
   *
   * @param[out] _aidl_return An IFrontendController, or null if the frontend is already opened by another client.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
   */
  virtual ::android::binder::Status open(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Close the frontend and invalidate the FrontendController.
   *
   * Cleanup all attached (hardware) resources and brings the frontend back into a state where it can be opened again.
   * Stops the current tuning and all output on TSOUT.
   *
   * @param controller Non-null controller obtained from open() on the same frontend.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The frontend is not opened.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The controller was not obtained from open() on this
   *                                                        frontend.
   */
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& controller) = 0;
  // @aidl-doc
  /**
   * @brief Acquire a DemuxDataProvider that must be passed to a Demux.
   *
   * @param[in] token The caller's client token. The claim is released if the owning client terminates.
   *
   * @param[out] _aidl_return A DemuxDataProvider that can be used to connect a Demux to this frontend, or null if one has already
   *                          been acquired.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
   */
  virtual ::android::binder::Status acquireDataProvider(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Releases the DemuxDataProvider previously acquired.
   *
   * @param[in] provider The provider obtained from acquireDataProvider() on this frontend.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The frontend has no DemuxDataProvider acquired.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The provider was not obtained from
   *                                                        acquireDataProvider() on the same frontend.
   */
  virtual ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) = 0;
  // @aidl-doc
  /**
   * @brief Opens the LNB controller for exclusive access.
   *
   * The returned ILnbController interface is used for controlling satellite equipment.
   *
   * @param[in] token The caller's client token. The claim is released if the owning client terminates.
   *
   * @param[out] _aidl_return An ILnbController, or null if the LNB controller is already opened by another client.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION The frontend does not support LNB control.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
   */
  virtual ::android::binder::Status openLnb(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Closes the LNB controller and invalidates the LnbController.
   *
   * Cleanup all attached (hardware) resources and brings the LNB controller back into a state where it can be opened
   * again.
   *
   * @param[in] controller Non-null controller obtained from openLnb() on the same FrontEnd
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The LNB controller is not opened.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The controller was not obtained from openLnb() on this
   *                                                        frontend.
   */
  virtual ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& controller) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFrontend

class IFrontendDefault : public IFrontend {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isOpen(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType /*frontendType*/, ::com::rdk::hal::broadcast::frontend::FrontendCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& /*controller*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquireDataProvider(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& /*provider*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openLnb(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& /*controller*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFrontendDefault
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
