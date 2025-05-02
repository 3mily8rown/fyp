cmake_minimum_required(VERSION 3.15)
project(absl_minimal LANGUAGES CXX)

set(ABSEIL_PATH ${CMAKE_SOURCE_DIR}/../../../third_party/abseil-cpp)

include_directories(
  ${ABSEIL_PATH}
  ${ABSEIL_PATH}/absl
  ${ABSEIL_PATH}/absl/strings
  ${ABSEIL_PATH}/absl/strings/internal
  ${ABSEIL_PATH}/absl/base/internal
  ${ABSEIL_PATH}/absl/crc/internal
)

set(ABSL_MINIMAL_SRCS
  ${ABSEIL_PATH}/absl/strings/cord.cc
  ${ABSEIL_PATH}/absl/strings/internal/cord_internal.cc
  ${ABSEIL_PATH}/absl/strings/internal/cord_rep_btree.cc
  ${ABSEIL_PATH}/absl/strings/internal/cord_rep_consume.cc
  ${ABSEIL_PATH}/absl/strings/internal/cord_rep_crc.cc
  ${ABSEIL_PATH}/absl/strings/str_cat.cc
  ${ABSEIL_PATH}/absl/strings/ascii.cc
  ${ABSEIL_PATH}/absl/strings/match.cc
  ${ABSEIL_PATH}/absl/strings/numbers.cc
  ${ABSEIL_PATH}/absl/strings/charconv.cc
  ${ABSEIL_PATH}/absl/strings/internal/charconv_parse.cc
  ${ABSEIL_PATH}/absl/strings/internal/charconv_bigint.cc
  ${ABSEIL_PATH}/absl/strings/internal/ostringstream.cc
  ${ABSEIL_PATH}/absl/strings/internal/memutil.cc

  # Cordz diagnostics (required by modern Cord)
  # ${ABSEIL_PATH}/absl/strings/internal/cordz_info.cc
  # ${ABSEIL_PATH}/absl/strings/internal/cordz_functions.cc

  # CRC
  ${ABSEIL_PATH}/absl/crc/crc32c.cc
  ${ABSEIL_PATH}/absl/crc/internal/crc_cord_state.cc
  ${ABSEIL_PATH}/absl/crc/internal/crc.cc
  ${ABSEIL_PATH}/absl/crc/internal/crc_memcpy_fallback.cc
  ${ABSEIL_PATH}/absl/crc/internal/crc_non_temporal_memcpy.cc
  ${ABSEIL_PATH}/absl/crc/internal/crc_x86_arm_combined.cc

  # Minimal logging
  ${ABSEIL_PATH}/absl/base/internal/raw_logging.cc
  ${ABSEIL_PATH}/absl/base/log_severity.cc

  # Cycleclock
  ${ABSEIL_PATH}/absl/base/internal/cycleclock.cc
  ${ABSEIL_PATH}/absl/base/internal/unscaledcycleclock.cc


)



add_library(absl_minimal STATIC
  ${ABSL_MINIMAL_SRCS}
)

target_compile_features(absl_minimal PRIVATE cxx_std_17)

target_compile_definitions(absl_minimal PRIVATE
  -DABSL_NO_THREADS
  -DGOOGLE_PROTOBUF_NO_THREADLOCAL
  -DGOOGLE_PROTOBUF_NO_RTTI
  -DGOOGLE_PROTOBUF_NO_EXCEPTIONS
)
