#include "wasm_export.h"
#include "math.h"
#include "stdio.h"

// calls 2 wasm func from native code and adds result
int32_t
calculate_native(wasm_exec_env_t exec_env, int32_t n, int32_t func1,
                 int32_t func2)
{
    printf("calling into native function: %s, n=%d, func1=%d, func2=%d\n",
           __FUNCTION__, n, func1, func2);

    uint32_t argv[] = { n };
    if (!wasm_runtime_call_indirect(exec_env, func1, 1, argv)) {
        printf("call func1 failed\n");
        return 0xDEAD;
    }

    uint32_t n1 = argv[0];
    printf("call func1 and return n1=%d\n", n1);

    if (!wasm_runtime_call_indirect(exec_env, func2, 1, argv)) {
        printf("call func2 failed\n");
        return 0xDEAD;
    }

    uint32_t n2 = argv[0];
    printf("call func2 and return n2=%d\n", n2);
    return n1 + n2;
}