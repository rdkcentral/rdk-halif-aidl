#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/AVSource.h>
#include <com/rdk/hal/panel/PQParameter.h>
#include <com/rdk/hal/panel/PQParameterCapabilities.h>
#include <com/rdk/hal/videodecoder/DynamicRange.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace panel {
class PQParameterCapabilities : public ::android::Parcelable {
public:
  class PQParamPictureModeCapabilities : public ::android::Parcelable {
  public:
    class PQParamVideoFormatCapabilities : public ::android::Parcelable {
    public:
      ::com::rdk::hal::videodecoder::DynamicRange drFormat = ::com::rdk::hal::videodecoder::DynamicRange(0);
      ::std::vector<::com::rdk::hal::AVSource> supportedAVSources;
      inline bool operator!=(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) != std::tie(rhs.drFormat, rhs.supportedAVSources);
      }
      inline bool operator<(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) < std::tie(rhs.drFormat, rhs.supportedAVSources);
      }
      inline bool operator<=(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) <= std::tie(rhs.drFormat, rhs.supportedAVSources);
      }
      inline bool operator==(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) == std::tie(rhs.drFormat, rhs.supportedAVSources);
      }
      inline bool operator>(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) > std::tie(rhs.drFormat, rhs.supportedAVSources);
      }
      inline bool operator>=(const PQParamVideoFormatCapabilities& rhs) const {
        return std::tie(drFormat, supportedAVSources) >= std::tie(rhs.drFormat, rhs.supportedAVSources);
      }

      ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
      ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
      ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
      static const ::android::String16& getParcelableDescriptor() {
        static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.PQParamPictureModeCapabilities.PQParamVideoFormatCapabilities");
        return DESCIPTOR;
      }
      inline std::string toString() const {
        std::ostringstream os;
        os << "PQParamVideoFormatCapabilities{";
        os << "drFormat: " << ::android::internal::ToString(drFormat);
        os << ", supportedAVSources: " << ::android::internal::ToString(supportedAVSources);
        os << "}";
        return os.str();
      }
    };  // class PQParamVideoFormatCapabilities
    ::android::String16 pictureMode;
    ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::PQParamPictureModeCapabilities::PQParamVideoFormatCapabilities> pqParamVideoFormatCapabilities;
    inline bool operator!=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) != std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }
    inline bool operator<(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) < std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }
    inline bool operator<=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) <= std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }
    inline bool operator==(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) == std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }
    inline bool operator>(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) > std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }
    inline bool operator>=(const PQParamPictureModeCapabilities& rhs) const {
      return std::tie(pictureMode, pqParamVideoFormatCapabilities) >= std::tie(rhs.pictureMode, rhs.pqParamVideoFormatCapabilities);
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities.PQParamPictureModeCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "PQParamPictureModeCapabilities{";
      os << "pictureMode: " << ::android::internal::ToString(pictureMode);
      os << ", pqParamVideoFormatCapabilities: " << ::android::internal::ToString(pqParamVideoFormatCapabilities);
      os << "}";
      return os.str();
    }
  };  // class PQParamPictureModeCapabilities
  ::com::rdk::hal::panel::PQParameter pqParameter = ::com::rdk::hal::panel::PQParameter(0);
  bool isSupported = false;
  bool isGlobal = false;
  int32_t minValue = 0;
  int32_t maxValue = 0;
  ::std::vector<int32_t> values;
  ::std::vector<::com::rdk::hal::panel::PQParameterCapabilities::PQParamPictureModeCapabilities> pqParamPictureModeCapabilities;
  inline bool operator!=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) != std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator<(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) < std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator<=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) <= std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator==(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) == std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator>(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) > std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }
  inline bool operator>=(const PQParameterCapabilities& rhs) const {
    return std::tie(pqParameter, isSupported, isGlobal, minValue, maxValue, values, pqParamPictureModeCapabilities) >= std::tie(rhs.pqParameter, rhs.isSupported, rhs.isGlobal, rhs.minValue, rhs.maxValue, rhs.values, rhs.pqParamPictureModeCapabilities);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.panel.PQParameterCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PQParameterCapabilities{";
    os << "pqParameter: " << ::android::internal::ToString(pqParameter);
    os << ", isSupported: " << ::android::internal::ToString(isSupported);
    os << ", isGlobal: " << ::android::internal::ToString(isGlobal);
    os << ", minValue: " << ::android::internal::ToString(minValue);
    os << ", maxValue: " << ::android::internal::ToString(maxValue);
    os << ", values: " << ::android::internal::ToString(values);
    os << ", pqParamPictureModeCapabilities: " << ::android::internal::ToString(pqParamPictureModeCapabilities);
    os << "}";
    return os.str();
  }
};  // class PQParameterCapabilities
}  // namespace panel
}  // namespace hal
}  // namespace rdk
}  // namespace com
