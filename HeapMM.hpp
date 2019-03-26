
#include "math.h"
#include "HeapMM.h"

//Constructor (Builds Heap)
HeapMM::HeapMM(std::string type, std::string fName, int maxSize)
{
  heapType = type;
  MAX_SIZE = maxSize;
  heap = new int[MAX_SIZE];
  for (int i=0 ; i < MAX_SIZE ; i++) heap[i] = -1;     //Initialize heap to -1's
  std::ifstream file(fName);  //Load data as a complete binary tree given a file name.

  if (file.is_open()) {
    for (insertPoint=1; file >> heap[insertPoint]; insertPoint++); //fill as complete binary tree
    file.close();
    for (int h=insertPoint-1 ; h > 1 ; h--) heapify(h); //Heapify towards the root
    for (int h=insertPoint-1 ; h > 1 ; h--) heapify(h);
  } else std::cout << "\nCould not load input file " << fName << " into MaxMinHeap...";

}

//Destructor
HeapMM::~HeapMM()
{
  delete[] heap;
}

//Heapification
//swapPoint marks the child index to check if swapping is necessary
void HeapMM::heapify(int swapPoint)
{
    int parentPoint = getParent(swapPoint);
    int ancestorN = parentPoint;
    if (heap[swapPoint] > heap[parentPoint] && heap[parentPoint] != -1) { //x > parent
      if (isMax(parentPoint)) {        //need to hold: x < z for all max node z on path from x to root
        while (heap[swapPoint] > heap[ancestorN]) {
          if (!ancestorN) break;
          swap(swapPoint, ancestorN);
          swapPoint = ancestorN;
          ancestorN = getGrandparent(ancestorN);
        }
      } else {
        ancestorN = getGrandparent(swapPoint);
        while (heap[swapPoint] > heap[ancestorN]) {
          if (!ancestorN) break;
          swap(swapPoint, ancestorN);
          swapPoint = ancestorN;
          ancestorN = getGrandparent(ancestorN);
        }
      }
    } else if (heap[swapPoint] < heap[parentPoint] && heap[parentPoint] != -1) { //x < parent
      if (!isMax(parentPoint)) {   //need to hold: x > z for all min node z on the path from x to root
        int ancestorN = parentPoint;
        while (heap[swapPoint] < heap[ancestorN]) {
          swap(swapPoint, ancestorN);
          swapPoint = ancestorN;
          ancestorN = getGrandparent(ancestorN);
          if (!ancestorN) break;
        }
      } else {
        ancestorN = getGrandparent(swapPoint);
        while (heap[swapPoint] < heap[ancestorN]) {
          if (!ancestorN) break;
          swap(swapPoint, ancestorN);
          swapPoint = ancestorN;
          ancestorN = getGrandparent(ancestorN);
        }
      }
    }
}

//Given a node and knowing the heap Type, return whether it is a Max or Min node.
//A return value of false indicates a min node.
//bool b reflects whether the given node is the same 'min' or 'max'-level-ness as
//the root of the tree, given the heap type.
bool HeapMM::isMax(int index)
{
  bool b = ((int)floor(log(index)/log(2)) % 2);
  return (heapType == "maxmin") ? !b : b;
}

//Helper to perform a swap between two nodes.
void HeapMM::swap(int i, int j)
{
  int temp = heap[j];
  heap[j] = heap[i];
  heap[i] = temp;
}

//Insert a given value to the Heap (Bottom-up approach)
void HeapMM::insert(int value)
{
    heap[insertPoint] = value;
    heapify(insertPoint);
    std::cout << "\nIncrementing insertion point to " << insertPoint + 1 << ".";
    insertPoint++;
}

//Delete minimum/maximum values from Heap
void HeapMM::deleteMin()
{
  insertPoint--;
  if (heapType == "minmax") {
    swap(1, insertPoint);
    heap[insertPoint] = -1;
  } else {
    swap(findMin(), insertPoint);
    heap[insertPoint] = -1;
  }
}

void HeapMM::deleteMax()
{
  insertPoint--;
  if (heapType == "maxmin") {
    swap(1, insertPoint);
    heap[insertPoint] = -1;
  } else {
    swap(findMax(), insertPoint);
    heap[insertPoint] = -1;
  }
}

//Find minimum/maximum values in Heap
//Return - index of the located int, or -1 if not found.
int HeapMM::findMin()
{
  if (heapType == "minmax") return 1;

  int min = 1;
  for (int i = 1; i < getSize() ; i++) if (heap[min] > heap[i]) min = i;
  return min;
}
int HeapMM::findMax()
{
  if (heapType == "maxmin") return 1;

  int max = -1;
  for (int i = 1; i < getSize() ; i++) if (heap[max] < heap[i]) max = i;
  return max;
}


//Return value from the found index for convenient outputting
int HeapMM::getMin()
{ return (heap[findMin()]);}

int HeapMM::getMax()
{ return (heap[findMax()]);}

//Level-Order Traversal
void HeapMM::levelorder()
{
  std::cout << "\n";
  for (int i=1 ; i < getSize(); i++) {
    if ((log(i)/log(2)) == floor((log(i)/log(2)))) std::cout << "\n";
    else if (i % 2 == 0) std::cout << "- ";
    std::cout << heap[i] << " ";
  }

}


//Get the chosen child (given childID 1-5) for a given parent index.
//Returns -1 if not found.
int HeapMM::getChild(int childID, int parentIndex)
{ return ((2 * parentIndex) + childID); }

//Get the parent index of a child, given the child's index
int HeapMM::getParent(int childIndex)
{ return floor((childIndex) / 2); }

//Get the parent index of a child, given the child's index
int HeapMM::getGrandparent(int childIndex)
{ return floor((childIndex) / 4); }

int HeapMM::getSize()
{
  int size = 0;
  for (int i = 1; i < MAX_SIZE; i++) if (heap[i] != -1) size++;
  return size + 1;
}
