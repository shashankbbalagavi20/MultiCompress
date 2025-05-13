#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>

namespace huffman {

bool compress(const std::string& inputPath, const std::string& outputPath);
bool decompress(const std::string& inputPath, const std::string& outputPath);

} // namespace huffman

#endif // HUFFMAN_HPP