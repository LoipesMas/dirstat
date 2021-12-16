cmake_minimum_required (VERSION 3.20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)
project (dirstat)

add_executable (dirstat main.cpp pool.cpp dirstat.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(dirstat PRIVATE Threads::Threads)
set_property(TARGET dirstat PROPERTY CXX_STANDARD 17)
