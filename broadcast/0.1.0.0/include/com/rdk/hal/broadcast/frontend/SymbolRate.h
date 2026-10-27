#pragma once

#include <android/binder_to_string.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cstdint>
#include <tuple>
#include <utils/String16.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
// @aidl-doc
/**
 * @brief A symbol rate, carrying its unit in the type.
 *
 * Applies to DVB-C and DVB-S/S2/S2X only. The valid range is resource-specific: see minSymbolRate and maxSymbolRate on
 * DvbCCapabilities or DvbSCapabilities for the frontend in question.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class SymbolRate : public ::android::Parcelable {
public:
  // @aidl-doc
  /** The symbol rate in symbols per second. */
  int32_t symbolsPerSecond = 0;
  inline bool operator!=(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) != std::tie(rhs.symbolsPerSecond);
  }
  inline bool operator<(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) < std::tie(rhs.symbolsPerSecond);
  }
  inline bool operator<=(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) <= std::tie(rhs.symbolsPerSecond);
  }
  inline bool operator==(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) == std::tie(rhs.symbolsPerSecond);
  }
  inline bool operator>(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) > std::tie(rhs.symbolsPerSecond);
  }
  inline bool operator>=(const SymbolRate& rhs) const {
    return std::tie(symbolsPerSecond) >= std::tie(rhs.symbolsPerSecond);
  }

  // @aidl-doc
  /** No symbol rate selected. */
  enum : int32_t { UNDEFINED = 0 };
  // @aidl-doc
  /**
   * Detect the symbol rate automatically.
   *
   * Only valid where the frontend reports isAutoSymbolRateSupported, see DvbCCapabilities and DvbSCapabilities.
   */
  enum : int32_t { AUTO = -1 };
  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.SymbolRate");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "SymbolRate{";
    os << "symbolsPerSecond: " << ::android::internal::ToString(symbolsPerSecond);
    os << "}";
    return os.str();
  }
};  // class SymbolRate
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
