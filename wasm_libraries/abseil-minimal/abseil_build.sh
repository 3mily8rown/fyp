[ -d build ] && rm -rf build
mkdir -p build && cd build

# Add endian fix macros for WASI
ENDIAN_FLAGS="-D__ORDER_LITTLE_ENDIAN__=1234 -D__ORDER_BIG_ENDIAN__=4321 -D__BYTE_ORDER__=__ORDER_LITTLE_ENDIAN__"
WASI_FIX="-D__BEGIN_DECLS= -D__END_DECLS="

cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=../../../wasi-toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_CXX_FLAGS="--target=wasm32-wasi -std=c++17 -fno-exceptions -fvisibility=hidden -Wno-error=extern-c-compat ${ENDIAN_FLAGS} ${WASI_FIX}"

cmake --build .
