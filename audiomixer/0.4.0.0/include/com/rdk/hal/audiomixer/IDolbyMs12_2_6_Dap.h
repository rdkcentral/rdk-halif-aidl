#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DapCapabilities.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DownmixMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_DrcMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_GeqMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_IeqMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_LevellerMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_LevellerSettings.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_VirtualizerMode.h>
#include <com/rdk/hal/audiomixer/DolbyMs12_2_6_VirtualizerSettings.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace audiomixer {
// @aidl-doc
/**
 * @brief Dolby MS12 2.6 DAP runtime command control interface.
 * Provides one API method for each supported MS12 function.
 */
class IDolbyMs12_2_6_Dap : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DolbyMs12_2_6_Dap)
  static const int32_t VERSION = 4000;
  const std::string HASH = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  static constexpr char* HASHVALUE = "b1bb2fc05d2734036b32a73700b4ecb3f1ef2e64";
  // @aidl-doc
  /**
   * @brief Gets the MS12 2.6 DAP capabilities supported.
   *
   * The Dolby Audio Processing can be different for each output port.
   * The support for each DAP set function in this interface for the output port is
   * indicated by the capabilities.
   *
   * @param[out] _aidl_return DolbyMs12_2_6_DapCapabilities description for the output port.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enables or disables DAP surround decoder processing.
   * @param[in] enabled True to enable, false to disable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setSurroundDecoderEnabled(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP surround decoder processing state.
   *
   * @param[out] _aidl_return Current surround decoder enabled state.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getSurroundDecoderEnabled(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP bass enhancer boost value.
   * @param[in] boost Bass enhancer boost in range 0 to 100.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument is out of range.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setBassEnhancer(int32_t boost) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP bass enhancer boost value.
   * @param[out] _aidl_return Bass enhancer boost in range 0 to 100.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getBassEnhancer(int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP volume leveller mode and level.
   * @param[in] mode Volume leveller mode.
   * @param[in] level Volume leveller level in range 0 to 10.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument is out of range.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode mode, int32_t level) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP volume leveller mode and level.
   * @param[out] _aidl_return DolbyMs12_2_6_LevellerSettings containing the current mode and
   *                          level (level in range 0 to 10).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP surround virtualizer mode and boost.
   * @param[in] mode Surround virtualizer mode.
   * @param[in] boost Surround virtualizer boost in range 0 to 96.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument is out of range.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode mode, int32_t boost) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP surround virtualizer mode and boost.
   * @param[out] _aidl_return DolbyMs12_2_6_VirtualizerSettings containing the current mode
   *                          and boost (boost in range 0 to 96).
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enables or disables media intelligent steering.
   * @param[in] enabled True to enable, false to disable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setMediaIntelligentSteering(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets media intelligent steering state.
   * @param[out] _aidl_return True if media intelligent steering is enabled; false otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getMediaIntelligentSteering(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP post gain.
   * @param[in] gain Post gain in range -2080 to 480.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument is out of range.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setPostGain(float gain) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP post gain.
   * @param[out] _aidl_return Post gain in range -2080 to 480.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getPostGain(float* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP dialogue enhancer level.
   * @param[in] level Dialogue enhancer level in range 0 to 12.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument is out of range.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setDialogueEnhancer(int32_t level) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP dialogue enhancer level.
   * @param[out] _aidl_return Dialogue enhancer level in range 0 to 12.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getDialogueEnhancer(int32_t* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP intelligent equalizer mode.
   * @param[in] mode Intelligent equalizer mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument does not comply with the constrained set.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode mode) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP intelligent equalizer mode.
   * @param[out] _aidl_return Intelligent equalizer mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP graphic equalizer mode.
   * @param[in] mode Graphic equalizer mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument does not comply with the constrained set.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode mode) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP graphic equalizer mode.
   * @param[out] _aidl_return Graphic equalizer mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets DAP dynamic range control mode.
   * @param[in] mode Dynamic range control mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument does not comply with the constrained set.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode mode) = 0;
  // @aidl-doc
  /**
   * @brief Gets DAP dynamic range control mode.
   * @param[out] _aidl_return Dynamic range control mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets Dolby Atmos lock mode.
   * This is the only Atmos lock control in the HAL. It applies to this
   * output port and persists across playback sessions.
   * @param[in] enabled True to lock Atmos output, false to unlock.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setAtmosLock(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets Dolby Atmos lock mode.
   * @param[out] _aidl_return True if Atmos output lock is enabled; false otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getAtmosLock(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Sets downmix mode.
   * @param[in] mode Downmix mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_ILLEGAL_ARGUMENT if argument does not comply with the constrained set.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode mode) = 0;
  // @aidl-doc
  /**
   * @brief Gets downmix mode.
   * @param[out] _aidl_return Downmix mode.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enables or disables volume modeler.
   * @param[in] enabled True to enable, false to disable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setVolumeModelerEnabled(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets volume modeler state.
   * @param[out] _aidl_return True if volume modeler is enabled; false otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getVolumeModelerEnabled(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enables or disables centre spreading.
   * @param[in] enabled True to enable, false to disable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setCenterSpreadingEnabled(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets centre spreading state.
   * @param[out] _aidl_return True if centre spreading is enabled; false otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getCenterSpreadingEnabled(bool* _aidl_return) = 0;
  // @aidl-doc
  /**
   * @brief Enables or disables active downmix.
   * @param[in] enabled True to enable, false to disable.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status setActiveDownmixEnabled(bool enabled) = 0;
  // @aidl-doc
  /**
   * @brief Gets active downmix state.
   * @param[out] _aidl_return True if active downmix is enabled; false otherwise.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success, or one of the values below.
   * @retval ::android::binder::Status::EX_UNSUPPORTED_OPERATION if this MS12 2.6 feature is not supported.
   */
  virtual ::android::binder::Status getActiveDownmixEnabled(bool* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDolbyMs12_2_6_Dap

class IDolbyMs12_2_6_DapDefault : public IDolbyMs12_2_6_Dap {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DapCapabilities* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSurroundDecoderEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSurroundDecoderEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setBassEnhancer(int32_t /*boost*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getBassEnhancer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerMode /*mode*/, int32_t /*level*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVolumeLeveller(::com::rdk::hal::audiomixer::DolbyMs12_2_6_LevellerSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerMode /*mode*/, int32_t /*boost*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getSurroundVirtualizer(::com::rdk::hal::audiomixer::DolbyMs12_2_6_VirtualizerSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setMediaIntelligentSteering(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getMediaIntelligentSteering(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setPostGain(float /*gain*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getPostGain(float* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDialogueEnhancer(int32_t /*level*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDialogueEnhancer(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getIntelligentEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_IeqMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getGraphicEqualizerMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_GeqMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDynamicRangeControlMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DrcMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setAtmosLock(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getAtmosLock(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode /*mode*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getDownmixMode(::com::rdk::hal::audiomixer::DolbyMs12_2_6_DownmixMode* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setVolumeModelerEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getVolumeModelerEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setCenterSpreadingEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCenterSpreadingEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setActiveDownmixEnabled(bool /*enabled*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getActiveDownmixEnabled(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDolbyMs12_2_6_DapDefault
}  // namespace audiomixer
}  // namespace hal
}  // namespace rdk
}  // namespace com
