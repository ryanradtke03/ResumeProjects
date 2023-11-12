//********************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// Name of Author: Ryan Radtke
// ASU ID: 1223359969
// Description: This is the header file that defines an undirected graph
//              with an array of vertice and edges
//********************************************************************

//include necessary header file here
#include "Edge.h"

using namespace std;

class Graph
{
private:
    int V, E;             //number of vertice and edges in the graph
    City* setOfCities;    //an array of cities (vertex)
    Edge* setOfEdges;     //an array of edges

public:
    Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
    ~Graph();
    void make_set(City* aCity);
    City* find_set(City* aCity);
    void link(City* aCity, City* bCity);
    void Union(City* aCity, City* bCity);
    void SortEdges();
    void MST_Kruskal();

    //add any auxillary functions in case you need them
    void MergeSort(Edge* setOfEdges, int l, int r);
    void Merge(Edge* setOfEdges, int l, int m, int r);

};

//finish each function according to above definition
Graph::Graph(int numOfCities, int numOfEdges, City *cityArray, Edge *edgeArray)
{
    V = numOfCities;
    E = numOfEdges;
    setOfCities = cityArray;
    setOfEdges = edgeArray;
}

Graph::~Graph()
{
    setOfCities = NULL;
    delete setOfCities;
    setOfEdges = NULL;
    delete setOfEdges;
}

void Graph::make_set(City *aCity)
{
    aCity->parent = aCity;
    aCity->rank = 0;
}

City *Graph::find_set(City *aCity)
{
    if(aCity != aCity->parent)
    {
        aCity->parent = find_set(aCity->parent);
    }
    return aCity->parent;
}

void Graph::link(City *aCity, City *bCity)
{
    if(aCity->rank > bCity->rank)
    {
        bCity->parent = aCity;
    }
    else
    {
        aCity->parent = bCity;
        if(aCity->rank == bCity->rank)
        {
            bCity->rank = bCity->rank + 1;
        }
    }
}

void Graph::Union(City *aCity, City *bCity)
{
    link(find_set(aCity), find_set(bCity));
}

//Sort the array of edges using merge sort
void Graph::SortEdges()
{
    MergeSort(setOfEdges, 0, E-1);
}

void Graph::MergeSort(Edge* setOfEdges, int l, int r)
{
    if(l < r)
    {
        int m = (l + r) / 2;
        MergeSort(setOfEdges, l, m);
        MergeSort(setOfEdges, m+1, r);
        Merge(setOfEdges, l, m, r);
    }
}

void Graph::Merge(Edge* setOfEdges, int l, int m, int r)
{
    int i = l; //Staring index for left subarray
    int j = m+1; //Starting index for right subarray
    int k = l; //Starting index for temporary array

    Edge* tempArray = new Edge[E];

    while(i <= m && j <= r)
    {
        if(setOfEdges[i].getDistance() <= setOfEdges[j].getDistance())
        {
            tempArray[k] = setOfEdges[i]; //array[i] is smaller than array[j]
            i++;
            k++;
        }
        else
        {
            tempArray[k] = setOfEdges[j]; //array[j] is smaller than array[i]
            j++;
            k++;
        }
    }

    while(i <= m)
    {
        tempArray[k] = setOfEdges[i]; //copying all elements from left sub-array to temp
        i++;
        k++;
    }

    while(j <= r)
    {
        tempArray[k] = setOfEdges[j]; //copying all elements from right sub-array to temp
        j++;
        k++;
    }

    //putting the sorted array back into the original array
    for(int i = l; i <= r; i++)
    {
        setOfEdges[i] = tempArray[i];
    }
}

//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Graph::MST_Kruskal()
{
    cout << "MST Kruskal Algorithm Result\n" << endl;
    int totalDistance = 0;

    //little redundant but it works for now
    for(int i = 0; i < V; i++)
    {
        //make_set(setOfEdges[i].getCity1());
        //make_set(setOfEdges[i].getCity2());
        make_set(&setOfCities[i]);
    }

    SortEdges();

    for(int i = 0; i < E; i++)
    {
        if(find_set(setOfEdges[i].getCity1()) != find_set(setOfEdges[i].getCity2()))
        {
            //print the edge and its distance
            setOfEdges[i].printEdge();
            //add the distance of the added edge
            totalDistance += setOfEdges[i].getDistance();
            //add the edge to the connected graph
            Union(setOfEdges[i].getCity1(), setOfEdges[i].getCity2());

        }
    }

    cout << "=================================================" << endl;
    cout << "Total Distance: " << totalDistance << endl;
}