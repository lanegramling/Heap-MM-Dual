#include <iostream>   //I/O
#include <fstream>    //File Input handling
#include <string>     //String convenience

#include "HeapMM.h"	              //MaxMin or MinMax Heap

//Load a HeapMM from a (.txt) file
HeapMM* loadHeap(std::string type, std::string fName) {
  std::cout << "\n\nAttempting to create a " << type << " heap from table from file " << fName << "...";
  HeapMM* heap = new HeapMM(type, fName);
  return heap;
}

//Main function
int main(int argc, char* argv[])
{
  //Initialization
  if (!argv[1]) std::cout << "\nNo heap type given. Defaulting to MaxMin. \n(Usage: './lab8 maxmin' or './lab8 minmax')";
  std::string heapType = (argv[1]) ? argv[1] : "maxmin";
  if (heapType != "maxmin" && heapType != "minmax") {
    std::cout << "\nHeap Type not recognized. Defaulting to MaxMin.";
    heapType = "maxmin";
  }
  std::string fileName = "data.txt"; //File name assignment
  std::cout << "\nDefaulting to 'data.txt'...";

  //Create the heap from the given type and input file.
  HeapMM* heap = loadHeap(heapType, fileName);

  //Main IO loop - controls interaction with created HeapMM.
	int choice = 0;
	do {
    std::cout << "\n\n................................................................"
									<< "\nPlease choose one of the following commands:"
									<< "\n1-	Insert"
                  << "\n2-	DeleteMin"
                  << "\n3-	FindMin"
                  << "\n4-	FindMax"
                  << "\n5- 	DeleteMax"
                  << "\n6-	Level-Order"
                  << "\n7-	Exit"
									<< "\n> ";
    std::cin >> choice;
		int num = 0; //Contains I/O responses
    switch(choice) {
      case 1: //Handle Insert
        std::cout << "\nEnter a number to be inserted: \n> ";
				std::cin >> num;
        heap->insert(num);
        break;
      case 2: //Handle DeleteMin
        std::cout << "\nDeleting from min-heap...";
        heap->deleteMin();
        break;
      case 3: //Handle FindMin
        std::cout << "\nFinding the minimum value...";
        std::cout << "\nMinimum: " << heap->getMin();
        break;
      case 4: //Handle FindMax
        std::cout << "\nFinding the maximum value...";
        std::cout << "\nMaximum: " << heap->getMax();
        break;
      case 5: //Handle DeleteMax
        std::cout << "\nDeleting from max-heap...";
        heap->deleteMax();
        break;
      case 6: //Handle Level-order
        std::cout << "\nLevel-Order traversal:";
        heap->levelorder();
        break;
      case 7: break; //Handle Exit
      default:
        std::cout << "\nThat option was not found. Please try again.";
        break;
    }

} while (choice != 7);
  std::cout << "\n\nExiting - dumping heap...\n";
  delete heap;
}
