#ifndef RLE_HPP
#define RLE_HPP

#include <string>
#include <vector>

namespace rle {

bool compress(const std::string& inputPath, const std::string& outputPath);
bool decompress(const std::string& inputPath, const std::string& outputPath);

} // namespace rle

#endif // RLE_HPP