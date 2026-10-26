#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/Mpeg2TsPid.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSource.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSourceListener.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief Filter interface for opaque MPEG2-TS data.
 *
 * This is used for metadata, as well as in non-tunneled pipelines. In order to set the filter into an operational
 * state, setPids() or setAllPids() must be called.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IMpeg2TsDataFilter : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Mpeg2TsDataFilter)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /**
   * @brief Set the PIDs to filter for.
   *
   * Going from an empty list to a non-empty list will start the filter without flushing data. Going from a non-empty
   * list to an empty list will stop the filter without flushing data. Going from a non-empty list (or from
   * setAllPids()) to a different non-empty will update the filter, but old data may still be read from the filter
   * until the new data is available. Going from an empty list to another empty list does nothing.
   *
   * Providing a list of PIDs that exceeds getMaxPids() or contains a PID outside the range Mpeg2TsPid.MIN to
   * Mpeg2TsPid.MAX will throw an exception and not change the filter state.
   *
   * The implementation shall not provide any data before setPids() (with a non-empty list of PIDs) or setAllPids()
   * has been called for the first time. I.e. no data shall be available through the ring buffer that predates the
   * first call to one of these methods.
   *
   * @param[in] pids The PIDs to filter for, at most getMaxPids() of them. An empty list stops the filter.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The list of PIDs exceeds the maximum number of PIDs
   *                                                        that can be filtered for or contains a PID outside
   *                                                        the range Mpeg2TsPid.MIN to Mpeg2TsPid.MAX.
   */
  virtual ::android::binder::Status setPids(const ::std::vector<::com::rdk::hal::broadcast::demux::Mpeg2TsPid>& pids) = 0;
  // @aidl-doc
  /**
   * @brief Use this to enable the collection of the full transport stream via wildcard filtering.
   *
   * After calling this, data from all PIDs will be returned. Old, filtered data might still be available to read,
   * though, analogously to setPids(). One practical use-case for this is if the list of PIDs becomes larger than
   * getMaxPids().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status setAllPids() = 0;
  // @aidl-doc
  /**
   * @brief Get the maximum number of PIDs that can be filtered for.
   *
   * @param[out] _aidl_return The maximum number of PIDs accepted by setPids().
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getMaxPids(int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Register a consumer to read out data from the filter.
   *
   * @param[in] listener Listener notified when filtered data is available to read.
   *
   * @param[out] _aidl_return An IRingBufferSource interface used to read filtered data from the filter.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The filter already has a consumer registered.
   */
  virtual ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Unregister the consumer.
   *
   * @param[in] consumer The source obtained from registerConsumer() on this filter.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE The filter does not have a consumer registered.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The consumer was not registered with this filter.
   */
  virtual ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& consumer) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IMpeg2TsDataFilter

class IMpeg2TsDataFilterDefault : public IMpeg2TsDataFilter {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setPids(const ::std::vector<::com::rdk::hal::broadcast::demux::Mpeg2TsPid>& /*pids*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAllPids() override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMaxPids(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSourceListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterConsumer(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSource>& /*consumer*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IMpeg2TsDataFilterDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
