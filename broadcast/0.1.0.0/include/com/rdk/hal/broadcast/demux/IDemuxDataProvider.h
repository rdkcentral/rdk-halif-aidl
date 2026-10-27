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
 * @brief Polymorphic base interface for components that can feed data to a demux.
 *
 * This can be used to connect a frontend or a software input to a demux, in a platform-specific way. There is no need
 * for it in the API itself, but it can be used to implement additional functionality needed to facilitate the
 * connection between frontend and demux.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 *
 * @see IDemux.connect()
 * @see IFrontend.acquireDataProvider()
 * @see IDemuxSoftwareInput.acquireDataProvider()
 */
class IDemuxDataProvider : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(DemuxDataProvider)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IDemuxDataProvider

class IDemuxDataProviderDefault : public IDemuxDataProvider {
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
};  // class IDemuxDataProviderDefault
}  // namespace demux
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
