#!/bin/bash

set -e  # Exit immediately on any error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="${SCRIPT_DIR}/.."
OUT_DIR="${ROOT_DIR}/build"
WASM_APPS="${ROOT_DIR}/wasm"
PROTO_MESSAGES="${ROOT_DIR}/proto_messages"
NANOPB="${ROOT_DIR}/third_party/nanopb"

cd $ROOT_DIR

# Defaults to running cmake and crosscompiling the wasm files
BUILD_TYPE=${1:-full}
REBUILD_WASM=${2:-wasm}

if [ "$BUILD_TYPE" != "skip" ]; then
  echo "#####################build basic project"

  if [ "$BUILD_TYPE" = "full" ]; then
    echo "##################### Running setup_proto.sh"
    "${SCRIPT_DIR}/setup_proto.sh"

    echo "##################### Reconfiguring CMake"
    rm -rf "${OUT_DIR}" cmake-build-debug CMakeCache.txt CMakeFiles
    mkdir -p "${OUT_DIR}"/wasm-apps

    cd "${OUT_DIR}"

    cmake \
      -DCMAKE_C_COMPILER=/usr/bin/clang \
      -DCMAKE_CXX_COMPILER=/usr/bin/clang++ ..

  else
    cd "${OUT_DIR}"
  fi

  make -j "$(nproc)"

  if [ $? != 0 ];then
      echo "BUILD_FAIL basic exit as $?\n"
      exit 2
  fi

  echo "#####################build basic project done"
fi


if [ "$REBUILD_WASM" = "wasm" ]; then
  echo "#####################build wasm apps"
  cd "${WASM_APPS}"

  for i in *.cpp
  do
  APP_SRC="$i"
  OUT_FILE=${i%.*}.wasm

  # could use -Wl,--allow-undefined \ instead of a file listing functions
  $CXX \
          --target=wasm32-wasi \
          -I"${WASM_APPS}/../proto_messages/generated_nano" \
          -I"${WASM_APPS}/../third_party/nanopb" \
          -L"${WASM_APPS}/../wasm_libraries/nanopb/build" \
          -lnanopb \
          -Wl,--export-all \
          -Wl,--allow-undefined-file="${WASM_APPS}"/native_impls.txt \
          -o "${OUT_DIR}"/wasm-apps/"${OUT_FILE}" \
           "${APP_SRC}" "${WASM_APPS}/../proto_messages/generated_nano/message.pb.c"

  if [ -f "${OUT_DIR}"/wasm-apps/"${OUT_FILE}" ]; then
          echo "build ${OUT_FILE} success"
  else
          echo "build ${OUT_FILE} fail"
  fi
  done
  echo "####################build wasm apps done"
fi