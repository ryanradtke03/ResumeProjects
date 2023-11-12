//************************************************************************
// ASU CSE310 Assignment #8 Fall 2022
// ASU ID: 1223359969
// Name: Ryan Radtke
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

#include <iostream>

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance);
int searchCityArr(City* oneCityArray, int size, string oneCityName);

int main()
{
    int V, E;        //number of vertice and edges

    cin >> V >> E;
    cin.ignore(20, '\n');

    //a City array used to store all vertice (Cities) of the graph
    City* cityArray = new City[V];

    //an array used to store all edges of the graph
    Edge* edgeArray = new Edge[E];

    int i =0, j=0; //index for cityArray and edgeArray

    //local variables
    City* city1;
    City* city2;
    Edge* aNewEdge;

    string city1Name;

    string city2Info;
    string city2Name;
    int city2Distance;

    int numOfCities = 0;
    int numOfEdges = 0;

    string oneLine;

    getline(cin, oneLine);

    while(oneLine.compare("End") != 0)
    {
        //get one line of the input, extract the first token
        //create a City if it does not exist in cityArray,
        //insert it inside the cityArray. This will be first point of the 'aNewEdge'

        //EXTRACT oneLine into its component city(s)
        // -> X  ,  Y(d)  ,  Z(d)
        string delimiter = ",";
        int pos=oneLine.find(delimiter);
        string token = oneLine.substr(0,pos);
        city1Name = token;
        oneLine.erase(0, pos+delimiter.length());

        //if the city isn't in the array then add it to the array of cities
        if(searchCityArr(cityArray, numOfCities, city1Name) == -1)
        {
            //create a city
            city1 = new City(city1Name);
            //insert into cityArray
            cityArray[numOfCities] = *city1;
            //increase numOfCities
            numOfCities++;
        }
        //the city already exist so set it equal to city1
        else
        {
            city1 = &cityArray[searchCityArr(cityArray,numOfCities,city1Name)];
        }


        //extract the arrival city info. check whether it exists in
        //cityArray or not, if not, create a new City, add it inside.
        //This city will be the second point of the 'aNewEdge'
        //EXTRACT oneLine into its component city(s)
        //  X  , -> Y(d)  ,  Z(d)  ,  ...  and so on

        while(!oneLine.empty())
        {
            pos=oneLine.find(delimiter);
            token = oneLine.substr(0,pos);
            city2Info = token;
            oneLine.erase(0, pos+delimiter.length());

            //if the cityInfo isn't empty then get its components
            if(!city2Info.empty())
            {
                //get city2Name and city2Distance from city2Info
                getArrCityInfo(city2Info, city2Name, city2Distance);

                //if the city doesn't already exist then add it to array of cities
                if(searchCityArr(cityArray, numOfCities, city2Name) == -1)
                {
                    //create a city
                    city2 = new City(city2Name);
                    //insert into cityArray
                    cityArray[numOfCities] = *city2;
                    //increase numOfCities
                    numOfCities++;
                }
                    //if it does exist then just set city2 equal to the city
                else
                {
                    city2 = &cityArray[searchCityArr(cityArray, numOfCities, city2Name)];
                }

                //by using the two cities we got above, create a new edge
                aNewEdge = new Edge(&cityArray[searchCityArr(cityArray, numOfCities, city1->cityName)], &cityArray[searchCityArr(cityArray, numOfCities, city2->cityName)], city2Distance);
                //insert edge into edgeArray
                edgeArray[numOfEdges] = *aNewEdge;
                //increase the number of edges
                numOfEdges++;
            }
        }

        //get next line
        getline(cin, oneLine);
    } //repeat until the 'End'

    //Create a Graph object by using cityArray and edgeArray
    Graph* cityGraph = new Graph(numOfCities, numOfEdges, cityArray, edgeArray);

    //Run Kruskal MST algorithm on above graph
    cityGraph->MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Y(1234)', this function
//extract the arrival city name 'Y' and distance '1234'
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, int& distance)
{
    //GET oneArrCityInfo's arrCityName
    string delimiter = "(";
    int pos = oneArrCityInfo.find(delimiter);
    string token = oneArrCityInfo.substr(0, pos);
    arrCityName = token;
    oneArrCityInfo.erase(0, pos+delimiter.length());

    //GET oneArrCityInfo's distance
    delimiter = ")";
    pos = oneArrCityInfo.find(delimiter);
    token = oneArrCityInfo.substr(0, pos);
    distance = stoi(token);
    oneArrCityInfo.erase(0, pos+delimiter.length());
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCityArr(City* oneCityArray, int size, string oneCityName)
{
    //if the array is empty then there cannot be a city in the array so return -1
    if(size == 0)
    {
        return -1;
    }

    //loop through the array of cities and return index if it exists or -1 if it doesn't already exist
    for(int i = 0; i < size; i++)
    {
        if(oneCityArray[i].cityName.compare(oneCityName) == 0)
        {
            return i;
        }
    }
    return  -1;
}