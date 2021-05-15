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
    void insert(int iKey, int iHash, int iHeight, treeNode** treeTraverser);
    void findKey(int iKey, treeNode* treeTraverser);
    int getData(myDataType DataValue);
    void setData(int apa){ key = apa; };
    int getHeight(treeNode* searchNode);
};

int main()
{
    std::cout << "Hello World!\n";
    treeNode* myTree = new treeNode(10,-1,-1);
    treeNode** treeTraverser;
    treeTraverser = &myTree;
    myTree->insert(5,5, -1, treeTraverser);
    myTree->insert(15, 15, -1, treeTraverser);
    myTree->insert(16, 15, -1, treeTraverser);
    myTree->insert(3, 15, -1, treeTraverser);
    myTree->findKey(3,nullptr);

    delete myTree;
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
    while (leftLeaf != nullptr || rightLeaf != nullptr)
    {
        if (leftLeaf != nullptr)
        {
            delete leftLeaf;
            leftLeaf = nullptr;
        }
           
        if (rightLeaf != nullptr)
        {
            delete rightLeaf;
            rightLeaf = nullptr;
        }
    }
}

void treeNode::insert(int iKey, int iHash, int iHeight, treeNode** treeTraverser)
{   
    if ((*treeTraverser) == nullptr)
    {
        *treeTraverser = new treeNode(iKey, iHash, iHeight);
    }
    else if ((*treeTraverser)->getData(myDataType::key) < iKey)
    {
        // insert right
        //
        if((*treeTraverser)->rightLeaf != nullptr)
            this->insert(iKey,iHash,iHeight+1, &(*treeTraverser)->rightLeaf);
        else
            (*treeTraverser)->rightLeaf = new treeNode(iKey, iHash, iHeight + 1);
    }
    else if ((*treeTraverser)->getData(myDataType::key) > iKey)
    {
        // insert left
        //treeTraverser = &(*treeTraverser)->leftLeaf;

        if((*treeTraverser)->leftLeaf != nullptr)
            this->insert(iKey, iHash, iHeight+1, &(*treeTraverser)->leftLeaf);
        else 
            (*treeTraverser)->leftLeaf = new treeNode(iKey, iHash, iHeight+1);
    }
}

void treeNode::findKey(int iKey, treeNode* treeTraverser)
{
    if (treeTraverser == nullptr)
        treeTraverser = this;

    if (iKey < treeTraverser->key && treeTraverser->leftLeaf != nullptr)
        findKey(iKey, treeTraverser->leftLeaf);
    else if (iKey > treeTraverser->key && treeTraverser->rightLeaf != nullptr)
        findKey(iKey, treeTraverser->rightLeaf);
    else if (iKey == treeTraverser->key)
    {
        cout << "Key found" << endl;
    }
    else
        cout << "Key not found" << endl;
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


int treeNode::getHeight(treeNode* searchNode)
{
    if (searchNode == NULL)
        return 0;
    return searchNode->height;
}