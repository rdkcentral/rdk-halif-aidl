#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
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
namespace drm {
class DrmMetricValue : public ::android::Parcelable {
public:
  enum class Tag : int32_t {
    int64Value = 0,
    doubleValue = 1,
    stringValue = 2,
  };
  // Expose tag symbols for legacy code
  static const inline Tag int64Value = Tag::int64Value;
  static const inline Tag doubleValue = Tag::doubleValue;
  static const inline Tag stringValue = Tag::stringValue;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, DrmMetricValue>;

  DrmMetricValue() : _value(std::in_place_index<static_cast<size_t>(int64Value)>, int64_t(0L)) { }

  template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr DrmMetricValue(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit DrmMetricValue(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static DrmMetricValue make(_Tp&&... _args) {
    return DrmMetricValue(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static DrmMetricValue make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return DrmMetricValue(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

  inline bool operator!=(const DrmMetricValue& rhs) const {
    return _value != rhs._value;
  }
  inline bool operator<(const DrmMetricValue& rhs) const {
    return _value < rhs._value;
  }
  inline bool operator<=(const DrmMetricValue& rhs) const {
    return _value <= rhs._value;
  }
  inline bool operator==(const DrmMetricValue& rhs) const {
    return _value == rhs._value;
  }
  inline bool operator>(const DrmMetricValue& rhs) const {
    return _value > rhs._value;
  }
  inline bool operator>=(const DrmMetricValue& rhs) const {
    return _value >= rhs._value;
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.drm.DrmMetricValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "DrmMetricValue{";
    switch (getTag()) {
    case int64Value: os << "int64Value: " << ::android::internal::ToString(get<int64Value>()); break;
    case doubleValue: os << "doubleValue: " << ::android::internal::ToString(get<doubleValue>()); break;
    case stringValue: os << "stringValue: " << ::android::internal::ToString(get<stringValue>()); break;
    }
    os << "}";
    return os.str();
  }
private:
  std::variant<int64_t, double, ::android::String16> _value;
};  // class DrmMetricValue
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
namespace drm {
[[nodiscard]] static inline std::string toString(DrmMetricValue::Tag val) {
  switch(val) {
  case DrmMetricValue::Tag::int64Value:
    return "int64Value";
  case DrmMetricValue::Tag::doubleValue:
    return "doubleValue";
  case DrmMetricValue::Tag::stringValue:
    return "stringValue";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace drm
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::drm::DrmMetricValue::Tag, 3> enum_values<::com::rdk::hal::drm::DrmMetricValue::Tag> = {
  ::com::rdk::hal::drm::DrmMetricValue::Tag::int64Value,
  ::com::rdk::hal::drm::DrmMetricValue::Tag::doubleValue,
  ::com::rdk::hal::drm::DrmMetricValue::Tag::stringValue,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
