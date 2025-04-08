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

extern "C" int intToStr(int x, char *str, int str_len, int digit);
extern "C" int32_t calculate_native(wasm_exec_env_t exec_env, int32_t n, int32_t func1, int32_t func2);
extern "C" int32_t get_pow(wasm_exec_env_t exec_env, int32_t n, int32_t m);

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

// Call functions from WASM modules
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

int main() {
  wasm_module_t module = nullptr;
  wasm_module_inst_t module_inst = nullptr;
  wasm_exec_env_t exec_env = nullptr;
  char error_buf[128];
  uint32_t buf_size, stack_size = 8092, heap_size = 8092;

  static char global_heap_buf[512 * 1024];
  RuntimeInitArgs init_args;

  static NativeSymbol native_symbols[] = {
    { "intToStr", (void*)intToStr, "(i*~i)i", nullptr},
    { "calculate_native", (void*)calculate_native, "(iii)i", nullptr },
    { "get_pow", (void*)(get_pow), "(ii)i", nullptr }
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
  std::string wasmPath = "/home/eb/fyp/helloworld/build/wasm-apps/wasm_app.wasm";
  // read wasm file
  auto buffer = readFileToBytes(wasmPath);

  // load module and create execution environment
  module = load_module_minimal(buffer, module_inst, exec_env, stack_size, heap_size, error_buf, sizeof(error_buf));
  if (!module) {
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

  wasm_function_inst_t func = nullptr;
  wasm_function_inst_t func2 = nullptr;
  char *native_buffer = NULL;
  uint64_t wasm_buffer = 0;

  if (!(func = wasm_runtime_lookup_function(module_inst, "generate_float"))) {
    printf("The generate_float wasm function is not found.\n");
    return 1;
  }

  wasm_val_t results[1] = { { .kind = WASM_F32, .of.f32 = 0 } };
  wasm_val_t arguments[3] = {
      { .kind = WASM_I32, .of.i32 = 10 },
      { .kind = WASM_F64, .of.f64 = 0.000101 },
      { .kind = WASM_F32, .of.f32 = 300.002 },
  };

  // pass 4 elements for function arguments
  if (!wasm_runtime_call_wasm_a(exec_env, func, 1, results, 3, arguments)) {
      printf("call wasm function generate_float failed. %s\n",
            wasm_runtime_get_exception(module_inst));
      return 1;
  }

  float ret_val;
  ret_val = results[0].of.f32;
  printf("Native finished calling wasm function generate_float(), returned a "
        "float value: %ff\n",
        ret_val);

  uint32_t argv2[4];
  // makes the buffers refer to the same memory
  wasm_buffer = wasm_runtime_module_malloc(module_inst, 100, (void **)&native_buffer);

  memcpy(argv2, &ret_val, sizeof(float)); // the first argument
  argv2[1] = wasm_buffer; // the second argument is the wasm buffer address
  argv2[2] = 100;         //  the third argument is the wasm buffer size
  argv2[3] = 3; wasm_function_inst_t func = nullptr;
  wasm_function_inst_t func2 = nullptr;
  char *native_buffer = NULL;
  uint64_t wasm_buffer = 0;
  
  if (!(func = wasm_runtime_lookup_function(module_inst, "generate_float"))) {
    printf("The generate_float wasm function is not found.\n");
    return 1;
  }

  wasm_val_t results[1] = { { .kind = WASM_F32, .of.f32 = 0 } };
  wasm_val_t arguments[3] = {
      { .kind = WASM_I32, .of.i32 = 10 },
      { .kind = WASM_F64, .of.f64 = 0.000101 },
      { .kind = WASM_F32, .of.f32 = 300.002 },
  };

  // pass 4 elements for function arguments
  if (!wasm_runtime_call_wasm_a(exec_env, func, 1, results, 3, arguments)) {
      printf("call wasm function generate_float failed. %s\n",
            wasm_runtime_get_exception(module_inst));
      return 1;
  }

  float ret_val;
  ret_val = results[0].of.f32;
  printf("Native finished calling wasm function generate_float(), returned a "
        "float value: %ff\n",
        ret_val);

  // Next we will pass a buffer to the WASM function
  uint32_t argv2[4];

  // must allocate buffer from wasm instance memory space (never use pointer
  // from host runtime)
  wasm_buffer =
      wasm_runtime_module_malloc(module_inst, 100, (void **)&native_buffer);

  memcpy(argv2, &ret_val, sizeof(float)); // the first argument
  argv2[1] = wasm_buffer; // the second argument is the wasm buffer address
  argv2[2] = 100;         //  the third argument is the wasm buffer size
  argv2[3] = 3; //  the last argument is the digits after decimal point for converting float to string

  if (!(func2 =
            wasm_runtime_lookup_function(module_inst, "float_to_string"))) {
      printf(
          "The wasm function float_to_string wasm function is not found.\n");
      return 1;
  }

  if (wasm_runtime_call_wasm(exec_env, func2, 4, argv2)) {
      printf("Native finished calling wasm function: float_to_string, "
            "returned a formatted string: %s\n",
            native_buffer);
  }
  else {
      printf("call wasm function float_to_string failed. error: %s\n",
            wasm_runtime_get_exception(module_inst));
      return 1;
  }
}
