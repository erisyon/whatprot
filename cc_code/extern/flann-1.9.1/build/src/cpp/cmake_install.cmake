# Install script for directory: /mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so.1.9.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so.1.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann_cpp.so.1.9.1"
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann_cpp.so.1.9"
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann_cpp.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so.1.9.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so.1.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann_cpp.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann_cpp_s.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so.1.9.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so.1.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    endif()
  endforeach()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann.so.1.9.1"
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann.so.1.9"
    "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann.so"
    )
  foreach(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so.1.9.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so.1.9"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libflann.so"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/build/lib/libflann_s.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/mnt/c/Users/Matthew/ICES/MarcotteLab/git/Fluoroseq/cc_code/extern/flann-1.9.1/src/cpp/flann" FILES_MATCHING REGEX "/[^/]*\\.h$" REGEX "/[^/]*\\.hpp$")
endif()

