#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/demux/IAudioFilter.h>
#include <com/rdk/hal/broadcast/demux/IClockFilter.h>
#include <com/rdk/hal/broadcast/demux/IMpeg2TsDataFilter.h>
#include <com/rdk/hal/broadcast/demux/ISupplementaryAudioFilter.h>
#include <com/rdk/hal/broadcast/demux/IVideoFilter.h>
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
class Filter : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    mpeg2TsData = 0,
    clock = 1,
    video = 2,
    audio = 3,
    supplementaryAudio = 4,
  };
  // Expose tag symbols for legacy code
  static const inline Tag mpeg2TsData = Tag::mpeg2TsData;
  static const inline Tag clock = Tag::clock;
  static const inline Tag video = Tag::video;
  static const inline Tag audio = Tag::audio;
  static const inline Tag supplementaryAudio = Tag::supplementaryAudio;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, Filter>;

  Filter() : _value(std::in_place_index<static_cast<size_t>(mpeg2TsData)>, ::android::sp<::com::rdk::hal::broadcast::demux::IMpeg2TsDataFilter>()) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr Filter(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit Filter(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static Filter make(_Tp&&... _args) {
    return Filter(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static Filter make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return Filter(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const Filter& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const Filter& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const Filter& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const Filter& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const Filter& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const Filter& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.Filter");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "Filter{";
    switch (getTag()) {
    case mpeg2TsData: os << "mpeg2TsData: " << ::android::internal::ToString(get<mpeg2TsData>()); break;
    case clock: os << "clock: " << ::android::internal::ToString(get<clock>()); break;
    case video: os << "video: " << ::android::internal::ToString(get<video>()); break;
    case audio: os << "audio: " << ::android::internal::ToString(get<audio>()); break;
    case supplementaryAudio: os << "supplementaryAudio: " << ::android::internal::ToString(get<supplementaryAudio>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<::android::sp<::com::rdk::hal::broadcast::demux::IMpeg2TsDataFilter>, ::android::sp<::com::rdk::hal::broadcast::demux::IClockFilter>, ::android::sp<::com::rdk::hal::broadcast::demux::IVideoFilter>, ::android::sp<::com::rdk::hal::broadcast::demux::IAudioFilter>, ::android::sp<::com::rdk::hal::broadcast::demux::ISupplementaryAudioFilter>> _value;
};  // class Filter
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
[[nodiscard]] static inline std::string toString(Filter::Tag val) {
  switch(val) {
  case Filter::Tag::mpeg2TsData:
    return "mpeg2TsData";
  case Filter::Tag::clock:
    return "clock";
  case Filter::Tag::video:
    return "video";
  case Filter::Tag::audio:
    return "audio";
  case Filter::Tag::supplementaryAudio:
    return "supplementaryAudio";
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
constexpr inline std::array<::com::rdk::hal::broadcast::demux::Filter::Tag, 5> enum_values<::com::rdk::hal::broadcast::demux::Filter::Tag> = {
  ::com::rdk::hal::broadcast::demux::Filter::Tag::mpeg2TsData,
  ::com::rdk::hal::broadcast::demux::Filter::Tag::clock,
  ::com::rdk::hal::broadcast::demux::Filter::Tag::video,
  ::com::rdk::hal::broadcast::demux::Filter::Tag::audio,
  ::com::rdk::hal::broadcast::demux::Filter::Tag::supplementaryAudio,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
