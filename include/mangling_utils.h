#include "wasm_export.h"
#include <string>
#include <unordered_map>

struct WasmExport {
    const char *pretty;
    const char *mangled;
};

// Build the cache of exports for a
void cache_all_exports(wasm_module_inst_t module_inst,
                       const WasmExport export_names[]);

// Get a cached export by it's demangled name
WASMFunctionInstanceCommon* get_exported_func(const std::string& name, 
                                            wasm_module_inst_t module_inst);

