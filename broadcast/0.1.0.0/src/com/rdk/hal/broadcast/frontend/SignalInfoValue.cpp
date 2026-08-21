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
  case actualFrequency: {
    int64_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt64(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int64_t>) {
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
    float _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readFloat(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<float>) {
      set<rfLevel>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<rfLevel>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case cnr: {
    float _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readFloat(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<float>) {
      set<cnr>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<cnr>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case ber: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<ber>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<ber>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case preBer: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<preBer>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<preBer>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case uncorrectedErrors: {
    int64_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt64(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int64_t>) {
      set<uncorrectedErrors>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<uncorrectedErrors>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case ssi: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<ssi>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<ssi>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case sqi: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<sqi>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<sqi>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case plpId: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<plpId>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<plpId>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case plpIds: {
    ::std::vector<int32_t> _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32Vector(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::std::vector<int32_t>>) {
      set<plpIds>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<plpIds>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case t2SystemId: {
    int32_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int32_t>) {
      set<t2SystemId>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<t2SystemId>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case modulation: {
    ::com::rdk::hal::broadcast::frontend::Modulation _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Modulation>) {
      set<modulation>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<modulation>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case guardInterval: {
    ::com::rdk::hal::broadcast::frontend::GuardInterval _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::GuardInterval>) {
      set<guardInterval>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<guardInterval>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case transmissionMode: {
    ::com::rdk::hal::broadcast::frontend::TransmissionMode _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::TransmissionMode>) {
      set<transmissionMode>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<transmissionMode>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case bandwidth: {
    ::com::rdk::hal::broadcast::frontend::Bandwidth _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::Bandwidth>) {
      set<bandwidth>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<bandwidth>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case symbolRate: {
    int64_t _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt64(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<int64_t>) {
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
  case codingRate: {
    ::com::rdk::hal::broadcast::frontend::CodingRate _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readInt32(reinterpret_cast<int32_t *>(&_aidl_value))) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::CodingRate>) {
      set<codingRate>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<codingRate>(std::move(_aidl_value));
    }
    return ::android::OK; }
  case dvbTCodingRate: {
    ::com::rdk::hal::broadcast::frontend::DvbTCodingRate _aidl_value;
    if ((_aidl_ret_status = _aidl_parcel->readParcelable(&_aidl_value)) != ::android::OK) return _aidl_ret_status;
    if constexpr (std::is_trivially_copyable_v<::com::rdk::hal::broadcast::frontend::DvbTCodingRate>) {
      set<dvbTCodingRate>(_aidl_value);
    } else {
      // NOLINTNEXTLINE(performance-move-const-arg)
      set<dvbTCodingRate>(std::move(_aidl_value));
    }
    return ::android::OK; }
  }
  return ::android::BAD_VALUE;
}
::android::status_t SignalInfoValue::writeToParcel(::android::Parcel* _aidl_parcel) const {
  ::android::status_t _aidl_ret_status = _aidl_parcel->writeInt32(static_cast<int32_t>(getTag()));
  if (_aidl_ret_status != ::android::OK) return _aidl_ret_status;
  switch (getTag()) {
  case actualFrequency: return _aidl_parcel->writeInt64(get<actualFrequency>());
  case demodLockState: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<demodLockState>()));
  case rfLockState: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<rfLockState>()));
  case rfLevel: return _aidl_parcel->writeFloat(get<rfLevel>());
  case cnr: return _aidl_parcel->writeFloat(get<cnr>());
  case ber: return _aidl_parcel->writeInt32(get<ber>());
  case preBer: return _aidl_parcel->writeInt32(get<preBer>());
  case uncorrectedErrors: return _aidl_parcel->writeInt64(get<uncorrectedErrors>());
  case ssi: return _aidl_parcel->writeInt32(get<ssi>());
  case sqi: return _aidl_parcel->writeInt32(get<sqi>());
  case plpId: return _aidl_parcel->writeInt32(get<plpId>());
  case plpIds: return _aidl_parcel->writeInt32Vector(get<plpIds>());
  case t2SystemId: return _aidl_parcel->writeInt32(get<t2SystemId>());
  case modulation: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<modulation>()));
  case guardInterval: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<guardInterval>()));
  case transmissionMode: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<transmissionMode>()));
  case bandwidth: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<bandwidth>()));
  case symbolRate: return _aidl_parcel->writeInt64(get<symbolRate>());
  case dvbTStandard: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbTStandard>()));
  case dvbSStandard: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<dvbSStandard>()));
  case codingRate: return _aidl_parcel->writeInt32(static_cast<int32_t>(get<codingRate>()));
  case dvbTCodingRate: return _aidl_parcel->writeParcelable(get<dvbTCodingRate>());
  }
  __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "can't reach here");
}
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
