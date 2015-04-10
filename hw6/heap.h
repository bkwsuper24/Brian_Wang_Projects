#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename Comparator >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, Comparator c);

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
 	void heapify(int index);
 	void trickleUp(int index);
 	int m;
 	Comparator c;
 	std::vector <T> heapVec;
};

// Add implementation of member functions here


template <typename T, typename Comparator>
Heap<T, Comparator>::Heap(int m, Comparator c)
{
	this->m = m;
	this->c = c;
}

template <typename T, typename Comparator>
Heap<T, Comparator>::~Heap()
{

}
// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
T const & Heap<T,Comparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  else
  {
  	return heapVec[0];
  }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& item)
{
		heapVec.push_back(item);
		trickleUp(heapVec.size()-1);
}

// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename Comparator>
void Heap<T,Comparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  else
  {
  	heapVec[0] = heapVec.back();
  	heapVec.pop_back();
  	heapify(0);
  }

}

template <typename T, typename Comparator>
bool Heap<T,Comparator>::empty() const
{
	if(heapVec.size() == 0)
	{
		return true;
	}

	return false;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::trickleUp(int loc)
{
	int parent = (loc-1)/m;

	//trickle up and replacing 
	while((parent >= 0) && c(heapVec[loc], heapVec[parent]))
	{
		std::swap(heapVec[loc], heapVec[parent]);
		loc = parent;
		parent = (loc-1)/m;
	}
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::heapify(int index)
{
	if((index*m) >= heapVec.size())
	{
		return;
	}
	int child = m*index+1;
	int fchild = m*index+1;
	//for i=0 -> m is m*loc+i <= heapVec.size()
	for(unsigned int i=1; i<m; i++)
	{
		if(((index*m)+i) < heapVec.size())
		{
			int rchild = fchild+i;
			//min heapify, less than comparator
			if(c(heapVec[rchild], heapVec[child]))
			{
				child = rchild;
		
			}
		}
	}

	if(c(heapVec[child], heapVec[index]) == 1)
	{
		std::swap(heapVec[child], heapVec[index]);
		heapify(child);
	}
}

#endif

