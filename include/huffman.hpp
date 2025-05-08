#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include <string>
#include <vector>

namespace huffman {

bool compress(const std::string& input, std::string& output);
bool decompress(const std::string& input, std::string& output);

} // namespace huffman

#endif // HUFFMAN_HPP