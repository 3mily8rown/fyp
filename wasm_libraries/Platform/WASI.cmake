# build-lite/Platform/WASI.cmake
set(CMAKE_SYSTEM_NAME WASI)

set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR wasm32)
set(CMAKE_CROSSCOMPILING TRUE)

# Tell CMake that threads are not supported
set(THREADS_PREFER_PTHREAD_FLAG OFF)
set(CMAKE_USE_PTHREADS_INIT 0)
set(Threads_FOUND FALSE)
