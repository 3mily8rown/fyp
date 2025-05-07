// host.cpp (minimal WAMR runtime host)
#include <cstdio>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wasm_export.h>

#include "call_wasm_utils.h"
#include "host_proto.h"
#include "mangling_utils.h"
#include "load_module.h"

#include "wasm_app_exports.h"
#include "wasm_app_imports.h"
#include "protowasm_app_exports.h"
#include "protowasm_app_imports.h"

#include "/home/eb/fyp/my_repos/helloworld/proto_messages/generated_full/message.pb.h"       

int intToStr(int x, char *str, int str_len, int digit);
int32_t calculate_native(wasm_exec_env_t exec_env, int32_t n, int32_t func1, int32_t func2);
int32_t get_pow(wasm_exec_env_t exec_env, int32_t n, int32_t m);
void pass_to_native(wasm_exec_env_t exec_env, uint32_t offset, uint32_t length);

static NativeSymbol all_env_native_symbols[
  generated_wasm_app_native_symbols_count +
  generated_protowasm_app_native_symbols_count
];

static const size_t all_env_native_symbols_count =
  generated_wasm_app_native_symbols_count +
  generated_protowasm_app_native_symbols_count;

MyMessage make_example_msg() {
  MyMessage m;
  m.set_id(42);
  m.set_name("hello from native");
  return m;
}

void register_all_env_symbols() {
  size_t out_idx = 0;
  for (size_t i = 0; i < generated_wasm_app_native_symbols_count; ++i)
    all_env_native_symbols[out_idx++] = generated_wasm_app_native_symbols[i];
  for (size_t i = 0; i < generated_protowasm_app_native_symbols_count; ++i)
    all_env_native_symbols[out_idx++] = generated_protowasm_app_native_symbols[i];

  wasm_runtime_register_natives(
    "env",
    all_env_native_symbols,
    all_env_native_symbols_count
  );
}

int main() {
  wasm_runtime_set_log_level(WASM_LOG_LEVEL_DEBUG);

  wasm_module_t module = nullptr, proto_module = nullptr;
  wasm_module_inst_t module_inst = nullptr, proto_module_inst = nullptr;
  wasm_exec_env_t exec_env = nullptr, proto_exec_env = nullptr;
  char error_buf[128];
  uint32_t buf_size, stack_size = 8092, heap_size = 8092;

  static char global_heap_buf[512 * 1024];
  RuntimeInitArgs init_args;

  memset(&init_args, 0, sizeof(RuntimeInitArgs));
  init_args.mem_alloc_type = Alloc_With_Pool;
  
  init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
  init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

  if (!wasm_runtime_full_init(&init_args)) {
    printf("Init runtime environment failed.\n");
    return -1;
  }

  wasm_runtime_set_log_level(WASM_LOG_LEVEL_VERBOSE);

  register_all_env_symbols();

  // --------------------------Load first wasm module

  // TODO avoid hardcoding
  std::string wasmPath = "/home/eb/fyp/my_repos/helloworld/build/wasm-apps/wasm_app.wasm";
  auto buffer = readFileToBytes(wasmPath);

  // load module and create execution environment
  module = load_module_minimal(buffer, module_inst, exec_env, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!module) {
    return 1;
  }

  cache_all_exports(module_inst, WASM_APP_EXPORT_NAMES);

  // --------------------------Load second wasm module

  wasmPath = "/home/eb/fyp/my_repos/helloworld/build/wasm-apps/protowasm_app.wasm";
  auto proto_buffer = readFileToBytes(wasmPath);

  // load module and create execution environment
  proto_module = load_module_minimal(proto_buffer, proto_module_inst, proto_exec_env, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!proto_module) {
    return 1;
  }

  cache_all_exports(proto_module_inst, PROTOWASM_APP_EXPORT_NAMES);

  //-----------------------Calling WASM functions:
  // TODO: these seem very like they should be tests..
  int32_t result;

  // expecting 10
  if (call_cached_int_func(module_inst, exec_env, "mul5", {2}, result) == 0) {
    printf("Result from mul5(): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 10
  if (call_cached_int_func(module_inst, exec_env, "mul5", {2, 1}, result) == 0) {
    printf("Result from overloaded mul5(): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 70
  if (call_cached_int_func(module_inst, exec_env, "mul7", {10}, result) == 0) {
    printf("Result from mul7(10): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 88
  if (call_cached_int_func(module_inst, exec_env, "mul", {8,11}, result) == 0) {
    printf("Result from mul(8,11): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 16
  if (call_cached_int_func(module_inst, exec_env, "power", {2,4}, result) == 0) {
    printf("Result from power(2,4): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 96
  if (call_cached_int_func(module_inst, exec_env, "calculate", {8}, result) == 0) {
    printf("Result from calculate(8): %d\n", result);
  } else
  {
    return 1;
  }

  if (call_generate_and_format_float(exec_env, module_inst) == 0) {
    printf("Generated float\n");
  } else {
    printf("Error occurred during WASM call sequence.\n");
    return 1;
  }

  // sending a message from wasm to native using protobuffers
  auto func1 = get_exported_func("send_message", proto_module_inst);
  if (!func1) {
    fprintf(stderr, "send_message wasm function is not found.\n");
    return 1;
  }
  
  if (!wasm_runtime_call_wasm(proto_exec_env, func1, 0, nullptr)) {
    const char* ex = wasm_runtime_get_exception(proto_module_inst);
    fprintf(stderr, "send_message trapped: %s\n", ex ? ex : "(null)");
  }

  // sending a message from native to wasm with protobuffers
  WasmBuffer msg = make_wasm_buffer(make_example_msg(), proto_module_inst);
  const std::vector<uint32_t>& args = {msg.offset, msg.length};

    // Convert uint32_t args to wasm_val_t
    std::vector<wasm_val_t> wasm_args;
    for (uint32_t arg : args) {
    wasm_val_t val;
    val.kind = WASM_I32;
    val.of.i32 = arg;
    wasm_args.push_back(val);
    }

  auto func2 = get_exported_func("receive_message", proto_module_inst, wasm_args.data(), wasm_args.size());
  if (!func2) {
    fprintf(stderr, "receive_message wasm function is not found.\n");
    return 1;
  }

  if (!wasm_runtime_call_wasm_a(proto_exec_env, func2, 0, nullptr, wasm_args.size(), wasm_args.data())) {
    const char* ex = wasm_runtime_get_exception(proto_module_inst);
    fprintf(stderr, "receive_message trapped: %s\n", ex ? ex : "(null)");
  }
}
