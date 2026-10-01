// Touches a symbol defined in libhdmicec-v0.1.0.0-cpp (IMPLEMENT_META_INTERFACE),
// so a successful link proves the library, not only the headers, was found.
#include <com/rdk/hal/hdmicec/IHdmiCec.h>
#include <cstdio>

int main() {
    const auto& d = com::rdk::hal::hdmicec::IHdmiCec::descriptor;
    std::printf("%s\n", android::String8(d).c_str());
    return 0;
}
