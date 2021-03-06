#include "linear.h"
#include <chrono>

using namespace std;

// helper functions
void getLine(string& inputString);
void menu();

class myTimer
{
    chrono::time_point<chrono::system_clock>  i_start, i_end;
public:
    void start();
    void stop(std::string titleName);
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
    int findKey(int iKey, treeNode* treeTraverser);
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
    myTable linearTable;
    treeNode** treeTraverser;

    myTimer MyTimer;
    treeNode* myTree = new treeNode(3, linearTable.calculateHash("3", 100),-1);
    treeTraverser = &myTree;
    string inputPos[20] = { "2","1","4","5","6","7","16","15","14","13","12","11","10","8","9" };
    string inputData[20] = { "21","12","43","54","65","76","167","158","149","131","122","113","104","85","96" };
    int i = 0;


    int x, calcHash;
    char choise = ' ';
    string inputString = "";
    while (choise != '0')
    {
        menu();
        cin >> choise;
        switch (choise)
        {
        case '1':

            cout << endl << "Insert: (x,y)" << endl << "x: ";
            getLine(inputString);
            x = stoi(inputString);
            cout << "y: ";
            getLine(inputString);
            MyTimer.start();
            calcHash = linearTable.calculateHash(inputString, 100);
            myTree->insert(x, calcHash, treeTraverser);
            linearTable.insert(inputString, calcHash);
            MyTimer.stop("Insert time: ");
            break;
        case '2':
            cout << endl << "Search: ";
            getLine(inputString);
            MyTimer.start();
            calcHash = myTree->findKey(stoi(inputString), nullptr);
            if (calcHash != -1)
                cout << "Data: (x: " << inputString << " y: " << linearTable.getData(calcHash) << ")";
            else
                cout << endl << "Key not found" << endl;
            MyTimer.stop("Searchtime: ");
            break;
        case '3':
            cout << endl << "Remove: ";
            getLine(inputString);
            MyTimer.start();
            calcHash = myTree->findKey(stoi(inputString), nullptr);
            if (calcHash != -1)
            {
                myTree->remove(stoi(inputString), treeTraverser);
                linearTable.remove(inputString, calcHash);
            }
            MyTimer.stop("Remove time: ");
            break;
        case '4':
            myTree->printTree(*treeTraverser);
            cout << endl << endl;
            break;
        case '5':
            i = 0;
            for (string iPos : inputPos)
            {
                if (iPos == "")
                    break;
                calcHash = linearTable.calculateHash(iPos, 100);
                myTree->insert(stoi(iPos), calcHash, treeTraverser);
                linearTable.insert(inputData[i], calcHash);
                i++;
            }
            break;
        case '0':
            break;
        }
    }
    delete myTree;
    return 0;

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
    bool notchecked = true;
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
        treeNode** oldNode = &(*node);
        if ((*node)->leftLeaf != nullptr)
            *node = (*node)->leftLeaf;
        else *node = (*node)->rightLeaf;

        delete *oldNode;
        *oldNode = nullptr;
        this->checkBalance(node);
        notchecked = false;
    }
    if(notchecked)
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

int treeNode::findKey(int iKey, treeNode* treeTraverser)
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
        return treeTraverser->hashPointer;
    }
    else
    {
        cout << "Key not found" << endl;
        return -1;
    }
        
}

void getLine(string& inputString)
{
    if (isspace(cin.peek()))
        cin.ignore();

    getline(cin, inputString);
}

void myTimer::start()
{
    i_start = std::chrono::system_clock::now();
}

void myTimer::stop(string titleName)
{
    i_end = std::chrono::system_clock::now();
    auto totalTime = i_end - i_start;
    cout << endl << endl << titleName << " :" << std::chrono::duration_cast<std::chrono::nanoseconds>(totalTime).count() << " nanoseconds" << endl;
}

void menu()
{
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Remove" << endl;
    cout << "4. Print" << endl;
    cout << "5. Fill data" << endl;
    cout << "0. Quit " << endl;
}