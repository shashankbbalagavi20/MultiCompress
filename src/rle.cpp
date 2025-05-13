#include "../include/rle.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

namespace rle {

bool compress(const std::string& inputPath, const std::string& outputPath){
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream outputFile(outputPath, std::ios::binary);

    if(!inputFile.is_open()){
        std::cerr << "Error: could not open input file: " << inputPath << std::endl;
        return false;
    }
    if(!outputFile.is_open()){
        std::cerr << "Error: could not open output file: " << outputPath << std::endl;
        return false;
    }

    std::vector<unsigned char> buffer(1024);

    while(inputFile.read(reinterpret_cast<char*>(buffer.data()), buffer.size())){
        size_t count = inputFile.gcount();
        for(size_t i=0; i<count; ++i){
            unsigned char currentByte = buffer[i];
            size_t runLength = 1;
            while(i + runLength < count && buffer[i+runLength] == currentByte && runLength < 255){
                runLength++;
            }
            outputFile.write(reinterpret_cast<const char*>(&runLength), sizeof(runLength));
            outputFile.write(reinterpret_cast<const char*>(&currentByte), sizeof(currentByte));
            i += runLength - 1;
        }
    }
    if(inputFile.eof() && inputFile.gcount() > 0){
        for(size_t i=0; i< static_cast<size_t>(inputFile.gcount()); ++i){
            unsigned char currentByte = buffer[i];
            size_t runLength = 1;
            while(i + runLength < static_cast<size_t>(inputFile.gcount()) && buffer[i+runLength] == currentByte && runLength < 255){
                runLength++;
            }
            outputFile.write(reinterpret_cast<const char*>(&runLength), sizeof(runLength));
            outputFile.write(reinterpret_cast<const char*>(&currentByte), sizeof(currentByte));
            i += runLength - 1;
        }
    }
    else if(inputFile.fail() && !inputFile.eof()){
        std::cerr << "Error: failed to read input file: " << inputPath << std::endl;
        return false;
    }
    std::cout << "RLE Compression successful!" << std::endl;
    return true;
}

bool decompress(const std::string& inputPath, const std::string& outputPath){
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream outputFile(outputPath, std::ios::binary);

    if(!inputFile.is_open()){
        std::cerr << "Error: could not open input file: " << inputPath << std::endl;
        return false;
    }    
    if(!outputFile.is_open()){
        std::cerr << "Error: could not open output file: " << outputPath << std::endl;
        return false;
    }

    unsigned char runLength;
    unsigned char value;
    while(inputFile.read(reinterpret_cast<char*>(&runLength), sizeof(runLength))){
        if(!inputFile.read(reinterpret_cast<char*>(&value), sizeof(value))){
            std::cerr << "Error: Invalid compressed data format in " << inputPath << std::endl;
            return false;
        }
        for(size_t i=0; i<runLength; ++i){
            outputFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }
    }
    if(inputFile.fail() && !inputFile.eof()){
        std::cerr << "Error reading input file: " << inputPath << std::endl;
        return false;
    }

    std::cout << "RLE Decompression successful: " << inputPath << " -> " << outputPath << std::endl;
    return true; 
}

} // namespace rle