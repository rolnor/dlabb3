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
    int key;
    int hashPointer;
    int height;
    treeNode* leftLeaf;
    treeNode* rightLeaf;

public:
    treeNode* getLeft() { return this->leftLeaf; };
    treeNode* getRight() { return this->rightLeaf; };
    void insertLeft(treeNode Left);
    void insertRight(treeNode Right);
    int getData(myDataType DataValue);
};

int main()
{
    std::cout << "Hello World!\n";
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
