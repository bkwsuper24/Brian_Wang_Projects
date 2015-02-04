#include "alistint.h"
#include <cstdlib>

AListInt::AListInt()
{
	_data = new int[10];
	_capacity = 10;
	_size = 0;
}

AListInt::AListInt(int cap)
{
	_capacity = cap;
	_data = new int[cap];
	_size = 0;
}

AListInt::~AListInt()
{
	delete [] _data;


}

int AListInt::size() const
{
	return _size;
}

bool AListInt::empty() const
{
	if(_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AListInt::insert(int pos, const int&val)
{
	if(pos >=0 && pos <= _size)
	{
		if(_size == _capacity)
		{
			resize();
      	
			for(int i=_size; i>=pos; i--)
                	{
                		_data[i+1] = _data[i];
                	}	
                	_data[pos] = val;
                	_size++;		
		}
		else
		{
			for(int i=_size; i>=pos; i--)
			{
				_data[i+1] = _data[i];
			}
			_data[pos] = val;
			_size++;
		}
	}		
	else
	{
		return;
	}
}

void AListInt::remove(int pos)
{
	if(pos >=0 && pos < _size)
	{
		for(int i=pos; i<_size-1; i++)
		{
			_data[i] = _data[i+1];
		}
	_size--;
	}	
	else
	{
		return;
	}	
}

void AListInt::set(int position, const int& val)
{
	if(position >=0 && position <= _size)
	{
		for(int i=0; i< _size; i++)
		{
			if(i == position)
			{
				_data[i] = val;
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		return;
	}
}

int& AListInt::get(int position)
{
	int x=-1;
	if(_size!=0)
	{
		for(int i=0; i<_size;i++)
		{
			if(i == position)
			{
				return _data[i];
			}
		}
	}
	return x;
}

void AListInt::resize()
{
	int* array = new int[_capacity*2];

	for(int i=0; i<_size; i++)
	{
		array[i] = _data[i];
	}

	delete _data;
	_data = array; 
	_capacity = _capacity*2; 
}

int AListInt::capacity() const
{
	return _capacity;
}
			
