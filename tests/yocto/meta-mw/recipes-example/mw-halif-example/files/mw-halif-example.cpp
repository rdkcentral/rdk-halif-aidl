// EXAMPLE - middleware side: find the vendor's HAL service and call it. A sketch
// of the include/link contract plus the version-gating pattern.
//
// Built against the staged HAL on the mw mount, plus the Binder SDK:
//   -I<sysroot>/mw/rdk-halif-aidl/include/avclock/0.2.0.1/include -I<sysroot>/usr/include/binder_sdk
//   -L<sysroot>/mw/rdk-halif-aidl -lavclock-v0.2.0.1-cpp -lcommon-v0.2.0.0-cpp
//   -L<sysroot>/usr/lib/binder -lbinder -lutils
// (see mw-halif-example.bb for the recipe form using ${HALIF_STAGED} etc.)
//
// Client and server link the SAME interface library - the role difference is
// what the code does with it, not how it builds.
#include <com/rdk/hal/avclock/IAVClockManager.h>

#include <binder/IServiceManager.h>
#include <utils/StrongPointer.h>

#include <cstdint>

using ::com::rdk::hal::avclock::IAVClockManager;

int main() {
    // IAVClockManager is the registered SERVICE (an IAVClock is obtained from it;
    // IAVClock has no serviceName() of its own). Look it up under its published
    // serviceName() - the same name halcompat.h getService<IAVClockManager>() uses -
    // not a hard-coded descriptor string, which would miss the service.
    ::android::sp<::android::IBinder> binder =
        ::android::defaultServiceManager()->getService(
            ::android::String16(IAVClockManager::serviceName().c_str()));

    ::android::sp<IAVClockManager> manager = ::android::interface_cast<IAVClockManager>(binder);
    if (manager == nullptr) {
        return 1;   // the vendor implementation is not running
    }

    // Linking 0.2.0.1 headers does not guarantee the SERVER is that new. Ask it,
    // and gate newer calls on the answer rather than assuming - see
    // docs/standards/client-patterns.md. The generated C++ returns the version
    // directly (it is not an out-parameter).
    int32_t serverVersion = manager->getInterfaceVersion();
    (void)serverVersion;
    // if (serverVersion >= 2) { ...safe to call methods introduced in v2... }

    return 0;
}
