#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/demux/IDemuxSoftwareInput.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>
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
 * @brief Interface for a demux software input that can be used to feed data into a demux.
 *
 * Possible use-cases are  playing a recording from a file or for feeding data from a network source.
 *
 * The write claim and any acquired data provider are released when the owning client drops its Binder reference,
 * including on abnormal termination. See the design document for the mechanism.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IDemuxSoftwareInput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DemuxSoftwareInput)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /** Demux software input resource ID type. */
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.IDemuxSoftwareInput.Id");
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
   * @brief Get the ID of this software input.
   *
   * @param[out] _aidl_return The resource ID of this software input.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Open for writing.
   *
   * This is used for writing data to the demux, e.g. for playing a recording from a file or for feeding data from a
   * network source. It will work independently of the filters, i.e. it should be possible to write data to the demux
   * while filters are active and also if they are not. The data written to the demux will be processed by the filters
   * and made available to the clients as if it was coming from the tuner.
   *
   * The returned ring buffer is non-overflowing. When it is full, acquire() returns null rather than overwriting
   * data the demux has not yet consumed, and the client resumes writing once
   * IRingBufferSinkListener::onSpaceAvailable reports space. A software input carries a stream the client already
   * holds in full, such as a recording or a network feed, so the correct response to a slow demux is to make the
   * client wait rather than to discard transport packets: a dropped packet would corrupt the stream the client is
   * replaying, and the client cannot detect or repair that from this interface.
   *
   * @param[in] listener Listener notified when the ring buffer is ready to accept more data.
   *
   * @param[out] _aidl_return An IRingBufferSink interface used to write data into the demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The software input is already opened for writing.
   */
  virtual ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Close for writing.
   *
   * The IRingBufferSink obtained from openForWriting() will be invalidated.
   *
   * @param[in] bufferSink The sink obtained from openForWriting() on this software input.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The software input is not opened for writing.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The bufferSink was not obtained from openForWriting()
   *                                                        on the same software input.
   */
  virtual ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& bufferSink) = 0;
  // @aidl-doc
  /**
   * @brief Acquire a DemuxDataProvider that must be passed to a Demux.
   *
   * @param[out] _aidl_return A DemuxDataProvider that can be used to connect to a Demux, or null if one has already been acquired.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Releases the DemuxDataProvider previously acquired.
   *
   * @param[in] provider The provider obtained from acquireDataProvider() on this software input.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The software input is not connected to a Demux.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The provider was not obtained from
   *                                                        acquireDataProvider() on the same software input.
   */
  virtual ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemuxSoftwareInput

class IDemuxSoftwareInputDefault : public IDemuxSoftwareInput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& /*bufferSink*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& /*provider*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDemuxSoftwareInputDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
