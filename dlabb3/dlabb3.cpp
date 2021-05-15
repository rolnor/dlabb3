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
    void rotateWithLeftChild(treeNode** k2);
    void rotateWithRightChild(treeNode** k2);
    void doubleWithLeftChild(treeNode** k3);
    int getData(myDataType DataValue);
    int findMaxHeight(int a, int b);
    int findHeight(treeNode* node);
    int checkBalance(treeNode** node);
    void performBalance();
};

//1. An insertion into the left subtree of the left child of α - DONE!
//2. An insertion into the right subtree of the left child of α
//3. An insertion into the left subtree of the right child of α
//4. An insertion into the right subtree of the right child of α - DONE!


int main()
{
    std::cout << "Hello World!\n";
    treeNode* myTree = new treeNode(10,-1,-1);
    treeNode** treeTraverser;
    treeTraverser = &myTree;
    myTree->insert(5,5, treeTraverser);
    myTree->insert(12, 5, treeTraverser);
    myTree->insert(3, 15, treeTraverser);
    myTree->insert(4, 15, treeTraverser);
    myTree->findKey(3,nullptr);

 //   cout << endl << "Balanced: " << myTree->checkBalance() << endl;

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

    this->checkBalance(treeTraverser);
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

int treeNode::checkBalance(treeNode** node)
{
    if (this == nullptr)
        return 0;

    if (findHeight(this->leftLeaf) - findHeight(this->rightLeaf) > 1)
        if (findHeight(this->leftLeaf->leftLeaf) >= findHeight(this->leftLeaf->rightLeaf))
            rotateWithLeftChild(node);
        else
            doubleWithLeftChild(node);
          //  cout << "doubleWithLeftChild";
    else
        if (findHeight(this->rightLeaf) - findHeight(this->leftLeaf) > 1)
            if (findHeight(this->rightLeaf->rightLeaf) >= findHeight(this->rightLeaf->leftLeaf))
                rotateWithRightChild(node);
               // cout << "rotateWithRightChild";
            else
                //doubleWithRightChild(t);
                cout << "doubleWithRightChild";
   
    this->height = max(findHeight(this->leftLeaf), findHeight(this->rightLeaf)) + 1;


        // junk return
    return findHeight(this->leftLeaf) - findHeight(this->rightLeaf);
}



void treeNode::rotateWithLeftChild(treeNode** k2)
{
    treeNode* k1 = (*k2)->leftLeaf;
    (*k2)->leftLeaf = k1->rightLeaf;
    k1->rightLeaf = (*k2);
    (*k2)->height = max(findHeight((*k2)->leftLeaf), findHeight((*k2)->rightLeaf)) + 1;
    k1->height = max(findHeight(k1->leftLeaf), (*k2)->height) + 1;
    (*k2) = k1;
}

void treeNode::rotateWithRightChild(treeNode** k2)
{
    treeNode* k1 = (*k2)->rightLeaf;
    (*k2)->rightLeaf = k1->leftLeaf;
    k1->leftLeaf = (*k2);
    (*k2)->height = max(findHeight((*k2)->leftLeaf), findHeight((*k2)->rightLeaf)) + 1;
    k1->height = max(findHeight(k1->leftLeaf), (*k2)->height) + 1;
    (*k2) = k1;
}

void treeNode::doubleWithLeftChild(treeNode** k3)
{
    treeNode* k4 = (*k3)->leftLeaf;
    treeNode** k5 = &k4;
 //   k4 = &(*k4)->leftLeaf;
    rotateWithRightChild(k5);
    rotateWithLeftChild(k3);
}

void treeNode::performBalance()
{
  /*  int balance = this->checkBalance();

     unbalanced left -> single rotation
    if (balance > 1)
        cout << "Left inbalance" << endl;
    else if (balance < -1)
        cout << "Right inbalance" << endl;
         perform rotaion*/
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
