#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/frontend/DvbCCodeRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbSInnerFec.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCodeRates.h>
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
namespace frontend {
// @aidl-doc
/**
 * @brief Available code rates.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class CodeRate : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    // @aidl-doc
    /** Forward error correction code rate of a DVB-C carrier. */
    dvbC = 0,
    // @aidl-doc
    /** Inner forward error correction code rate of a DVB-S, DVB-S2 or DVB-S2X carrier. */
    dvbS = 1,
    // @aidl-doc
    /** Code rates of a DVB-T or DVB-T2 carrier. */
    dvbT = 2,
  };
  // Expose tag symbols for legacy code
  // @aidl-doc
  /** Forward error correction code rate of a DVB-C carrier. */
  static const inline Tag dvbC = Tag::dvbC;
  // @aidl-doc
  /** Inner forward error correction code rate of a DVB-S, DVB-S2 or DVB-S2X carrier. */
  static const inline Tag dvbS = Tag::dvbS;
  // @aidl-doc
  /** Code rates of a DVB-T or DVB-T2 carrier. */
  static const inline Tag dvbT = Tag::dvbT;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, CodeRate>;

  CodeRate() : _value(std::in_place_index<static_cast<size_t>(dvbC)>, ::com::rdk::hal::broadcast::frontend::DvbCCodeRate(::com::rdk::hal::broadcast::frontend::DvbCCodeRate::UNDEFINED)) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr CodeRate(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit CodeRate(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static CodeRate make(_Tp&&... _args) {
    return CodeRate(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static CodeRate make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return CodeRate(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const CodeRate& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const CodeRate& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const CodeRate& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const CodeRate& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const CodeRate& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const CodeRate& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.CodeRate");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "CodeRate{";
    switch (getTag()) {
    case dvbC: os << "dvbC: " << ::android::internal::ToString(get<dvbC>()); break;
    case dvbS: os << "dvbS: " << ::android::internal::ToString(get<dvbS>()); break;
    case dvbT: os << "dvbT: " << ::android::internal::ToString(get<dvbT>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<::com::rdk::hal::broadcast::frontend::DvbCCodeRate, ::com::rdk::hal::broadcast::frontend::DvbSInnerFec, ::com::rdk::hal::broadcast::frontend::DvbTCodeRates> _value;
};  // class CodeRate
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
[[nodiscard]] static inline std::string toString(CodeRate::Tag val) {
  switch(val) {
  case CodeRate::Tag::dvbC:
    return "dvbC";
  case CodeRate::Tag::dvbS:
    return "dvbS";
  case CodeRate::Tag::dvbT:
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::CodeRate::Tag, 3> enum_values<::com::rdk::hal::broadcast::frontend::CodeRate::Tag> = {
  ::com::rdk::hal::broadcast::frontend::CodeRate::Tag::dvbC,
  ::com::rdk::hal::broadcast::frontend::CodeRate::Tag::dvbS,
  ::com::rdk::hal::broadcast::frontend::CodeRate::Tag::dvbT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
