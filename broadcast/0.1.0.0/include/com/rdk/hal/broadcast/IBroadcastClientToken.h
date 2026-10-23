#pragma once

#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/Status.h>
#include <cstdint>
#include <string>
#include <utils/String16.h>
#include <utils/StrongPointer.h>

namespace com {
namespace rdk {
namespace hal {
namespace broadcast {
// @aidl-doc
/**
 * @brief Opaque token identifying a client that owns one or more claims.
 *
 * The token is implemented and hosted by the client, not by the service, which is what makes it useful: the service
 * receives a remote Binder proxy and can therefore link to its death. When the client process terminates, for any
 * reason, the service is notified and releases every claim made with that token.
 *
 * A client creates one token and passes the same instance to every claim-making call it makes, including resource
 * creation and exclusive acquisition. Apart from the diagnostic name below, the token carries no data; only its Binder
 * identity and lifetime are meaningful. The client must keep it alive for as long as it holds any claim.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
class IBroadcastClientToken : public ::android::IInterface {
public:
  DECLARE_META_INTERFACE(BroadcastClientToken)
  static const int32_t VERSION = 1000;
  const std::string HASH = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  static constexpr char* HASHVALUE = "2f7eb31eac1255b3a10532403a0bc61d536f9106";
  // @aidl-doc
  /**
   * @brief Get a human-readable name for the client, for diagnostic purposes only.
   *
   * Intended for logs, traces and diagnostic dumps, so that an operator can see which client holds a claim. It
   * exists to make use of the HAL observable, nothing more.
   *
   * The returned string has no semantics. An implementation shall not parse it, compare it, key any state on it, or
   * vary its behaviour according to its content. It is not an identity, not a capability and not an authorisation;
   * Binder identity and lifetime remain the only meaningful properties of the token. Any value is acceptable,
   * including an empty string, and a client is not required to return the same value on every call.
   *
   * @note This call runs in the opposite direction to the rest of this API - the service calls into the client - so
   * it is synchronous and can block or fail if the client is slow or has already terminated. An implementation
   * should call it only when producing diagnostics, never on a data or tuning path, and must treat a failure as
   * nothing more than a missing log label.
   *
   * @param[out] _aidl_return A human-readable name for the client, or an empty string if the client does not provide one.
   *
   * @returns ::android::binder::Status - ::android::binder::Status::EX_NONE on success.
   */
  virtual ::android::binder::Status getWhoAmI(::std::string* _aidl_return) = 0;
  virtual int32_t getInterfaceVersion() = 0;
  virtual std::string getInterfaceHash() = 0;
};  // class IBroadcastClientToken

class IBroadcastClientTokenDefault : public IBroadcastClientToken {
public:
  ::android::IBinder* onAsBinder() override {
    return nullptr;
  }
  ::android::binder::Status getWhoAmI(::std::string* /*_aidl_return*/) override {
    return ::android::binder::Status::fromStatusT(::android::UNKNOWN_TRANSACTION);
  }
  int32_t getInterfaceVersion() override {
    return 0;
  }
  std::string getInterfaceHash() override {
    return "";
  }
};  // class IBroadcastClientTokenDefault
}  // namespace broadcast
}  // namespace hal
}  // namespace rdk
}  // namespace com
