[ -d build ] && rm -rf build
mkdir -p build && cd build

cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=../../../wasi-toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -Dprotobuf_BUILD_TESTS=OFF \
  -Dprotobuf_BUILD_PROTOC_BINARIES=OFF \
  -Dprotobuf_BUILD_SHARED_LIBS=OFF \
  -Dprotobuf_DISABLE_RTTI=ON \
  -Dprotobuf_BUILD_LIBPROTOBUF=OFF \
  -Dprotobuf_BUILD_LIBPROTOC=OFF \
  -Dprotobuf_WITH_ZLIB=OFF \
  -Dprotobuf_USE_EXTERNAL_ABSL=OFF \

cmake --build .