# CI-ONLY relaxation — do NOT copy into a real consumer recipe.
#
# The stub linux-binder stages a Binder SDK built for the HOST (glibc 2.38), not
# cross-built for the kirkstone target. That is enough to:
#   - build the HAL's shared libraries (a .so defers symbol resolution), and
#   - prove THIS consumer's own references resolve against the staged HAL + binder
#     API (IHdmiCec, PropertyValue, BBinder, String16, Status all link).
#
# But a full target EXECUTABLE link also drags in libbinder.so's transitive
# closure (libbase/liblog/libcutils) and host-libc-versioned symbols
# (…@GLIBC_2.38, …@GLIBCXX_3.4.32) that the kirkstone sysroot does not provide.
# On a real RDK target the real linux-binder is cross-built for the target and
# these resolve normally — this gap exists ONLY because the CI stub is host-ABI.
#
# --allow-shlib-undefined lets the executable link by deferring symbols that are
# undefined *inside the shared libraries* to their runtime provider, while STILL
# requiring this recipe's own references to resolve. So the staging + link proof
# stays meaningful: if the HAL were mis-staged, the consumer's own symbols would
# still fail here.
LDFLAGS:append = " -Wl,--allow-shlib-undefined"
