#include <cstdio>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wasm_export.h>

#include "message.pb.h"

int call_generate_and_format_float(wasm_exec_env_t exec_env, wasm_module_inst_t module_inst) {
    wasm_function_inst_t func_generate = nullptr;
    wasm_function_inst_t func_format = nullptr;
    char *native_buffer = nullptr;
    uint64_t wasm_buffer = 0;

    // Lookup generate_float
    if (!(func_generate = wasm_runtime_lookup_function(module_inst, "generate_float"))) {
        printf("The generate_float wasm function is not found.\n");
        return 1;
    }

    // Prepare arguments and result buffer
    wasm_val_t results[1] = { { .kind = WASM_F32, .of.f32 = 0 } };
    wasm_val_t arguments[3] = {
        { .kind = WASM_I32, .of.i32 = 10 },
        { .kind = WASM_F64, .of.f64 = 0.000101 },
        { .kind = WASM_F32, .of.f32 = 300.002 },
    };

    if (!wasm_runtime_call_wasm_a(exec_env, func_generate, 1, results, 3, arguments)) {
        printf("call wasm function generate_float failed. %s\n",
               wasm_runtime_get_exception(module_inst));
        return 1;
    }

    float ret_val = results[0].of.f32;
    printf("Native finished calling generate_float(), returned: %ff\n", ret_val);

    // Allocate buffer from WASM memory
    wasm_buffer = wasm_runtime_module_malloc(module_inst, 100, (void **)&native_buffer);
    if (!wasm_buffer || !native_buffer) {
        printf("Failed to allocate WASM memory buffer.\n");
        return 1;
    }

    // Prepare arguments for float_to_string
    uint32_t argv2[4];
    memcpy(&argv2[0], &ret_val, sizeof(float));
    argv2[1] = (uint32_t)wasm_buffer;
    argv2[2] = 100;
    argv2[3] = 3;  // digits after decimal

    // Lookup float_to_string
    if (!(func_format = wasm_runtime_lookup_function(module_inst, "float_to_string"))) {
        printf("The float_to_string wasm function is not found.\n");
        return 1;
    }

    if (wasm_runtime_call_wasm(exec_env, func_format, 4, argv2)) {
        // printf("Native finished calling float_to_string, returned: %s\n", native_buffer);
        // replaced ^ with below incase malformed string
        printf("Raw bytes from WASM buffer:\n");
        for (int i = 0; i < 100; i++) {
            if (native_buffer[i] == 0) break;
            putchar(native_buffer[i]);
        }
        putchar('\n');
    } else {
        printf("call wasm function float_to_string failed. %s\n",
               wasm_runtime_get_exception(module_inst));
        return 1;
    }

    return 0;
}

// call a function that takes in vector of int args and outputs 1 int
int call_int_func(wasm_module_inst_t module_inst,
    wasm_exec_env_t exec_env,
    const char* func_name,
    const std::vector<uint32_t>& args,
    int32_t& result_out)
{
    wasm_function_inst_t func = nullptr;
    // lookup wasm function being called
    if (!(func = wasm_runtime_lookup_function(module_inst, func_name))) {
    printf("The %s wasm function is not found.\n", func_name);
    return 1;
    }

    // Convert uint32_t args to wasm_val_t
    std::vector<wasm_val_t> wasm_args;
    for (uint32_t arg : args) {
    wasm_val_t val;
    val.kind = WASM_I32;
    val.of.i32 = arg;
    wasm_args.push_back(val);
    }

    // return result
    // wasm_val_t results[1] = { { .kind = WASM_I32, .of.i32 = 0 } };
    wasm_val_t results[1];
    results[0].kind = WASM_I32;
    results[0].of.i32 = 0;

    if (!wasm_runtime_call_wasm_a(exec_env, func, 1, results, wasm_args.size(), wasm_args.data())) {
    printf("call wasm function %s failed. %s\n",
    func_name,
    wasm_runtime_get_exception(module_inst));
    return 1;
    }

    result_out = results[0].of.i32;
    return 0;
}

// Call functions from WASM modules takes a string pointer and returns one(NOT USED)
const char* call_func(wasm_module_inst_t inst, wasm_exec_env_t env, const char* func_name, const char* arg = nullptr) {
    wasm_function_inst_t func = wasm_runtime_lookup_function(inst, func_name);
  
    if (!func) {
      printf("Function %s not found\n", func_name);
      exit(1);
    }
  
    wasm_val_t args[1], results[1];  // <-- Declare results for both branches
  
    if (arg) {
      args[0].kind = WASM_I32;
  
      uint32_t str_ptr = wasm_runtime_module_malloc(inst, strlen(arg) + 1, nullptr);
      char* str_in_wasm = (char*)wasm_runtime_addr_app_to_native(inst, str_ptr);
      strcpy(str_in_wasm, arg);
      args[0].of.i32 = str_ptr;
  
      if (!wasm_runtime_call_wasm_a(env, func, 1, results, 1, args)) {
        printf("Call failed: %s\n", wasm_runtime_get_exception(inst));
        return nullptr;
      }
    } else {
      if (!wasm_runtime_call_wasm_a(env, func, 1, results, 0, nullptr)) {
        printf("Call failed: %s\n", wasm_runtime_get_exception(inst));
        return nullptr;
      }
    }
  
    // Safe to use results[0] in either case now
    const char* ret_ptr = (char*)wasm_runtime_addr_app_to_native(inst, results[0].of.i32);
    return ret_ptr;
  }
