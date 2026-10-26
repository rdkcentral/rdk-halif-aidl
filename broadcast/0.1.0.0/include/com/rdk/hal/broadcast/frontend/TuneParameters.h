#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/frontend/AtscTuneParameters.h>
#include <com/rdk/hal/broadcast/frontend/DvbCTuneParameters.h>
#include <com/rdk/hal/broadcast/frontend/DvbSTuneParameters.h>
#include <com/rdk/hal/broadcast/frontend/DvbTTuneParameters.h>
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
 * @brief Tuner-specific tuning parameters.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class TuneParameters : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    // @aidl-doc
    /** Tune parameters for tuning ATSC tuners. */
    atsc = 0,
    // @aidl-doc
    /** Tune parameters for tuning DVB-C tuners. */
    dvbC = 1,
    // @aidl-doc
    /** Tune parameters for tuning DVB-S/S2/S2X tuners. */
    dvbS = 2,
    // @aidl-doc
    /** Tune parameters for tuning DVB-T tuners. */
    dvbT = 3,
  };
  // Expose tag symbols for legacy code
  // @aidl-doc
  /** Tune parameters for tuning ATSC tuners. */
  static const inline Tag atsc = Tag::atsc;
  // @aidl-doc
  /** Tune parameters for tuning DVB-C tuners. */
  static const inline Tag dvbC = Tag::dvbC;
  // @aidl-doc
  /** Tune parameters for tuning DVB-S/S2/S2X tuners. */
  static const inline Tag dvbS = Tag::dvbS;
  // @aidl-doc
  /** Tune parameters for tuning DVB-T tuners. */
  static const inline Tag dvbT = Tag::dvbT;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, TuneParameters>;

  TuneParameters() : _value(std::in_place_index<static_cast<size_t>(atsc)>, ::com::rdk::hal::broadcast::frontend::AtscTuneParameters()) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr TuneParameters(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit TuneParameters(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static TuneParameters make(_Tp&&... _args) {
    return TuneParameters(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static TuneParameters make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return TuneParameters(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const TuneParameters& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const TuneParameters& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const TuneParameters& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const TuneParameters& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const TuneParameters& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const TuneParameters& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.TuneParameters");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "TuneParameters{";
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
  std::variant<::com::rdk::hal::broadcast::frontend::AtscTuneParameters, ::com::rdk::hal::broadcast::frontend::DvbCTuneParameters, ::com::rdk::hal::broadcast::frontend::DvbSTuneParameters, ::com::rdk::hal::broadcast::frontend::DvbTTuneParameters> _value;
};  // class TuneParameters
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
[[nodiscard]] static inline std::string toString(TuneParameters::Tag val) {
  switch(val) {
  case TuneParameters::Tag::atsc:
    return "atsc";
  case TuneParameters::Tag::dvbC:
    return "dvbC";
  case TuneParameters::Tag::dvbS:
    return "dvbS";
  case TuneParameters::Tag::dvbT:
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::TuneParameters::Tag, 4> enum_values<::com::rdk::hal::broadcast::frontend::TuneParameters::Tag> = {
  ::com::rdk::hal::broadcast::frontend::TuneParameters::Tag::atsc,
  ::com::rdk::hal::broadcast::frontend::TuneParameters::Tag::dvbC,
  ::com::rdk::hal::broadcast::frontend::TuneParameters::Tag::dvbS,
  ::com::rdk::hal::broadcast::frontend::TuneParameters::Tag::dvbT,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
