#include <huffman.h>

Huffman::Huffman(const std::string &filename) : Filename(filename)
{
    for (int i = 0; i < 256; i++)
    {
        Frequencies[i] = 0;
        NodesArray[i] = NULL;
    }
}

Huffman::~Huffman()
{

}

bool Huffman::readFile()
{
    unsigned char byte;
    std::FILE* f;
    f = std::fopen(Filename.data(), "rb");
    if (f)
    {
        totalFreq = 0;
        while (!std::feof(f))
        {
            if (std::fread(&byte, 1, 1, f))
            {
                Frequencies[byte]++;
                totalFreq++;
            }
        }
        std::fclose(f);
        std::clog << "File successfully read: '" << Filename << "'" << std::endl;
        return true;
    }
    else
    {
        std::cerr << "File was not opened: '" << Filename << "' !" << std::endl;
        return false;
    }
}

void Huffman::sortTree()
{
    std::sort(Tree.begin(), Tree.end(), Node::Descending);
}

void Huffman::insert(Node* node)
{
    Tree.push_back(node);
}

void Huffman::buildTree()
{
    for (int i = 0; i < 256; i++)
    {
        if (Frequencies[i] > 0)
        {
            Node* node = new Node(i, Frequencies[i]);
            insert(node);
        }
    }
    while (Tree.size() > 1)
    {
        sortTree();
        Node* leftNode = Tree.back();
        Tree.pop_back();
        Node* rightNode = Tree.back();
        Tree.pop_back();
        Node* node = new Node(-1, leftNode->Freq + rightNode->Freq, NULL, leftNode, rightNode);

        // In case of equal occurences, the untie will be the byte
        if (leftNode->Freq == rightNode->Freq)
        {
            if (leftNode->Byte < rightNode->Byte)
            {
                node->Left = leftNode;
                node->Right = rightNode;
            }
            else
            {
                node->Left = rightNode;
                node->Right = leftNode;
            }
        }
        else
        {
            if (leftNode->Freq < rightNode->Freq)
            {
                node->Left = leftNode;
                node->Right = rightNode;
            }
            else
            {
                node->Left = rightNode;
                node->Right = leftNode;
            }
        }
        node->Left->Up = node;
        node->Left->Edge = '0';
        node->Right->Up = node;
        node->Right->Edge = '1';
        insert(node);
    }
    courseTree(Tree.back());
}

void Huffman::courseTree(Node *node)
{
    if (node)
    {
        courseTree(node->Left);
        if (node->Byte > -1)
        {
            climbTree(node);
            std::clog << "ASCII: " << node->Byte << " /"
                      << " Char: " << ((char) node->Byte)
                      << " Freq: " << node->Freq << " /"
                      << " Huffman's encoding: " << node->code << " /"
                      << " Probability: " << std::fixed << std::setprecision(2)
                      << (node->Freq / (float) totalFreq) * 100.f  << " %"
                      << std::endl;
            NodesArray[node->Byte] = node;
        }
        courseTree(node->Right);
    }
}

void Huffman::climbTree(Node *node)
{
    std::string code = "";
    Node* tmp = node;
    while(tmp)
    {
        if (tmp->Up)
        {
            code += tmp->Edge;
        }
        tmp = tmp->Up;
    }
    std::reverse(code.begin(), code.end());
    node->code = code;
}

void Huffman::encode()
{
    unsigned char byte;
    std::FILE* f;
    f = std::fopen(Filename.data(), "rb");
    if (f)
    {
        while (!std::feof(f))
        {
            if (std::fread(&byte, 1, 1, f))
            {
                encodedString += NodesArray[byte]->code;
            }
        }
        std::clog << std::endl;
        std::fclose(f);
        std::clog << "Successful enconding of '" << Filename << "'" << std::endl << std::endl;
        std::clog << "Code: " << std::endl << encodedString << std::endl << std::endl;
    }
    else
    {
        std::cerr << "File was not encoded: '" << Filename << "' !" << std::endl;
    }
}

void Huffman::decode()
{
    Node* root = Tree.back();
    std::clog << "Successful decoding of '" << Filename << "'" << std::endl << std::endl;
    std::clog << "Decode: ";
    for (unsigned int i = 0; i < encodedString.size(); i++)
    {
        if (encodedString[i] == '0')
        {
            root = root->Left;
        }
        else if (encodedString[i] == '1')
        {
            root = root->Right;
        }
        if (root->Byte > -1)
        {
            std::clog << ((char) root->Byte);
            root = Tree.back();
        }
    }
    std::clog << std::endl;
}
