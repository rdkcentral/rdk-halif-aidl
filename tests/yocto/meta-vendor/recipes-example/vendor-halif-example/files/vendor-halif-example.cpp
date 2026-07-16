// EXAMPLE - vendor side: implement an RDK HAL AIDL interface and register it so
// middleware can find it. A sketch of the include/link contract, not a working
// HAL: the method overrides are left to the real implementation.
//
// Built against, from the rdk-halif-aidl-hdmicec + -common packages:
//   -I${STAGING_INCDIR}/rdk-halif-aidl/hdmicec/0.1.0.0/include
//   -L${STAGING_LIBDIR}/rdk-halif-aidl -lhdmicec-v0.1.0.0-cpp
//
// The include path above is what makes this namespace path resolvable:
#include <com/rdk/hal/hdmicec/BnHdmiCec.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/StrongPointer.h>

using ::com::rdk::hal::hdmicec::BnHdmiCec;

// The vendor implementation subclasses the generated Bn<Interface> server stub
// and overrides the methods declared in the .aidl. Each returns
// ::android::binder::Status.
class VendorHdmiCec : public BnHdmiCec {
    // ::android::binder::Status open(...) override { ... }
    // ::android::binder::Status close(...) override { ... }
};

int main() {
    ::android::sp<VendorHdmiCec> hal = new VendorHdmiCec();

    // Register under the interface's well-known name so clients can look it up.
    ::android::defaultServiceManager()->addService(
        ::android::String16("com.rdk.hal.hdmicec.IHdmiCec"), hal);

    ::android::ProcessState::self()->startThreadPool();
    ::android::IPCThreadState::self()->joinThreadPool();
    return 0;
}
