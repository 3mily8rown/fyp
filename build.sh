#!/bin/bash

#
# Copyright (C) 2019 Intel Corporation.  All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
#

set -e  # Exit immediately on any error

CURR_DIR=$PWD
OUT_DIR=${PWD}/build
WASM_APPS=${PWD}/wasm

# Defaults to running cmake and crosscompiling the wasm files
BUILD_TYPE=${1:-full}
REBUILD_WASM=${2:-wasm}

echo "#####################build basic project"

if [ "$BUILD_TYPE" = "full" ]; then
  rm -rf "${OUT_DIR}" cmake-build-debug CMakeCache.txt CMakeFiles
  mkdir -p "${OUT_DIR}"/wasm-apps

  cd "${CURR_DIR}"
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

echo -e "\n"

if [ "$REBUILD_WASM" = "wasm" ]; then
  echo "#####################build wasm apps"
  cd ${WASM_APPS}

  for i in *.cpp
  do
  APP_SRC="$i"
  OUT_FILE=${i%.*}.wasm

  # use WAMR SDK to build out the .wasm binary
  # could use -Wl,--allow-undefined \ instead of a file listing functions
  $CXX \
          -Wl,--export-all \
          -Wl,--allow-undefined-file="${WASM_APPS}"/native_impls.txt \
          -o "${OUT_DIR}"/wasm-apps/"${OUT_FILE}" \
           "${APP_SRC}"

  if [ -f ${OUT_DIR}/wasm-apps/${OUT_FILE} ]; then
          echo "build ${OUT_FILE} success"
  else
          echo "build ${OUT_FILE} fail"
  fi
  done
  echo "####################build wasm apps done"
fi