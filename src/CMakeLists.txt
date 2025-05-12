add_library(multicompress_lib STATIC)

target_sources(multicompress_lib
    PRIVATE
        rle.cpp
        huffman.cpp
)

target_include_directories(multicompress_lib
    PUBLIC
        ../include
)