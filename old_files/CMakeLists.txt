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

include (ExternalProject)
include (FetchContent)

#set(BUILD_TESTING OFF)
#set(ABSL_PROPAGATE_CXX_STD ON)
#set(ABSL_ENABLE_LOGGING ON)
#set(ABSL_ENABLE_STRINGIFY ON)
#set(Protobuf_USE_STATIC_LIBS ON)
#set(Protobuf_USE_ABSL ON)
#set(CMAKE_PREFIX_PATH "/home/eb/.local")
#
#add_subdirectory(third_party/abseil-cpp)
#
#include(../cmake/common.cmake)
#
## Proto file
#get_filename_component(hw_proto "../../protos/helloworld.proto" ABSOLUTE)
#get_filename_component(hw_proto_path "${hw_proto}" PATH)
#
## Generated sources
#set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
#set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
#set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
#set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")
#add_custom_command(
#      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
#      COMMAND ${_PROTOBUF_PROTOC}
#      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
#        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
#        -I "${hw_proto_path}"
#        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#        "${hw_proto}"
#      DEPENDS "${hw_proto}")
#
## Include generated *.pb.h files
#include_directories("${CMAKE_CURRENT_BINARY_DIR}")
#
## hw_grpc_proto
#add_library(hw_grpc_proto
#  ${hw_grpc_srcs}
#  ${hw_grpc_hdrs}
#  ${hw_proto_srcs}
#  ${hw_proto_hdrs})
#target_link_libraries(hw_grpc_proto
#        # Abseil (without absl::stringify)
#        absl::check
#        absl::flags
#        absl::flags_parse
#        absl::str_format
#        absl::strings
#        absl::core_headers
#        absl::base
#        absl::type_traits
#        absl::utility
#        # gRPC
#        ${_GRPC_GRPCPP}
#        grpc++_reflection
#        ${_REFLECTION}
#        # Protobuf
#        ${_PROTOBUF_LIBPROTOBUF}
#        ${_PROTOBUF_LIBPROTOC}
#        ${_PROTOBUF_PROTOC_EXECUTABLE}
#)
#
#
#
#
#
## Targets greeter_[async_](client|server)
#foreach(_target
#  greeter_client greeter_server
#  greeter_callback_client greeter_callback_server
#  greeter_async_client greeter_async_client2 greeter_async_server)
#  add_executable(${_target} "${_target}.cc")
#  target_link_libraries(${_target}
#          hw_grpc_proto
#          # Abseil
#          absl::check
#          absl::flags
#          absl::flags_parse
#          absl::str_format
#          absl::strings
#          absl::core_headers
#          absl::base
#          absl::type_traits
#          absl::utility
#
#          # gRPC
#          ${_GRPC_GRPCPP}
#          grpc++_reflection
#          ${_REFLECTION}
#
#          # Protobuf
#          ${_PROTOBUF_LIBPROTOBUF}
#          ${_PROTOBUF_LIBPROTOC}
#          ${_PROTOBUF_PROTOC_EXECUTABLE}
#  )
#
#endforeach()

# ------------------------------
# Add WAMR support for wasm_host
# ------------------------------

FetchContent_Declare(wamr_ext
        GIT_REPOSITORY "https://github.com/bytecodealliance/wasm-micro-runtime"
        GIT_TAG "4e50d2191ca8f177ad03a9d80eebc44b59a932db"
)
FetchContent_MakeAvailable(wamr_ext)

FetchContent_GetProperties(wamr_ext SOURCE_DIR WAMR_ROOT_DIR)
message(STATUS WAMR_ROOT_DIR ${WAMR_ROOT_DIR})

set(WAMR_BUILD_PLATFORM "linux")
set(WAMR_BUILD_TARGET X86_64)
set(WAMR_BUILD_SPEC_TEST 0)
set(WAMR_BUILD_INTERP 1)
set(WAMR_BUILD_AOT 0)
set(WAMR_BUILD_JIT 0)
set(WAMR_BUILD_LAZY_JIT 0)
set(WAMR_BUILD_LIBC_BUILTIN 1)
set(WAMR_BUILD_LIBC_WASI 1)
set(WAMR_BUILD_LIB_PTHREAD 0)
set(WAMR_BUILD_REF_TYPES 1)

include (${WAMR_ROOT_DIR}/build-scripts/runtime_lib.cmake)
add_library(wamrlib "${WAMR_RUNTIME_LIB_SOURCE}")
target_include_directories(wamrlib PUBLIC
        ${PLATFORM_SHARED_DIR}
)

# Build the wasm_host executable
add_executable(wasm_host host.cpp)

# Link the prebuilt libraries
target_link_libraries(wasm_host
        wamrlib
        pthread
        m
        dl
)





