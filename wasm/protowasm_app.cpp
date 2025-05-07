#include <stdio.h>
#include <cstdint>

#include "pb_encode.h"
#include "pb_decode.h"
#include "message.pb.h"

extern "C" void pass_to_native(uint32_t offset, uint32_t length);

extern "C" void* malloc(size_t size);
struct MessageBuffer {
    uint8_t* ptr;
    uint32_t size;
};

MessageBuffer message_to_buffer(const MyMessage msg) {
    // Allocate memory inside the WASM module's heap
    uint32_t size = 128;
    uint8_t* buffer_ptr = (uint8_t*)malloc(size);
    if (!buffer_ptr) return {nullptr, 0};

    // Create a Nanopb stream pointing to this WASM memory
    pb_ostream_t stream = pb_ostream_from_buffer(buffer_ptr, size);

    // Encode into the WASM buffer
    if (!pb_encode(&stream, MyMessage_fields, &msg)) {
        printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
        return {nullptr, 0}; 
    }

    return {buffer_ptr, static_cast<uint32_t>(stream.bytes_written)};
}

void send_message() {
    MyMessage msg = MyMessage_init_default;
    msg.id = 42;
    strcpy(msg.name, "hello from wasm");

    // nanopb doesnt have .SerializeToString()
    MessageBuffer buf = message_to_buffer(msg);
    if (buf.ptr && buf.size > 0) {
        pass_to_native((uint32_t)buf.ptr, buf.size);
    }
}

void receive_message(uint32_t offset, uint32_t length) {
    // Turn linear memory into nanopb stream
    pb_istream_t stream = pb_istream_from_buffer((pb_byte_t*)(uintptr_t)offset, length);

    // Decode into nanopb struct:
    MyMessage msg = MyMessage_init_zero;
    if (!pb_decode(&stream, MyMessage_fields, &msg)) {
        printf("Wasm decode failed: %s\n", PB_GET_ERROR(&stream));
        return;
    }
    
    printf("Wasm recv: \"%s\"\n", msg.name);
}
