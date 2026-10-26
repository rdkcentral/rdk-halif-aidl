#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/ParcelFileDescriptor.h>
#include <binder/Status.h>
#include <com/rdk/hal/planecontrol/GraphicsFbCapabilities.h>
#include <com/rdk/hal/planecontrol/GraphicsFbInfo.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
// @aidl-doc
/**
 *  @brief     Graphics Frame Buffer (Fb) interface.
 *  @author    Gerald Weatherup
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
class IGraphicsFbProvider : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(GraphicsFbProvider)
  static const int32_t VERSION = 3000;
  const std::string HASH = "c63ddb239dd34186f904592456a46c65039f7bd3";
  static constexpr char* HASHVALUE = "c63ddb239dd34186f904592456a46c65039f7bd3";
  // @aidl-doc
  /**
   * Gets the graphics frame buffer capabilities.
   *
   * This function can be called at any time and is not dependent on any Plane Control state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return GraphicsFbCapabilities
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Commit the graphics frame buffer to be displayed on the graphics plane.
   *
   * This is a non-blocking function to commit this frame buffer to display at the earliest opportunity.
   * After the frame has been displayed an event is raised to indicate that the buffer, previously on display, is now
   * free to be re-used.
   *
   * @param[in] graphicsFbId                The Frame Id of the buffer to replace the currently displaying buffer
   *
   * @param[out] _aidl_return boolean
   *   - true: The frame was accepted for display.
   *   - false: The frame was not accepted because the graphics frame id is invalid or unknown to this provider.
   * @see createGraphicsFb()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid value.
   */
  virtual ::android::binder::Status commitGraphicsFb(int32_t graphicsFbId, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Creates a graphics frame buffer for this plane.
   *
   * This function can be called multiple times to create up to the maximum allowed graphics frames specified in the
   * plane resources capabilities. The returned file descriptor can be the same for all created graphics frame
   * buffers.
   *
   * @param[in] width                 The requested width of the graphics frame buffer.
   * @param[in] height                The requested height of the graphics frame buffer.
   * @param[out] outInfo              A parcelable describing the graphics frame buffer.
   *
   * @param[out] _aidl_return A Dma-Buf file descriptor and the associated graphics frame buffer info.
   *
   *                 width and height must not exceed the GraphicsFbCapabilities.
   *
   * @see destroyGraphicsFb()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid value.
   */
  virtual ::android::binder::Status createGraphicsFb(int32_t width, int32_t height, ::com::rdk::hal::planecontrol::GraphicsFbInfo* outInfo, ::android::os::ParcelFileDescriptor* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Frees a graphics frame buffer.
   *
   * @param[in] graphicsFbId    The graphics frame buffer identifier
   *
   * @see createGraphicsFb()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid value.
   */
  virtual ::android::binder::Status destroyGraphicsFb(int32_t graphicsFbId) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IGraphicsFbProvider

class IGraphicsFbProviderDefault : public IGraphicsFbProvider {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::planecontrol::GraphicsFbCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status commitGraphicsFb(int32_t /*graphicsFbId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status createGraphicsFb(int32_t /*width*/, int32_t /*height*/, ::com::rdk::hal::planecontrol::GraphicsFbInfo* /*outInfo*/, ::android::os::ParcelFileDescriptor* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status destroyGraphicsFb(int32_t /*graphicsFbId*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IGraphicsFbProviderDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
