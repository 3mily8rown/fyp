#!/bin/bash

set -e  # Exit immediately on any error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="${SCRIPT_DIR}/.."
OUT_DIR="${ROOT_DIR}/build/wasm-apps"
WASM_APPS="${ROOT_DIR}/wasm"
GEN_DIR="${ROOT_DIR}/generated"

echo "##################### build wasm apps"

mkdir -p "${OUT_DIR}" "${GEN_DIR}"
cd "${WASM_APPS}"

mkdir -p "${GEN_DIR}"

for src in *.cpp
do
  BASE="${src%.*}"
  OUT_FILE="${OUT_DIR}/${BASE}.wasm"

  echo "building ${OUT_FILE} from ${src}"
  # could use -Wl,--allow-undefined \ instead of a file listing functions
  $CXX \
          --target=wasm32-wasi \
          -I"${WASM_APPS}/../proto_messages/generated_nano" \
          -I"${WASM_APPS}/../third_party/nanopb" \
          -L"${WASM_APPS}/../wasm_libraries/nanopb/build" \
          -lnanopb \
          -Wl,--export-all \
          -Wl,--no-gc-sections \
          -Wl,--allow-undefined-file="${WASM_APPS}/native_impls.txt" \
          -o "${OUT_FILE}" \
          "${src}" \
          "${WASM_APPS}/../proto_messages/generated_nano/message.pb.c"

  # generate export list header
  echo "Generating exports header ${BASE}"

  python3 "${SCRIPT_DIR}/generate_wasm_exports.py" \
    "${OUT_FILE}" "${GEN_DIR}/${BASE}_exports.h"

done

echo "####################build wasm apps done"