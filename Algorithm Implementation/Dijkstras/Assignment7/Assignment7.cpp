//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name: Ryan Radtke
// ASU ID: 1223359969
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
#include "ArrivalCityList.h"
#include "MinPriorityQueue.h"
#include "Graph.h"

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);     //**optional

int main()
{
    int count;       //a variable for number of nodes
    string oneLine, sourceCityName;
    string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times

    cout << "Enter number of cities: ";
    cin >> count;
    cin.ignore(20, '\n');

    //For each line of the file, we will create an ArrivalCityList(which is a linked list)
    //for a specific departure city. It represents all its reachable arrival cities with distance info.
    //Here we use an array of DepCity to store them
    DepCity* depCityArr = new DepCity[count];

    //Initialize depCityArr. Set each node's d value to be very large 30000
    //initialize each arrival city list
    for(int i = 0; i< count; i++)
    {
        depCityArr[i].d = 30000;
        depCityArr[i].arrCityList = new ArrivalCityList();
        depCityArr[i].pi = NULL;
        depCityArr[i].depCityName = "";
    }

    //get input line by line and create the depCityArr

    MinPriorityQueue* priorityQueue = new MinPriorityQueue(count);

    for(int i = 0; i< count; i++)
    {
        getline(cin, oneLine);

        string delimiter = ",";


        //----
    }

    //create a Graph object
    Graph* graph = new Graph(count, priorityQueue);

    //print the graph adjacency list before running Dijkstra algorithm
    cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
    priorityQueue->printHeap();

    //Next you need to design a sentinel value controlled while loop base on answer
    //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
    //shortest path, then ask whether user want to continue or not...
    while(true)
    {


        break;
    }



}

//************************************************************************
//Give one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
    //----
    //----
    cout << "This will be shown";

}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60), this function
//extract arrival city name 'Z' and distance 60 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
    //----
    //----
}