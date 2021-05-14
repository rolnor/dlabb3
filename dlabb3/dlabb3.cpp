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
    treeNode*& getLeft() { return this->leftLeaf; };
    treeNode*& getRight() { return this->rightLeaf; };
    void insert(int iKey, int iHash, treeNode** treeTraverser);
    int getData(myDataType DataValue);
    void setData(int apa){ key = apa; };
};

int main()
{
    std::cout << "Hello World!\n";
    treeNode* myTree = new treeNode(10,-1,-1);
    treeNode** treeTraverser;
    treeTraverser = &myTree->getLeft();
    myTree->insert(5,5, treeTraverser);

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
    cout << "dfsdasdsa" << endl;
  //  (*treeTraverser)->setData(2);
    // this works
    //leftLeaf = new treeNode(iKey, iHash, -1);


    //treeNode** fuckaduck;
    //fuckaduck = treeTraverser->leftLeaf;

    //*fuckaduck = new treeNode(iKey, iHash, -1);



    if ((*treeTraverser) == nullptr)
    {
        *treeTraverser = new treeNode(iKey, iHash, -1);
    }
    //else if (treeTraverser->getData(myDataType::key) < iKey)
    //{
    //    // insert right
    //    treeTraverser = this->getRight();
    //    this->insert(iKey, iHash, treeTraverser);
    //}
    //else if (treeTraverser->getData(myDataType::key) > iKey)
    //{
    //    // insert left
    //    treeTraverser = this->getLeft();
    //    this->insert(iKey, iHash, treeTraverser);
    //}
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
