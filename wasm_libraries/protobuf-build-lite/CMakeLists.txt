cmake_minimum_required(VERSION 3.15)
project(protobuf_lite_wasm LANGUAGES CXX)

set(PROTOBUF_PATH ${CMAKE_SOURCE_DIR}/../../third_party/protobuf)

# Include dirs
include_directories(
    ${PROTOBUF_PATH}/src
)

add_library(protobuf-lite STATIC
    ${PROTOBUF_PATH}/src/google/protobuf/io/coded_stream.cc
    ${PROTOBUF_PATH}/src/google/protobuf/io/zero_copy_stream.cc
    ${PROTOBUF_PATH}/src/google/protobuf/io/zero_copy_stream_impl_lite.cc
    ${PROTOBUF_PATH}/src/google/protobuf/message_lite.cc
    ${PROTOBUF_PATH}/src/google/protobuf/repeated_field.cc  #have to not use repeated fields in proto messages 
    ${PROTOBUF_PATH}/src/google/protobuf/wire_format_lite.cc

    # ${PROTOBUF_PATH}/src/google/protobuf/stubs/common.cc
    # ${PROTOBUF_PATH}/src/google/protobuf/stubs/strutil.cc
    # ${PROTOBUF_PATH}/src/google/protobuf/stubs/status.cc
    # ${PROTOBUF_PATH}/src/google/protobuf/stubs/int128.cc

    # ${PROTOBUF_PATH}/src/google/protobuf/stubs/stringpiece.cc
    # ${PROTOBUF_PATH}/src/google/protobuf/parse_context.cc
    # ${PROTOBUF_PATH}/src/google/protobuf/io/zero_copy_stream_impl.cc

    ${CMAKE_CURRENT_SOURCE_DIR}/src/google/protobuf/arena.cc

)

# Disable unsupported features
target_compile_definitions(protobuf-lite PRIVATE
    -DGOOGLE_PROTOBUF_NO_RTTI
    -DGOOGLE_PROTOBUF_NO_THREADLOCAL
    -DGOOGLE_PROTOBUF_NO_EXCEPTIONS
    # -DGOOGLE_PROTOBUF_NO_ARENA
)

target_include_directories(protobuf-lite BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/stubs)

target_compile_features(protobuf-lite PRIVATE 
    cxx_std_17
)

target_compile_options(protobuf-lite PRIVATE
    -fno-exceptions
    -fno-rtti
)
