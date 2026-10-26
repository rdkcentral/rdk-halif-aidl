#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/broadcast/frontend/Bandwidth.h>
#include <com/rdk/hal/broadcast/frontend/Ber.h>
#include <com/rdk/hal/broadcast/frontend/Cnr.h>
#include <com/rdk/hal/broadcast/frontend/CodeRate.h>
#include <com/rdk/hal/broadcast/frontend/DemodLockState.h>
#include <com/rdk/hal/broadcast/frontend/DvbCAnnex.h>
#include <com/rdk/hal/broadcast/frontend/DvbSInputStreamId.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPilot.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPlsCode.h>
#include <com/rdk/hal/broadcast/frontend/DvbSPlsMode.h>
#include <com/rdk/hal/broadcast/frontend/DvbSStandard.h>
#include <com/rdk/hal/broadcast/frontend/DvbT2SystemId.h>
#include <com/rdk/hal/broadcast/frontend/DvbTHierarchy.h>
#include <com/rdk/hal/broadcast/frontend/DvbTMiso.h>
#include <com/rdk/hal/broadcast/frontend/DvbTPlpId.h>
#include <com/rdk/hal/broadcast/frontend/DvbTStandard.h>
#include <com/rdk/hal/broadcast/frontend/Frequency.h>
#include <com/rdk/hal/broadcast/frontend/FrontendType.h>
#include <com/rdk/hal/broadcast/frontend/GuardInterval.h>
#include <com/rdk/hal/broadcast/frontend/Modulation.h>
#include <com/rdk/hal/broadcast/frontend/RfLevel.h>
#include <com/rdk/hal/broadcast/frontend/RfLockState.h>
#include <com/rdk/hal/broadcast/frontend/RollOff.h>
#include <com/rdk/hal/broadcast/frontend/SignalQualityIndicator.h>
#include <com/rdk/hal/broadcast/frontend/SignalStrengthIndicator.h>
#include <com/rdk/hal/broadcast/frontend/SpectralInversion.h>
#include <com/rdk/hal/broadcast/frontend/SymbolRate.h>
#include <com/rdk/hal/broadcast/frontend/TransmissionMode.h>
#include <com/rdk/hal/broadcast/frontend/UncorrectedErrorCount.h>
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
// @aidl-doc
/**
 * @brief SignalInfo values.
 *
 * These are the values that can be returned on status requests. The members correspond one-to-one, and in the same
 * order, with the entries of @ref SignalInfoProperty following its UNDEFINED entry. When adding a value here, add the
 * matching property there in the same position.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class SignalInfoValue : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    // @aidl-doc
    /** The current frontend type used for tuning. */
    frontendType = 0,
    // @aidl-doc
    /** The actual frequency that the tuner is locked on. */
    actualFrequency = 1,
    // @aidl-doc
    /** Demodulator lock state. */
    demodLockState = 2,
    // @aidl-doc
    /** RF lock state. */
    rfLockState = 3,
    // @aidl-doc
    /** RF signal level. */
    rfLevel = 4,
    // @aidl-doc
    /** Carrier to noise ratio. */
    cnr = 5,
    // @aidl-doc
    /** Bit error rate. */
    ber = 6,
    // @aidl-doc
    /** Pre Viterbi BER - the bit error rate before correction. */
    preBer = 7,
    // @aidl-doc
    /** Uncorrected Error count. */
    uncorrectedErrors = 8,
    // @aidl-doc
    /** Signal Strength Indicator as defined in NorDig. */
    ssi = 9,
    // @aidl-doc
    /** Signal Quality Indicator as defined in NorDig. */
    sqi = 10,
    // @aidl-doc
    /** Physical Layer Pipe ID. */
    plpId = 11,
    // @aidl-doc
    /** Physical Layer Pipe IDs. */
    plpIds = 12,
    // @aidl-doc
    /** DVB-T2 System ID. */
    t2SystemId = 13,
    // @aidl-doc
    /** The used modulation/sub-modulation. */
    modulation = 14,
    // @aidl-doc
    /** The used guard interval. */
    guardInterval = 15,
    // @aidl-doc
    /** The used transmission mode. */
    transmissionMode = 16,
    // @aidl-doc
    /** Bandwidth. */
    bandwidth = 17,
    // @aidl-doc
    /** The symbol rate. */
    symbolRate = 18,
    // @aidl-doc
    /** DVB-T Standard. */
    dvbTStandard = 19,
    // @aidl-doc
    /** DVB-S Standard. */
    dvbSStandard = 20,
    // @aidl-doc
    /** Standard-specific code rate; CodeRate.dvbS contains DVB-S/S2/S2X inner FEC. */
    codeRate = 21,
    // @aidl-doc
    /** DVB-C Annex. */
    dvbCAnnex = 22,
    // @aidl-doc
    /** Spectral inversion mode. */
    inversion = 23,
    // @aidl-doc
    /** Roll-off factor. */
    rollOff = 24,
    // @aidl-doc
    /** DVB-T hierarchical transmission mode. */
    dvbTHierarchy = 25,
    // @aidl-doc
    /** DVB-T MISO mode. */
    dvbTMiso = 26,
    // @aidl-doc
    /** DVB-S2/S2X pilot mode. */
    dvbSPilot = 27,
    // @aidl-doc
    /** DVB-S2/S2X physical-layer scrambling mode. */
    dvbSPlsMode = 28,
    // @aidl-doc
    /** DVB-S2/S2X physical-layer scrambling code. */
    dvbSPlsCode = 29,
    // @aidl-doc
    /** DVB-S2/S2X input stream identifier. */
    dvbSInputStreamId = 30,
  };
  // Expose tag symbols for legacy code
  // @aidl-doc
  /** The current frontend type used for tuning. */
  static const inline Tag frontendType = Tag::frontendType;
  // @aidl-doc
  /** The actual frequency that the tuner is locked on. */
  static const inline Tag actualFrequency = Tag::actualFrequency;
  // @aidl-doc
  /** Demodulator lock state. */
  static const inline Tag demodLockState = Tag::demodLockState;
  // @aidl-doc
  /** RF lock state. */
  static const inline Tag rfLockState = Tag::rfLockState;
  // @aidl-doc
  /** RF signal level. */
  static const inline Tag rfLevel = Tag::rfLevel;
  // @aidl-doc
  /** Carrier to noise ratio. */
  static const inline Tag cnr = Tag::cnr;
  // @aidl-doc
  /** Bit error rate. */
  static const inline Tag ber = Tag::ber;
  // @aidl-doc
  /** Pre Viterbi BER - the bit error rate before correction. */
  static const inline Tag preBer = Tag::preBer;
  // @aidl-doc
  /** Uncorrected Error count. */
  static const inline Tag uncorrectedErrors = Tag::uncorrectedErrors;
  // @aidl-doc
  /** Signal Strength Indicator as defined in NorDig. */
  static const inline Tag ssi = Tag::ssi;
  // @aidl-doc
  /** Signal Quality Indicator as defined in NorDig. */
  static const inline Tag sqi = Tag::sqi;
  // @aidl-doc
  /** Physical Layer Pipe ID. */
  static const inline Tag plpId = Tag::plpId;
  // @aidl-doc
  /** Physical Layer Pipe IDs. */
  static const inline Tag plpIds = Tag::plpIds;
  // @aidl-doc
  /** DVB-T2 System ID. */
  static const inline Tag t2SystemId = Tag::t2SystemId;
  // @aidl-doc
  /** The used modulation/sub-modulation. */
  static const inline Tag modulation = Tag::modulation;
  // @aidl-doc
  /** The used guard interval. */
  static const inline Tag guardInterval = Tag::guardInterval;
  // @aidl-doc
  /** The used transmission mode. */
  static const inline Tag transmissionMode = Tag::transmissionMode;
  // @aidl-doc
  /** Bandwidth. */
  static const inline Tag bandwidth = Tag::bandwidth;
  // @aidl-doc
  /** The symbol rate. */
  static const inline Tag symbolRate = Tag::symbolRate;
  // @aidl-doc
  /** DVB-T Standard. */
  static const inline Tag dvbTStandard = Tag::dvbTStandard;
  // @aidl-doc
  /** DVB-S Standard. */
  static const inline Tag dvbSStandard = Tag::dvbSStandard;
  // @aidl-doc
  /** Standard-specific code rate; CodeRate.dvbS contains DVB-S/S2/S2X inner FEC. */
  static const inline Tag codeRate = Tag::codeRate;
  // @aidl-doc
  /** DVB-C Annex. */
  static const inline Tag dvbCAnnex = Tag::dvbCAnnex;
  // @aidl-doc
  /** Spectral inversion mode. */
  static const inline Tag inversion = Tag::inversion;
  // @aidl-doc
  /** Roll-off factor. */
  static const inline Tag rollOff = Tag::rollOff;
  // @aidl-doc
  /** DVB-T hierarchical transmission mode. */
  static const inline Tag dvbTHierarchy = Tag::dvbTHierarchy;
  // @aidl-doc
  /** DVB-T MISO mode. */
  static const inline Tag dvbTMiso = Tag::dvbTMiso;
  // @aidl-doc
  /** DVB-S2/S2X pilot mode. */
  static const inline Tag dvbSPilot = Tag::dvbSPilot;
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling mode. */
  static const inline Tag dvbSPlsMode = Tag::dvbSPlsMode;
  // @aidl-doc
  /** DVB-S2/S2X physical-layer scrambling code. */
  static const inline Tag dvbSPlsCode = Tag::dvbSPlsCode;
  // @aidl-doc
  /** DVB-S2/S2X input stream identifier. */
  static const inline Tag dvbSInputStreamId = Tag::dvbSInputStreamId;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, SignalInfoValue>;

  SignalInfoValue() : _value(std::in_place_index<static_cast<size_t>(frontendType)>, ::com::rdk::hal::broadcast::frontend::FrontendType(::com::rdk::hal::broadcast::frontend::FrontendType::UNDEFINED)) { }

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
    case frontendType: os << "frontendType: " << ::android::internal::ToString(get<frontendType>()); break;
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
    case codeRate: os << "codeRate: " << ::android::internal::ToString(get<codeRate>()); break;
    case dvbCAnnex: os << "dvbCAnnex: " << ::android::internal::ToString(get<dvbCAnnex>()); break;
    case inversion: os << "inversion: " << ::android::internal::ToString(get<inversion>()); break;
    case rollOff: os << "rollOff: " << ::android::internal::ToString(get<rollOff>()); break;
    case dvbTHierarchy: os << "dvbTHierarchy: " << ::android::internal::ToString(get<dvbTHierarchy>()); break;
    case dvbTMiso: os << "dvbTMiso: " << ::android::internal::ToString(get<dvbTMiso>()); break;
    case dvbSPilot: os << "dvbSPilot: " << ::android::internal::ToString(get<dvbSPilot>()); break;
    case dvbSPlsMode: os << "dvbSPlsMode: " << ::android::internal::ToString(get<dvbSPlsMode>()); break;
    case dvbSPlsCode: os << "dvbSPlsCode: " << ::android::internal::ToString(get<dvbSPlsCode>()); break;
    case dvbSInputStreamId: os << "dvbSInputStreamId: " << ::android::internal::ToString(get<dvbSInputStreamId>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<::com::rdk::hal::broadcast::frontend::FrontendType, ::com::rdk::hal::broadcast::frontend::Frequency, ::com::rdk::hal::broadcast::frontend::DemodLockState, ::com::rdk::hal::broadcast::frontend::RfLockState, ::com::rdk::hal::broadcast::frontend::RfLevel, ::com::rdk::hal::broadcast::frontend::Cnr, ::com::rdk::hal::broadcast::frontend::Ber, ::com::rdk::hal::broadcast::frontend::Ber, ::com::rdk::hal::broadcast::frontend::UncorrectedErrorCount, ::com::rdk::hal::broadcast::frontend::SignalStrengthIndicator, ::com::rdk::hal::broadcast::frontend::SignalQualityIndicator, ::com::rdk::hal::broadcast::frontend::DvbTPlpId, ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTPlpId>, ::com::rdk::hal::broadcast::frontend::DvbT2SystemId, ::com::rdk::hal::broadcast::frontend::Modulation, ::com::rdk::hal::broadcast::frontend::GuardInterval, ::com::rdk::hal::broadcast::frontend::TransmissionMode, ::com::rdk::hal::broadcast::frontend::Bandwidth, ::com::rdk::hal::broadcast::frontend::SymbolRate, ::com::rdk::hal::broadcast::frontend::DvbTStandard, ::com::rdk::hal::broadcast::frontend::DvbSStandard, ::com::rdk::hal::broadcast::frontend::CodeRate, ::com::rdk::hal::broadcast::frontend::DvbCAnnex, ::com::rdk::hal::broadcast::frontend::SpectralInversion, ::com::rdk::hal::broadcast::frontend::RollOff, ::com::rdk::hal::broadcast::frontend::DvbTHierarchy, ::com::rdk::hal::broadcast::frontend::DvbTMiso, ::com::rdk::hal::broadcast::frontend::DvbSPilot, ::com::rdk::hal::broadcast::frontend::DvbSPlsMode, ::com::rdk::hal::broadcast::frontend::DvbSPlsCode, ::com::rdk::hal::broadcast::frontend::DvbSInputStreamId> _value;
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
  case SignalInfoValue::Tag::frontendType:
    return "frontendType";
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
  case SignalInfoValue::Tag::codeRate:
    return "codeRate";
  case SignalInfoValue::Tag::dvbCAnnex:
    return "dvbCAnnex";
  case SignalInfoValue::Tag::inversion:
    return "inversion";
  case SignalInfoValue::Tag::rollOff:
    return "rollOff";
  case SignalInfoValue::Tag::dvbTHierarchy:
    return "dvbTHierarchy";
  case SignalInfoValue::Tag::dvbTMiso:
    return "dvbTMiso";
  case SignalInfoValue::Tag::dvbSPilot:
    return "dvbSPilot";
  case SignalInfoValue::Tag::dvbSPlsMode:
    return "dvbSPlsMode";
  case SignalInfoValue::Tag::dvbSPlsCode:
    return "dvbSPlsCode";
  case SignalInfoValue::Tag::dvbSInputStreamId:
    return "dvbSInputStreamId";
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
constexpr inline std::array<::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag, 31> enum_values<::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag> = {
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::frontendType,
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
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::codeRate,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbCAnnex,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::inversion,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::rollOff,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbTHierarchy,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbTMiso,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbSPilot,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbSPlsMode,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbSPlsCode,
  ::com::rdk::hal::broadcast::frontend::SignalInfoValue::Tag::dvbSInputStreamId,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
