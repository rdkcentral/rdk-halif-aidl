/*
 * If not stated otherwise in this file or this component's LICENSE file the following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
 * an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
 * specific language governing permissions and limitations under the License.
 */
package com.rdk.hal.broadcast;

/**
 * @brief Opaque token identifying the client that owns an exclusive claim.
 *
 * The token is implemented and hosted by the client, not by the service, which is what makes it useful: the service
 * receives a remote Binder proxy and can therefore link to its death. When the client process terminates, for any
 * reason, the service is notified and releases every claim made with that token.
 *
 * A client creates one token and passes the same instance to every acquiring call it makes. Apart from the diagnostic
 * name below, the token carries no data; only its Binder identity and lifetime are meaningful. The client must keep it
 * alive for as long as it holds any claim.
 *
 * @author Jan Pedersen
 * @author Christian George
 * @author Philipp Trommler
 */
@VintfStability
interface IBroadcastClientToken {
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
     * @returns A human-readable name for the client, or an empty string if the client does not provide one.
     */
    @utf8InCpp String getWhoAmI();
}
