cmake_minimum_required (VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)
project (dirstat)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(tests)

add_executable (dirstat main.cpp pool.cpp dirstat.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(dirstat PRIVATE Threads::Threads)

add_library(dirstatl STATIC pool.cpp dirstat.cpp)

