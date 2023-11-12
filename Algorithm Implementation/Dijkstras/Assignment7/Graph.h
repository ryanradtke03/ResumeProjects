//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Ryan Radtke
// ASU ID: 1223359969
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
//----

using namespace std;

class Graph
{
private:
    int numOfNode;                 //number of nodes in the graph
    MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
    //of departure city objects
public:
    Graph(int numOfNode, MinPriorityQueue* cityHeap);
    ~Graph();
    void printGraph();
    void initialize_single_source(string sourceCityName);
    void relax(DepCity u, DepCity v);
    int findOneCity(string aCityName);
    void dijkstra(string sourceCityName);
    void printDijkstraPath(string sourceCityName);
    void printPath(string sourceCityName, DepCity* aCity);

    //add any auxiliary functions here in case you need them
    //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
    this->numOfNode = numOfNode;
    this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
    delete [] cityHeap;
    cityHeap = NULL;
    numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph()
{



   cout << left;
   cout << setw(15) << "City Name" <<

}

void Graph::initialize_single_source(string sourceCityName)
{
    for(int i = 0; i < numOfNode; i++)
    {
        cityHeap->getDepCityArr()[i].d = INT_MAX;
        cityHeap->getDepCityArr()[i].pi = NULL;
    }

    cityHeap->getDepCityArr()[cityHeap->isFound(sourceCityName)].d = 0;

}

void Graph::relax(DepCity u, DepCity v)
{

    if(v.d > (u.d + u.arrCityList->findArrCity(v.depCityName)->distance))
    {
        v.d = u.arrCityList->findArrCity(v.depCityName)->distance;
        //set pi
        v.pi = &u;
    }

}

int Graph::findOneCity(string aCityName)
{
    return cityHeap->isFound(aCityName);
}

void Graph::dijkstra(string sourceCityName)
{

    DepCity* visited = new DepCity[numOfNode];
    int i = 0;

    while(cityHeap->getSize() != 0)
    {
        //get smallest distance
        DepCity u = cityHeap->getHeapMin();
        cityHeap->extractHeapMin();

        //add min to set of visited nodes
        visited[i] = u;
        i++;

        //loop through all adjacent nodes to u
        ArrCity* curr = u.arrCityList->getHead()->next;
        while(curr != NULL)
        {
            DepCity v = cityHeap->getDepCityArr()[cityHeap->isFound(curr->arrCityName)];
            relax(u,v);
            curr = curr->next;
        }

    }

}

void Graph::printDijkstraPath(string sourceCityName)
{

    ArrCity* cityList = cityHeap->getDepCityArr()[cityHeap->isFound(sourceCityName)].arrCityList->getHead();

    for(int i = 0 ; i < cityHeap->getSize(); i++) {
        cout << "Source City: " << sourceCityName << endl;
        cout << endl;

        cout << "Arrival City" << setw(12) << "Shortest Dist." << setw(12) << "Shortest Path" << endl;
        cout << cityList->arrCityName << setw(12) << cityList->distance << setw(12) <<  "Path" << endl;

    }

}

void Graph::printPath(string sourceCityName, DepCity *aCity)
{

}
