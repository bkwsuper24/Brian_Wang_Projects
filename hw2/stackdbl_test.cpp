#include "stackdbl.h"
#include "llistdbl.h"
#include <iostream>

using namespace std;

int main() 
{
  StackDbl * stack = new StackDbl();

  // Check if the list is initially empty.
  if (stack->empty()) {
    cout << "SUCCESS: List is empty initially." << endl;
  } else {
    cout << "FAIL: List is not empty initially when it should be." << endl;
  }
	//pushing stack
	stack->push(3);
		
	if(stack->top() == 3)
	{
		cout << "SUCCESS: Just pushed 3 onto stack. " << endl;
	}
	else
	{
		cout << "FAIL: Did not push 3 successfully." << endl;
	}

	stack->push(6);
	stack->push(8);

	if(stack->top() == 8)
	{
		cout << "SUCCESS: Just pushed 6 and 8, but 8 is on top." << endl;
	}
	else
	{
		cout << "FAIL: Did not get top succesfully," << endl;
	}

	//pop off the top
	stack->pop();

	if(stack->top() == 6)
	{
		cout << "SUCCESS: Just popped 8 off the top." << endl;
	}
	else
	{
		cout << "FAIL: Did not pop. " << endl;
	}

	stack->pop();

	if(stack->top() == 3)
	{
		cout << "SUCCESS: Now popped 6 off the top. 3 is value on stack." << endl;
	}
	else
	{
		cout << "FAIL: Did not pop. " << endl;
	}

delete stack;
}

