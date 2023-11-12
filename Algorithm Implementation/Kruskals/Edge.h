//******************************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// Name of Author:
// ASU ID: Ryan Radtke
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the distance between them
//*******************************************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
    string cityName;
    int rank;
    struct City* parent;

    //C++ don't provide a default constructor, need it here.
    City()
    {
        cityName = "";
        rank = 0;
        parent = NULL;
    }

    //overloaded constructor
    City(string name)
    {
        cityName = name;
        rank = 0;
        parent = NULL;
    }

};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
private:
    struct City* city1;
    struct City* city2;
    int distance;

public:
    Edge();  //default constructor
    Edge(City* city1, City* city2, int distance);
    ~Edge();
    City* getCity1();
    City* getCity2();
    int getDistance();
    void printEdge();
};

//finish each function according to above definition

Edge::Edge()
{
    city1 = NULL;
    city2 = NULL;
    distance = 0;
}

Edge::Edge(City* city1, City* city2, int distance)
{
    this->city1 = city1;
    this->city2 = city2;
    this->distance = distance;
}

Edge::~Edge()
{
    city1 = NULL;
    delete city1;
    city2 = NULL;
    delete city2;
}

City* Edge::getCity1()
{
    return city1;
}

City* Edge::getCity2()
{
    return city2;
}

int Edge::getDistance()
{
    return distance;
}

void Edge::printEdge()
{
    cout << left;
    cout << setw(15) << city1->cityName
         << setw(8) << "<--->"
         << setw(15) << city2->cityName
         << setw(3) << " = "
         << setw(8) << right << getDistance()
         << endl;
}