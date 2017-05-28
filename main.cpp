#include <huffman.h>

int main()
{
    Huffman* huffman = new Huffman("file.txt");
    huffman->readFile();
    huffman->buildTree();
    huffman->encode();
    huffman->decode();
    delete huffman;
    return 0;
}
