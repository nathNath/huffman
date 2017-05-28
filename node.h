#ifndef NODE_H
#define NODE_H

#include <iostream>

struct Node
{
    // Constructor
    Node(int byte = -1,
         long freq = 0,
         Node* up = NULL,
         Node* left = NULL,
         Node* right = NULL);

    // Destructor
    ~Node();

    // Public members
    int Byte;
    long Freq;
    char Edge;
    Node* Up;
    Node* Left;
    Node* Right;
    std::string code;

    // Sort order
    static bool Descending(const Node* n1, const Node* n2);
};

#endif // NODE_H
