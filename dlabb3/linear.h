#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class myTable
{
private:
    string data[100];
    int collisions;
public:
    myTable() { collisions = 0; };
    void insert(string& inputData, int hashLocation);
    void search(string& inputData, int hashLocation);
    void remove(string& inputData, int hashLocation);
    void repartition(int trueHash, int newHashLocation);
    int calculateHash(const string& key, int tableSize);
    void incCollisions();
    int getCollisions() { return collisions; };
    void print();
};
