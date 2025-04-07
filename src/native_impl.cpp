#include <iostream>
#include <cstdint>
#include <array>
#include <cmath>
#include <wasm_export.h>

// to prevent name mangling
extern "C" {
    // calculate_native works on the assumption both functions take in exactly one int32_t and return such also
    // (must take in 1 arg so the result is put into argv array)
    // cannot call directly like host.cpp because just have func table indexes not name of funcs
    int32_t calculate_native(wasm_exec_env_t exec_env, int32_t n, int32_t func1, int32_t func2)
    {
        std::cout << "Calling into native function: " << __FUNCTION__
                          << ", n=" << n << ", func1=" << func1 << ", func2=" << func2 << std::endl;

        std::array<uint32_t, 1> argv = { static_cast<uint32_t>(n) };

        if (!wasm_runtime_call_indirect(exec_env, func1, 1, argv.data())) {
            std::cerr << "Call to func1 failed" << std::endl;
            return 0xDEAD;
        }

        uint32_t n1 = argv[0];
        std::cout << "Call to func1 returned n1=" << n1 << std::endl;

        argv = { static_cast<uint32_t>(n) };

        if (!wasm_runtime_call_indirect(exec_env, func2, 1, argv.data())) {
            std::cerr << "Call to func2 failed" << std::endl;
            return 0xDEAD;
        }

        uint32_t n2 = argv[0];
        std::cout << "Call to func2 returned n2=" << n2 << std::endl;

        return static_cast<int32_t>(n1 + n2);
    }

    int32_t get_pow(wasm_exec_env_t exec_env, int x, int y)
        {
            std::cout << "Calling into native function: " << __FUNCTION__ << std::endl;
            return static_cast<int32_t>(pow(x, y));
        }
}
