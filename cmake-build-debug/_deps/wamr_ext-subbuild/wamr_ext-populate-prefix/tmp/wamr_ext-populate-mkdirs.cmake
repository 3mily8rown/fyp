# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-src")
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-src")
endif()
file(MAKE_DIRECTORY
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-build"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/tmp"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
