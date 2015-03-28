#ifndef MSORT_H
#define MSORT_H

#include <vector>
#include <cmath>

using namespace std;

template<class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp);

template<class T, class Comparator>
void Merge(std::vector<T>& finalArray, std::vector<T> left, std::vector<T>right, Comparator comp);


template<class T, class Comparator>
void Merge(std::vector<T>& finalArray, std::vector<T> left, std::vector<T>right, Comparator comp)
{
	int lhs_traverse = 0;
	int rhs_traverse = 0;
	int finalArray_traverse = 0;
	while(left.size() > lhs_traverse && right.size() > rhs_traverse)
	{
		// left < right
		if(comp(left[lhs_traverse], right[rhs_traverse]) == 1)
		{
			finalArray[finalArray_traverse] = left[lhs_traverse];
			lhs_traverse++;
		}
		else
		{
			finalArray[finalArray_traverse] = right[rhs_traverse];
			rhs_traverse++;
		}
		finalArray_traverse++;
	}

	//reading and overwriting final array
	for(unsigned int i=lhs_traverse; i<left.size(); i++)
	{
		finalArray[finalArray_traverse] = left[i];
		finalArray_traverse++;
	}

	for(unsigned int i=rhs_traverse; i<right.size(); i++)
	{
		finalArray[finalArray_traverse] = right[i];
		finalArray_traverse++;
	}
}

template <class T, class Comparator>
void mergeSort(std::vector<T>& myArray, Comparator comp)
{
	std::vector<T> obj_lhs;
	std::vector<T> obj_rhs;
	int obj_middle = floor(myArray.size()/2);

	if(myArray.size() <= 1)
	{
		return;
	}
	else
	{
		//read into left-hand side array
		for(unsigned int i=0; i<obj_middle; i++)
		{
			obj_lhs.push_back(myArray[i]);
		}

		//read into right-hand side array
		for(unsigned int i=obj_middle; i< myArray.size(); i++)
		{
			obj_rhs.push_back(myArray[i]);
		}
		mergeSort(obj_lhs, comp);
		mergeSort(obj_rhs,comp);
		Merge(myArray, obj_lhs, obj_rhs, comp);
	}
	
}
#endif

