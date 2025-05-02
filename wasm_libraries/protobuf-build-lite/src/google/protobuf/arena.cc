#include "google/protobuf/arena.h"
#include <typeinfo>

namespace google {
namespace protobuf {

// Declare the methods yourself since they aren't in arena.h
void* Arena::AllocateAlignedWithHook(size_t n, const std::type_info*) {
  return operator new(n);  // No-op alignment for WASM
}

void* Arena::AllocateAlignedWithCleanup(size_t n, size_t /*align*/, void (* /*destructor*/)(void*)) {
  return operator new(n);  // No cleanup for now
}

}  // namespace protobuf
}  // namespace google
