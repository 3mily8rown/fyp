// native_impls.h
#pragma once

#include <cstdint>
#include <wasm_export.h>   // for wasm_exec_env_t, wasm_module_inst_t, etc.
#include <string>

int32_t calculate_native(wasm_exec_env_t exec_env,
                        int32_t n,
                         int32_t func1,
                         int32_t func2);

int32_t get_pow(wasm_exec_env_t exec_env, int x,
                int y);

void reverse(wasm_exec_env_t exec_env, char *str,
             int len);

int intToStr(wasm_exec_env_t exec_env, int x,
             char *str,
             int str_len,
             int digit);

void pass_to_native(wasm_exec_env_t exec_env, uint32_t offset,
                    uint32_t length);
