#include <iostream>
#include <algorithm>
#include "heap.h"
#include <functional>

using namespace std;

int main()
{
	Heap<int, std::less<int> > * minheap = new Heap<int, std::less<int> >(4, std::less<int>());
	Heap<int, std::greater<int> > * maxheap = new Heap<int, std::greater<int> >(3, std::greater<int>());

	std::cout << "MINHEAP" << std::endl;

	minheap->push(3);
	minheap->push(7);
	minheap->push(2);
	minheap->push(9);
	minheap->push(-15);

	for(int i=0; i<4; i++)
	{
		cout << i << "number is " << minheap->top() << endl;
		minheap->pop();
	}

	std::cout << "MAXHEAP" << std::endl;

	maxheap->push(15);
	maxheap->push(27);
	maxheap->push(5);
	maxheap->push(13);
	maxheap->push(10);
	maxheap->push(1);
	maxheap->push(-99);
	maxheap->push(3);
	maxheap->push(3);

	for(int i=0; i<9; i++)
	{
		cout << i << "number is " << maxheap->top() << endl;
		maxheap->pop();
	}


}

