#include "../include/huffman.hpp"
#include "fstream"
#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

namespace huffman {

// Helper struct for the priority queue
struct Node {
    unsigned char ch;
    int freq;
    Node* left;
    Node* right;

    Node(unsigned char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
    ~Node(){ delete left; delete right;}
};

// Custom comparison for the priority queue(min-heap based on frequency)
struct CompareNodes {
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(const std::map<unsigned char, int>& freq){
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> pq;

    // Create a leaf node for each character and add it to the priority queue
    for(const auto& pair : freq){
        pq.push(new Node(pair.first, pair.second));
    }

    // Combine nodes until one node (the root) is left
    while(pq.size() != 1){
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        Node* newNode = new Node('\0', left->freq + right->freq); 
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }
    return pq.top(); // The root node
}

// Function to generate Huffman codes from the Huffman tree
void generateHuffmanCodes(Node* root, const std::string& code, std::map<unsigned char, std::string>& huffmanCode) {
    if (!root) return;

    if (root->ch != '\0') {
        huffmanCode[root->ch] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCode);
    generateHuffmanCodes(root->right, code + "1", huffmanCode);
}

bool compress(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream outputFile(outputPath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return false;
    }

    // 1. Calculate frequency of each character
    std::map<unsigned char, int> freq;
    unsigned char ch;
    while (inputFile.get(reinterpret_cast<char&>(ch))) {
        freq[ch]++;
    }
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg); // Reset file pointer

    // 2. Build Huffman Tree
    Node* root = buildHuffmanTree(freq);

    // 3. Generate Huffman Codes
    std::map<unsigned char, std::string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);

    // 4. Write the frequency table to the output file (for decompression)
    outputFile << freq.size() << std::endl; // Number of unique characters
    for (auto pair : freq) {
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    // 5. Compress the input data
    std::string encodedData = "";
    while (inputFile.get(reinterpret_cast<char&>(ch))) {
        encodedData += huffmanCode[ch];
    }

    // Pad the encoded data to be a multiple of 8 bits
    int padding = 8 - (encodedData.length() % 8);
    if (padding == 8) padding = 0;
    for (int i = 0; i < padding; ++i) {
        encodedData += '0';
    }

    // Write padding info and encoded data to the output file
    outputFile << padding << std::endl;
    for (size_t i = 0; i < encodedData.length(); i += 8) {
        std::string byteStr = encodedData.substr(i, 8);
        unsigned char byte = std::stoi(byteStr, nullptr, 2);
        outputFile.write(reinterpret_cast<const char*>(&byte), 1);
    }

    delete root; // Clean up the Huffman tree
    std::cout << "Huffman Compression successful!" << std::endl;
    return true;
}

bool decompress(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream inputFile(inputPath, std::ios::binary);
    std::ofstream outputFile(outputPath, std::ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return false;
    }

    // 1. Read the frequency table
    int numChars;
    inputFile >> numChars;
    inputFile.ignore(); // Consume the newline

    std::map<unsigned char, int> freq;
    for (int i = 0; i < numChars; ++i) {
        unsigned char c;
        int f;
        inputFile >> c >> f;
        inputFile.ignore(); // Consume the newline
        freq[c] = f;
    }

    // 2. Rebuild the Huffman Tree
    Node* root = buildHuffmanTree(freq);

    // 3. Generate Huffman Codes (needed for decoding)
    std::map<unsigned char, std::string> huffmanCode;
    generateHuffmanCodes(root, "", huffmanCode);
    std::map<std::string, unsigned char> reverseHuffmanCode;
    for (auto pair : huffmanCode) {
        reverseHuffmanCode[pair.second] = pair.first;
    }

    // 4. Read padding and encoded data
    int padding;
    inputFile >> padding;
    inputFile.ignore(); // Consume the newline

    std::vector<unsigned char> encodedBytes;
    unsigned char encodedByte;
    while (inputFile.read(reinterpret_cast<char*>(&encodedByte), 1)) {
        encodedBytes.push_back(encodedByte);
    }

    // 5. Decode the data
    std::string decodedData = "";
    std::string currentCode = "";
    for (unsigned char byte : encodedBytes) {
        for (int i = 7; i >= 0; --i) {
            currentCode += ((byte >> i) & 1) ? '1' : '0';
            if (reverseHuffmanCode.count(currentCode)) {
                decodedData += reverseHuffmanCode[currentCode];
                currentCode = "";
            }
        }
    }
    if (padding > 0) {
        decodedData = decodedData.substr(0, decodedData.length() - padding);
    }

    outputFile << decodedData;

    delete root; // Clean up the Huffman tree
    std::cout << "Huffman Decompression successful!" << std::endl;
    return true;
}

} // namespace huffman