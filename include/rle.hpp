#ifndef RLE_HPP
#define RLE_HPP

#include <string>
#include <vector>

namespace rle {

bool compress(const std::string& input, std::string& output);
bool decompress(const std::string& input, std::string& output);

} // namespace rle

#endif // RLE_HPP