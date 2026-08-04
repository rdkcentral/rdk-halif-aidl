/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2026 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.rdk.hal.metrics;
import com.rdk.hal.metrics.MetricKind;
import com.rdk.hal.metrics.MetricUnit;

/**
 *  @brief     What one declared field is — enough to interpret the number
 *             without consulting anything else at runtime.
 *
 *  <h3>Two contracts, one declaration</h3>
 *  A profile states one field once, and that statement is read by two audiences.
 *
 *  The DECLARATION contract is what a vendor implements against and what a test
 *  asserts: every key in the profile, prose included. It is consumed at build time, by
 *  people and by test suites, and it lives in the profile and the reference documents
 *  generated from it.
 *
 *  The RUNTIME contract is this parcelable: what a consumer needs in order to read a
 *  number correctly. It carries the field's identity, what the number counts, what
 *  arithmetic is valid on it, whether it can be written, and the id that detects any
 *  of those changing underneath a name.
 *
 *  The runtime contract is the smaller one deliberately. It is returned per field, per
 *  source, and a device declaring 45 fields carries roughly 8 KB of prose if the
 *  declaration's descriptions ride along - repeated on every source, to say something
 *  fixed that no consumer computes with. Prose belongs where it is read.
 *
 *  Provenance is the same case. Whether a figure is measured or computed changes what
 *  a consumer may do with it, so it is carried - as MetricDomainInfo.derived, once per
 *  domain, because derivation is a property of the domain. Which inputs a computed
 *  figure was derived from does not change how it is read, and stays in the profile.
 */
@VintfStability
parcelable MetricFieldInfo
{
    /** Field name within its element, e.g. "frames_decoded". */
    String name;

    /** What the number counts. */
    MetricUnit unit;

    /** How the value behaves over time, and so what arithmetic is valid on it. */
    MetricKind kind;

    /** True when setField() is accepted on this field. */
    boolean writable;

    /**
     *  Content-derived identity of this field's contract: the first 8 bytes of
     *  SHA-256 over "<domain>.<element>.<field>|<unit>|<kind>", carried as the
     *  BIT PATTERN of those 8 bytes big-endian. Roughly half of all ids have the top
     *  bit set and therefore arrive negative; a consumer compares the 64 bits, never
     *  the signed magnitude. The declaration writes the same value as an unsigned
     *  0x-prefixed 16-digit literal.
     *
     *  A consumer compares this against the id it was built with. Matching
     *  names are not enough on their own - a product that serves
     *  decode_latency_sum_us but populates milliseconds still matches by name,
     *  and the consumer reports figures a thousand times wrong; a CURRENT
     *  sample reclassified as a COUNTER gets differenced and produces
     *  nonsense. Both change the id, so both become a hard mismatch here
     *  instead of a wrong number downstream.
     *
     *  Nothing allocates it, so it needs no registry: the same id means the
     *  same name, unit and kind, which is the same field.
     */
    long id;
}
