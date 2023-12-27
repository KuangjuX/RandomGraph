cmake_minimum_required(VERSION 3.17)
project(RandomGraph C CXX)

option(BUILD_TEST "Build test code" ON)

# 添加选项
option(ENABLE_DEBUG "启用调试模式" OFF)

# 根据选项设置宏定义
if(ENABLE_DEBUG)
    add_compile_definitions(DEBUG)
    message(STATUS "Enable debug mode")
else()
    message(STATUS "Disable debug mode")
endif()

if(ENABLE_ACC)
    add_compile_definitions(ACC)
    message(STATUS "Enable acc mode")
else()
    message(STATUS "Disable acc mode")
endif()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src)
include_directories(3rd-party/fmt/include)
add_definitions(-D FMT_HEADER_ONLY)

if(BUILD_TEST)
    include_directories(3rd-party/googletest/googletest/include)
    add_subdirectory(3rd-party/googletest)
endif()

file(GLOB_RECURSE SOURCE 
    src/*.cpp
)


enable_testing()

add_compile_options(-Wall)
add_compile_options(-Werror)

add_library(randomgraph SHARED ${SOURCE})
target_link_directories(randomgraph PRIVATE 3rd-party/fmt/build)
target_link_libraries(randomgraph PRIVATE fmt)


function(build_test files)
  # Non-recursive glob for skip failed tests
  file(GLOB TEST_SOURCES ${files})
  foreach(testsourcefile ${TEST_SOURCES})
    get_filename_component(testname ${testsourcefile} NAME_WE)
    add_executable(${testname} ${testsourcefile})
    target_link_libraries(${testname} randomgraph GTest::gtest_main)
    add_test(NAME ${testname} COMMAND ${testname})
  endforeach(testsourcefile ${TEST_SOURCES})
endfunction()

if(BUILD_TEST)
    build_test(tests/*.cpp)
endif()
