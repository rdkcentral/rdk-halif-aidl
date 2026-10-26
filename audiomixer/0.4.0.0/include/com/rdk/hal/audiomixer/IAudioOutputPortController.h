#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/PropertyValue.h>
#include <com/rdk/hal/audiomixer/IAudioCapture.h>
#include <com/rdk/hal/audiomixer/IAudioCaptureListener.h>
#include <com/rdk/hal/audiomixer/IDolbyMs12_2_6_Dap.h>
#include <com/rdk/hal/audiomixer/OutputPortProperty.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief    Audio Output Port Controller HAL interface.
 *
 *           Exclusive write controller returned by IAudioOutputPort.open().
 *           Hosts mutating operations on the output port (property writes for
 *           volume, mute, output format, transcode format, AQ processor, etc.)
 *           and factory methods for write-capable sub-interfaces — the
 *           Dolby MS12 v2.6 DAP runtime command surface and the audio
 *           capture interface.
 *
 *           Only one client may hold the controller at a time. If the holding
 *           client crashes, the HAL detects the binder death and releases
 *           the port internally — equivalent to calling
 *           IAudioOutputPort.close(controller) on the orphaned controller —
 *           so a subsequent open() from another client succeeds.
 *
 *           Read access (getProperty, getCapabilities) remains on
 *           IAudioOutputPort and does not require ownership.
 *
 * @author   Gerald Weatherup
 */
class IAudioOutputPortController : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioOutputPortController)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief    Sets a property value for the controlled output port.
   *
   *           The property must be writable in the current port state. Property
   *           writability is documented per-key in OutputPortProperty.aidl.
   *           Output port properties are written in READY, the only state in
   *           which this controller exists (e.g., VOLUME, OUTPUT_FORMAT).
   *
   * @param[in] property  Property key (from OutputPortProperty enum).
   * @param[in] value     Property value; union field must match the property type.
   *
   * @param[out] _aidl_return true on successful write, false if the property is not supported
   *                          by this port or the value is rejected.
   *
   * @see IAudioOutputPort.getProperty()
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if property is unknown or
   *                     value type does not match.
   * @retval ::android::binder::Status::EX_ILLEGAL_STATE if the port is not in a state
   *                     that permits writing this property.
   */
  virtual ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty property, const ::com::rdk::hal::PropertyValue& value, bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Returns the Dolby MS12 v2.6 DAP runtime command interface
   *           for this port.
   *
   *           Acquiring the DAP interface requires holding this
   *           IAudioOutputPortController. Because the interface itself
   *           is acquired here, the port controller's ownership boundary
   *           gates all DAP access — reads as well as writes — for the
   *           lifetime of the controller. No separate DAP-level
   *           open()/close() is needed.
   *
   *           Supported when OutputPortCapabilities.supportedAQProcessors
   *           for this port contains AQProcessor.DOLBY_MS12_2_6.
   *
   * @param[out] _aidl_return IDolbyMs12_2_6_Dap runtime command interface.
   *
   * @see IAudioOutputPort.open()
   * @see OutputPortCapabilities.supportedAQProcessors
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if Dolby MS12 v2.6
   *                     DAP is not supported on this port.
   */
  virtual ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief    Creates an audio capture interface for the controlled port.
   *
   *           Acquiring the audio capture interface requires holding this
   *           IAudioOutputPortController. Capture acquisition is gated
   *           by holding the port controller — the read-side
   *           IAudioOutputPort handle does not expose getAudioCapture(),
   *           so only the controller owner can capture from this port.
   *
   *           Supported when OutputPortCapabilities.supportsAudioCapture
   *           is true for this port (note: that field's own docblock
   *           also references this controller-acquired path).
   *
   * @param[in] audioCaptureListener  Listener for capture callbacks.
   *
   * @param[out] _aidl_return IAudioCapture interface for the controlled port.
   *
   * @see IAudioOutputPort.open()
   * @see com.rdk.hal.audiomixer.OutputPortCapabilities.supportsAudioCapture
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if audio capture
   *                     from this port is not supported.
   * @retval ::android::binder::Status::EX_NULL_POINTER if @c audioCaptureListener
   *                     is null.
   */
  virtual ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& audioCaptureListener, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioOutputPortController

class IAudioOutputPortControllerDefault : public IAudioOutputPortController {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setProperty(::com::rdk::hal::audiomixer::OutputPortProperty /*property*/, const ::com::rdk::hal::PropertyValue& /*value*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDolbyMs12_2_6_Dap(::android::sp<::com::rdk::hal::audiomixer::IDolbyMs12_2_6_Dap>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAudioCapture(const ::android::sp<::com::rdk::hal::audiomixer::IAudioCaptureListener>& /*audioCaptureListener*/, ::android::sp<::com::rdk::hal::audiomixer::IAudioCapture>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioOutputPortControllerDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
