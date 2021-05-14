#include <iostream>
#include <string>

using namespace std;

enum class myDataType { key, hashPointer, height };

// helper functions
void getLine(string& inputString);

struct Point2d
{
    int x;
    int y;
};

class treeNode
{
private:
    int key;
    int hashPointer;
    int height;
    treeNode* leftLeaf;
    treeNode* rightLeaf;

public:
    treeNode(int iKey, int iHashpointer, int iHeight);
    treeNode();
    ~treeNode();
    treeNode* getLeft() { return this->leftLeaf; };
    treeNode* getRight() { return this->rightLeaf; };
    void insert(treeNode& newNode);
    void insertLeft(treeNode Left);
    void insertRight(treeNode Right);
    int getData(myDataType DataValue);
};

int main()
{
    std::cout << "Hello World!\n";
}

treeNode::treeNode(int iKey, int iHashpointer, int iHeight)
{
    leftLeaf = nullptr;
    rightLeaf = nullptr;
    key = iKey;
    hashPointer = iHashpointer;
    height = iHeight;
}

treeNode::treeNode()
{
    leftLeaf = nullptr;
    rightLeaf = nullptr;
    key = -1;
    hashPointer = -1;
    height = -1;
}

treeNode::~treeNode()
{
    while (leftLeaf == nullptr || rightLeaf == nullptr)
    {
        if (leftLeaf != nullptr)
            delete leftLeaf;
        if (rightLeaf != nullptr)
            delete rightLeaf;
    }
}

void treeNode::insert(int iKey, int iHash)
{
    if()
}

void treeNode::insertLeft(treeNode Left)
{
}

void treeNode::insertRight(treeNode Right)
{
}

int treeNode::getData(myDataType DataValue)
{
    if(DataValue == myDataType::key)
        return this->key;
    else if (DataValue == myDataType::height)
        return this->height;
    else 
        return this->hashPointer;
}

void getLine(string& inputString)
{
    if (isspace(cin.peek()))
        cin.ignore();

    getline(cin, inputString);
}
