#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PQParameterValue.h>
#include <com/rdk/hal/panel/PanelSource.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class IPanelOutputControllerListener : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(PanelOutputControllerListener)
  static const int32_t VERSION = 2000;
  const std::string HASH = "ad01bbf3a2f440a172cbb53d051a83f99e4b4ef3";
  static constexpr char* HASHVALUE = "ad01bbf3a2f440a172cbb53d051a83f99e4b4ef3";
  // @aidl-doc
  /**
   * Callback when the picture mode changes.
   *
   * This can occur on an AVSource or DynamicRange change in the video
   * or occurs after a call to setPictureModes().
   *
   * @param[in] pictureMode   The new picture mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onPictureModeChanged(const ::android::String16& pictureMode) = 0;
  // @aidl-doc
  /**
   * Callback when a PQ picture property value changes.
   *
   * @param[in] pictureMode             The picture mode for which the change applies.
   * @param[in] avSource                The AV source for which the change applies.
   * @param[in] dynamicRange            The dynamic range for which the change applies.
   * @param[in] pictureProperty         The PQ picture property that changed.
   * @param[in] picturePropertyValue    The changed value variant.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status onPQParameterChanged(const ::android::String16& pictureMode, const ::com::rdk::hal::panel::PanelSource& avSource, ::com::rdk::hal::videodecoder::DynamicRange dynamicRange, ::com::rdk::hal::panel::PQParameter pictureProperty, const ::com::rdk::hal::panel::PQParameterValue& picturePropertyValue) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IPanelOutputControllerListener

class IPanelOutputControllerListenerDefault : public IPanelOutputControllerListener {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status onPictureModeChanged(const ::android::String16& /*pictureMode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status onPQParameterChanged(const ::android::String16& /*pictureMode*/, const ::com::rdk::hal::panel::PanelSource& /*avSource*/, ::com::rdk::hal::videodecoder::DynamicRange /*dynamicRange*/, ::com::rdk::hal::panel::PQParameter /*pictureProperty*/, const ::com::rdk::hal::panel::PQParameterValue& /*picturePropertyValue*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IPanelOutputControllerListenerDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
