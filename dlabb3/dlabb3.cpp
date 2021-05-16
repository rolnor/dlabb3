#include <iostream>
#include <string>

using namespace std;

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
    void doubleWithRightChild(treeNode** k3);
    int findMaxHeight(int a, int b);
    treeNode** findMinHeight(treeNode** node);
    int findHeight(treeNode* node);
    void checkBalance(treeNode** node);
    void printTree(treeNode* treeTraverser);
    void remove(int iKey, treeNode** node);
};

int main()
{
    std::cout << "Hello World!\n";
    treeNode* myTree = new treeNode(3,-1,-1);
    treeNode** treeTraverser;
    treeTraverser = &myTree;
    myTree->insert(2, 2, treeTraverser);
    myTree->insert(1, 1, treeTraverser);
    myTree->insert(4, 4, treeTraverser);
    myTree->insert(5, 5, treeTraverser);
    myTree->insert(6, 5, treeTraverser);
    myTree->insert(7, 7, treeTraverser);
    myTree->insert(16, 16, treeTraverser);
    myTree->insert(15, 15, treeTraverser);
    myTree->insert(14, 14, treeTraverser);
    myTree->insert(13, 13, treeTraverser);
    myTree->insert(12, 12, treeTraverser);
    myTree->insert(11, 11, treeTraverser);
    myTree->insert(10, 10, treeTraverser);
    myTree->insert(8, 8, treeTraverser);
    myTree->insert(9, 9, treeTraverser);
    myTree->remove(11,treeTraverser);
    myTree->findKey(11,nullptr);
    myTree->printTree(*treeTraverser);

    delete myTree;
}


void treeNode::printTree(treeNode* treeTraverser)
{
    if (treeTraverser->leftLeaf != nullptr)
        printTree(treeTraverser->leftLeaf);

    cout << treeTraverser->key << " ";

    if (treeTraverser->rightLeaf != nullptr)
        printTree(treeTraverser->rightLeaf);
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
    if (*treeTraverser == nullptr)
        (*treeTraverser) = new treeNode(iKey, iHash);
    else if (iKey < (*treeTraverser)->key)
        insert(iKey, iHash, &(*treeTraverser)->leftLeaf);
    else if ((*treeTraverser)->key < iKey)
        insert(iKey, iHash, &(*treeTraverser)->rightLeaf);   
    this->checkBalance(treeTraverser);
}

int treeNode::findMaxHeight(int a, int b) 
{
    return (a > b) ? a : b;
}

treeNode** treeNode::findMinHeight(treeNode** node)
{
    if ((*node) == nullptr)
        return nullptr;
    if ((*node)->leftLeaf == nullptr)
        return node;
    return findMinHeight(&(*node)->leftLeaf);
}

int treeNode::findHeight(treeNode* node)
{
    if (node == nullptr)
        return -1;
    return node->height;
}

void treeNode::checkBalance(treeNode** node)
{
    if ((*node) == nullptr)
        return;

    if (findHeight((*node)->leftLeaf) - findHeight((*node)->rightLeaf) > 1)
        if (findHeight((*node)->leftLeaf->leftLeaf) >= findHeight((*node)->leftLeaf->rightLeaf))
            rotateWithLeftChild(node);
        else
            doubleWithLeftChild(node);
    else
        if (findHeight((*node)->rightLeaf) - findHeight((*node)->leftLeaf) > 1)
            if (findHeight((*node)->rightLeaf->rightLeaf) >= findHeight((*node)->rightLeaf->leftLeaf))
                rotateWithRightChild(node);
            else
                doubleWithRightChild(node);
   
    (*node)->height = max(findHeight((*node)->leftLeaf), findHeight((*node)->rightLeaf)) + 1;
}

void treeNode::remove(int iKey, treeNode** node)
{
    if (node == nullptr)
        return; 

    if (iKey < (*node)->key)
        remove(iKey, &(*node)->leftLeaf);
    else if ((*node)->key < iKey)
        remove(iKey, &(*node)->rightLeaf);
    else if ((*node)->leftLeaf != nullptr && (*node)->rightLeaf != nullptr)
    {
        treeNode** nextNode = &(*node)->rightLeaf;
        (*node)->key = (*(findMinHeight(nextNode)))->key;
        remove((*node)->key, nextNode);
    }
    else
    {
        treeNode* oldNode = (*node);
        *node = (&(*node)->leftLeaf != nullptr) ? (*node)->leftLeaf : (*node)->rightLeaf;
        delete oldNode;
    }
    
    this->checkBalance(node);
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
    treeNode** k4 = &(*k3)->leftLeaf;
    rotateWithRightChild(k4);
    rotateWithLeftChild(k3);
}

void treeNode::doubleWithRightChild(treeNode** k3)
{
    treeNode** k4 = &(*k3)->rightLeaf;
    rotateWithLeftChild(k4);
    rotateWithRightChild(k3);
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

void getLine(string& inputString)
{
    if (isspace(cin.peek()))
        cin.ignore();

    getline(cin, inputString);
}
