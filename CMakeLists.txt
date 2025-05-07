cmake_minimum_required(VERSION 3.10)
project(MultiCompress VERSION 1.0)

set(CMAKE_Cxx_STANDARD 17)
set(CMAKE_Cxx_STANDARD_REQUIRED ON)

# Add subdirectory for source files
add_subdirectory(src)

# Add main executable
add_executable(multicompress main.cpp)

# Link the main executable with the compression library
target_link_libraries(multicompress multicompress_lib)

# Add subdirectory for tests
add_subdirectory(test)

# Enable testing
enable_testing()