// client_wasm.cc

#include <string>
#include <cstring>

extern "C" {

  const char* generate_request() {
    std::string name = "Alice";
    printf("Hello from WASM: %s\n", name.c_str());
    return name.c_str();
  }

  void handle_response(const char* response) {
    // Just print for now (in real Wasm this would go to stdout via host)
    // WAMR supports stdout so this will appear when run with `iwasm`
    printf("WASM CLIENT received response: %s\n", response);
  }

  void hello() {
    printf("Hello from WASM");
  }
}
