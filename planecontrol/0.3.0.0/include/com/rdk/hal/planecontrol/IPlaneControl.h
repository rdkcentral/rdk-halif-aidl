#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProvider.h>
#include <com/rdk/hal/planecontrol/IGraphicsFbProviderListener.h>
#include <com/rdk/hal/planecontrol/IPlaneControlListener.h>
#include <com/rdk/hal/planecontrol/PlaneCapabilities.h>
#include <com/rdk/hal/planecontrol/Property.h>
#include <com/rdk/hal/planecontrol/PropertyKVPair.h>
#include <com/rdk/hal/planecontrol/SourcePlaneMapping.h>
#include <cstdint>
#include <optional>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace planecontrol {
// @aidl-doc
/**
 *  @brief     Plane Control HAL interface.
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
class IPlaneControl : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PlaneControl)
  static const int32_t VERSION = 3000;
  const std::string HASH = "c63ddb239dd34186f904592456a46c65039f7bd3";
  static constexpr char* HASHVALUE = "c63ddb239dd34186f904592456a46c65039f7bd3";
  // @aidl-doc
  /** The service name to publish. To be returned by getServiceName() in the derived class. */
  static const ::std::string& serviceName();
  // @aidl-doc
  /**
   * Gets the platform plane resources and their capabilities.
   *
   * This function can be called at any time and is not dependent on any Plane Control state.
   * The returned value is not allowed to change between calls.
   *
   * @param[out] _aidl_return PlaneCapabilities[] array of plane resource instance capabilities.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::PlaneCapabilities>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets the destination plane for one or more video sources.
   *
   * This function allows multiple video [source -> plane] mappings to be changed together.
   * Operations such as main and PIP video swaps can be performed using this call.
   *
   * To unmap a source from its plane, map it to a `destinationPlaneIndex` of -1.
   *
   * If a source type and source index appear multiple times in the mapping list then the call fails.
   * If a plane index appears multiple times in the mapping list then the call fails.
   * If a plane index is already mapped to a source, then the exception status ``binder::Status EX_ILLEGAL_STATE`` is
   * returned.
   *
   * @param[in] listSourcePlaneMapping    An array of video source to video plane mappings.
   *
   * @param[out] _aidl_return boolean
   *   - true: The mapping was updated.
   *   - false: One or more mappings were invalid.
   * @see getVideoSourceDestinationPlaneMapping()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid value.
   */
  virtual ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& listSourcePlaneMapping, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets the video source to plane mapping for all video planes.
   *
   * This function always returns an array with one element for each video plane.
   * If a video plane has no source mapped, then `SourceType.NONE` is mapped to it.
   *
   * @param[out] _aidl_return SourcePlaneMapping[]    An array of video source to video plane mappings.
   *
   * @see setVideoSourceDestinationPlaneMapping()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   */
  virtual ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a property of a plane.
   *
   * @param[in] planeResourceIndex    The plane resource index.
   * @param[in] property              Property enum.
   *
   * @param[out] _aidl_return PropertyValue or null on invalid parameter.
   *
   * @see setProperty(), getPropertyMulti()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameter value.
   */
  virtual ::android::binder::Status getProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, ::std::optional<::com::rdk::hal::PropertyValue>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets a property of a plane.
   *
   * @param[in] planeResourceIndex    The plane resource index.
   * @param[in] property              Property enum.
   * @param[in] propertyValue         Property value.
   *
   * @param[out] _aidl_return boolean
   *   - true: Property was set successfully.
   *   - false: Invalid plane index, property or property value parameter.
   * @see getProperty(), setPropertyMultiAtomic()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid value.
   */
  virtual ::android::binder::Status setProperty(int32_t planeResourceIndex, ::com::rdk::hal::planecontrol::Property property, const ::com::rdk::hal::PropertyValue& propertyValue, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets multiple properties for a plane.
   *
   * Retrieves values for a list of property keys on the specified plane.
   *
   * Input `properties` is a non-null array of `Property` keys. Each key must be a
   * valid enum value; unknown or out-of-range values are treated as invalid.
   *
   * Output `propertyKVList` returns one `PropertyKVPair` per requested key, with
   * the same ordering as `properties`. For each pair, the `property` field echoes
   * the requested key and `propertyValue` is populated on success.
   *
   * Error handling and return semantics:
   * - Passing an empty `properties` array fails with `EX_ILLEGAL_ARGUMENT`.
   * - If any key in `properties` is invalid, no values are populated and the
   *   call fails with `EX_ILLEGAL_ARGUMENT`.
   * - If a required out-parameter is null (e.g. `propertyKVList`), the call fails
   *   with `EX_NULL_POINTER`.
   * - When an exception is raised, no return value is transmitted.
   *
   * @param[in] planeResourceIndex    The plane resource index.
   * @param[in] properties            Non-empty list of property keys to query.
   * @param[out] propertyKVList       Returned key/value pairs corresponding to `properties`.
   *
   * @param[out] _aidl_return boolean
   *   - true: All property values were returned successfully.
   *   - false: The property values could not be retrieved.
   * @see getProperty(), setPropertyMultiAtomic()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE Success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT Invalid plane index, property key(s) or empty input
   * list.
   * @retval ::android::binder::Status::EX_NULL_POINTER Null out-parameter.
   */
  virtual ::android::binder::Status getPropertyMulti(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::Property>& properties, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* propertyKVList, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Sets multiple properties atomically for a plane.
   *
   * For example, the `X`, `Y`, `WIDTH` and `HEIGHT` properties can be set in a single call.
   * Properties must only appear once in the list.
   *
   * @param[in] planeResourceIndex    The plane resource index.
   * @param[in] propertyKVList        Array of property key-value pairs.
   *
   * @param[out] _aidl_return boolean
   *   - true: Properties were set successfully.
   *   - false: Invalid plane index, property or property value parameter.
   * @see setProperty(), getPropertyMulti()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT for invalid parameters.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status setPropertyMultiAtomic(int32_t planeResourceIndex, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& propertyKVList, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Registers a callback listener for events generated by the Plane Control.
   *
   * An `IPlaneControlListener` can only be registered once and will fail on subsequent
   * registration attempts.
   *
   * @param[in] listener              IPlaneControlListener interface.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was registered.
   *   - false: The event listener is already registered.
   * @see unregisterListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Unregisters a callback listener for events generated by the Plane Control.
   *
   * @param[in] listener              Reference to IPlaneControlListener interface.
   *
   * @param[out] _aidl_return boolean
   *   - true: The event listener was unregistered.
   *   - false: The event listener was not found registered.
   * @see registerListener()
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& listener, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * Gets a Graphics Frame Buffer Provider for a Graphics plane resource.
   *
   * A provider is only available for plane resources of type GRAPHICS. The
   * method returns `null` rather than throwing an exception.
   * All graphics planes must support a Graphics Frame Buffer Provider.
   *
   * @param[in] planeResourceIndex               The ID of the plane resource.
   * @param[in] graphicsFbProviderListener       Listener for provider callbacks.
   *
   * @param[out] _aidl_return A valid graphics frame buffer provider instance when the plane resource index refers
   *                          to a graphics plane, or `null` if the plane resource index is invalid or the indexed
   *                          plane is not a graphics plane.
   *
   * @returns ::android::binder::Status - one of the values below.
   * @retval ::android::binder::Status::EX_NONE for success.
   * @retval ::android::binder::Status::EX_NULL_POINTER for Null object.
   */
  virtual ::android::binder::Status getGraphicsFbProvider(int32_t planeResourceIndex, const ::android::sp<::com::rdk::hal::planecontrol::IGraphicsFbProviderListener>& graphicsFbProviderListener, ::android::sp<::com::rdk::hal::planecontrol::IGraphicsFbProvider>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPlaneControl

class IPlaneControlDefault : public IPlaneControl {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::std::vector<::com::rdk::hal::planecontrol::PlaneCapabilities>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVideoSourceDestinationPlaneMapping(const ::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>& /*listSourcePlaneMapping*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVideoSourceDestinationPlaneMapping(::std::vector<::com::rdk::hal::planecontrol::SourcePlaneMapping>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getProperty(int32_t /*planeResourceIndex*/, ::com::rdk::hal::planecontrol::Property /*property*/, ::std::optional<::com::rdk::hal::PropertyValue>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setProperty(int32_t /*planeResourceIndex*/, ::com::rdk::hal::planecontrol::Property /*property*/, const ::com::rdk::hal::PropertyValue& /*propertyValue*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPropertyMulti(int32_t /*planeResourceIndex*/, const ::std::vector<::com::rdk::hal::planecontrol::Property>& /*properties*/, ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>* /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPropertyMultiAtomic(int32_t /*planeResourceIndex*/, const ::std::vector<::com::rdk::hal::planecontrol::PropertyKVPair>& /*propertyKVList*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status registerListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status unregisterListener(const ::android::sp<::com::rdk::hal::planecontrol::IPlaneControlListener>& /*listener*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getGraphicsFbProvider(int32_t /*planeResourceIndex*/, const ::android::sp<::com::rdk::hal::planecontrol::IGraphicsFbProviderListener>& /*graphicsFbProviderListener*/, ::android::sp<::com::rdk::hal::planecontrol::IGraphicsFbProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPlaneControlDefault
}  // namespace planecontrol
}  // namespace hal
}  // namespace rdk
}  // namespace com
