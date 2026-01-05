#pragma once

#include <android/binder_to_string.h>
#include <array>
#include <binder/Enums.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <cassert>
#include <com/rdk/hal/PropertyValue.h>
#include <cstdint>
#include <optional>
#include <string>
#include <tuple>
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
class PropertyValue : public ::android::Parcelable {
public:
  class Value : public ::android::Parcelable {
  public:
    enum class Tag : int32_t {
      booleanValue = 0,
      byteValue = 1,
      charValue = 2,
      intValue = 3,
      longValue = 4,
      floatValue = 5,
      doubleValue = 6,
      stringValue = 7,
    };
    // Expose tag symbols for legacy code
    static const inline Tag booleanValue = Tag::booleanValue;
    static const inline Tag byteValue = Tag::byteValue;
    static const inline Tag charValue = Tag::charValue;
    static const inline Tag intValue = Tag::intValue;
    static const inline Tag longValue = Tag::longValue;
    static const inline Tag floatValue = Tag::floatValue;
    static const inline Tag doubleValue = Tag::doubleValue;
    static const inline Tag stringValue = Tag::stringValue;

    template<typename _Tp>
    static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, Value>;

    Value() : _value(std::in_place_index<static_cast<size_t>(booleanValue)>, bool(false)) { }

    template <typename _Tp, typename = std::enable_if_t<_not_self<_Tp>>>
    // NOLINTNEXTLINE(google-explicit-constructor)
    constexpr Value(_Tp&& _arg)
        : _value(std::forward<_Tp>(_arg)) {}

    template <size_t _Np, typename... _Tp>
    constexpr explicit Value(std::in_place_index_t<_Np>, _Tp&&... _args)
        : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

    template <Tag _tag, typename... _Tp>
    static Value make(_Tp&&... _args) {
      return Value(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
    }

    template <Tag _tag, typename _Tp, typename... _Up>
    static Value make(std::initializer_list<_Tp> _il, _Up&&... _args) {
      return Value(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
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

    inline bool operator!=(const Value& rhs) const {
      return _value != rhs._value;
    }
    inline bool operator<(const Value& rhs) const {
      return _value < rhs._value;
    }
    inline bool operator<=(const Value& rhs) const {
      return _value <= rhs._value;
    }
    inline bool operator==(const Value& rhs) const {
      return _value == rhs._value;
    }
    inline bool operator>(const Value& rhs) const {
      return _value > rhs._value;
    }
    inline bool operator>=(const Value& rhs) const {
      return _value >= rhs._value;
    }

    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.PropertyValue.Value");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Value{";
      switch (getTag()) {
      case booleanValue: os << "booleanValue: " << ::android::internal::ToString(get<booleanValue>()); break;
      case byteValue: os << "byteValue: " << ::android::internal::ToString(get<byteValue>()); break;
      case charValue: os << "charValue: " << ::android::internal::ToString(get<charValue>()); break;
      case intValue: os << "intValue: " << ::android::internal::ToString(get<intValue>()); break;
      case longValue: os << "longValue: " << ::android::internal::ToString(get<longValue>()); break;
      case floatValue: os << "floatValue: " << ::android::internal::ToString(get<floatValue>()); break;
      case doubleValue: os << "doubleValue: " << ::android::internal::ToString(get<doubleValue>()); break;
      case stringValue: os << "stringValue: " << ::android::internal::ToString(get<stringValue>()); break;
      }
      os << "}";
      return os.str();
    }
  private:
    std::variant<bool, int8_t, char16_t, int32_t, int64_t, float, double, ::android::String16> _value;
  };  // class Value
  ::std::optional<::com::rdk::hal::PropertyValue::Value> value;
  inline bool operator!=(const PropertyValue& rhs) const {
    return std::tie(value) != std::tie(rhs.value);
  }
  inline bool operator<(const PropertyValue& rhs) const {
    return std::tie(value) < std::tie(rhs.value);
  }
  inline bool operator<=(const PropertyValue& rhs) const {
    return std::tie(value) <= std::tie(rhs.value);
  }
  inline bool operator==(const PropertyValue& rhs) const {
    return std::tie(value) == std::tie(rhs.value);
  }
  inline bool operator>(const PropertyValue& rhs) const {
    return std::tie(value) > std::tie(rhs.value);
  }
  inline bool operator>=(const PropertyValue& rhs) const {
    return std::tie(value) >= std::tie(rhs.value);
  }

  ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
  ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
  ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
  static const ::android::String16& getParcelableDescriptor() {
    static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.PropertyValue");
    return DESCIPTOR;
  }
  inline std::string toString() const {
    std::ostringstream os;
    os << "PropertyValue{";
    os << "value: " << ::android::internal::ToString(value);
    os << "}";
    return os.str();
  }
};  // class PropertyValue
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace com {
namespace rdk {
namespace hal {
[[nodiscard]] static inline std::string toString(PropertyValue::Value::Tag val) {
  switch(val) {
  case PropertyValue::Value::Tag::booleanValue:
    return "booleanValue";
  case PropertyValue::Value::Tag::byteValue:
    return "byteValue";
  case PropertyValue::Value::Tag::charValue:
    return "charValue";
  case PropertyValue::Value::Tag::intValue:
    return "intValue";
  case PropertyValue::Value::Tag::longValue:
    return "longValue";
  case PropertyValue::Value::Tag::floatValue:
    return "floatValue";
  case PropertyValue::Value::Tag::doubleValue:
    return "doubleValue";
  case PropertyValue::Value::Tag::stringValue:
    return "stringValue";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace hal
}  // namespace rdk
}  // namespace com
namespace android {
namespace internal {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
template <>
constexpr inline std::array<::com::rdk::hal::PropertyValue::Value::Tag, 8> enum_values<::com::rdk::hal::PropertyValue::Value::Tag> = {
  ::com::rdk::hal::PropertyValue::Value::Tag::booleanValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::byteValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::charValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::intValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::longValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::floatValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::doubleValue,
  ::com::rdk::hal::PropertyValue::Value::Tag::stringValue,
};
#pragma clang diagnostic pop
}  // namespace internal
}  // namespace android
