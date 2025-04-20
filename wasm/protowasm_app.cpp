#include <iostream>
#include <cstdint>

#include "message.pb.h"

extern "C" void pass_to_native(uint32_t offset, uint32_t length);

extern "C" void* malloc(size_t size);

extern "C" void send_message() {
    app::messages::MyMessage msg;
    msg.set_id(42);
    msg.set_name("hello from wasm");

    std::string serialized;
    msg.SerializeToString(&serialized);

    void* buffer_ptr = malloc(serialized.size());
    uint32_t buffer_offset = reinterpret_cast<uint32_t>(buffer_ptr);

    memcpy(buffer_ptr, serialized.data(), serialized.size());
    pass_to_native(buffer_offset, serialized.size());
}
