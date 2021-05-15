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
    treeNode(int iKey, int iHashpointer, int iHeight = 1);
    treeNode();
    ~treeNode();
    void insert(int iKey, int iHash, treeNode** treeTraverser);
    void findKey(int iKey, treeNode* treeTraverser);
    int getData(myDataType DataValue);
    int findMaxHeight(int a, int b);
    int findHeight(treeNode* node);
    bool checkBalance(int balanceFactor = 1);
};

int main()
{
    std::cout << "Hello World!\n";
    treeNode* myTree = new treeNode(10,-1,-1);
    treeNode** treeTraverser;
    treeTraverser = &myTree;
    myTree->insert(5,5, treeTraverser);
 //   myTree->insert(3, 15, treeTraverser);
 //   myTree->insert(2, 15, treeTraverser);
    myTree->findKey(2,nullptr);

    cout << endl << "Balanced: " << myTree->checkBalance() << endl;

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

void treeNode::insert(int iKey, int iHash, treeNode** treeTraverser)
{   
    if ((*treeTraverser) == nullptr)
    {
        *treeTraverser = new treeNode(iKey, iHash);
    }
    else if ((*treeTraverser)->getData(myDataType::key) < iKey)
    {
        // insert right
        if((*treeTraverser)->rightLeaf != nullptr)
            this->insert(iKey,iHash, &(*treeTraverser)->rightLeaf);
        else
            (*treeTraverser)->rightLeaf = new treeNode(iKey, iHash);
    }
    else if ((*treeTraverser)->getData(myDataType::key) > iKey)
    {
        // insert left
        if ((*treeTraverser)->leftLeaf != nullptr)
            this->insert(iKey, iHash, &(*treeTraverser)->leftLeaf);
        else
            (*treeTraverser)->leftLeaf = new treeNode(iKey, iHash);   
    } 
    // recalculate height
    if ((*treeTraverser)->height != -1)
        (*treeTraverser)->height = 1 + findMaxHeight(findHeight((*treeTraverser)->leftLeaf), findHeight((*treeTraverser)->rightLeaf));
}

int treeNode::findMaxHeight(int a, int b) 
{
    return (a > b) ? a : b;
}

int treeNode::findHeight(treeNode* node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

bool treeNode::checkBalance(int balanceFactor)
{
    if (abs(findHeight(this->leftLeaf) - findHeight(this->rightLeaf)) > balanceFactor)
        return false;
    else
        return true;
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
