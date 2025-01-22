Linux Binder Output
===========================

Following are the binaries, libraries and header files installed as part of Linux Binder with example.

      /usr/
        ├── bin
        │   ├── servicemanager
        │   ├── FWManagerService
        │   ├── FWManagerClient
        │   └── binder-device
        ├── lib
        │   ├── libbase.so
        │   ├── libbinder.so
        │   ├── libcutils.so
        │   ├── libcutils_sockets.so
        │   ├── liblog.so
        │   ├── libutils.so
        │   └── libfwmanager.so
        └── include
           ├── android
           │   ├── binder_auto_utils.h
           │   ├── binder_enums.h
           │   ├── binder_interface_utils.h
           │   ├── binder_internal_logging.h
           │   ├── binder_parcelable_utils.h
           │   ├── binder_parcel_utils.h
           │   ├── binder_to_string.h
           │   └── log.h
           ├── android-base
           │   ├── chrono_utils.h
           │   ├── cmsg.h
           │   ├── collections.h
           │   ├── endian.h
           │   ├── errno_restorer.h
           │   ├── errors.h
           │   ├── expected.h
           │   ├── file.h
           │   ├── format.h
           │   ├── function_ref.h
           │   ├── hex.h
           │   ├── logging.h
           │   ├── macros.h
           │   ├── mapped_file.h
           │   ├── memory.h
           │   ├── no_destructor.h
           │   ├── off64_t.h
           │   ├── parsebool.h
           │   ├── parsedouble.h
           │   ├── parseint.h
           │   ├── parsenetaddress.h
           │   ├── process.h
           │   ├── properties.h
           │   ├── result-gmock.h
           │   ├── result.h
           │   ├── scopeguard.h
           │   ├── silent_death_test.h
           │   ├── stringprintf.h
           │   ├── strings.h
           │   ├── test_utils.h
           │   ├── thread_annotations.h
           │   ├── threads.h
           │   ├── unique_fd.h
           │   └── utf8.h
           ├── binder
           │   ├── Binder.h
           │   ├── BinderService.h
           │   ├── BpBinder.h
           │   ├── Enums.h
           │   ├── IBinder.h
           │   ├── IInterface.h
           │   ├── IMemory.h
           │   ├── IPCThreadState.h
           │   ├── IPermissionController.h
           │   ├── IResultReceiver.h
           │   ├── IServiceManager.h
           │   ├── IShellCallback.h
           │   ├── LazyServiceRegistrar.h
           │   ├── MemoryBase.h
           │   ├── MemoryDealer.h
           │   ├── MemoryHeapBase.h
           │   ├── Parcelable.h
           │   ├── ParcelableHolder.h
           │   ├── ParcelFileDescriptor.h
           │   ├── Parcel.h
           │   ├── PermissionCache.h
           │   ├── PermissionController.h
           │   ├── PersistableBundle.h
           │   ├── ProcessState.h
           │   ├── RpcCertificateFormat.h
           │   ├── RpcKeyFormat.h
           │   ├── RpcServer.h
           │   ├── RpcSession.h
           │   ├── RpcTransport.h
           │   ├── RpcTransportRaw.h
           │   ├── SafeInterface.h
           │   ├── Stability.h
           │   ├── Status.h
           │   └── TextOutput.h
           ├── cutils
           │   ├── android_filesystem_config.h -> ../private/android_filesystem_config.h
           │   ├── android_get_control_file.h
           │   ├── android_reboot.h
           │   ├── ashmem.h
           │   ├── atomic.h
           │   ├── bitops.h
           │   ├── compiler.h
           │   ├── config_utils.h
           │   ├── fs.h
           │   ├── hashmap.h
           │   ├── iosched_policy.h
           │   ├── klog.h
           │   ├── list.h
           │   ├── log.h
           │   ├── memory.h
           │   ├── misc.h
           │   ├── multiuser.h
           │   ├── native_handle.h
           │   ├── partition_utils.h
           │   ├── properties.h
           │   ├── qtaguid.h
           │   ├── record_stream.h
           │   ├── sched_policy.h
           │   ├── sockets.h
           │   ├── str_parms.h
           │   ├── threads.h
           │   ├── trace.h
           │   └── uevent.h
           ├── log
           │   ├── event_tag_map.h
           │   ├── log_event_list.h
           │   ├── log.h
           │   ├── log_id.h
           │   ├── log_main.h
           │   ├── logprint.h
           │   ├── log_properties.h
           │   ├── log_radio.h
           │   ├── log_read.h
           │   ├── log_safetynet.h
           │   ├── log_system.h
           │   └── log_time.h
           └── utils
               ├── AndroidThreads.h
               ├── Atomic.h
               ├── BitSet.h
               ├── ByteOrder.h
               ├── CallStack.h
               ├── Compat.h
               ├── Condition.h
               ├── Debug.h
               ├── Endian.h
               ├── Errors.h
               ├── ErrorsMacros.h
               ├── FastStrcmp.h
               ├── FileMap.h
               ├── Flattenable.h
               ├── Functor.h
               ├── JenkinsHash.h
               ├── KeyedVector.h
               ├── LightRefBase.h
               ├── List.h
               ├── Log.h
               ├── Looper.h
               ├── LruCache.h
               ├── misc.h
               ├── Mutex.h
               ├── NativeHandle.h
               ├── Printer.h
               ├── ProcessCallStack.h
               ├── RefBase.h
               ├── RWLock.h
               ├── Singleton.h
               ├── SortedVector.h
               ├── StopWatch.h
               ├── String16.h
               ├── String8.h
               ├── StrongPointer.h
               ├── SystemClock.h
               ├── ThreadDefs.h
               ├── Thread.h
               ├── threads.h
               ├── Timers.h
               ├── Tokenizer.h
               ├── Trace.h
               ├── TypeHelpers.h
               ├── Unicode.h
               ├── Vector.h
               └── VectorImpl.h

