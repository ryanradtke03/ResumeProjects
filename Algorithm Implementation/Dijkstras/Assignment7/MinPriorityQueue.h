//********************************************************************
// ASU CSE310 Fall 2022 Assignment #7
// Name of Author: Ryan Radtke
// ASU ID: 1223559969
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
#include <cmath>

using namespace std;

//represent each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    int d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
private:
    struct DepCity* depCityArr;	        //a DepCity array
    int capacity, size;

public:
    MinPriorityQueue(int capacity);
    ~MinPriorityQueue();

    DepCity* getDepCityArr();
    int getSize();
    int getCapacity();
    int isFound(string oneDepCityName);
    bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
    bool insert(DepCity oneDepCity);
    void heapify(int index);
    DepCity getHeapMin();
    void extractHeapMin();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
    void build_min_heap();
};


MinPriorityQueue::MinPriorityQueue(int capacity)
{
    depCityArr = new DepCity[capacity];
    this->capacity = capacity;
    size = 0;
}

MinPriorityQueue::~MinPriorityQueue()
{
    delete[] depCityArr;
}

DepCity* MinPriorityQueue::getDepCityArr()
{
    return depCityArr;
}

int MinPriorityQueue::getSize()
{
    return size;
}

int MinPriorityQueue::getCapacity()
{
    return capacity;
}

int MinPriorityQueue::isFound(string oneDepCityName)
{
    for(int i = 0; i < size; i++)
    {
        if(depCityArr[i].depCityName == oneDepCityName)
        {
            return i;
        }
    }
    //return -1 if it doesnt exist
    return -1;
}

bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue)
{

    if(index >= size)
    {
        //doesnt exist
        return false;
    }

    //change value at index
    depCityArr[index] = oneDepCityWithNewDValue;

    //while child is smaller than parent move it up
    while(index > 0 && depCityArr[parent(index)].d > depCityArr[index].d)
    {
        swap(depCityArr[parent(index)], depCityArr[index]);
    }

    return true;

}

bool MinPriorityQueue::insert(DepCity oneDepCity)
{


    //if no cars then insert w/o heapify
    if(size == 0)
    {
        size++;
        depCityArr[size-1] = oneDepCity;
        return true;
    }

    //check if car exists, if so return false
    if(isFound(oneDepCity.depCityName) != -1)
    {
        return false;
    }

    //check capacity, if capacity == size then double capacity
    if(size == capacity)
    {
        capacity = capacity * 2;
        DepCity* newArray = new DepCity[capacity];

        //copy values from old array to new
        for(int i = 0; i < size; i++)
        {
            newArray[i] = depCityArr[i];
        }

        delete[] depCityArr;
        depCityArr = newArray;
        newArray = NULL;

    }


    //insert elements as last element
    size++;
    depCityArr[size-1] = oneDepCity;
    //heapify
    decreaseKey(size-1, oneDepCity);
    return true;

}

void MinPriorityQueue::heapify(int index)
{
    int left = leftChild(index);
    int right = rightChild(index);
    int largest;


    if(left <= size-1 && depCityArr[left].d < depCityArr[index].d)
    {
        largest = left;
    }else
    {
        largest = index;
    }

    if(right <= size-1 && depCityArr[right].d < depCityArr[largest].d)
    {
        largest = right;
    }

    if(largest != index)
    {
        swap(depCityArr[index], depCityArr[largest]);
        heapify(largest);
    }

}

DepCity MinPriorityQueue::getHeapMin()
{
    return depCityArr[0];
}

void MinPriorityQueue::extractHeapMin()
{
    if(size <= 0)
    {
        return;
    }
    if(size == 1)
    {
        size--;
        return;
    }

    DepCity temp = depCityArr[0];
    depCityArr[0] = depCityArr[size -1];
    size--;
    heapify(0);
    return;
}

int MinPriorityQueue::leftChild(int parentIndex)
{
    return (2*parentIndex) + 1;
}

int MinPriorityQueue::rightChild(int parentIndex)
{
    return (2*parentIndex) + 2;
}

int MinPriorityQueue::parent(int childIndex)
{
    return floor((childIndex-1)/2);
}

void MinPriorityQueue::printHeap()
{

    cout << "\nHeap size = " << getSize() << "\n" << endl;

    cout << left;
    cout << setw(15) << "Dep. City"
         << setw(12) << "d Value"
         << setw(15) << "PI"
         << "Arrival City List" << endl;
    //----
    //----
}

void MinPriorityQueue::build_min_heap()
{
    for(int i = (size/2); i >= 0; i--)
    {
        heapify(i);
    }

}
