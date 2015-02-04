#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() {
  StackDbl * stack  = new StackDbl();

  // Check if the list is initially empty.
  if (stack->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }	

 	//Push an item to top.
	stack->push(5);
	
	//Get top value
	stack->top
	stack->push(2);
	stack->push(7);


  // Check if the list is still empty.
  if (!list->empty()) {
    cout << "SUCCESS: List is not empty after insertions." << endl;
  } else {
    cout << "FAIL: List is empty after one insertion." << endl;
  }

  if (list->size() == 1) {
    cout << "SUCCESS: List has size 1 after one insertion." << endl;
  } else {
    cout << "FAIL: List has size " << list->size() << " after one insertion.";
    cout << endl;
  }

  // Check if the value is correct.
  if (list->get(0) == 3.3) {
    cout << "SUCCESS: 3.3 is at the 0th index of the list." << endl;
  } else {
    cout << "FAIL: 3.3 is not at the 0th index of the list, " << list->get(0);
    cout << " is instead." << endl;
  }
	//insert item at tail
	list->insert(1,4);
	if(list->get(1) == 4)
	{
		cout << "SUCCESS: 4 is at the 1st index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 4 is not at the 0th index of the list," << list->get(1);
		cout << " is instead." <<  endl;
	}

	//insert item at tail
	list->insert(2,4.1);
	if(list->get(2) == 4.1)
	{
		cout << "SUCCESS: 4.1 is at the 2nd index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 4.1 is not at the 2nd index of the list, " << list->get(2);
		cout << " is instead."  << endl;
	}

	//insert item at tail
	list->insert(3,5);
	
	if(list->get(3) == 5)
	{
		cout << "SUCCESS: 5 is at the 3rd index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 5 is not at the 3rd index of the list, " << list->get(3);
		cout << " is instead" << endl;
	}
	
	//insert item in middle of list
	list->insert(2,5.5);
	if(list->get(2) == 5.5)
	{
		cout << "SUCCESS: 5.5 has been inserted at the 2nd index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 5.5 is not at the 2nd index of the list, " << list->get(2);
		cout << " is instead" << endl;
	}
	if(list->get(3) == 4.1)
	{
		cout << "SUCCESS: 4.1 has now moved from 2nd to 3rd index of list." << endl;
	}
	else
	{
		cout << "FAIL: 4.1 is not at the 3rd index of the list, " << list->get(3);
		cout << " is instead"  << endl;
	}
	if(list->get(4) == 5)
	{
		cout << "SUCCESS: 5 has now moved from 3rd to 4th index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 5 is not at the 4th index of the list, " << list->get(4);
		cout << " is instead" << endl;
	}
	
	//insert item in middle of list
	list->insert(4, 1.7);
	if(list->get(4) == 1.7)
	{
		cout << "SUCCESS: 1.7 has been inserted at the 4th index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 1.7 is not at the 4th index of the list, " << list->get(4);
		cout << " is instead" << endl;
	}
	if(list->get(5) == 5)
	{
		cout << "SUCCESS: 5 has now moved from 4th to 5th index of the list." << endl;
	}
	else
	{
		cout << "FAIL: 5 is not at the 5th index of the list, " << list->get(5);
		cout << " is instead" << endl;
	} 
	if(list->size() == 6)
	{
		cout << "SUCCESS: 6 total items in list" << endl;
	}
	else
	{
		cout << "FAIL: List has size " << list->size() << " after six insertions.";
    		cout << endl;
	}

	//remove from tail
	list->remove(5);

	if(list->size() == 5)
	{
		cout << "SUCCESS: Just removed last item." << endl;
		cout << "List has size:" << list->size() << endl;
	}
	else
	{
		cout << "FAIL: List size is:" << list->size() << endl;
	}

	//remove from head
	list->remove(0);
	if(list->get(0) == 4)
	{
		cout << "SUCCESS: Just removed head item." << endl;
		cout << list->get(0) << " has moved from 1st to 0th index." << endl;
	}
	else
	{
		cout << "FAIL: Value is: " << list->get(0) << endl;
	}

	if(list->size() == 4)
	{
		cout << "SUCCESS: List has size of: " << list->size() << endl;
	}
	else
	{
		cout << "FAIL: List has size: " << list->size() << endl;
	}
	
	//remove from middle
	list->remove(2);
	if(list->get(2) == 1.7)
	{
		cout << "SUCCESS: Removed middle item." << endl;
		cout << list->get(2) << " has moved from 3rd to 2nd index." << endl;
	}
	else
	{
		cout << "FAIL: " << list->get(2)  << endl;
	}
	
	// remove from middle
	list->remove(1);
	if(list->get(1) == 1.7)
	{
		cout << "SUCCESS: Removed middle item." << endl;
		cout << list->get(1) << " has moved from 2nd to 1st index." << endl;
	}
	else
	{
		cout << "FAIL: " << list->get(1) << endl;
	}

	//remove from head
	list->remove(0);
	if(list->size() == 1)
	{
		cout << "SUCCESS: Removed head. " << list->size() << " item left." << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
	
	//remove from head
	list->remove(0);
	if(list->size() == 0)
	{
		cout << "SUCCESS: Done with all removals." << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}

  // Clean up memory.
  delete list;
}
