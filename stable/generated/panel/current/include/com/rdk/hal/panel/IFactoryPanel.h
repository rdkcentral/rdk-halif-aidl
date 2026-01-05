#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/panel/IFactoryPanel.h>
#include <com/rdk/hal/panel/WhiteBalance2PointSettings.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class IFactoryPanel : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(FactoryPanel)
  static const int32_t VERSION = 1;
  const std::string HASH = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  static constexpr char* HASHVALUE = "cdc73f570c9b30e5c89acdbde61c0f2c8312ef91";
  enum class SaveTo : int8_t {
    DISPLAY = 1,
    FLASH = 2,
    DISPLAY_AND_FLASH = 3,
  };
  class LocalDimmingZone : public ::android::Parcelable {
  public:
    int32_t x = 0;
    int32_t y = 0;
    int32_t level = 0;
    inline bool operator!=(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) != std::tie(rhs.x, rhs.y, rhs.level);
    }
    inline bool operator<(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) < std::tie(rhs.x, rhs.y, rhs.level);
    }
    inline bool operator<=(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) <= std::tie(rhs.x, rhs.y, rhs.level);
    }
    inline bool operator==(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) == std::tie(rhs.x, rhs.y, rhs.level);
    }
    inline bool operator>(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) > std::tie(rhs.x, rhs.y, rhs.level);
    }
    inline bool operator>=(const LocalDimmingZone& rhs) const {
      return std::tie(x, y, level) >= std::tie(rhs.x, rhs.y, rhs.level);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.IFactoryPanel.LocalDimmingZone");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "LocalDimmingZone{";
      os << "x: " << ::android::internal::ToString(x);
      os << ", y: " << ::android::internal::ToString(y);
      os << ", level: " << ::android::internal::ToString(level);
      os << "}";
      return os.str();
    }
  };  // class LocalDimmingZone
  virtual ::android::binder::Status setFactoryPanelConfiguration(int32_t panelId, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryPanelConfiguration(int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setFactoryWhiteBalanceCalibration(int32_t colorTemperature, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& whiteBalance, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryWhiteBalanceCalibration(int32_t colorTemperature, ::com::rdk::hal::panel::WhiteBalance2PointSettings* _aidl_return) = 0;
  virtual ::android::binder::Status setFactoryGammaTable(int32_t colorTemperature, const ::std::vector<int32_t>& red, const ::std::vector<int32_t>& green, const ::std::vector<int32_t>& blue, ::com::rdk::hal::panel::IFactoryPanel::SaveTo saveTo, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryGammaTable(int32_t colorTemperature, ::std::vector<int32_t>* red, ::std::vector<int32_t>* green, ::std::vector<int32_t>* blue) = 0;
  virtual ::android::binder::Status setFactoryPeakBrightness(int32_t dimmingLevel, int32_t nits, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryPeakBrightness(int32_t dimmingLevel, int32_t* _aidl_return) = 0;
  virtual ::android::binder::Status setFactoryLocalDimming(const ::std::vector<::com::rdk::hal::panel::IFactoryPanel::LocalDimmingZone>& zones, int32_t durationMs, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setFactoryLocalDimmingTestMode(int32_t mode, int32_t durationMs, bool* _aidl_return) = 0;
  virtual ::android::binder::Status setFactoryLocalDimmingPixelCompensation(bool enabled, bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryLocalDimmingPixelCompensation(bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFactoryBacklightHealth(int32_t* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFactoryPanel

class IFactoryPanelDefault : public IFactoryPanel {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status setFactoryPanelConfiguration(int32_t /*panelId*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryPanelConfiguration(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryWhiteBalanceCalibration(int32_t /*colorTemperature*/, const ::com::rdk::hal::panel::WhiteBalance2PointSettings& /*whiteBalance*/, ::com::rdk::hal::panel::IFactoryPanel::SaveTo /*saveTo*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryWhiteBalanceCalibration(int32_t /*colorTemperature*/, ::com::rdk::hal::panel::WhiteBalance2PointSettings* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryGammaTable(int32_t /*colorTemperature*/, const ::std::vector<int32_t>& /*red*/, const ::std::vector<int32_t>& /*green*/, const ::std::vector<int32_t>& /*blue*/, ::com::rdk::hal::panel::IFactoryPanel::SaveTo /*saveTo*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryGammaTable(int32_t /*colorTemperature*/, ::std::vector<int32_t>* /*red*/, ::std::vector<int32_t>* /*green*/, ::std::vector<int32_t>* /*blue*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryPeakBrightness(int32_t /*dimmingLevel*/, int32_t /*nits*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryPeakBrightness(int32_t /*dimmingLevel*/, int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryLocalDimming(const ::std::vector<::com::rdk::hal::panel::IFactoryPanel::LocalDimmingZone>& /*zones*/, int32_t /*durationMs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryLocalDimmingTestMode(int32_t /*mode*/, int32_t /*durationMs*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status setFactoryLocalDimmingPixelCompensation(bool /*enabled*/, bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryLocalDimmingPixelCompensation(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFactoryBacklightHealth(int32_t* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFactoryPanelDefault
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace panel {
[[nodiscard]] static inline std::string toString(IFactoryPanel::SaveTo val) {
  switch(val) {
  case IFactoryPanel::SaveTo::DISPLAY:
    return "DISPLAY";
  case IFactoryPanel::SaveTo::FLASH:
    return "FLASH";
  case IFactoryPanel::SaveTo::DISPLAY_AND_FLASH:
    return "DISPLAY_AND_FLASH";
  default:
    return std::to_string(static_cast<int8_t>(val));
  }
}
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::panel::IFactoryPanel::SaveTo, 3> enum_values<::com::rdk::hal::panel::IFactoryPanel::SaveTo> = {
  ::com::rdk::hal::panel::IFactoryPanel::SaveTo::DISPLAY,
  ::com::rdk::hal::panel::IFactoryPanel::SaveTo::FLASH,
  ::com::rdk::hal::panel::IFactoryPanel::SaveTo::DISPLAY_AND_FLASH,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
