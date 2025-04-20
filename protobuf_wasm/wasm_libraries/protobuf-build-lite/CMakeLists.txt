cmake_minimum_required(VERSION 3.15)
project(protobuf_lite_wasm LANGUAGES CXX)
set(PROTOBUF_PATH ${CMAKE_SOURCE_DIR}/../../../third_party/protobuf)

# Include dirs
include_directories(
    ${PROTOBUF_PATH}/src
    ${PROTOBUF_PATH}/../abseil-cpp
    ${PROTOBUF_PATH}/../protobuf/third_party/utf8_range
)

# Source files (cleaned for Protobuf 21+)
add_library(protobuf-lite STATIC
    ${PROTOBUF_PATH}/src/google/protobuf/arena.cc
    ${PROTOBUF_PATH}/src/google/protobuf/arenastring.cc
    ${PROTOBUF_PATH}/src/google/protobuf/io/coded_stream.cc
    ${PROTOBUF_PATH}/src/google/protobuf/io/zero_copy_stream.cc
    ${PROTOBUF_PATH}/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
    ${PROTOBUF_PATH}/src/google/protobuf/message_lite.cc
    ${PROTOBUF_PATH}/src/google/protobuf/repeated_field.cc
    ${PROTOBUF_PATH}/src/google/protobuf/wire_format_lite.cc
    ${PROTOBUF_PATH}/src/google/protobuf/stubs/common.cc
)


# Disable unsupported features
target_compile_definitions(protobuf-lite PRIVATE
    -DGOOGLE_PROTOBUF_NO_RTTI
    -DGOOGLE_PROTOBUF_NO_THREADLOCAL
    -DGOOGLE_PROTOBUF_NO_EXCEPTIONS
)

target_compile_features(protobuf-lite PRIVATE cxx_std_17)
