#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/frontend/FrontendCapabilities.h>
#include <com/rdk/hal/broadcast/frontend/FrontendType.h>
#include <com/rdk/hal/broadcast/frontend/IFrontend.h>
#include <com/rdk/hal/broadcast/frontend/IFrontendController.h>
#include <com/rdk/hal/broadcast/frontend/ILnbController.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>
#include <vector>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace frontend {
class IFrontend : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(Frontend)
  static const int32_t VERSION = 1;
  const std::string HASH = "notfrozen";
  static constexpr char* HASHVALUE = "notfrozen";
  class Id : public ::android::Parcelable {
  public:
    int32_t value = 0;
    inline bool operator!=(const Id& rhs) const {
      return std::tie(value) != std::tie(rhs.value);
    }
    inline bool operator<(const Id& rhs) const {
      return std::tie(value) < std::tie(rhs.value);
    }
    inline bool operator<=(const Id& rhs) const {
      return std::tie(value) <= std::tie(rhs.value);
    }
    inline bool operator==(const Id& rhs) const {
      return std::tie(value) == std::tie(rhs.value);
    }
    inline bool operator>(const Id& rhs) const {
      return std::tie(value) > std::tie(rhs.value);
    }
    inline bool operator>=(const Id& rhs) const {
      return std::tie(value) >= std::tie(rhs.value);
    }

    enum : int32_t { UNDEFINED = -1 };
    ::android::Parcelable::Stability getStability() const override { return ::android::Parcelable::Stability::STABILITY_VINTF; }
    ::android::status_t readFromParcel(const ::android::Parcel* _aidl_parcel) final;
    ::android::status_t writeToParcel(::android::Parcel* _aidl_parcel) const final;
    static const ::android::String16& getParcelableDescriptor() {
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.frontend.IFrontend.Id");
      return DESCIPTOR;
    }
    inline std::string toString() const {
      std::ostringstream os;
      os << "Id{";
      os << "value: " << ::android::internal::ToString(value);
      os << "}";
      return os.str();
    }
  };  // class Id
  virtual ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* _aidl_return) = 0;
  virtual ::android::binder::Status isOpen(bool* _aidl_return) = 0;
  virtual ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* _aidl_return) = 0;
  virtual ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType frontendType, ::std::optional<::com::rdk::hal::broadcast::frontend::FrontendCapabilities>* _aidl_return) = 0;
  virtual ::android::binder::Status open(::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* _aidl_return) = 0;
  virtual ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& controller) = 0;
  virtual ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) = 0;
  virtual ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) = 0;
  virtual ::android::binder::Status openLnb(::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* _aidl_return) = 0;
  virtual ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& controller) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IFrontend

class IFrontendDefault : public IFrontend {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(::com::rdk::hal::broadcast::frontend::IFrontend::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status isOpen(bool* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getFrontendTypes(::std::vector<::com::rdk::hal::broadcast::frontend::FrontendType>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status getCapabilities(::com::rdk::hal::broadcast::frontend::FrontendType /*frontendType*/, ::std::optional<::com::rdk::hal::broadcast::frontend::FrontendCapabilities>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status open(::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status close(const ::android::sp<::com::rdk::hal::broadcast::frontend::IFrontendController>& /*controller*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& /*provider*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openLnb(::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeLnb(const ::android::sp<::com::rdk::hal::broadcast::frontend::ILnbController>& /*controller*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IFrontendDefault
}  // namespace frontend
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
