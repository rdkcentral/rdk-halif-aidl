#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
// @aidl-doc
/**
 *  @brief     Callbacks listener interface from graphics frame buffer provider.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
class IGraphicsFbProviderListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsFbProviderListener)
  static const int32_t VERSION = 3000;
  const std::string HASH = "c63ddb239dd34186f904592456a46c65039f7bd3";
  static constexpr char* HASHVALUE = "c63ddb239dd34186f904592456a46c65039f7bd3";
  // @aidl-doc
  /**
   * @brief     Called after a call to commitGraphicsFb() when the Graphics Frame Buffer has become current.
   * @param[in] oldGraphicsFbId  The Frame Id of the old frame replaced by the newly committed frame.
   * @param[in] timestampNs      The CLOCK_MONOTONIC time, in nanoseconds, at which the old frame was
   *                             replaced by the new one. The client compares this against the
   *                             CLOCK_MONOTONIC time of its commitGraphicsFb() call to measure
   *                             commit-to-present latency; CLOCK_MONOTONIC is system-wide, so the two
   *                             readings are directly comparable across processes.
   *
   * If no old frame exists (e.g. on the first invocation), this callback is invoked with oldGraphicsFbId set to -1.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onGraphicsFbReleased(int32_t oldGraphicsFbId, int64_t timestampNs) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IGraphicsFbProviderListener

class IGraphicsFbProviderListenerDefault : public IGraphicsFbProviderListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onGraphicsFbReleased(int32_t /*oldGraphicsFbId*/, int64_t /*timestampNs*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IGraphicsFbProviderListenerDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
