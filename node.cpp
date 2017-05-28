#include <node.h>

Node::Node(int byte,
           long freq,
           Node* up,
           Node* left,
           Node* right) :
    Byte(byte),
    Freq(freq),
    Up(up),
    Left(left),
    Right(right)
{

}

Node::~Node()
{
    std::clog << "~Node()" << std::endl;
}

bool Node::Descending(const Node* n1, const Node* n2)
{
   if (n1->Freq == n2->Freq)
   {
       return n1->Byte < n2->Byte;
   }
   return n1->Freq > n2->Freq;
}
