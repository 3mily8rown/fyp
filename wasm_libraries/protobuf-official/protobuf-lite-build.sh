# Trying to use official protobuf lite (it still has threads :/)
[ -d build ] && rm -rf build
mkdir -p build && cd build

cmake -S /home/eb/fyp/protobuf \
  -DCMAKE_TOOLCHAIN_FILE=../../wasi-toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DBUILD_SHARED_LIBS=OFF \
  -Dprotobuf_BUILD_TESTS=OFF \
  -Dprotobuf_BUILD_PROTOC_BINARIES=OFF \
  -Dprotobuf_BUILD_LIBPROTOC=OFF \
  -Dprotobuf_WITH_ZLIB=OFF

cmake --build . --target libprotobuf-lite

