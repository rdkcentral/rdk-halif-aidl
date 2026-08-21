#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/demux/Mpeg2TsDataFilterParameters.h>
#include <com/rdk/hal/broadcast/demux/Mpeg2TsTunnelFilterParameters.h>
#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>
#include <utils/String16.h>
#include <variant>

#ifndef __BIONIC__
#define __assert2(a,b,c,d) ((void)0)
#endif

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class FilterParameters : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    mpeg2TsData = 0,
    mpeg2TsClock = 1,
    mpeg2TsVideo = 2,
    mpeg2TsAudio = 3,
    mpeg2TsSupplementaryAudio = 4,
  };
  // Expose tag symbols for legacy code
  static const inline Tag mpeg2TsData = Tag::mpeg2TsData;
  static const inline Tag mpeg2TsClock = Tag::mpeg2TsClock;
  static const inline Tag mpeg2TsVideo = Tag::mpeg2TsVideo;
  static const inline Tag mpeg2TsAudio = Tag::mpeg2TsAudio;
  static const inline Tag mpeg2TsSupplementaryAudio = Tag::mpeg2TsSupplementaryAudio;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, FilterParameters>;

  FilterParameters() : _value(std::in_place_index<static_cast<size_t>(mpeg2TsData)>, ::com::rdk::hal::broadcast::demux::Mpeg2TsDataFilterParameters()) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr FilterParameters(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit FilterParameters(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static FilterParameters make(_Tp&&... _args) {
    return FilterParameters(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static FilterParameters make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return FilterParameters(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const FilterParameters& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const FilterParameters& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const FilterParameters& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const FilterParameters& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const FilterParameters& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const FilterParameters& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.FilterParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "FilterParameters{";
    switch (getTag()) {
    case mpeg2TsData: os << "mpeg2TsData: " << ::android::internal::ToString(get<mpeg2TsData>()); break;
    case mpeg2TsClock: os << "mpeg2TsClock: " << ::android::internal::ToString(get<mpeg2TsClock>()); break;
    case mpeg2TsVideo: os << "mpeg2TsVideo: " << ::android::internal::ToString(get<mpeg2TsVideo>()); break;
    case mpeg2TsAudio: os << "mpeg2TsAudio: " << ::android::internal::ToString(get<mpeg2TsAudio>()); break;
    case mpeg2TsSupplementaryAudio: os << "mpeg2TsSupplementaryAudio: " << ::android::internal::ToString(get<mpeg2TsSupplementaryAudio>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<::com::rdk::hal::broadcast::demux::Mpeg2TsDataFilterParameters, ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters, ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters, ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters, ::com::rdk::hal::broadcast::demux::Mpeg2TsTunnelFilterParameters> _value;
};  // class FilterParameters
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
[[nodiscard]] static inline std::string toString(FilterParameters::Tag val) {
  switch(val) {
  case FilterParameters::Tag::mpeg2TsData:
    return "mpeg2TsData";
  case FilterParameters::Tag::mpeg2TsClock:
    return "mpeg2TsClock";
  case FilterParameters::Tag::mpeg2TsVideo:
    return "mpeg2TsVideo";
  case FilterParameters::Tag::mpeg2TsAudio:
    return "mpeg2TsAudio";
  case FilterParameters::Tag::mpeg2TsSupplementaryAudio:
    return "mpeg2TsSupplementaryAudio";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::broadcast::demux::FilterParameters::Tag, 5> enum_values<::com::rdk::hal::broadcast::demux::FilterParameters::Tag> = {
  ::com::rdk::hal::broadcast::demux::FilterParameters::Tag::mpeg2TsData,
  ::com::rdk::hal::broadcast::demux::FilterParameters::Tag::mpeg2TsClock,
  ::com::rdk::hal::broadcast::demux::FilterParameters::Tag::mpeg2TsVideo,
  ::com::rdk::hal::broadcast::demux::FilterParameters::Tag::mpeg2TsAudio,
  ::com::rdk::hal::broadcast::demux::FilterParameters::Tag::mpeg2TsSupplementaryAudio,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
