// EXAMPLE - vendor side: implement an RDK HAL AIDL interface and register it so
// middleware can find it.
//
// This is a REAL, COMPILING skeleton, not pseudo-code - tests/yocto/ci/
// yocto_example_check.sh compiles it against the actual interface libraries, so
// it stays honest. The method bodies are stubs (a real HAL drives hardware
// here), but the shape is exactly what a vendor implementation looks like.
//
// Built against the staged HAL on the vendor mount, plus the Binder SDK:
//   -I<sysroot>/vendor/rdk-halif-aidl/include/hdmicec/0.1.0.0/include -I<sysroot>/usr/include/binder_sdk
//   -L<sysroot>/vendor/rdk-halif-aidl -lhdmicec-v0.1.0.0-cpp -lcommon-v0.2.0.0-cpp
//   -L<sysroot>/usr/lib/binder -lbinder -lutils
// (see vendor-halif-example.bb for the recipe form using ${HALIF_STAGED} etc.)
//
// The include path above is what makes this namespace path resolvable:
#include <com/rdk/hal/hdmicec/BnHdmiCec.h>

#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <utils/StrongPointer.h>

#include <cstdint>
#include <optional>
#include <vector>

using ::android::binder::Status;
using ::com::rdk::hal::PropertyValue;
using ::com::rdk::hal::hdmicec::BnHdmiCec;
using ::com::rdk::hal::hdmicec::IHdmiCecController;
using ::com::rdk::hal::hdmicec::IHdmiCecEventListener;
using ::com::rdk::hal::hdmicec::Property;
using ::com::rdk::hal::hdmicec::State;

// A vendor implementation subclasses the generated Bn<Interface> server stub and
// overrides every method the .aidl declares. getInterfaceVersion() and
// getInterfaceHash() come from BnHdmiCec - do NOT reimplement them; they are what
// lets a client version-gate its calls.
class VendorHdmiCec : public BnHdmiCec {
public:
    Status getState(State* _aidl_return) override {
        *_aidl_return = State::CLOSED;      // a real HAL reports actual state
        return Status::ok();
    }

    Status getProperty(Property /*property*/,
                       std::optional<PropertyValue>* _aidl_return) override {
        *_aidl_return = std::nullopt;       // property not supported by this stub
        return Status::ok();
    }

    Status getLogicalAddresses(std::vector<int32_t>* _aidl_return) override {
        _aidl_return->clear();              // a real HAL returns the CEC addresses
        return Status::ok();
    }

    Status open(const ::android::sp<IHdmiCecEventListener>& /*listener*/,
                ::android::sp<IHdmiCecController>* _aidl_return) override {
        *_aidl_return = nullptr;            // a real HAL returns its controller
        return Status::ok();
    }

    Status close(const ::android::sp<IHdmiCecController>& /*controller*/,
                 bool* _aidl_return) override {
        *_aidl_return = true;
        return Status::ok();
    }

    Status registerEventListener(const ::android::sp<IHdmiCecEventListener>& /*l*/,
                                 bool* _aidl_return) override {
        *_aidl_return = true;
        return Status::ok();
    }

    Status unregisterEventListener(const ::android::sp<IHdmiCecEventListener>& /*l*/,
                                   bool* _aidl_return) override {
        *_aidl_return = true;
        return Status::ok();
    }
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
