#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/IBroadcastClientToken.h>
#include <com/rdk/hal/broadcast/demux/DemuxCapabilities.h>
#include <com/rdk/hal/broadcast/demux/IDemux.h>
#include <com/rdk/hal/broadcast/demux/IDemuxController.h>
#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/demux/IDemuxSoftwareInput.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief Interface for a demux.
 *
 * Provides non-exclusive access to the demux instance, allowing multiple clients to connect to the same demux and
 * gather information about its capabilities. By connecting a data provider to the demux, clients can acquire exclusive
 * access to the demux through the controller interface, enabling them to set up filters and manage data flow.
 *
 * Exclusive claims are released when the owning client drops its Binder reference, including on abnormal termination,
 * so a crashed client cannot hold the demux indefinitely. See the design document for the mechanism.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IDemux : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Demux)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /** Demux resource ID type. */
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.IDemux.Id");
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
   * @brief Get the ID of this demux.
   *
   * @param[out] _aidl_return The resource ID of this demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemux::Id* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Check whether this demux is already connected.
   *
   * Be aware of possible TOCTOU issues when using this method, especially in connection with connect().
   *
   * @param[out] _aidl_return Connection state of the demux.
   *   - true: The demux is connected to a DemuxDataProvider.
   *   - false: The demux is not connected.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status isConnected(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Get the supported capabilities.
   *
   * @param[out] _aidl_return The capabilities of this demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::demux::DemuxCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Connect this Demux to a DemuxDataProvider.
   *
   * Each demux might only be connected to one DemuxDataProvider. The connected demux represented by the
   * DemuxController can be used to set up multiple filters, depending on the Capabilities.
   *
   * @param[in] token The caller's client token. The claim is released if the owning client terminates.
   * @param[in] provider The DemuxDataProvider to connect the Demux to.
   *
   * @param[out] _aidl_return An IDemuxController, or null if this Demux is already connected (isConnected() is true).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The DemuxDataProvider is already connected to another
   *                                                        Demux, or the token is null or is not hosted by the
   *                                                        caller.
   */
  virtual ::android::binder::Status connect(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Disconnect this Demux from a DemuxDataProvider.
   *
   * The DemuxController object will be invalidated.
   *
   * @param[in] controller Non-null DemuxController obtained from connect() on the same Demux.
   *
   * @param[out] _aidl_return IDemuxDataProvider the provider instance passed to connect().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The DemuxController is not originating from this Demux.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE isConnected() is false.
   */
  virtual ::android::binder::Status disconnect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>& controller, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Create a software source for this demux.
   *
   * The created DemuxSoftwareInput can be used to write data to the demux, and only to *this* demux instance.
   *
   * Creation and acquisition are separate claims and may be made by different clients in different processes: the
   * token passed here identifies the creating client, while acquireSoftwareInput() records the acquiring one. An
   * implementation must track the two independently rather than assuming a single owner.
   *
   * @param[in] token The caller's client token, identifying the creating client.
   *
   * @param[out] _aidl_return An IDemuxSoftwareInput.Id, or null if the maximum number of DemuxSoftwareInput instances has already
   *                          been created.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION The demux does not support software sources.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The token is null or is not hosted by the caller.
   */
  virtual ::android::binder::Status createSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, ::std::optional<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Destroy the given software source.
   *
   * The ID is invalidated and must not be passed to acquireSoftwareInput() again.
   *
   * @param[in] id Non-null ID for the software source obtained from createSoftwareInput() on the same Demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is still acquired by a client.
   */
  virtual ::android::binder::Status destroySoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id) = 0;
  // @aidl-doc
  /**
   * @brief Acquire the given software source.
   *
   * @param[in] token The caller's client token. The claim is released if the owning client terminates.
   * @param[in] id Non-null software source ID obtained from createSoftwareInput() on the same Demux.
   *
   * @param[out] _aidl_return The software input instance for the given ID or null if already acquired.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source ID is not valid for this demux,
   *                                                        or the token is null or is not hosted by the caller.
   */
  virtual ::android::binder::Status acquireSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& token, const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& id, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Release the given software source.
   *
   * The software source remains created and can be acquired again; use destroySoftwareInput() to remove it.
   *
   * @param[in] input The instance of the software input obtained from acquireSoftwareInput() on the same Demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The software source is not valid for this demux.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The DemuxSoftwareInput is not acquired by any client.
   */
  virtual ::android::binder::Status releaseSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>& input) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemux

class IDemuxDefault : public IDemux {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemux::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isConnected(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::demux::DemuxCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status connect(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& /*provider*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status disconnect(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxController>& /*controller*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, ::std::optional<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status destroySoftwareInput(const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& /*id*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquireSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::IBroadcastClientToken>& /*token*/, const ::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id& /*id*/, ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseSoftwareInput(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput>& /*input*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDemuxDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
