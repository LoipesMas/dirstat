cmake_minimum_required (VERSION 3.20)

find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Test Test.cpp)
target_link_libraries(Test PUBLIC
    gtest_main
    dirstatl
)

add_test(
    NAME Test
    COMMAND Test
)

add_custom_command(
        TARGET Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/test/
            ${CMAKE_CURRENT_BINARY_DIR}/test_files/
)

add_custom_command(
        TARGET Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/test/*
            ${CMAKE_CURRENT_BINARY_DIR}/test_files/
)
