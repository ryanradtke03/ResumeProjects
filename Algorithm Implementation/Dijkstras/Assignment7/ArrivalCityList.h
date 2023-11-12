//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Ryan Radtke
// ASU ID: 1223359969
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    int distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
//class ArrivalCityList contains a linked list of ArrCity
class ArrivalCityList
{
private:
    struct ArrCity* head;

public:
    ArrivalCityList();
    ~ArrivalCityList();
    ArrCity* getHead();
    ArrCity* findArrCity(string oneCity);
    bool addArrCity(string oneCity, int distance);
    void printArrCityList();
};


ArrivalCityList::ArrivalCityList()
{
    head = NULL;
}

ArrivalCityList::~ArrivalCityList()
{
    ArrCity *curr = head;
    while(curr != NULL)
    {
        ArrCity *temp = curr;
        curr = curr->next;
        delete temp;
    }
    delete curr;
    delete head;
}

ArrCity* ArrivalCityList::getHead()
{
    return head;
}

//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
ArrCity*  ArrivalCityList::findArrCity(string oneCity)
{

    ArrCity* curr = head->next;

    //traverse through the city
    while(curr!= NULL)
    {
        //if we find the city return curr
        if(curr->arrCityName.compare(oneCity) == 0)
        {
            return curr;
        }
        //iterate
        curr = curr->next;
    }

    //return nothing if the city doesn't exist
    return NULL;
}

//*******************************************************************
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.
bool ArrivalCityList::addArrCity(string oneCity, int distance)
{
    //checking if the city exists
    if(findArrCity(oneCity) != NULL)
    {
        //cant insert duplicate cities
        return false;
    }else
    {
        ArrCity *prv = head;
        ArrCity *curr = head->next;

        ArrCity *newCity;
        newCity->arrCityName = oneCity;
        newCity->distance = distance;
        newCity->next = NULL;

        //check if ArrCityList is empty, if so insert it behind the head
        if(curr == NULL)
        {
            head->next = newCity;
        //loop through and sort alphabetically
        }else
        {
            while (curr != NULL)
            {
                //if newCity name comes before curr then insert it before
                if(curr->arrCityName.compare(newCity->arrCityName) <0)
                {
                    prv->next = newCity;
                    newCity->next = curr;
                }else
                {
                    //iterate
                    prv = curr;
                    curr = curr->next;
                }
            }
        }
    }
    //if you somehow got here
    return NULL;
}

void ArrivalCityList::printArrCityList()
{
    ArrCity *curr = head->next;

    if(head->next == NULL)
    {
        //empty list
    }else
    {
        while(curr != NULL)
        {
          /*  cout << left    << setw(18) << temp->model
                 << left    << setw(18) << temp->make
                 << right   << setw(8)  << temp->vin
                 << setw(10) << fixed << setprecision(2) << temp->price << "\n";

            */
          curr = curr->next;
        }
    }
}
