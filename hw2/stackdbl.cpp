#include "stackdbl.h"
#include "llistdbl.h"
#include <iostream>
#include <cstdlib>

using namespace std;

StackDbl::StackDbl()
{

}

StackDbl::~StackDbl()
{

}
 /**
   * Returns true if the stack is empty, false otherwise
   */
bool StackDbl::empty() const
{
	return list_.empty();
}

  /**
   * Pushes a new value, val, onto the top of the stack
   */
void StackDbl::push(const double& val)
{
	list_.insert(0,val);
	return;
}
  /**
   * Returns the top value on the stack
   */
double const &  StackDbl::top() const
{
	return list_.get(0);
}
	
  /**
   * Removes the top element on the stack
   */
void StackDbl::pop()
{
	list_.remove(0);
	return;
}
