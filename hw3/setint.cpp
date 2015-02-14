#include "setint.h"
#include <cstdlib>

SetInt::SetInt()
{


}

SetInt::~SetInt()
{
	while(!list_.empty())
	{
		list_.clear();
	}

}


int SetInt::size() const
{
	return list_.size();
}

bool SetInt::empty() const
{
	return list_.empty();
}

void SetInt::insert(const int& val)
{
	if(exists(val) != true)
	{
		list_.push_back(val);
	}
}

void SetInt::remove(const int& val)
{
	if(exists(val) == true)
	{
		list_.remove(val);
	}
}

bool SetInt::exists(const int&val) const
{
	bool exist = false;

	for(int i=0; i<list_.size(); i++)
	{
		if(val == list_.get(i))
		{
			exist = true;
			return exist;
		}
	}
	return exist;
}

int const* SetInt::first()
{
	counter = 0;
	if(list_.size()==0)
	{
		return NULL;
	}

	return &list_.get(0);
}

int const* SetInt::next()
{
	if(counter == list_.size())
	{
		return NULL;
	}
	
	counter++;
	return &list_.get(counter);
}

SetInt SetInt::setIntersection(const SetInt& other) const
{
	SetInt intersection;

	for(int i=0; i<list_.size(); i++)
	{
		if(other.exists(list_.get(i)))
		{
			intersection.insert(list_.get(i));
		}
	}

	return intersection;
}

SetInt SetInt::setUnion(const SetInt& other) const
{
	SetInt result;
	
	for(int i=0; i<list_.size(); i++)
	{
		if(other.exists(list_.get(i)))
		{
			result.insert(list_.get(i));
		}
		else
		{
			result.insert(list_.get(i));
		}
	}
	
	for(int i=0; i<other.size(); i++)
	{
		if(other.exists(list_.get(i)) == false)
		{
			result.insert(i);
		}
	}
	return result;
}

SetInt SetInt::operator|(const SetInt& other) const
{
	return setIntersection(other);
}

SetInt SetInt::operator&(const SetInt& other) const
{
	return setUnion(other);
}
		
		
		
		
		
