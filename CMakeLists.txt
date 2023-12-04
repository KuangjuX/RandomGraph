cmake_minimum_required(VERSION 3.17)
project(RandomGraph C CXX)

option(BUILD_TEST "Build test code" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(BUILD_TEST)
    include_directories(3rd-party/googletest/googletest/include)
    add_subdirectory(3rd-party/googletest)
endif()

add_compile_options(-Wall)
add_compile_options(-Werror)

enable_testing()


file(GLOB_RECURSE SOURCE 
    src/*.cpp
)

add_library(randomgraph SHARED ${SOURCE})

add_compile_options(-Wall)
add_compile_options(-Werror)

# target_link_directories(tilegraph PRIVATE 3rd-party/fmt/build)
# target_link_libraries(tilegraph PRIVATE fmt)

# function(build_test files)
#   # Non-recursive glob for skip failed tests
#   file(GLOB TEST_SOURCES ${files})
#   foreach(testsourcefile ${TEST_SOURCES})
#     get_filename_component(testname ${testsourcefile} NAME_WE)
#     add_executable(${testname} ${testsourcefile})
#     target_link_libraries(${testname} tilegraph GTest::gtest_main)
#     add_test(NAME ${testname} COMMAND ${testname})
#   endforeach(testsourcefile ${TEST_SOURCES})
# endfunction()

# if(BUILD_TEST)
#     build_test(tests/operators/*.cpp)
#     build_test(tests/graph/*.cpp)
#     build_test(tests/fusion/*.cpp)
#     if(USE_CUDA)
#       build_test(tests/codegen/*.cpp)
#     endif()
# endif()
