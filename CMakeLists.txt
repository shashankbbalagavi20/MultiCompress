cmake_minimum_required(VERSION 3.10)
project(MultiCompress VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")

# Add subdirectory for source files
add_subdirectory(src)

# Add main executable
add_executable(multicompress main.cpp)
target_include_directories(multicompress PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(multicompress multicompress_lib)

# Add subdirectory for tests
add_subdirectory(test)

# Enable testing
enable_testing()

# Fetch and build Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.17.0
    CMAKE_ARGS     -DCMAKE_POLICY_VERSION_MINIMUM=3.5
)
FetchContent_MakeAvailable(googletest)

# Function to define the test executable and its dependencies
function(define_test_target)
  add_executable(multicompress_test test/test_main.cpp)
  target_link_libraries(multicompress_test PRIVATE GTest::gtest GTest::gtest_main multicompress_lib)
  target_include_directories(multicompress_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_include_directories(multicompress_test PRIVATE ${googletest_SOURCE_DIR}/include)
endfunction()

# Call the function AFTER FetchContent_MakeAvailable
define_test_target()