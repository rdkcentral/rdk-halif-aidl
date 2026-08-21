#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/ParcelableHolder.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/frontend/AtscCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/DvbCCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/DvbSCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/FrontendCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/SignalInfoProperty.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <utils/String16.h>
#include <variant>
#include <vector>

#ifndef __BIONIC__
#define __assert2(a,b,c,d) ((void)0)
#endif

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class FrontendCapabilities : public ::android::Parcelable {
public:
  class SpecificCapabilities : public ::android::Parcelable {
  public:
    enum class Tag : int32_t {
      atsc = 0,
      dvbC = 1,
      dvbS = 2,
      dvbT = 3,
    };
    // Expose tag symbols for legacy code
    static const inline Tag atsc = Tag::atsc;
    static const inline Tag dvbC = Tag::dvbC;
    static const inline Tag dvbS = Tag::dvbS;
    static const inline Tag dvbT = Tag::dvbT;

    template<typename _Tp>
    static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, SpecificCapabilities>;

    SpecificCapabilities() : _value(std::in_place_index<static_cast<size_t>(atsc)>, ::com::rdk::hal::broadcast::frontend::AtscCapabilities()) { }

    template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr SpecificCapabilities(_Tp&& _arg)
        : _value(std::forward<_Tp>(_arg)) {}

    template <size_t _Np, typename... _Tp>
    constexpr explicit SpecificCapabilities(std::in_place_index_t<_Np>, _Tp&&... _args)
        : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

    template <Tag _tag, typename... _Tp>
    static SpecificCapabilities make(_Tp&&... _args) {
      return SpecificCapabilities(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
    }

    template <Tag _tag, typename _Tp, typename... _Up>
    static SpecificCapabilities make(std::initializer_list<_Tp> _il, _Up&&... _args) {
      return SpecificCapabilities(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
    }

    Tag getTag() const {
      return static_cast<Tag>(_value.index());
    }

    template <Tag _tag>
    const auto& get() const {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag>
    auto& get() {
      if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
      return std::get<static_cast<size_t>(_tag)>(_value);
    }

    template <Tag _tag, typename... _Tp>
    void set(_Tp&&... _args) {
      _value.emplace<static_cast<size_t>(_tag)>(std::forward<_Tp>(_args)...);
    }

    inline bool operator!=(const SpecificCapabilities& rhs) const {
      return _value != rhs._value;
    }
    inline bool operator<(const SpecificCapabilities& rhs) const {
      return _value < rhs._value;
    }
    inline bool operator<=(const SpecificCapabilities& rhs) const {
      return _value <= rhs._value;
    }
    inline bool operator==(const SpecificCapabilities& rhs) const {
      return _value == rhs._value;
    }
    inline bool operator>(const SpecificCapabilities& rhs) const {
      return _value > rhs._value;
    }
    inline bool operator>=(const SpecificCapabilities& rhs) const {
      return _value >= rhs._value;
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.FrontendCapabilities.SpecificCapabilities");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "SpecificCapabilities{";
      switch (getTag()) {
      case atsc: os << "atsc: " << ::android::internal::ToString(get<atsc>()); break;
      case dvbC: os << "dvbC: " << ::android::internal::ToString(get<dvbC>()); break;
      case dvbS: os << "dvbS: " << ::android::internal::ToString(get<dvbS>()); break;
      case dvbT: os << "dvbT: " << ::android::internal::ToString(get<dvbT>()); break;
      }
      os << "}";
      return os.str();
    }
  private:
    std::variant<::com::rdk::hal::broadcast::frontend::AtscCapabilities, ::com::rdk::hal::broadcast::frontend::DvbCCapabilities, ::com::rdk::hal::broadcast::frontend::DvbSCapabilities, ::com::rdk::hal::broadcast::frontend::DvbTCapabilities> _value;
  };  // class SpecificCapabilities
  ::std::vector<::com::rdk::hal::broadcast::frontend::SignalInfoProperty> signalInfoProperties;
  int64_t minFrequency = 0L;
  int64_t maxFrequency = 0L;
  int64_t acquireFrequencyRange = 0L;
  int32_t minSymbolRate = 0;
  int32_t maxSymbolRate = 0;
  bool hasAutoSymbolRate = false;
  ::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities specifics;
  ::android::os::ParcelableHolder extension { ::android::Parcelable::Stability::STABILITY_VINTF };
  inline bool operator!=(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) != std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }
  inline bool operator<(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) < std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }
  inline bool operator<=(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) <= std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }
  inline bool operator==(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) == std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }
  inline bool operator>(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) > std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }
  inline bool operator>=(const FrontendCapabilities& rhs) const {
    return std::tie(signalInfoProperties, minFrequency, maxFrequency, acquireFrequencyRange, minSymbolRate, maxSymbolRate, hasAutoSymbolRate, specifics, extension) >= std::tie(rhs.signalInfoProperties, rhs.minFrequency, rhs.maxFrequency, rhs.acquireFrequencyRange, rhs.minSymbolRate, rhs.maxSymbolRate, rhs.hasAutoSymbolRate, rhs.specifics, rhs.extension);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.FrontendCapabilities");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FrontendCapabilities{";
    os << "signalInfoProperties: " << ::android::internal::ToString(signalInfoProperties);
    os << ", minFrequency: " << ::android::internal::ToString(minFrequency);
    os << ", maxFrequency: " << ::android::internal::ToString(maxFrequency);
    os << ", acquireFrequencyRange: " << ::android::internal::ToString(acquireFrequencyRange);
    os << ", minSymbolRate: " << ::android::internal::ToString(minSymbolRate);
    os << ", maxSymbolRate: " << ::android::internal::ToString(maxSymbolRate);
    os << ", hasAutoSymbolRate: " << ::android::internal::ToString(hasAutoSymbolRate);
    os << ", specifics: " << ::android::internal::ToString(specifics);
    os << ", extension: " << ::android::internal::ToString(extension);
    os << "}";
    return os.str();
  }
};  // class FrontendCapabilities
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
[[nodiscard]] static inline std::string toString(FrontendCapabilities::SpecificCapabilities::Tag val) {
  switch(val) {
  case FrontendCapabilities::SpecificCapabilities::Tag::atsc:
    return "atsc";
  case FrontendCapabilities::SpecificCapabilities::Tag::dvbC:
    return "dvbC";
  case FrontendCapabilities::SpecificCapabilities::Tag::dvbS:
    return "dvbS";
  case FrontendCapabilities::SpecificCapabilities::Tag::dvbT:
    return "dvbT";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag, 4> enum_values<::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag> = {
  ::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag::atsc,
  ::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag::dvbC,
  ::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag::dvbS,
  ::com::rdk::hal::broadcast::frontend::FrontendCapabilities::SpecificCapabilities::Tag::dvbT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
