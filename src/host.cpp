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

#include "host_utils.h"
#include "host_proto.h"

#include "/home/eb/fyp/helloworld/proto_messages/generated_full/message.pb.h"       

extern "C" int intToStr(int x, char *str, int str_len, int digit);
extern "C" int32_t calculate_native(wasm_exec_env_t exec_env, int32_t n, int32_t func1, int32_t func2);
extern "C" int32_t get_pow(wasm_exec_env_t exec_env, int32_t n, int32_t m);
extern "C" void pass_to_native_wrapper(wasm_exec_env_t exec_env, uint32_t offset, uint32_t length);

MyMessage make_example_msg() {
  MyMessage m;
  m.set_id(42);
  m.set_name("hello from native");
  return m;
}

// used to read WASM bytecode at runtime (into byte array)
std::vector<uint8_t> readFileToBytes(const std::string& path)
{
  int fd = open(path.c_str(), O_RDONLY);
  if (fd < 0) {
    throw std::runtime_error("Couldn't open file " + path);
  }
  struct stat statbuf;
  int staterr = fstat(fd, &statbuf);
  if (staterr < 0) {
    throw std::runtime_error("Couldn't stat file " + path);
  }
  ssize_t fsize = statbuf.st_size;
  posix_fadvise(fd, 0, 0, POSIX_FADV_SEQUENTIAL);
  std::vector<uint8_t> result;
  result.resize(fsize);
  int cpos = 0;
  while (cpos < fsize) {
    int rc = read(fd, result.data(), fsize - cpos);
    if (rc < 0) {
      perror("Couldn't read file");
      throw std::runtime_error("Couldn't read file " + path);
    } else {
      cpos += rc;
    }
  }
  close(fd);
  return result;
}

// read wasm file, load module and create execution environment
wasm_module_t load_module_minimal(
  std::vector<uint8_t>& buffer,
  wasm_module_inst_t& out_inst,
  wasm_exec_env_t& out_env,
  uint32_t stack_size,
  uint32_t heap_size,
  char* error_buf,
  size_t error_buf_size) {

  wasm_module_t module = wasm_runtime_load(buffer.data(), buffer.size(), error_buf, error_buf_size);
  if (!module) {
    printf("Load wasm module failed. error: %s\n", error_buf);
    return nullptr;
  }

  out_inst = wasm_runtime_instantiate(module, stack_size, heap_size, error_buf, error_buf_size);
  if (!out_inst) {
    printf("Instantiate wasm module failed. error: %s\n", error_buf);
    wasm_runtime_unload(module);
    return nullptr;
  }

  out_env = wasm_runtime_create_exec_env(out_inst, stack_size);
  if (!out_env) {
    printf("Create wasm execution environment failed.\n");
    wasm_runtime_deinstantiate(out_inst);
    wasm_runtime_unload(module);
    return nullptr;
  }

  return module;
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

  static NativeSymbol native_symbols[] = {
    { "intToStr", (void*)intToStr, "(i*~i)i", nullptr},
    { "calculate_native", (void*)calculate_native, "(iii)i", nullptr },
    { "get_pow", (void*)(get_pow), "(ii)i", nullptr },
    { "pass_to_native", (void*)pass_to_native_wrapper, "(ii)", nullptr}
  };

  memset(&init_args, 0, sizeof(RuntimeInitArgs));
  init_args.mem_alloc_type = Alloc_With_Pool;
  init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
  init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

  // Native symbols need below registration phase
  init_args.n_native_symbols = sizeof(native_symbols) / sizeof(NativeSymbol);
  init_args.native_module_name = "env";
  init_args.native_symbols = native_symbols;

  if (!wasm_runtime_full_init(&init_args)) {
    printf("Init runtime environment failed.\n");
    return -1;
  }

  wasm_runtime_set_log_level(WASM_LOG_LEVEL_VERBOSE);

  // TODO avoid hardcoding
  // Load first wasm module
  std::string wasmPath = "/home/eb/fyp/helloworld/build/wasm-apps/wasm_app.wasm";
  auto buffer = readFileToBytes(wasmPath);

  // load module and create execution environment
  module = load_module_minimal(buffer, module_inst, exec_env, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!module) {
    return 1;
  }

  // Load second wasm module
  wasmPath = "/home/eb/fyp/helloworld/build/wasm-apps/protowasm_app.wasm";
  auto proto_buffer = readFileToBytes(wasmPath);

  // load module and create execution environment
  proto_module = load_module_minimal(proto_buffer, proto_module_inst, proto_exec_env, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!proto_module) {
    return 1;
  }


  //Calling WASM functions:
  int32_t result;

  // expecting 10
  if (call_int_func(module_inst, exec_env, "mul5", {2}, result) == 0) {
    printf("Result from mul5(): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 70
  if (call_int_func(module_inst, exec_env, "mul7", {10}, result) == 0) {
    printf("Result from mul7(10): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 88
  if (call_int_func(module_inst, exec_env, "mul", {8,11}, result) == 0) {
    printf("Result from mul(8,11): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 16
  if (call_int_func(module_inst, exec_env, "power", {2,4}, result) == 0) {
    printf("Result from power(2,4): %d\n", result);
  } else
  {
    return 1;
  }

  // expecting 96
  if (call_int_func(module_inst, exec_env, "calculate", {8}, result) == 0) {
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
  wasm_function_inst_t func1 = wasm_runtime_lookup_function(proto_module_inst, "send_message");
  if (!func1) {
    printf("Function not found in wasm module :(");
  }
  if (!wasm_runtime_call_wasm(proto_exec_env, func1, 0, nullptr)) {
    const char* ex = wasm_runtime_get_exception(proto_module_inst);
    fprintf(stderr, "send_message trapped: %s\n", ex ? ex : "(null)");
  }

  // sending a message from native to wasm with protobuffers
  wasm_function_inst_t func2 = wasm_runtime_lookup_function(proto_module_inst, "receive_message");
  if (!func2) {
    printf("Function not found in wasm module :(");
  }

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

  if (!wasm_runtime_call_wasm_a(proto_exec_env, func2, 0, nullptr, wasm_args.size(), wasm_args.data())) {
    const char* ex = wasm_runtime_get_exception(proto_module_inst);
    fprintf(stderr, "receive_message trapped: %s\n", ex ? ex : "(null)");
  }
}
