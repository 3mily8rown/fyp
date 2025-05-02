#include <iostream>
#include <cstdint>
#include <array>
#include <cmath>
#include <wasm_export.h>

#include "message.pb.h"

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


    // The first parameter is not exec_env because it is invoked by native functions
    void
    reverse(char *str, int len)
    {
        int i = 0, j = len - 1, temp;
        while (i < j) {
            temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            i++;
            j--;
        }
    }

    // Converts a given integer x to string str[].
    // digit is the number of digits required in the output.
    // If digit is more than the number of digits in x,
    // then 0s are added at the beginning.
    int
    intToStr(wasm_exec_env_t exec_env, int x, char *str, int str_len, int digit)
    {
        int i = 0;

        printf("calling into native function: %s\n", __FUNCTION__);

        while (x) {
            // native is responsible for checking the str_len overflow
            if (i >= str_len) {
                return -1;
            }
            str[i++] = (x % 10) + '0';
            x = x / 10;
        }

        // If number of digits required is more, then
        // add 0s at the beginning
        while (i < digit) {
            if (i >= str_len) {
                return -1;
            }
            str[i++] = '0';
        }

        reverse(str, i);

        if (i >= str_len)
            return -1;
        str[i] = '\0';
        return i;
    }
    
    void pass_to_native_wrapper(wasm_exec_env_t exec_env, uint32_t offset, uint32_t length) {
        wasm_module_inst_t inst = wasm_runtime_get_module_inst(exec_env);
        uint8_t* memory = static_cast<uint8_t*>(wasm_runtime_addr_app_to_native(inst, offset));
    
        if (!memory) {
            printf("Invalid memory address\n");
            return;
        }
    
        std::string data((char*)memory, length);
    
        MyMessage msg;
        // MyMessage msg;
        if (!msg.ParseFromString(data)) {
            printf("Failed to parse protobuf\n");
            return;
        }
    
        std::cout << "Received message! ID = " << msg.id() << ", Name = " << msg.name() << std::endl;
    }
}
