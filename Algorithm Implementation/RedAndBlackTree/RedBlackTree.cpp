//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Ryan Radtke
// ASU ID: 1223359969
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

//include the relevant header file
#include "RedBlackTree.h"

using namespace std;

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
    root = NULL;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
    destroyRecursively(root);

    cout << "The number of nodes deleted: " << nodeSize << endl;
}

void RedBlackTree::destroyRecursively(Node* node)
{
    if(node)
    {
        destroyRecursively(node->leftChild);
        destroyRecursively(node->rightChild);
        delete node;
    }
}




//**************************************************************
//Accessor for the root of the red-black tree
Node *RedBlackTree::getRoot()
{
    return root;
}


//write your own code according to red-black tree definition
//----


//*******************************************************************
//delete the sub-tree rooted at 'node' and return number of nodes deleted
//This should be defined as a recursive function

//write your own code according to red-black tree definition
//----


//****************************************************************
//This is the general BST insertion operation.
//It does not care about the color of the newly added node.

//write your own code according to red-black tree definition
void RedBlackTree::insertNode(Node *node)
{

    //get node's oneline key
    string nodeKey = to_string(node->vin) + node->make + node->model;

    //Insert the node normally
    Node *y = NULL;
    Node *x = root;

    //loop through till we reach a null node
    while(x != NULL) {
        y = x;

        if (compareNodes(x, nodeKey) < 0)
        {
            x = x->leftChild;
        } else
        {
            x = x->rightChild;
        }
    }

    //set nodes parent
    node->parent = y;

    //tree is empty else set parent nodes.
    if(y == NULL)
    {
        root = node;
    //put new node as correct child
    }else if(compareNodes(y, nodeKey) < 0)
    {
        y->leftChild = node;
    }else
    {
        y->rightChild = node;
    }

    //fill new node color and children
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->color = "RED";

    //use fix up to restore RedBlackTree properties
    fixUp(node);
}


//*******************************************************************
//At beginning, each newly added node will always be RED,
//this may violate the red-black tree property #4. fixUp()
//function will restore the property.

//write your own code according to red-black tree definition
void RedBlackTree::fixUp(Node *node)
{
    Node *y = NULL;
    //fix tree while nodes parent is not black

    while(node->parent != NULL && node->parent->color.compare("RED") == 0)
    {
        //left symmetry
        if(node->parent->parent->leftChild != NULL && node->parent == node->parent->parent->leftChild)
        {
            y = node->parent->parent->rightChild; //y = nodes uncle
            //CASE 1
            //UNCLE is RED
            if(y != NULL && y->color.compare("RED") == 0)
            {
                node->parent->color = "BLACK"; //change color of parent
                y->color = "BLACK"; //change color of uncle
                node->parent->parent->color = "RED"; //change color of grandparent
                node = node->parent->parent; //make new node to check old nodes grandparent
            //CASE 2
            //UNCLE is BLACK
            }else
            {
                if(node == node->parent->rightChild)
                {
                    node = node->parent;
                    leftRotate(node);
                }
                //CASE 3
                //Y (uncle) is black and node is a left child
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                rightRotate(node->parent->parent);
            }
        //right symmetry
        }else
        {
            y = node->parent->parent->leftChild; //y = nodes uncle
            //CASE 1
            //UNCLE is RED
            if(y != NULL  && y->color.compare("RED") == 0)
            {
                node->parent->color = "BLACK"; //change color of parent
                y->color = "BLACK"; //change color of uncle
                node->parent->parent->color = "RED"; //change color of grandparent
                node = node->parent->parent; //make new node to check old nodes grandparent
            //CASE 2
            //UNCLE is BLACK
            }else
            {
                if(node == node->parent->leftChild)
                {
                    node = node->parent;
                    rightRotate(node);
                }
                //CASE 3
                //Y (uncle) is black and node is a right child
                node->parent->color = "BLACK";
                node->parent->parent->color = "RED";
                leftRotate(node->parent->parent);
            }
        }
    }
    //make sure the root is always black
    root->color = "BLACK";
    return;
}




//*****************************************************
//This function print the pre-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
void RedBlackTree::preOrderTraversal(Node *node)
{
    //return if we get to a NULL node
    if(node == NULL)
    {
        return;
    }

    //print node
    print(node);

    //recur on left node
    preOrderTraversal(node->leftChild);

    //recur on right node
    preOrderTraversal(node->rightChild);

}

//**************************************************
//This function print the in-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
void RedBlackTree::inorderTraversal(Node *node)
{
    //return iuf we get to a NULL node
    if(node == NULL)
    {
        return;
    }

    //recur on left child
    inorderTraversal(node->leftChild);

    //print node
    print(node);

    //recur on right child
    inorderTraversal(node->rightChild);
}

//**************************************************
//This function print the post-order traversal of the
//subtree rooted at 'node'.It's a recursive function

//write your own code according to red-black tree definition
void RedBlackTree::postOrderTraversal(Node *node)
{

    //return if we get to a NULL node
    if(node == NULL)
    {
        return;
    }

    //recur on left
    postOrderTraversal(node->leftChild);

    //recur on right
    postOrderTraversal(node->rightChild);

    //print node info
    print(node);

}


//**************************************************************
//This function returns a pointer points to the minimum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
Node* RedBlackTree::findMinimumNode(Node *node)
{
    Node *y = NULL;
    Node *x = node;

    while(x != NULL)
    {
        y = x; //set prv = curr
        x = x->leftChild; //traverse down the left of the tree
    }
    return y;
}


//**************************************************************
//This function returns a pointer points to the maximum node from
//the current sub-tree rooted at 'node'. It should be designed as
//a recursive function

//write your own code according to red-black tree definition
Node* RedBlackTree::findMaximumNode(Node *node)
{
    Node *y = NULL;
    Node *x = node;

    while(x != NULL)
    {
        y = x; //set prv = curr
        x = x->rightChild; //traverse down the right of the tree
    }
    return y;
}

//**************************************************************
//This function search the tree for a given key of a Car
//Note: key is the combination of vin, model and make of the Car
//It returns a pointer points to the node if founded; otherwise it returns NULL

//write your own code according to red-black tree definition
Node* RedBlackTree::treeSearch(int vin, string model, string make)
{
    //get node's oneline key
    string nodeKey = to_string(vin) + make + model;

    Node *x = root;
    while(x != NULL)
    {
        //node is equal to key
        if(x->vin == vin && x->model == model && x->make == make)
        {
            return x;
        }
        //if key is less than current node go left else go right
        int compare = compareNodes(x,nodeKey);
        if(compare < 0)
        {
            x = x->leftChild;
        }else if(compare >= 0)
        {
            x = x->rightChild;
        }
    }
    //if the node was unfound

    return NULL;
}


//****************************************************
//This function left-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
void RedBlackTree::leftRotate(Node *node)
{
    Node *y = node->rightChild;
    node->rightChild = y->leftChild; //turn y's subtree into node's right subtree

    if(y->leftChild != NULL)
    {
        y->leftChild->parent = node;
    }

    y->parent = node->parent; //set y's parent as node's parent
    if(node->parent == NULL) //node is the root
    {
        root = y;
    }else
    {
        if(node == node->parent->leftChild) //if node is a left child
        {
            node->parent->leftChild = y;
        }else //node is a right child
        {
            node->parent->rightChild = y;
        }
    }

    y->leftChild = node;
    node->parent = y;

}


//***************************************************
//This function right-rotate the BST rooted at 'node'

//write your own code according to red-black tree definition
void RedBlackTree::rightRotate(Node *node)
{
    Node *y = node->leftChild;
    node->leftChild = y->rightChild; //turn y's subtree into node's left subtree

    if(y->rightChild != NULL)
    {
        y->rightChild->parent = node;
    }

    y->parent = node->parent; //set y's parent as node's parent
    if(node->parent == NULL) //node is the root
    {
        root = y;
    }else
    {
        if(node == node->parent->rightChild) //if node is a right child
        {
            node->parent->rightChild = y;
        }else //node is a right child
        {
            node->parent->leftChild = y;
        }
    }

    y->rightChild = node;
    node->parent = y;
}


//**************************************************************
//This function finds the predecessor of the given 'node'
//it prints the relevant predecessor info. on screen and also
//return a pointer that points to the predecessor

//write your own code according to red-black tree definition
Node* RedBlackTree::findPredecessorNode(Node *node)
{
    Node *successor = NULL;
    Node *x = root;

    //get node's oneline key
    string nodeKey = to_string(node->vin) + node->make + node->model;

    if(node == findMinimumNode(root))
    {
        return NULL;
    }


    if(node->leftChild != NULL)
    {
        return findMaximumNode(node->leftChild);
    }else if(node == node->parent->leftChild)
    {
        return node->parent->parent;
    }else
    {
        return node->parent;
    }
}

//**************************************************************
//This function finds the successor of the given 'node'
//it prints the relevant successor info. on screen and also return
//a pointer that points to the successor node

//write your own code according to red-black tree definition
Node* RedBlackTree::findSuccessorNode(Node *node)
{

    Node *successor = NULL;
    Node *x = root;

    //get node's oneline key
    string nodeKey = to_string(node->vin) + node->make + node->model;


    while(x != NULL)
    {
        if(compareNodes(x, nodeKey) >= 0)
        {
            x = x->rightChild;
        }else
        {
            successor = x;
            x = x->leftChild;
        }
    }

    if(findMaximumNode(root) == node)
    {
        return NULL;
    }

    return successor;

}

//****************************************************************
//This function find the minimum node of the entire red-black tree
//It print out the minimum node info. on screen if tree is not empty
//or print Tree is empty. No Minimum. message on screen.

//write your own code according to red-black tree definition
void RedBlackTree::treeMinimum()
{
    //travers all the way to the left of the tree from root
    Node *y = findMinimumNode(root);
    if(y == NULL)
    {
        cout << "tree is empty" << endl;
        return;
    }
    print(y);
    return;
}

//**************************************************************
//This function find the maximum node of the entire red-black tree
//It print out the maximum node info. on screen if tree is not empty
//or print Tree is empty. No Maximum. message on screen.

//write your own code according to red-black tree definition
void RedBlackTree::treeMaximum()
{
    //travers all the way to the right of the tree from the root
    Node* y = findMaximumNode(root);
    if(y == NULL)
    {
        cout << "tree is empty" << endl;
        return;
    }
    print(y);
    return;
}

//****************************************************************************
//This function print out the pre-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treePreorder()
{
    //if tree is empty
    if(root == NULL)
    {
        cout << "tree is empty" << endl;
    }

    //print out tree traversal
    preOrderTraversal(root);
}

//***************************************************************************
//This function print out the in-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treeInorder()
{
    if(root == NULL)
    {
        cout << "tree is empty" << endl;
    }

    //print out tree traversal
    inorderTraversal(root);
}
//*****************************************************************************
//This function print out the post-order traversal of the entire red-black tree

//write your own code according to red-black tree definition
void RedBlackTree::treePostorder()
{
    if(root == NULL)
    {
        cout << "tree is empty" << endl;
    }

    //print out tree traversal
    postOrderTraversal(root);
}


//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its predecessor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
void RedBlackTree::treePredecessor(int vin, string model, string make)
{
    //find the node
    Node *currentNode= treeSearch(vin,model,make);

    //print original nodes info
    cout << setw(8) << vin
         << setw(12) << model
         << setw(12) << make
         << setw(12) << "is FOUND."
         << endl;
    //nodes predecessor exists or not
    Node *predecessor = findPredecessorNode(currentNode);
    if(predecessor == NULL)
    {
        cout << "Its Predecessor does NOT EXIST";
        return;
    }else
    {
        //find the predecessor
        cout << "Its Predecessor is: " << endl;
        print(predecessor);
        return;
    }
}

//******************************************************************
//Given a Car key, this function first check whether the
//Car is inside the tree or not, if it is inside, it will print
//its successor info. on screen, if not, it print an error message

//write your own code according to red-black tree definition
void RedBlackTree::treeSucessor(int vin, string model, string make)
{
    //find if node does exist
    Node *successor = treeSearch(vin,model,make);


    //print nodes info
    cout << setw(8)  << successor->vin
         << setw(12) <<successor->model
         << setw(12) << successor->make
         << setw(12) << "is FOUND."
         << endl;

    //nodes successor exists
    successor = findSuccessorNode(successor);
    if(successor == NULL)
    {
        cout << "Its Successor does NOT EXIST";
    }else
    {
        //find the successor
        cout << "Its Successor is: " << endl;
        print(successor);
    }
}

//**************************************************************
//This function create a node from the given info., then insert
//the node inside the red-black tree. Note: at beginning, the newly
//added node should always be 'RED'

//write your own code according to red-black tree definition
void RedBlackTree::treeInsert(int vin, string model, string make, double price)
{
    //creating a new node
    Node *newNode = new Node();
    newNode->vin = vin;
    newNode->model = model;
    newNode->make = make;
    newNode->price = price;

    //check if car already exist
    if(treeSearch(vin,model,model))
    {
       //car exists
       return;
    }else
    {
        //car does not exist so add it
        insertNode(newNode);
        nodeSize++;
    }
}

//******************************************************************
//Given a 'node', this function prints all the node information on screen
void RedBlackTree::print(Node *node)
{
    cout << left;
    cout << setw(8)  << node->vin
         << setw(12) << node->model
         << setw(12) << node->make
         << setw(10) << fixed << setprecision(2) << node->price;
    cout << right << setw(7) << node->color << endl;
}

//**************************************************************
//Given a Node 'node1', this function compares it with another
//node's key.
//key is a string combination of vin + model + make
//It returns a negative number if in alphabetical order, key2 is
//in front of 'node1'; otherwise it returns a positive number

//write your own code according to red-black tree definition
int RedBlackTree::compareNodes(Node *node, string key)
{

    //get node's oneline key
    string nodeKey = to_string(node->vin) + node->make + node->model;

    //returns a positive number is key is before node
    int comparedValue = nodeKey.compare(key);

    //key comes before nodesKey
    if(comparedValue > 0)
    {
        return -1;
    }else
    {
        return  1;
    }



}