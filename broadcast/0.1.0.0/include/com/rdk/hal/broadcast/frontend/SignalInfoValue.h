#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/CodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DemodLockState.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
#include <com/rdk/hal/broadcast/frontend/DvbTCodingRate.h>
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/GuardInterval.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/RfLockState.h>
#include <com/rdk/hal/broadcast/frontend/TransmissionMode.h>
#include <cstdint>
#include <string>
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
class SignalInfoValue : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    actualFrequency = 0,
    demodLockState = 1,
    rfLockState = 2,
    rfLevel = 3,
    cnr = 4,
    ber = 5,
    preBer = 6,
    uncorrectedErrors = 7,
    ssi = 8,
    sqi = 9,
    plpId = 10,
    plpIds = 11,
    t2SystemId = 12,
    modulation = 13,
    guardInterval = 14,
    transmissionMode = 15,
    bandwidth = 16,
    symbolRate = 17,
    dvbTStandard = 18,
    dvbSStandard = 19,
    codingRate = 20,
    dvbTCodingRate = 21,
  };
  // Expose tag symbols for legacy code
  static const inline Tag actualFrequency = Tag::actualFrequency;
  static const inline Tag demodLockState = Tag::demodLockState;
  static const inline Tag rfLockState = Tag::rfLockState;
  static const inline Tag rfLevel = Tag::rfLevel;
  static const inline Tag cnr = Tag::cnr;
  static const inline Tag ber = Tag::ber;
  static const inline Tag preBer = Tag::preBer;
  static const inline Tag uncorrectedErrors = Tag::uncorrectedErrors;
  static const inline Tag ssi = Tag::ssi;
  static const inline Tag sqi = Tag::sqi;
  static const inline Tag plpId = Tag::plpId;
  static const inline Tag plpIds = Tag::plpIds;
  static const inline Tag t2SystemId = Tag::t2SystemId;
  static const inline Tag modulation = Tag::modulation;
  static const inline Tag guardInterval = Tag::guardInterval;
  static const inline Tag transmissionMode = Tag::transmissionMode;
  static const inline Tag bandwidth = Tag::bandwidth;
  static const inline Tag symbolRate = Tag::symbolRate;
  static const inline Tag dvbTStandard = Tag::dvbTStandard;
  static const inline Tag dvbSStandard = Tag::dvbSStandard;
  static const inline Tag codingRate = Tag::codingRate;
  static const inline Tag dvbTCodingRate = Tag::dvbTCodingRate;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, SignalInfoValue>;

  SignalInfoValue() : _value(std::in_place_index<static_cast<size_t>(actualFrequency)>, int64_t(0L)) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr SignalInfoValue(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit SignalInfoValue(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static SignalInfoValue make(_Tp&&... _args) {
    return SignalInfoValue(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static SignalInfoValue make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return SignalInfoValue(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const SignalInfoValue& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const SignalInfoValue& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const SignalInfoValue& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const SignalInfoValue& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const SignalInfoValue& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const SignalInfoValue& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.SignalInfoValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SignalInfoValue{";
    switch (getTag()) {
    case actualFrequency: os << "actualFrequency: " << ::android::internal::ToString(get<actualFrequency>()); break;
    case demodLockState: os << "demodLockState: " << ::android::internal::ToString(get<demodLockState>()); break;
    case rfLockState: os << "rfLockState: " << ::android::internal::ToString(get<rfLockState>()); break;
    case rfLevel: os << "rfLevel: " << ::android::internal::ToString(get<rfLevel>()); break;
    case cnr: os << "cnr: " << ::android::internal::ToString(get<cnr>()); break;
    case ber: os << "ber: " << ::android::internal::ToString(get<ber>()); break;
    case preBer: os << "preBer: " << ::android::internal::ToString(get<preBer>()); break;
    case uncorrectedErrors: os << "uncorrectedErrors: " << ::android::internal::ToString(get<uncorrectedErrors>()); break;
    case ssi: os << "ssi: " << ::android::internal::ToString(get<ssi>()); break;
    case sqi: os << "sqi: " << ::android::internal::ToString(get<sqi>()); break;
    case plpId: os << "plpId: " << ::android::internal::ToString(get<plpId>()); break;
    case plpIds: os << "plpIds: " << ::android::internal::ToString(get<plpIds>()); break;
    case t2SystemId: os << "t2SystemId: " << ::android::internal::ToString(get<t2SystemId>()); break;
    case modulation: os << "modulation: " << ::android::internal::ToString(get<modulation>()); break;
    case guardInterval: os << "guardInterval: " << ::android::internal::ToString(get<guardInterval>()); break;
    case transmissionMode: os << "transmissionMode: " << ::android::internal::ToString(get<transmissionMode>()); break;
    case bandwidth: os << "bandwidth: " << ::android::internal::ToString(get<bandwidth>()); break;
    case symbolRate: os << "symbolRate: " << ::android::internal::ToString(get<symbolRate>()); break;
    case dvbTStandard: os << "dvbTStandard: " << ::android::internal::ToString(get<dvbTStandard>()); break;
    case dvbSStandard: os << "dvbSStandard: " << ::android::internal::ToString(get<dvbSStandard>()); break;
    case codingRate: os << "codingRate: " << ::android::internal::ToString(get<codingRate>()); break;
    case dvbTCodingRate: os << "dvbTCodingRate: " << ::android::internal::ToString(get<dvbTCodingRate>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<int64_t, ::com::rdk::hal::broadcast::frontend::DemodLockState, ::com::rdk::hal::broadcast::frontend::RfLockState, float, float, int32_t, int32_t, int64_t, int32_t, int32_t, int32_t, ::std::vector<int32_t>, int32_t, ::com::rdk::hal::broadcast::frontend::Modulation, ::com::rdk::hal::broadcast::frontend::GuardInterval, ::com::rdk::hal::broadcast::frontend::TransmissionMode, ::com::rdk::hal::broadcast::frontend::Bandwidth, int64_t, ::com::rdk::hal::broadcast::frontend::DvbTStandard, ::com::rdk::hal::broadcast::frontend::DvbSStandard, ::com::rdk::hal::broadcast::frontend::CodingRate, ::com::rdk::hal::broadcast::frontend::DvbTCodingRate> _value;
};  // class SignalInfoValue
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
[[nodiscard]] static inline std::string toString(SignalInfoValue::Tag val) {
  switch(val) {
  case SignalInfoValue::Tag::actualFrequency:
    return "actualFrequency";
  case SignalInfoValue::Tag::demodLockState:
    return "demodLockState";
  case SignalInfoValue::Tag::rfLockState:
    return "rfLockState";
  case SignalInfoValue::Tag::rfLevel:
    return "rfLevel";
  case SignalInfoValue::Tag::cnr:
    return "cnr";
  case SignalInfoValue::Tag::ber:
    return "ber";
  case SignalInfoValue::Tag::preBer:
    return "preBer";
  case SignalInfoValue::Tag::uncorrectedErrors:
    return "uncorrectedErrors";
  case SignalInfoValue::Tag::ssi:
    return "ssi";
  case SignalInfoValue::Tag::sqi:
    return "sqi";
  case SignalInfoValue::Tag::plpId:
    return "plpId";
  case SignalInfoValue::Tag::plpIds:
    return "plpIds";
  case SignalInfoValue::Tag::t2SystemId:
    return "t2SystemId";
  case SignalInfoValue::Tag::modulation:
    return "modulation";
  case SignalInfoValue::Tag::guardInterval:
    return "guardInterval";
  case SignalInfoValue::Tag::transmissionMode:
    return "transmissionMode";
  case SignalInfoValue::Tag::bandwidth:
    return "bandwidth";
  case SignalInfoValue::Tag::symbolRate:
    return "symbolRate";
  case SignalInfoValue::Tag::dvbTStandard:
    return "dvbTStandard";
  case SignalInfoValue::Tag::dvbSStandard:
    return "dvbSStandard";
  case SignalInfoValue::Tag::codingRate:
    return "codingRate";
  case SignalInfoValue::Tag::dvbTCodingRate:
    return "dvbTCodingRate";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag, 22> enum_values<::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag> = {
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::actualFrequency,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::demodLockState,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::rfLockState,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::rfLevel,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::cnr,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::ber,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::preBer,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::uncorrectedErrors,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::ssi,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::sqi,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::plpId,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::plpIds,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::t2SystemId,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::modulation,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::guardInterval,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::transmissionMode,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::bandwidth,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::symbolRate,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbTStandard,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbSStandard,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::codingRate,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbTCodingRate,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
