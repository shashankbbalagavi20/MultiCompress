#include <iostream>
#include <string>
#include "include/rle.hpp"
#include "include/huffman.hpp"
#include <limits>

int main(){
    std::string mode;
    std::string algorithm;
    std::string inputFile;
    std::string outputFile;

    std::cout << "Welcome to the Multi Compression Tool!" << std::endl;
    
    // Choose the mode
    while(true){
        std::cout << "Choose the mode (compress/decompress): -->";
        std::cin >> mode;
        if(mode == "compress" || mode == "decompress"){
            break;
        }
        else{
            std::cout << "Invalid mode. Please enter 'compress' or 'decompress'." << std::endl;
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
        }
    }

    // Choose the algorithm
    while(true){
        std::cout << "Choose the algorithm (rle/huffman): -->";
        std::cin >> algorithm;
        if(algorithm == "rle" || algorithm == "huffman"){
            break;
        }
        else{
            std::cout << "Invalid algorithm. Please enter 'rle' or 'huffman'." << std::endl;
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the invalid input
        }
    }

    // Get the input file path
    std::cout << "Enter the input file path: " << std::endl;
    std::cin >> inputFile;

    // Get the output file path
    std::cout << "Enter the output file path: " << std::endl;
    std::cin >> outputFile;

    if(algorithm == "rle"){
        if(mode == "compress"){
            if(rle::compress(inputFile, outputFile)){
                std::cout << "RLE compression completed successfully!" << std::endl;
                return 0;
            }
            else{
                std::cerr << "Sorry, RLE compression failed." << std::endl;
                return 1;
            }
        }
        if(mode == "decompress"){
            if(rle::decompress(inputFile, outputFile)){
                std::cout << "RLE decompression completed successfully!" << std::endl;
                return 0;
            }
            else{
                std::cerr << "Sorry, RLE decompression failed." << std::endl;
                return 1;
            }
        }
    }
    else if(algorithm == "huffman"){
        if(mode == "compress"){
            if(huffman::compress(inputFile, outputFile)){
                std::cerr << "Error : Huffman Compression not yet implemented" << std::endl;
                return 1;
            }
        }
        else if(mode == "decompress"){
            if(huffman::decompress(inputFile, outputFile)){
                std::cerr << "Error : Huffman Decompression not yet implemented" << std::endl;
                return 1;
            }
        }
    }
    return 1; // If something unexpected happened
}