# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/eb/fyp/grpc/examples/cpp/third_party/abseil-cpp"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src/absl-build"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/tmp"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src/absl-stamp"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src"
  "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src/absl-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src/absl-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/eb/fyp/grpc/examples/cpp/helloworld/cmake/build/absl/src/absl-stamp${cfgdir}") # cfgdir has leading slash
endif()
