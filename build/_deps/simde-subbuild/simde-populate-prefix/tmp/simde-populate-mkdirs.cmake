# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/eb/fyp/helloworld/build/_deps/simde-src"
  "/home/eb/fyp/helloworld/build/_deps/simde-build"
  "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix"
  "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/tmp"
  "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp"
  "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/src"
  "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/build/_deps/simde-subbuild/simde-populate-prefix/src/simde-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
