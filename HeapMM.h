#ifndef HEAPMM_H
#define HEAPMM_H

#include <string>
#include <fstream>
#include <iostream>

//This Class is an implementation of an Integer HeapMM (maxmin or minmax) using an array.

class HeapMM
{
private:
  std::string heapType;
  int MAX_SIZE = 500;

  int* heap; //Heap contents
  int insertPoint;

  //Get the chosen child (given childID 1-5) for a given parent index.
  //Returns -1 if not found.
  int getChild(int childID, int parentIndex);

  //Get the parent value of a child, given the child's index
  int getParent(int childIndex);
  //Get the grandparent value of a child, given the child's index.
  int getGrandparent(int childIndex);

public:
  //Constructor
  HeapMM(std::string type, std::string fName, int maxSize=500);

  //Destructor
  ~HeapMM();

  //Build the Heap
  void heapify(int swapPoint);

  //Helper to determine whether a given node is a min or max node.
  bool isMax(int index);

  //Helper to carry out swapping of two nodes by their given indices.
  void swap(int i, int j);

  //Insert a given value to the Heap
  void insert(int value);

  //Delete minimum/maximum values from Heap
  void deleteMin();
  void deleteMax();

  //Find minimum/maximum values in Heap
  int findMin();
  int findMax();

  //Return value from the found index for convenient outputting
  int getMin();
  int getMax();

  //Get the current size of the heap
  int getSize();

  //Level-Order Traversal
  void levelorder();

};

#include "HeapMM.hpp"

#endif
