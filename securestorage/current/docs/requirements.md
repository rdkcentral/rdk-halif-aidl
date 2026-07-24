# SecureStorage HAL — Requirements

The SecureStorage HAL provides tamper-evident, generational storage for
provisioned device data — values that are written once (or rotated) at
provisioning time and must be read back intact for the life of the device. Its
canonical payloads are the device ESN and other clear provisioning data (device
certificates carried as data, provisioned configuration) that an authorised
service or application reads but must never be able to forge or roll back.

The guarantee SecureStorage provides is **integrity**, not confidentiality: a
stored item is readable in the clear by an authorised caller, and what the
platform enforces is that the item was written at provisioning and cannot be
tampered with or reverted afterwards.

## Position in the architecture

SecureStorage sits **beside** the KeyVault and CryptoEngine HALs, not above them.
It depends on neither: clear provisioning data needs no key and no crypto, so
the store is a flat peer of the other two rather than a layer built on them.

| HAL | Plane | Primary guarantee | Depends on |
|-----|-------|-------------------|------------|
| CryptoEngine | key **use** (operations) | operations run in the secure environment | — |
| KeyVault | key **management** (storage, lifecycle) | key material never leaves the secure environment | CryptoEngine |
| **SecureStorage** | **provisioned-data storage** | **write-once / anti-rollback integrity of clear data** | — |

The division of responsibility is strict:

- **Secret key material** (device AES/HMAC keys such as Kde/Kdh, wrapping keys,
  signing keys) is provisioned and held in the **KeyVault** HAL. SecureStorage
  never holds key material.
- **Clear provisioned data** (ESN, device identifiers, certificate bytes,
  provisioned config) is held in **SecureStorage**.
- **Confidential-at-rest application data** (device-bound blobs a caller wants
  encrypted) is not a SecureStorage responsibility. Confidentiality is obtained
  by layering: a KeyVault key + a CryptoEngine AEAD operation + an ordinary
  file, above these HALs.

A single provisioning partition may back both KeyVault and SecureStorage on a
given platform; that is an implementation detail of the backing store and is not
visible in the interface.

## Prior art

The split above follows established secure-platform practice, where keys and
arbitrary provisioned data are distinct services unified only by a common access
gate:

- **Android** keeps keys in **KeyMint** (non-exportable, TEE/StrongBox
  operations) and puts write-once / rollback-resistant data in separate
  services — **Trusty secure storage** (RPMB-backed, anti-rollback),
  **Weaver/Gatekeeper** (rollback-resistant counters). Arbitrary confidential
  app data is a **library** (Jetpack Security) layered over KeyMint, not a HAL.
- **HashiCorp Vault** exposes keys through the **Transit** engine
  (non-exportable unless explicitly `exportable`) and arbitrary values through
  the **KV** engine — distinct engines, unified by one auth/policy/path layer.
  Its **KV v2** engine versions every value; re-writing a secret creates a new
  version rather than mutating in place.

Both draw the same two conclusions this HAL adopts: separate the storage
**semantics** (keys vs provisioned data) into distinct interfaces, unify
**access** in a broker above them, and version stored values from the start.

## Functional overview

Two interface layers, mirroring the KeyVault shape so callers reuse one mental
model:

| Interface | Role |
|-----------|------|
| `ISecureStorage` | Top-level manager. Enumerates stores, opens sessions. |
| `ISecureStorageController` | Per-session controller. Item read/write, generation access, introspection. |
| `ISecureStorageEventListener` | Asynchronous callbacks for store state changes and item invalidation. |

Access is gated **before** the HAL, by the same RDK Crypto Service broker that
gates KeyVault: it resolves the caller's verified identity (AppArmor label +
Binder UID) against a per-store access policy and only then forwards `open()`.
The store **name** is the access unit; whether a store is single-owner or shared
across clients is a policy attribute of the store, independent of its contents.

## Implementation Requirements

| # | Requirement | Comments |
|---|-------------|----------|
| HAL.SS.1 | The service shall register with Binder Service Manager using the service name `SecureStorage`. | Defined as `ISecureStorage.serviceName`. |
| HAL.SS.2 | Platform-provisioned stores shall be available immediately after service startup. | Declared in the HFP `stores` section. |
| HAL.SS.3 | Stored items shall be clear (or caller-opaque) byte values readable by an authorised caller. The HAL guarantees integrity, not confidentiality. | Distinguishes SecureStorage from KeyVault, whose items are unreadable by default. |
| HAL.SS.4 | The HAL shall not store secret key material. Keys are provisioned and held in the KeyVault HAL. | Enforces the key/data boundary. |
| HAL.SS.5 | Every item shall carry a monotonically increasing **generation**. A re-provision or rotation shall create a new generation; item values shall never be mutated in place. | Versioning is a day-one property, following Vault KV v2. |
| HAL.SS.6 | A read shall return the current generation by default; a specific retained prior generation may be requested where the store's retention policy keeps it. | `get()` vs `getAt(key, generation)`. Retention depth is a store capability. |
| HAL.SS.7 | The item and its generation shall be tamper-evident and rollback-resistant; a forced or replayed older generation shall be detectable and rejected. | Backed by RPMB, a monotonic counter, or an equivalent secure partition — the property that cannot be reconstructed above KeyVault + CryptoEngine. |
| HAL.SS.8 | Each item shall declare a write policy: `WRITE_ONCE`, `VERSIONED`, or `MUTABLE`. | Factory identifiers (ESN) are `WRITE_ONCE`; rotatable certs are `VERSIONED`. |
| HAL.SS.9 | A `WRITE_ONCE` item shall be writable only into an empty slot; once populated it shall be immutable and non-deletable through the runtime API. | A write to an already-populated `WRITE_ONCE` item returns `EX_SECURITY` / `EX_ILLEGAL_STATE`. Its value changes only after the underlying store is cleared or replaced by out-of-band service tooling (HAL.SS.14), which empties the slot. |
| HAL.SS.14 | Refurbishment is performed by 3rd-party service-centre tooling that is outside HAL scope. The HAL shall neither define nor expose an erase or re-provision operation. Its sole obligation is to *support* refurbishment: once the tooling has cleared or replaced the underlying store, empty slots shall accept provisioning through the ordinary write path (HAL.SS.8), identically to first-time provisioning. | Service tooling — reprogramming the flash in place, or physically replacing it — is 3rd-party controlled and out of scope. Being empty is the trigger; there is no HAL erase verb and no distinct re-provision step. |
| HAL.SS.10 | Store access shall be gated on the caller's verified identity by the RDK Crypto Service before any call reaches the HAL. A store's access mode (single-owner or shared) shall be declared in the HFP. | Same gate as KeyVault; identity never enters the HAL. |
| HAL.SS.11 | The store shall advertise its security level, integrity-backing type, maximum item size, capacity, and generation-retention depth via `getCapabilities()`, and reject any request exceeding them. | Not all platforms provide the same integrity backing. |
| HAL.SS.12 | On deep sleep the HAL is closed; on resume it is reopened and persistent stores re-initialise and re-validate integrity. | Callers check `getState()` after `open()`, as with KeyVault. |
| HAL.SS.13 | `flush()` shall persist all pending writes and re-establish the integrity authenticator over the store. | Write failure returns `EX_SERVICE_SPECIFIC`. |

## Data model

`ItemDescriptor` (metadata only; the value is fetched separately):

| Field | Meaning |
|-------|---------|
| `key` | Item name within the store. |
| `sizeInBytes` | Size of the current-generation value. |
| `generation` | Per-item counter, incremented when a `VERSIONED` item is rotated. A `WRITE_ONCE` item stays at generation 1. |
| `writePolicy` | `WRITE_ONCE` \| `VERSIONED` \| `MUTABLE`. |
| `integrityProtected` | Whether the item is covered by the store's anti-rollback authenticator. |
| `createdAtMs` / `updatedAtMs` | Provisioning and last-write timestamps. |

Two independent counters carry the anti-rollback signal, at different scopes:

- **Per-item `generation`** — advances when a `VERSIONED` item is rotated in the
  field (e.g. a provisioned certificate). Prior values are retained up to the
  store's retention depth, so a reader can pin a known generation and an
  attacker cannot silently substitute an older one. `WRITE_ONCE` items never
  rotate, so their generation is fixed.
- **Store `provisioningEpoch`** — anchored in the platform's OTP monotonic
  counter, not in the flash-resident store, so it survives a flash replacement
  (HAL.SS.14). It distinguishes one provisioning of the device from the next;
  data from a prior epoch — or from another device — cannot be rolled in.

Both are present from the first interface version rather than retrofitted.

## Refurbishment / re-provisioning

Refurbishment is wholesale, not incremental, and its tooling is **3rd-party
controlled and out of HAL scope**. A service centre takes one of two paths, and
in both the HAL's role is identical — it sees an empty store and provisions into
it through the ordinary write path (HAL.SS.8, HAL.SS.14):

- **Reprogram in place** — the tooling clears the flash-resident store. The
  slots go empty; provisioning writes fresh values.
- **Replace the flash** — the store hardware is physically swapped. The new
  flash arrives empty (or foreign); provisioning writes fresh values.

The HAL neither performs nor observes the clear/replace step and exposes no verb
for it. Two properties make it *support* both paths safely:

- **Empty is the only trigger.** A `WRITE_ONCE` slot accepts a write exactly
  when it is empty, so first-time provisioning and post-refurbishment
  provisioning are the same operation. The field never mutates a populated
  `WRITE_ONCE` item in place.
- **Device binding.** Replacement or foreign flash is inert until it is
  provisioned against *this* box's OTP root. A store carrying another device's
  provisioning cannot be dropped in and used, and the OTP-anchored provisioning
  epoch prevents rolling a prior provisioning back over the current one.

## Proposed interface surface

Requirements-level sketch, to be refined during interface definition:

```java
interface ISecureStorage {
    const @utf8InCpp String serviceName = "SecureStorage";
    @utf8InCpp String[] getStoreNames();
    SecurityLevel getSecurityLevel(in @utf8InCpp String storeName);
    @nullable ISecureStorageController open(in @utf8InCpp String storeName,
                                            in @nullable ISecureStorageEventListener listener);
    boolean close(in ISecureStorageController controller);
}

interface ISecureStorageController {
    StorageCapabilities getCapabilities();
    StorageState        getState();

    ItemDescriptor put(in @utf8InCpp String key, in byte[] value);   // new generation
    byte[]         get(in @utf8InCpp String key);                    // current generation
    byte[]         getAt(in @utf8InCpp String key, in int generation);
    ItemDescriptor[] list();
    @nullable ItemDescriptor getInfo(in @utf8InCpp String key);
    void           deleteItem(in @utf8InCpp String key);             // policy-gated
    void           flush();
}
```

There is no erase or re-provision verb on the interface. Clearing or replacing
the store is 3rd-party service tooling, out of HAL scope (HAL.SS.14);
provisioning — first-time or post-refurbishment — is the ordinary `put()` into
an empty slot.

## Product customization (HFP)

Platform vendors declare stores and their provisioned items in a HAL Feature
Profile (`hfp-securestorage.yaml`), mirroring `hfp-keyvault.yaml`:

```yaml
securestorage:
  interfaceVersion: current
  stores:
    - name: "device-provisioning"
      description: "Factory-provisioned device identity data"
      securityLevel: TEE
      integrityBacking: RPMB
      accessMode: shared             # readable by authorised services
      persistsAcrossSleep: true
      generationRetention: 2
      items:
        - key: "ESN"
          writePolicy: WRITE_ONCE
        - key: "device-cert"
          writePolicy: VERSIONED
```

## Open boundary decision

One division is still to be confirmed with the provisioning chain: whether the
device secret keys (**Kde/Kdh**) are provisioned into a **KeyVault** instance
(the position these requirements take — keys belong in KeyVault, reachable via
`importWrappedKey` / boot derivation) or whether the provisioning partition is a
SecureStorage object that KeyVault reads at boot. These requirements assume the
former: **SecureStorage holds the clear ESN and non-key provisioned data;
KeyVault holds Kde/Kdh.** If the provisioning flow dictates otherwise, HAL.SS.4
is the requirement to revisit.
