// EXAMPLE - middleware side: find the vendor's HAL service and call it. A sketch
// of the include/link contract plus the version-gating pattern.
//
// Built against, from the rdk-halif-aidl-avclock + -common packages:
//   -I${STAGING_INCDIR}/rdk-halif-aidl/avclock/0.2.0.1/include
//   -L${STAGING_LIBDIR}/rdk-halif-aidl -lavclock-v0.2.0.1-cpp
//
// Client and server link the SAME interface library - the role difference is
// what the code does with it, not how it builds.
#include <com/rdk/hal/avclock/IAVClock.h>

#include <binder/IServiceManager.h>
#include <utils/StrongPointer.h>

#include <cstdint>

using ::com::rdk::hal::avclock::IAVClock;

int main() {
    ::android::sp<::android::IBinder> binder =
        ::android::defaultServiceManager()->getService(
            ::android::String16("com.rdk.hal.avclock.IAVClock"));

    ::android::sp<IAVClock> avclock = ::android::interface_cast<IAVClock>(binder);
    if (avclock == nullptr) {
        return 1;   // the vendor implementation is not running
    }

    // Linking 0.2.0.1 headers does not guarantee the SERVER is that new. Ask it,
    // and gate newer calls on the answer rather than assuming - see
    // docs/standards/client-patterns.md.
    int32_t serverVersion = 0;
    avclock->getInterfaceVersion(&serverVersion);
    // if (serverVersion >= 2) { ...safe to call methods introduced in v2... }

    return 0;
}
