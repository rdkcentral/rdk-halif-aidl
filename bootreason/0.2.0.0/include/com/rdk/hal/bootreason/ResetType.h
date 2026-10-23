#pragma once

#include <array>
#include <binder/Enums.h>
#include <cstdint>
#include <string>

namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
// @aidl-doc
/**
 *  @brief     Reset types.
 *  @author    Luc Kennedy-Lamb
 *  @author    Peter Stieglitz
 *  @author    Douglas Adler
 */
enum class ResetType : int32_t {
  // @aidl-doc
  /**
   * Upon restart, the system shall come up and delete all persistent data partitions and recreate them.
   * BootCause will be reported as WARM_RESET
   */
  FULL_SYSTEM_RESET = 0,
  // @aidl-doc
  /**
   * Upon restart, the current application image is invalidated and shall NOT be selected for loading
   * on the next boot. If the platform supports multiple application image banks then the alternate
   * bank should be selected; otherwise the Disaster Recovery Image (DRI) will be loaded.
   * BootCause will be reported as WARM_RESET
   * @note After the next boot, the running image cannot determine from BootCause alone that this
   *       reset type caused the transition. The exact boot-selection behaviour is platform-dependent.
   * @note The precise semantics and sequencing of this reset type are under review. A sequence
   *       diagram documenting entry, exit and observable state should be provided.
   */
  INVALIDATE_CURRENT_APPLICATION_IMAGE = 1,
  // @aidl-doc
  /**
   * Upon restart, the system shall enter disaster recovery mode by loading the
   * Disaster Recovery Image (DRI).
   * BootCause will be reported as WARM_RESET
   * @note From a Primary/Current Image (PCI) perspective there is no visibility that the system
   *       entered disaster recovery mode. Only the DRI itself knows it was force-loaded. After the
   *       DRI completes recovery and the system returns to normal operation, the BootCause will not
   *       reflect that a forced disaster recovery occurred.
   * @note This reset type may not be supported on all platforms (e.g. platforms without a dedicated
   *       disaster recovery image). Clients **MUST** verify platform support by checking
   *       Capabilities.supportedResetTypes before requesting this reset type.
   * @note The precise semantics, sequencing and terminology for this reset type are under review.
   *       A sequence diagram documenting how the system enters, executes and exits disaster recovery
   *       mode should be provided.
   */
  FORCE_DISASTER_RECOVERY = 2,
  // @aidl-doc
  /**
   * Performing Reboot for a Maintenance reason. The caller **MUST** set the reasonString
   * BootCause will be reported as MAINTENANCE_REBOOT
   */
  MAINTENANCE_REBOOT = 3,
  // @aidl-doc
  /**
   * Performing Reboot for a Software reason (which is specifically not a Maintenance Reboot). The caller **MUST** set
   * the reasonString BootCause will be reported as WARM_RESET, unless overridden by setBootCause prior to reboot.
   */
  SOFTWARE_REBOOT = 4,
};
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace bootreason {
[[nodiscard]] static inline std::string toString(ResetType val) {
  switch(val) {
  case ResetType::FULL_SYSTEM_RESET:
    return "FULL_SYSTEM_RESET";
  case ResetType::INVALIDATE_CURRENT_APPLICATION_IMAGE:
    return "INVALIDATE_CURRENT_APPLICATION_IMAGE";
  case ResetType::FORCE_DISASTER_RECOVERY:
    return "FORCE_DISASTER_RECOVERY";
  case ResetType::MAINTENANCE_REBOOT:
    return "MAINTENANCE_REBOOT";
  case ResetType::SOFTWARE_REBOOT:
    return "SOFTWARE_REBOOT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace bootreason
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::bootreason::ResetType, 5> enum_values<::com::rdk::hal::bootreason::ResetType> = {
  ::com::rdk::hal::bootreason::ResetType::FULL_SYSTEM_RESET,
  ::com::rdk::hal::bootreason::ResetType::INVALIDATE_CURRENT_APPLICATION_IMAGE,
  ::com::rdk::hal::bootreason::ResetType::FORCE_DISASTER_RECOVERY,
  ::com::rdk::hal::bootreason::ResetType::MAINTENANCE_REBOOT,
  ::com::rdk::hal::bootreason::ResetType::SOFTWARE_REBOOT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
