file(GLOB WASM_SOURCES *.cpp)

add_library(wasm_apps STATIC ${WASM_SOURCES})

target_include_directories(wasm_apps PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(wasm_apps PUBLIC cxx_std_17)
