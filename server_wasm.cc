// server_wasm.cc

#include <string>
#include <cstring>

extern "C" {

  const char* handle_request(const char* name) {
    static std::string reply;
    reply = "Hello ";
    reply += name;
    return reply.c_str();
  }

}
