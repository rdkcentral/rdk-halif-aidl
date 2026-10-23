#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
namespace demux {
// @aidl-doc
/**
 * @brief MPEG-2 TS audio filter interface for tunneled pipelines.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IAudioFilter : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(AudioFilter)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IAudioFilter

class IAudioFilterDefault : public IAudioFilter {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IAudioFilterDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
