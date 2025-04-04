# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-src"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-build"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/tmp"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src"
  "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/eb/fyp/helloworld/build/_deps/wamr_ext-subbuild/wamr_ext-populate-prefix/src/wamr_ext-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
