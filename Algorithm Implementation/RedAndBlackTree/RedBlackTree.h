//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Ryan Radtke
// ASU ID: 1223359969
// Description: Red black tree header file. It defines the Node and the
//              red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is a Car
struct Node
{
    int vin;
    string model, make;
    double price;
    Node *parent;
    Node *leftChild;
    Node *rightChild;
    string color;
};

class RedBlackTree
{
private:
    Node *root;
    int nodeSize = 0;
public:
    RedBlackTree();
    ~RedBlackTree();
    Node* getRoot();
    int deleteNode(Node *node);
    void insertNode(Node *node);
    void fixUp(Node *node);

    void preOrderTraversal(Node *node);
    void inorderTraversal(Node *node);
    void postOrderTraversal(Node *node);

    Node* findMinimumNode(Node *node);
    Node* findMaximumNode(Node *node);
    Node* treeSearch(int vin, string model, string make);
    void leftRotate(Node *node);
    void rightRotate(Node *node);
    Node* findPredecessorNode(Node *node);
    Node* findSuccessorNode(Node *node);

    void treeMinimum();
    void treeMaximum();
    void treePreorder();
    void treeInorder();
    void treePostorder();
    void treePredecessor(int vin, string model, string make);
    void treeSucessor(int vin, string model, string make);
    void treeInsert(int vin, string model, string make, double price);

    void print(Node *node);
    int compareNodes(Node *node, string key);

    void destroyRecursively(Node* node);

};
#endif