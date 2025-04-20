find generated -maxdepth 1 -type f -delete

protoc --proto_path=. --cpp_out=generated message.proto
