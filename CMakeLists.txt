cmake_minimum_required(VERSION 3.0)
project(impromptu)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)
include(ExternalProject)
include(FindPkgConfig)

pkg_search_module(LIBGIT2 libgit2)
if(NOT ${LIBGIT2_FOUND})
    message("-- Did not find libgit2, building it")
    ExternalProject_Add(
        libgit2
        SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/libgit2
        CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=OFF -DUSE_SSH=OFF -DUSE_HTTPS=OFF -DUSE_NSEC=OFF -DBUILD_CLAR=OFF -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external
    )
    set(LIBGIT2_LIBRARIES git2 pthread z)
else()
  message("-- Using libgit2 from prefix ${LIBGIT2_PREFIX}")
  include_directories(SYSTEM ${LIBGIT2_INCLUDEDIR} ${LIBGIT2_INCLUDE_DIRS})
  link_directories(${LIBGIT2_LIBDIR} ${LIBGIT2_LIBRARY_DIRS})
endif()

ExternalProject_Add(
    google-benchmark
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/benchmark
    CMAKE_ARGS -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/external
)

link_directories(impromptu ${CMAKE_BINARY_DIR}/external/lib)
include_directories(SYSTEM ${CMAKE_BINARY_DIR}/external/include)

check_include_file_cxx(pwd.h        PWD_H_FOUND)
check_include_file_cxx(unistd.h     UNISTD_H_FOUND)
check_include_file_cxx(sys/ioctl.h  SYS_IOCTL_H_FOUND)

check_cxx_symbol_exists(gethostname unistd.h GETHOSTNAME_FOUND)
check_cxx_symbol_exists(geteuid     unistd.h GETEUID_FOUND)
check_cxx_symbol_exists(getpwuid    pwd.h    GETPWUID_FOUND)
check_cxx_symbol_exists(getcwd      unistd.h GETCWD_FOUND)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(impromptu STATIC
    src/impromptu/external_info.cpp
    src/impromptu/git.cpp
    src/impromptu/host.cpp
    src/impromptu/shell.cpp
    src/impromptu/subprocess.cpp
    src/impromptu/terminal.cpp
    src/impromptu/time.cpp
    src/impromptu/user.cpp
    src/impromptu/vcs.cpp
)
target_link_libraries(impromptu stdc++fs)

add_executable(fkoehler src/fkoehler.cpp)
target_link_libraries(fkoehler ${LIBGIT2_LIBRARIES} impromptu)

add_executable(bench src/bench.cpp)
target_link_libraries(bench benchmark benchmark_main pthread impromptu)

configure_file(${CMAKE_SOURCE_DIR}/tools/run_bench ${CMAKE_BINARY_DIR}/run_bench COPYONLY)

# install(TARGETS fkoehler RUNTIME DESTINATION bin)
