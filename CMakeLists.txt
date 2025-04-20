# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
cmake_minimum_required(VERSION 3.8)

project(HelloWorld C CXX)

# to download and build external content ie git repos at configure time
include (ExternalProject)
include (FetchContent)

set(SOURCES
    src/host.cpp
    src/native_impl.cpp
    src/host_utils.cpp
    proto_messages/generated/message.pb.cc
)

# add_subdirectory(wasm)

# ------------------------------
# Add WAMR support for wasm_host
# ------------------------------

# downloading WAMR
FetchContent_Declare(
        wamr_ext
        GIT_REPOSITORY "https://github.com/bytecodealliance/wasm-micro-runtime"
        GIT_TAG "4e50d2191ca8f177ad03a9d80eebc44b59a932db"
)
FetchContent_MakeAvailable(wamr_ext)

# extracts path downloaded WAMR to
FetchContent_GetProperties(wamr_ext SOURCE_DIR WAMR_ROOT_DIR)
message(STATUS WAMR_ROOT_DIR ${WAMR_ROOT_DIR})

# configure which features of WAMR to include
set(WAMR_BUILD_PLATFORM "linux")
set(WAMR_BUILD_TARGET X86_64)
set(WAMR_BUILD_SPEC_TEST 0)
set(WAMR_BUILD_INTERP 1)   # builds interpreter version not AoT/JIT
set(WAMR_BUILD_AOT 0)
set(WAMR_BUILD_JIT 0)
set(WAMR_BUILD_LAZY_JIT 0)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_LIBC_WASI 1)   # WASI support for syscalls
set(WAMR_BUILD_LIB_PTHREAD 0)
set(WAMR_BUILD_REF_TYPES 1)

set(ABSL_ENABLE_INSTALL ON)


# builds wamr, creating wamrlib static library and links to public interface of wamrlib
include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
add_library(wamrlib "${WAMR_RUNTIME_LIB_SOURCE}")
target_include_directories(wamrlib PUBLIC
        ${PLATFORM_SHARED_DIR}
)

# Build the wasm_host executable
add_executable(wasm_host ${SOURCES})

target_include_directories(wasm_host PRIVATE
    include
    ${wamr_ext_SOURCE_DIR}/core/iwasm/include
    proto_messages/generated
)

# ----------------------------------
# Add protobuf & abseil from source
# ----------------------------------

# Abseil
FetchContent_Declare(
  abseil
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git
  GIT_TAG        20250127.1
)
FetchContent_MakeAvailable(abseil)

# Protobuf
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG        v30.1  # Or a version you prefer
)
set(protobuf_BUILD_TESTS OFF)  # Prevent absl::scoped_mock_log errors
set(protobuf_ABSL_PROVIDER "package")  # Use our own Abseil
FetchContent_MakeAvailable(protobuf)

# Add include dirs for generated protobuf headers
target_include_directories(wasm_host PRIVATE
    ${protobuf_SOURCE_DIR}/src
    proto_messages/generated
)

set(PROTOC_EXECUTABLE $<TARGET_FILE:protobuf::protoc>)


# Link the prebuilt libraries
target_link_libraries(wasm_host
        wamrlib
        pthread
        m
        dl
        
        protobuf::libprotobuf
        absl::check
        absl::flags
        absl::flags_parse
        absl::log
        absl::log_initialize
)
