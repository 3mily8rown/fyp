# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-src")
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-src")
endif()
file(MAKE_DIRECTORY
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-build"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/tmp"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/src"
  "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/cmake-build-debug/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
