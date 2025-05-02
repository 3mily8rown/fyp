#!/bin/bash
set -e

ROOT_DIR=$(dirname "$0")/..
cd "$ROOT_DIR"

# --- Fetch Abseil and Protobuf ---
mkdir -p third_party
cd third_party

if [ ! -d protobuf ]; then
  git clone -b v3.21.12 --depth 1 https://github.com/protocolbuffers/protobuf.git
fi
if [ ! -d abseil-cpp ]; then
  git clone -b 20230125.2 --depth 1 https://github.com/abseil/abseil-cpp.git
fi

cd protobuf
mkdir -p build
cd build

cmake .. \
    -DCMAKE_C_COMPILER=/usr/bin/clang \
    -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
    -DCMAKE_BUILD_TYPE=Release \
    -Dprotobuf_BUILD_TESTS=OFF \
    -Dprotobuf_INSTALL=OFF \
    -Dprotobuf_BUILD_PROTOC_BINARIES=ON \
    -DCMAKE_C_FLAGS="-pthread" \
    -DCMAKE_CXX_FLAGS="-pthread"
make -j$(nproc) protoc
PROTOC_BIN=$(pwd)/protoc

cd "$ROOT_DIR"

# --- Generate Protobuf files ---
PROTO_DIR=proto_messages
PROTO_FILE=$PROTO_DIR/message.proto

OUT_CPP=$PROTO_DIR/generated_full

mkdir -p "$OUT_CPP"

echo "Generating full Protobuf C++ files..."
$PROTOC_BIN \
    --proto_path="$PROTO_DIR" \
    --cpp_out="$OUT_CPP" \
    "$PROTO_FILE"

# Set up venv if needed
VENV_DIR="$ROOT_DIR/.venv"
if [ ! -d "$VENV_DIR" ]; then
  echo "Creating Python virtual environment..."
  python3 -m venv "$VENV_DIR"
  "$VENV_DIR/bin/pip" install --upgrade pip
  "$VENV_DIR/bin/pip" install protobuf grpcio-tools
fi

# --- Generate Nanopb files ---

# Run protoc with plugin using venv Python
export PATH="$VENV_DIR/bin:$PATH"

OUT_NANO=generated_nano
PROTO_NANO_FILE=message.proto

mkdir -p "$OUT_NANO"

echo "Generating Nanopb C files..."

rm -rf "$OUT_NANO"/*

# done inside proto dir so it can find the options file
cd $PROTO_DIR 
$PROTOC_BIN \
  --plugin=protoc-gen-nanopb="$ROOT_DIR/wasm_libraries/nanopb/nanopb_plugin.sh" \
  --proto_path=. \
  --proto_path=third_party/nanopb/generator/proto \
  --nanopb_out="$OUT_NANO" \
  "$PROTO_NANO_FILE" # 2>&1 | tee nanopb_gen.log



