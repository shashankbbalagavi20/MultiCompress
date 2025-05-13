#include <gtest/gtest.h>
#include "../include/rle.hpp"
#include "../include/huffman.hpp"
#include <string>

TEST(RLECompression, SimpleCompression) {
    std::string input = "AAABBBCCCDD";
    std::string compressed;
    rle::compress(input, compressed);
    ASSERT_EQ(compressed, "3A3B3C2D");
}

TEST(RLEDecompression, SimpleDecompression) {
    std::string compressed = "3A3B3C2D";
    std::string decompressed;
    rle::decompress(compressed, decompressed);
    ASSERT_EQ(decompressed, "AAABBBCCCDD");
}

TEST(HuffmanCompression, SimpleCompression) {
    std::string input = "hello world";
    std::string compressed;
    huffman::compress(input, compressed);
    // Add your assertions here (you'll need to know the expected compressed output)
}

TEST(HuffmanDecompression, SimpleDecompression) {
    std::string compressed = "/* some compressed data */"; // Replace with actual compressed data
    std::string decompressed;
    huffman::decompress(compressed, decompressed);
    ASSERT_EQ(decompressed, "hello world");
}