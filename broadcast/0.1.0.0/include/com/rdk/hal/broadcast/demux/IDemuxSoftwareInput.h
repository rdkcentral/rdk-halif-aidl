#pragma once

#include <android/binder_to_string.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/Status.h>
#include <com/rdk/hal/broadcast/demux/IDemuxDataProvider.h>
#include <com/rdk/hal/broadcast/demux/IDemuxSoftwareInput.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSink.h>
#include <com/rdk/hal/ringbuffer/IRingBufferSinkListener.h>
#include <cstdint>
#include <optional>
#include <tuple>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
class IDemuxSoftwareInput : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DemuxSoftwareInput)
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
      static const ::android::StaticString16 DESCIPTOR (u"com.rdk.hal.broadcast.demux.IDemuxSoftwareInput.Id");
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
  virtual ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* _aidl_return) = 0;
  virtual ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& listener, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* _aidl_return) = 0;
  virtual ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& bufferSink) = 0;
  virtual ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* _aidl_return) = 0;
  virtual ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& provider) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemuxSoftwareInput

class IDemuxSoftwareInputDefault : public IDemuxSoftwareInput {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getId(::com::rdk::hal::broadcast::demux::IDemuxSoftwareInput::Id* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status openForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSinkListener>& /*listener*/, ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status closeForWriting(const ::android::sp<::com::rdk::hal::ringbuffer::IRingBufferSink>& /*bufferSink*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status acquireDataProvider(::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  ::android::binder::Status releaseDataProvider(const ::android::sp<::com::rdk::hal::broadcast::demux::IDemuxDataProvider>& /*provider*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IDemuxSoftwareInputDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
