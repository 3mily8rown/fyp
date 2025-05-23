#!/bin/bash

set -e  # Exit immediately on any error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="${SCRIPT_DIR}/.."
OUT_DIR="${ROOT_DIR}/build"
GEN_DIR="${ROOT_DIR}/generated"

# Default to reconfiguration and building
MODE=${1:-full}

echo "#####################build basic project"

if [ ! -d "${GEN_DIR}" ]; then
  echo "ERROR: Generated headers not found in ${GEN_DIR}, need to run Wasm build first"
  exit 1
fi

mkdir -p "${OUT_DIR}"
cd "${OUT_DIR}"

if [ "${MODE}" = "full" ]; then
    echo "##################### Reconfiguring CMake"

    cmake \
      -DCMAKE_C_COMPILER=/usr/bin/clang \
      -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
      -DCMAKE_INCLUDE_PATH="${GEN_DIR}" \
      ..
fi

echo "Building native host"
make -j "$(nproc)"

echo "#####################build basic project done"