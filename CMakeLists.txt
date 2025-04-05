# Copyright 2018 gRPC authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# cmake build file for C++ helloworld example.
# Assumes protobuf and gRPC have been installed using cmake.
# See cmake_externalproject/CMakeLists.txt for all-in-one cmake build
# that automatically builds all the dependencies before building helloworld.

cmake_minimum_required(VERSION 3.8)

project(HelloWorld C CXX)

# to download and build external content ie git repos at configure time
include (ExternalProject)
include (FetchContent)

set(SOURCES
    src/host.cpp
    src/native_impl.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/include)

# ------------------------------
# Add WAMR support for wasm_host
# ------------------------------

# downloading WAMR
FetchContent_Declare(wamr_ext
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

# builds wamr, creating wamrlib static library and links to public interface of wamrlib
include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
add_library(wamrlib "${WAMR_RUNTIME_LIB_SOURCE}")
target_include_directories(wamrlib PUBLIC
        ${PLATFORM_SHARED_DIR}
)

# Build the wasm_host executable
add_executable(wasm_host ${SOURCES})

# Link the prebuilt libraries
target_link_libraries(wasm_host
        wamrlib
        pthread
        m
        dl
)





