#!/usr/bin/env bash
set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/scripts"
ROOT_DIR="${SCRIPT_DIR}/.."
OUT_DIR="${ROOT_DIR}/build"

BUILD_STEP=${1:-all}      # wasm, host, all
HOST_MODE=${2:-full}      # full, build

if [[ "$HOST_MODE" == "full" && "$BUILD_STEP" != "wasm" ]]; then
    rm -rf "${OUT_DIR}" cmake-build-debug CMakeCache.txt CMakeFiles
    mkdir -p "${OUT_DIR}"/wasm-apps
    # script to fetch protobuf and build proto messages
    "${SCRIPT_DIR}/setup_proto.sh"
fi

case "${BUILD_STEP}" in
  wasm)
    "${SCRIPT_DIR}/build_wasm.sh"
    ;;
  host)
    "${SCRIPT_DIR}/build_host.sh" "${HOST_MODE}"
    ;;
  all)
    "${SCRIPT_DIR}/build_wasm.sh"
    "${SCRIPT_DIR}/build_host.sh" "${HOST_MODE}"
    ;;
esac