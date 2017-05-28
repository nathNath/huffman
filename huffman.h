#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <node.h>

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm> // std::sort
#include <fstream> // std::fopen, std::fclose

class Huffman
{
private:
    std::string encodedString;
    std::string decodedString;
    std::string Filename; // nome do arquivo
    unsigned long totalFreq;
    unsigned long Frequencies[256]; // array de ocorrências
    Node* NodesArray[256];  // array de ponteiros para folhas
public:
    std::vector<Node*> Tree;
    Huffman(const std::string &filename);
    ~Huffman();
    bool readFile();
    void sortTree();
    void insert(Node* node);
    void buildTree();
    void courseTree(Node* node);
    void climbTree(Node* node);
    void encode();
    void decode();
};

#endif // HUFFMAN_H
