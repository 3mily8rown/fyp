# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# compile ASM with /usr/bin/clang
# compile C with /usr/bin/clang
ASM_DEFINES = -DBH_FREE=wasm_runtime_free -DBH_MALLOC=wasm_runtime_malloc -DBH_PLATFORM_LINUX -DBUILD_TARGET_X86_64 -DWAMR_ENABLE_COPY_CALLSTACK=0 -DWASM_DISABLE_HW_BOUND_CHECK=0 -DWASM_DISABLE_STACK_HW_BOUND_CHECK=0 -DWASM_DISABLE_WAKEUP_BLOCKING_OP=0 -DWASM_DISABLE_WRITE_GS_BASE=0 -DWASM_ENABLE_AOT=1 -DWASM_ENABLE_AOT_INTRINSICS=1 -DWASM_ENABLE_BULK_MEMORY=1 -DWASM_ENABLE_FAST_INTERP=1 -DWASM_ENABLE_INTERP=1 -DWASM_ENABLE_LIBC_BUILTIN=1 -DWASM_ENABLE_LIBC_WASI=1 -DWASM_ENABLE_MINI_LOADER=0 -DWASM_ENABLE_MODULE_INST_CONTEXT=1 -DWASM_ENABLE_MULTI_MODULE=0 -DWASM_ENABLE_QUICK_AOT_ENTRY=1 -DWASM_ENABLE_REF_TYPES=1 -DWASM_ENABLE_SHARED_MEMORY=0 -DWASM_ENABLE_SHRUNK_MEMORY=1 -DWASM_ENABLE_SIMD=1 -DWASM_ENABLE_SIMDE=1 -DWASM_GLOBAL_HEAP_SIZE=10485760 -DWASM_HAVE_MREMAP=1 -D_GNU_SOURCE

ASM_INCLUDES = -I/home/eb/fyp/helloworld/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/interpreter -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/aot -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-builtin -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/simde -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/simde/simde -I/home/eb/fyp/helloworld/build/_deps/simde-src -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/linux -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/linux/../include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/common/libc-util -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/mem-alloc -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/common -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/utils -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/utils/uncommon

ASM_FLAGS = -O3 -DNDEBUG

C_DEFINES = -DBH_FREE=wasm_runtime_free -DBH_MALLOC=wasm_runtime_malloc -DBH_PLATFORM_LINUX -DBUILD_TARGET_X86_64 -DWAMR_ENABLE_COPY_CALLSTACK=0 -DWASM_DISABLE_HW_BOUND_CHECK=0 -DWASM_DISABLE_STACK_HW_BOUND_CHECK=0 -DWASM_DISABLE_WAKEUP_BLOCKING_OP=0 -DWASM_DISABLE_WRITE_GS_BASE=0 -DWASM_ENABLE_AOT=1 -DWASM_ENABLE_AOT_INTRINSICS=1 -DWASM_ENABLE_BULK_MEMORY=1 -DWASM_ENABLE_FAST_INTERP=1 -DWASM_ENABLE_INTERP=1 -DWASM_ENABLE_LIBC_BUILTIN=1 -DWASM_ENABLE_LIBC_WASI=1 -DWASM_ENABLE_MINI_LOADER=0 -DWASM_ENABLE_MODULE_INST_CONTEXT=1 -DWASM_ENABLE_MULTI_MODULE=0 -DWASM_ENABLE_QUICK_AOT_ENTRY=1 -DWASM_ENABLE_REF_TYPES=1 -DWASM_ENABLE_SHARED_MEMORY=0 -DWASM_ENABLE_SHRUNK_MEMORY=1 -DWASM_ENABLE_SIMD=1 -DWASM_ENABLE_SIMDE=1 -DWASM_GLOBAL_HEAP_SIZE=10485760 -DWASM_HAVE_MREMAP=1 -D_GNU_SOURCE

C_INCLUDES = -I/home/eb/fyp/helloworld/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/interpreter -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/aot -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-builtin -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/libc-wasi/sandboxed-system-primitives/src -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/simde -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/libraries/simde/simde -I/home/eb/fyp/helloworld/build/_deps/simde-src -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/linux -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/linux/../include -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/platform/common/libc-util -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/mem-alloc -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/iwasm/common -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/utils -I/home/eb/fyp/helloworld/build/_deps/wamr_ext-src/core/shared/utils/uncommon

C_FLAGS =  -std=gnu99 -ffunction-sections -fdata-sections -Wall -Wno-unused-parameter -Wno-pedantic -fPIC -Wall -Wextra -Wformat -Wformat-security -ffunction-sections -fdata-sections -Wno-unused-parameter -Wno-pedantic -fvisibility=hidden -O3 -DNDEBUG -std=gnu99

