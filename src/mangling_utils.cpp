#include "mangling_utils.h"
#include <cxxabi.h>
#include <unordered_map>
#include <mutex>
#include <cstdio>

#include <wasm_export.h>

using ExportMap = std::unordered_map<std::string, WASMFunctionInstanceCommon*>;

static std::unordered_map<wasm_module_inst_t, ExportMap>  exports_map;
static std::mutex map_mutex;

// if want just one cache for all modules could just have the Inner map and not do m.clear()
void cache_all_exports(wasm_module_inst_t inst,
                      const WasmExport exports[]) {
  std::lock_guard<std::mutex> guard(map_mutex);
  auto &map = exports_map[inst]; 
  map.clear();

  for (auto *e = exports; e->pretty; ++e) {
    if (auto *fn = wasm_runtime_lookup_function(inst, e->mangled)) {
      map.emplace(e->pretty, fn);
    }
  }
}

WASMFunctionInstanceCommon* get_exported_func(const std::string& name, wasm_module_inst_t module_inst) {
  std::lock_guard<std::mutex> guard(map_mutex);

  // find module map
  auto mod = exports_map.find(module_inst);
  if (mod == exports_map.end()) {
    std::fprintf(stderr,
                 "ERROR: module_inst %p not cached\n", (void*)module_inst);
    return nullptr;
  }

  // find function
  auto &map = mod->second;
  auto func = map.find(name);
  if (func == map.end()) {
    std::fprintf(stderr,
                 "ERROR: export '%s' not found in module %p\n",
                 name.c_str(), (void*)module_inst);
    return nullptr;
  }
  return func->second;
}