/*
*[.wasm file] --(read)--> [byte buffer]
    ↓
[wasm_runtime_load]
    ↓
[wasm_runtime_instantiate]
    ↓
[wasm_runtime_create_exec_env]
    ↓
[wasm_runtime_lookup_function]
    ↓
[wasm_runtime_call_wasm_a]
    ↓
[return value or result]
 *
 */

// host.cpp (minimal WAMR runtime host)
#include <stdio.h>
#include <string>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "wasm_export.h"

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
  size_t fsize = statbuf.st_size;
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

// Utility to load a Wasm module and initialises wamr runtime and creates execution environment
wasm_module_t load_module(const char* path, wasm_module_inst_t &out_inst, wasm_exec_env_t &out_env) {
    uint8_t *wasm_file_buf = nullptr;
    uint32_t wasm_file_size = 0;

    FILE *fp = fopen(path, "rb");
    if (!fp) {
        printf("Failed to open %s\n", path);
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    wasm_file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    wasm_file_buf = new uint8_t[wasm_file_size];
    fread(wasm_file_buf, 1, wasm_file_size, fp);
    fclose(fp);

    RuntimeInitArgs init_args;
    memset(&init_args, 0, sizeof(init_args));
    static char global_heap_buf[512 * 1024];
    init_args.mem_alloc_type = Alloc_With_Pool;
    init_args.mem_alloc_option.pool.heap_buf = global_heap_buf;
    init_args.mem_alloc_option.pool.heap_size = sizeof(global_heap_buf);

    wasm_runtime_full_init(&init_args);

    char error_buf[128];
    wasm_module_t module = wasm_runtime_load(wasm_file_buf, wasm_file_size, error_buf, sizeof(error_buf));
    delete[] wasm_file_buf;
    if (!module) {
        printf("Error loading module: %s\n", error_buf);
        exit(1);
    }

    out_inst = wasm_runtime_instantiate(module, 64 * 1024, 64 * 1024, error_buf, sizeof(error_buf));
    if (!out_inst) {
        printf("Error instantiating module: %s\n", error_buf);
        exit(1);
    }

    out_env = wasm_runtime_create_exec_env(out_inst, 64 * 1024);
    return module;
}

// used to call functions from WASM modules
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


// int main_old() {
//     wasm_module_inst_t client_inst, server_inst;
//     wasm_exec_env_t client_env, server_env;
//
//     load_module("/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/test_wasm_app.wasm", client_inst, client_env);
//     load_module("/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/server.wasm", server_inst, server_env);
//
//
//     const char* name = call_func(client_inst, client_env, "mul5");
//     printf("%s\n", name);
//     // const char* response = call_func(server_inst, server_env, "handle_request", name);
//     // call_func(client_inst, client_env, "handle_response", response);
//
//     return 0;
// }

int main() {
  wasm_module_t module = NULL;
  wasm_module_inst_t module_inst = NULL;
  wasm_exec_env_t exec_env = NULL;
  wasm_function_inst_t func = NULL;
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
  std::string wasmPath = "/home/eb/fyp/grpc/examples/cpp/helloworld_wasm/test_wasm_app.wasm";
  auto buffer = readFileToBytes(wasmPath);

  module = wasm_runtime_load(buffer.data(), buffer.size(), error_buf,
                             sizeof(error_buf));
  if (!module) {
    printf("Load wasm module failed. error: %s\n", error_buf);
    return 1;
  }

  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size,
                                         error_buf, sizeof(error_buf));

  if (!module_inst) {
    printf("Instantiate wasm module failed. error: %s\n", error_buf);
    return 1;
  }

  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
  if (!exec_env) {
    printf("Create wasm execution environment failed.\n");
    return 1;
  }

  if (!(func = wasm_runtime_lookup_function(module_inst, "mul5"))) {
    printf("The mul5 wasm function is not found.\n");
    return 1;
  }

  wasm_val_t results[1] = { { .kind = WASM_I32, .of.f32 = 0 } };
  if (!wasm_runtime_call_wasm_a(exec_env, func, 1, results, 0, nullptr)) {
    printf("call wasm function mul5 failed. %s\n",
           wasm_runtime_get_exception(module_inst));
    return 1;
  }
}
