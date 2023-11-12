//************************************************************************
// ASU CSE310 Assignment #6 Fall 2022
// Author: Ryan Radtke
// ASU ID: 1223359969
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get the key of a Car which is the combination of vin, model & make
void getCarKey(string oneLine, int& vin, string& model, string& make);

//This function used to get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price);

int main()
{

    int vin;
    string model, make;
    double price;
    string command, oneLine, token;
    string delimiter = ",";

    int pos = 0;

    bool loop = true;

    //Create a RedBlackTree object here, use it throughout the program
    RedBlackTree *redBlackTree = new RedBlackTree();


    do
    {
        getline(cin, oneLine);
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        command = token;
        oneLine.erase(0, pos + delimiter.length());


        if(command.compare("quit")==0)
        {
            cout << "\nCommand: quit" << endl;
            //call the relevant function on the red black tree
            //deconstruct the red-black tree
            redBlackTree->~RedBlackTree();
            loop = false;
            break;
        }
        else if(command.compare("tree_preorder")==0)
        {
            cout << "\nCommand: tree_preorder" << endl;

            //call the relevant function on the red black tree
            //call preorder function
            redBlackTree->treePreorder();
        }
        else if(command.compare("tree_inorder")==0)
        {
            cout << "\nCommand: tree_inorder" << endl;

            //call the relevant function on the red black tree
            //call inorder function
            redBlackTree->treeInorder();
        }
        else if(command.compare("tree_postorder")==0)
        {
            cout << "\nCommand: tree_postorder" << endl;

            //call the relevant function on the red black tree
            //call postorder function
            redBlackTree->treePostorder();
        }
        else if(command.compare("tree_minimum")==0)
        {
            cout << "\nCommand: tree_minimum" << endl;

            //call the relevant function on the red black tree
            //call tree minimum
            redBlackTree->treeMinimum();
        }
        else if(command.compare("tree_maximum")==0)
        {
            cout << "\nCommand: tree_maximum" << endl;

            //call the relevant function on the red black tree
            //call tree maximum
            redBlackTree->treeMaximum();
        }
        else if(command.compare("tree_predecessor")==0)
        {
            //call the getCarKey function to get the Car key first
            getCarKey(oneLine, vin, model, make);

            cout << "\nCommand: tree_predecessor" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treePredecessor(vin, model, make);
        }
        else if(command.compare("tree_successor")==0)
        {
            //call the getCarKey function to get the Car key first
            getCarKey(oneLine, vin, model, make);

            cout << "\nCommand: tree_successor" << endl;

            //call the relevant function on the red black tree
            redBlackTree->treeSucessor(vin, model, make);
        }
        else if(command.compare("tree_search")==0)
        {
            //call the getCarKey function to get the Car key first
            getCarKey(oneLine, vin, model, make);
            cout << "\nCommand: tree_search" << endl;
            //call the relevant function on the red black tree
            Node *foundNode = redBlackTree->treeSearch(vin, model, make);

            //node doesnt exist
            if(foundNode == NULL)
            {
                cout << setw(8)  << vin
                     << setw(12) << model
                     << setw(12) << make
                     << setw(12) << " is NOT FOUND." << endl;
            //node does exist
            }else
            {
                cout << setw(8)  << vin
                     << setw(12) << model
                     << setw(12) << make
                     << setw(12) << " is FOUND." << endl;
            }

        }
        else if(command.compare("tree_insert")==0)
        {
            //call the getCarInfo function to get the Car key first
            getCarInfo(oneLine, vin, model, make, price);


            cout << "\nCommand: tree_insert" << endl;
            cout << left;
            cout << setw(8)  << vin
                 << setw(12) << model
                 << setw(12) << make
                 << setw(12) << fixed << setprecision(2) << price << endl;

            redBlackTree->treeInsert(vin, model,make, price);

        }
    } while(loop);  //continue until 'quit'
    return 0;
}

//*********************************************************************************
//This function from one line, extracts the vin, model, make of a Car
void getCarKey(string oneLine, int& vin, string& model, string& make)
{
    //Design your own code here
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    vin = stoi(token);
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    model = token;
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    make = token;
    oneLine.erase(0, pos+delimiter.length());
}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of a Car
void getCarInfo(string oneLine, int& vin, string& model, string& make, double& price)
{
    //Design your own code here
    string delimiter = ",";
    int pos=oneLine.find(delimiter);
    string token = oneLine.substr(0,pos);
    vin = stoi(token);
    oneLine.erase(0, pos+delimiter.length());

    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    model = token;
    oneLine.erase(0, pos+delimiter.length());


    pos=oneLine.find(delimiter);
    token = oneLine.substr(0,pos);
    make = token;
    oneLine.erase(0, pos+delimiter.length());

    price = stod(oneLine);

}