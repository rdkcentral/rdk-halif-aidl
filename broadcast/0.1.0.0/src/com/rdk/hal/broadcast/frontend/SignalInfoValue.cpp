#include <com/rdk/hal/broadcast/frontend/SignalInfoValue.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
::android::status_t SignalInfoValue::readFromParcel(const ::android::Parcel* _aidl_parcel) {
  ::android::status_t _aidl_ret_status;
  int32_t _aidl_tag;
  if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_tag)) != ::android::OK) return _aidl_ret_status;
  switch (static_cast<Tag>(_aidl_tag)) {
  case frontendType: {
    ::com::rdk::hal::broadcast::frontend::FrontendType _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::FrontendType>) {
      set<frontendType>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<frontendType>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case actualFrequency: {
    ::com::rdk::hal::broadcast::frontend::Frequency _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Frequency>) {
      set<actualFrequency>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<actualFrequency>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case demodLockState: {
    ::com::rdk::hal::broadcast::frontend::DemodLockState _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DemodLockState>) {
      set<demodLockState>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<demodLockState>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case rfLockState: {
    ::com::rdk::hal::broadcast::frontend::RfLockState _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::RfLockState>) {
      set<rfLockState>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<rfLockState>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case rfLevel: {
    ::com::rdk::hal::broadcast::frontend::RfLevel _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::RfLevel>) {
      set<rfLevel>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<rfLevel>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case cnr: {
    ::com::rdk::hal::broadcast::frontend::Cnr _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Cnr>) {
      set<cnr>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<cnr>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case ber: {
    ::com::rdk::hal::broadcast::frontend::Ber _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Ber>) {
      set<ber>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<ber>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case preBer: {
    ::com::rdk::hal::broadcast::frontend::Ber _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Ber>) {
      set<preBer>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<preBer>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case uncorrectedErrors: {
    ::com::rdk::hal::broadcast::frontend::UncorrectedErrorCount _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::UncorrectedErrorCount>) {
      set<uncorrectedErrors>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<uncorrectedErrors>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case ssi: {
    ::com::rdk::hal::broadcast::frontend::SignalStrengthIndicator _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::SignalStrengthIndicator>) {
      set<ssi>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<ssi>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case sqi: {
    ::com::rdk::hal::broadcast::frontend::SignalQualityIndicator _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::SignalQualityIndicator>) {
      set<sqi>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<sqi>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case plpId: {
    ::com::rdk::hal::broadcast::frontend::DvbTPlpId _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTPlpId>) {
      set<plpId>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<plpId>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case plpIds: {
    ::std::vector<::com::rdk::hal::broadcast::frontend::DvbTPlpId> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelableVector(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::std::vector<::com::rdk::hal::broadcast::frontend::DvbTPlpId>>) {
      set<plpIds>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<plpIds>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case t2SystemId: {
    ::com::rdk::hal::broadcast::frontend::DvbT2SystemId _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbT2SystemId>) {
      set<t2SystemId>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<t2SystemId>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case modulation: {
    ::com::rdk::hal::broadcast::frontend::Modulation _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Modulation>) {
      set<modulation>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<modulation>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case guardInterval: {
    ::com::rdk::hal::broadcast::frontend::GuardInterval _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::GuardInterval>) {
      set<guardInterval>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<guardInterval>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case transmissionMode: {
    ::com::rdk::hal::broadcast::frontend::TransmissionMode _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::TransmissionMode>) {
      set<transmissionMode>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<transmissionMode>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case bandwidth: {
    ::com::rdk::hal::broadcast::frontend::Bandwidth _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Bandwidth>) {
      set<bandwidth>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<bandwidth>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case symbolRate: {
    ::com::rdk::hal::broadcast::frontend::SymbolRate _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::SymbolRate>) {
      set<symbolRate>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<symbolRate>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbTStandard: {
    ::com::rdk::hal::broadcast::frontend::DvbTStandard _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTStandard>) {
      set<dvbTStandard>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbTStandard>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbSStandard: {
    ::com::rdk::hal::broadcast::frontend::DvbSStandard _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSStandard>) {
      set<dvbSStandard>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbSStandard>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case codeRate: {
    ::com::rdk::hal::broadcast::frontend::CodeRate _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::CodeRate>) {
      set<codeRate>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<codeRate>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbCAnnex: {
    ::com::rdk::hal::broadcast::frontend::DvbCAnnex _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbCAnnex>) {
      set<dvbCAnnex>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbCAnnex>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case inversion: {
    ::com::rdk::hal::broadcast::frontend::SpectralInversion _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::SpectralInversion>) {
      set<inversion>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<inversion>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case rollOff: {
    ::com::rdk::hal::broadcast::frontend::RollOff _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::RollOff>) {
      set<rollOff>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<rollOff>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbTHierarchy: {
    ::com::rdk::hal::broadcast::frontend::DvbTHierarchy _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTHierarchy>) {
      set<dvbTHierarchy>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbTHierarchy>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbTMiso: {
    ::com::rdk::hal::broadcast::frontend::DvbTMiso _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTMiso>) {
      set<dvbTMiso>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbTMiso>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbSPilot: {
    ::com::rdk::hal::broadcast::frontend::DvbSPilot _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSPilot>) {
      set<dvbSPilot>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbSPilot>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbSPlsMode: {
    ::com::rdk::hal::broadcast::frontend::DvbSPlsMode _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSPlsMode>) {
      set<dvbSPlsMode>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbSPlsMode>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbSPlsCode: {
    ::com::rdk::hal::broadcast::frontend::DvbSPlsCode _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSPlsCode>) {
      set<dvbSPlsCode>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbSPlsCode>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbSInputStreamId: {
    ::com::rdk::hal::broadcast::frontend::DvbSInputStreamId _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbSInputStreamId>) {
      set<dvbSInputStreamId>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbSInputStreamId>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t SignalInfoValue::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case frontendType: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<frontendType>()));
  case actualFrequency: return _aidl_parcel->writeParcelable(get<actualFrequency>());
  case demodLockState: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<demodLockState>()));
  case rfLockState: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<rfLockState>()));
  case rfLevel: return _aidl_parcel->writeParcelable(get<rfLevel>());
  case cnr: return _aidl_parcel->writeParcelable(get<cnr>());
  case ber: return _aidl_parcel->writeParcelable(get<ber>());
  case preBer: return _aidl_parcel->writeParcelable(get<preBer>());
  case uncorrectedErrors: return _aidl_parcel->writeParcelable(get<uncorrectedErrors>());
  case ssi: return _aidl_parcel->writeParcelable(get<ssi>());
  case sqi: return _aidl_parcel->writeParcelable(get<sqi>());
  case plpId: return _aidl_parcel->writeParcelable(get<plpId>());
  case plpIds: return _aidl_parcel->writeParcelableVector(get<plpIds>());
  case t2SystemId: return _aidl_parcel->writeParcelable(get<t2SystemId>());
  case modulation: return _aidl_parcel->writeParcelable(get<modulation>());
  case guardInterval: return _aidl_parcel->writeParcelable(get<guardInterval>());
  case transmissionMode: return _aidl_parcel->writeParcelable(get<transmissionMode>());
  case bandwidth: return _aidl_parcel->writeParcelable(get<bandwidth>());
  case symbolRate: return _aidl_parcel->writeParcelable(get<symbolRate>());
  case dvbTStandard: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbTStandard>()));
  case dvbSStandard: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbSStandard>()));
  case codeRate: return _aidl_parcel->writeParcelable(get<codeRate>());
  case dvbCAnnex: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbCAnnex>()));
  case inversion: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<inversion>()));
  case rollOff: return _aidl_parcel->writeParcelable(get<rollOff>());
  case dvbTHierarchy: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbTHierarchy>()));
  case dvbTMiso: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbTMiso>()));
  case dvbSPilot: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbSPilot>()));
  case dvbSPlsMode: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbSPlsMode>()));
  case dvbSPlsCode: return _aidl_parcel->writeParcelable(get<dvbSPlsCode>());
  case dvbSInputStreamId: return _aidl_parcel->writeParcelable(get<dvbSInputStreamId>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
