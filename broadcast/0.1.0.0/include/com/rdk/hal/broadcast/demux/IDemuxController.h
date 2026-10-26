#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/Filter.h>
#include <com/rdk/hal/broadcast/demux/FilterParameters.h>
#include <cstdint>
#include <optional>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief Interface for an opened demux.
 *
 * Grants exclusive access to the demux and allows opening and closing of filters. See IFrontendController for the
 * details on what this means in terms of synchronization requirements.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IDemuxController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DemuxController)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /**
   * @brief Open a filter for the given filter type.
   *
   * The returned union contains exactly one active member, representing the concrete type-specific filter interface.
   *
   * @param[in] parameters The parameters of the filter to create. The actual filter type to be returned is determined
   *                       by the type of the filter parameters.
   *
   * @param[out] _aidl_return A Filter holding the concrete filter interface, or null if the demux cannot provide any more filters of
   *                          the given filter type.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION The demux does not support the given filter type.
   */
  virtual ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& parameters, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Closes the given filter.
   *
   * The filter object will be invalidated. The call to closeFilter() will stop the filter.
   *
   * @param[in] filter A filter obtained from openFilter() on this demux.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT The filter was not opened on this demux.
   */
  virtual ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& filter) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemuxController

class IDemuxControllerDefault : public IDemuxController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status openFilter(const ::com::rdk::hal::broadcast::demux::FilterParameters& /*parameters*/, ::std::optional<::com::rdk::hal::broadcast::demux::Filter>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeFilter(const ::com::rdk::hal::broadcast::demux::Filter& /*filter*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDemuxControllerDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
