
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/arch/invokeNative_em64_simd.s" "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/arch/invokeNative_em64_simd.s.o"
  )
set(CMAKE_ASM_COMPILER_ID "Clang")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "BH_FREE=wasm_runtime_free"
  "BH_MALLOC=wasm_runtime_malloc"
  "BH_PLATFORM_LINUX"
  "BUILD_TARGET_X86_64"
  "WAMR_ENABLE_COPY_CALLSTACK=0"
  "WASM_DISABLE_HW_BOUND_CHECK=0"
  "WASM_DISABLE_STACK_HW_BOUND_CHECK=0"
  "WASM_DISABLE_WAKEUP_BLOCKING_OP=0"
  "WASM_DISABLE_WRITE_GS_BASE=0"
  "WASM_ENABLE_AOT=1"
  "WASM_ENABLE_AOT_INTRINSICS=1"
  "WASM_ENABLE_BULK_MEMORY=1"
  "WASM_ENABLE_FAST_INTERP=1"
  "WASM_ENABLE_INTERP=1"
  "WASM_ENABLE_LIBC_BUILTIN=1"
  "WASM_ENABLE_LIBC_WASI=1"
  "WASM_ENABLE_MINI_LOADER=0"
  "WASM_ENABLE_MODULE_INST_CONTEXT=1"
  "WASM_ENABLE_MULTI_MODULE=0"
  "WASM_ENABLE_QUICK_AOT_ENTRY=1"
  "WASM_ENABLE_REF_TYPES=1"
  "WASM_ENABLE_SHARED_MEMORY=0"
  "WASM_ENABLE_SHRUNK_MEMORY=1"
  "WASM_ENABLE_SIMD=1"
  "WASM_ENABLE_SIMDE=1"
  "WASM_GLOBAL_HEAP_SIZE=10485760"
  "WASM_HAVE_MREMAP=1"
  "_GNU_SOURCE"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "_deps/wamr_ext-src/core/iwasm/interpreter"
  "_deps/wamr_ext-src/core/iwasm/aot"
  "_deps/wamr_ext-src/core/iwasm/libraries/libc-builtin"
  "_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/include"
  "_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src"
  "_deps/wamr_ext-src/core/iwasm/libraries/simde"
  "_deps/wamr_ext-src/core/iwasm/libraries/simde/simde"
  "_deps/simde-src"
  "_deps/wamr_ext-src/core/iwasm/include"
  "_deps/wamr_ext-src/core/shared/platform/linux"
  "_deps/wamr_ext-src/core/shared/platform/linux/../include"
  "_deps/wamr_ext-src/core/shared/platform/common/libc-util"
  "_deps/wamr_ext-src/core/shared/mem-alloc"
  "_deps/wamr_ext-src/core/iwasm/common"
  "_deps/wamr_ext-src/core/shared/utils"
  "_deps/wamr_ext-src/core/shared/utils/uncommon"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/aot/aot_intrinsic.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_intrinsic.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_intrinsic.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/aot/aot_loader.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_loader.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_loader.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/aot/aot_runtime.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_runtime.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/aot_runtime.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/aot/arch/aot_reloc_x86_64.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/arch/aot_reloc_x86_64.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/aot/arch/aot_reloc_x86_64.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_application.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_application.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_application.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_blocking_op.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_blocking_op.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_blocking_op.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_c_api.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_c_api.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_c_api.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_exec_env.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_exec_env.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_exec_env.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_loader_common.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_loader_common.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_loader_common.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_memory.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_memory.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_memory.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_native.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_native.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_native.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_runtime_common.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_runtime_common.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_runtime_common.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/common/wasm_shared_memory.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_shared_memory.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/common/wasm_shared_memory.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/interpreter/wasm_interp_fast.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_interp_fast.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_interp_fast.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/interpreter/wasm_loader.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_loader.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_loader.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/interpreter/wasm_runtime.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_runtime.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/interpreter/wasm_runtime.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-builtin/libc_builtin_wrapper.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/libc_wasi_wrapper.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/libc_wasi_wrapper.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/libc_wasi_wrapper.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/blocking_op.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/blocking_op.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/blocking_op.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/posix.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/posix.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/posix.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/random.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/random.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/random.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/str.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/str.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src/str.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/mem-alloc/ems/ems_alloc.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_alloc.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_alloc.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/mem-alloc/ems/ems_gc.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_gc.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_gc.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/mem-alloc/ems/ems_hmu.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_hmu.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_hmu.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/mem-alloc/ems/ems_kfc.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_kfc.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/ems/ems_kfc.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/mem-alloc/mem_alloc.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/mem_alloc.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/mem-alloc/mem_alloc.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/libc-util/libc_errno.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/libc-util/libc_errno.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/libc-util/libc_errno.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_blocking_op.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_blocking_op.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_blocking_op.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_clock.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_clock.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_clock.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_file.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_file.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_file.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_malloc.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_malloc.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_malloc.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_memmap.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_memmap.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_memmap.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_sleep.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_sleep.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_sleep.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_socket.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_socket.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_socket.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_thread.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_thread.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_thread.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/common/posix/posix_time.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_time.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/common/posix/posix_time.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/platform/linux/platform_init.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/linux/platform_init.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/platform/linux/platform_init.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_assert.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_assert.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_assert.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_bitmap.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_bitmap.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_bitmap.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_common.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_common.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_common.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_hashmap.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_hashmap.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_hashmap.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_leb128.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_leb128.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_leb128.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_list.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_list.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_list.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_log.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_log.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_log.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_queue.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_queue.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_queue.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/bh_vector.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_vector.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/bh_vector.c.o.d"
  "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/build/_deps/wamr_ext-src/core/shared/utils/runtime_timer.c" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/runtime_timer.c.o" "gcc" "_deps/wamr_ext-build/CMakeFiles/vmlib.dir/core/shared/utils/runtime_timer.c.o.d"
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_LINKED_INFO_FILES
  )

# Targets to which this target links which contain Fortran sources.
set(CMAKE_Fortran_TARGET_FORWARD_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
