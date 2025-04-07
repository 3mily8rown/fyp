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

// int
// intToStr(int x, char *str, int str_len, int digit);
// int
// get_pow(int x, int y);
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

// calls a functions that takes in vector of int args and outputs 1 int
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
    //   {
    //     "intToStr", // the name of WASM function name
    //     intToStr,   // the native function pointer
    //     "(i*~i)i",  // the function prototype signature, avoid to use i32
    //     NULL        // attachment is NULL
    // },
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
  std::string wasmPath = "/home/eb/fyp/helloworld/build/wasm-apps/wasm_app.wasm";
  // read wasm file
  auto buffer = readFileToBytes(wasmPath);

  // Creating and Initialising WAMR runtime
  // load wamr runtime
  module = wasm_runtime_load(buffer.data(), buffer.size(), error_buf,
                             sizeof(error_buf));
  if (!module) {
    printf("Load wasm module failed. error: %s\n", error_buf);
    return 1;
  }

  // instantiate wamr
  module_inst = wasm_runtime_instantiate(module, stack_size, heap_size,
                                         error_buf, sizeof(error_buf));

  if (!module_inst) {
    printf("Instantiate wasm module failed. error: %s\n", error_buf);
    return 1;
  }

  // create wamr exec env
  exec_env = wasm_runtime_create_exec_env(module_inst, stack_size);
  if (!exec_env) {
    printf("Create wasm execution environment failed.\n");
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

  // expecting 96 (8*7 + 8*5)
  if (call_int_func(module_inst, exec_env, "calculate", {8}, result) == 0) {
    printf("Result from calculate(8): %d\n", result);
  } else
  {
    return 1;
  }
}
