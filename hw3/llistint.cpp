#include "llistint.h"
#include <cstdlib>

LListInt::LListInt()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

LListInt::~LListInt()
{
  clear();
}

bool LListInt::empty() const
{
  return size_ == 0;
}

int LListInt::size() const
{
  return size_;
}

/**
 * Complete the following function
 */
void LListInt::insert(int loc, const double& val)
{
	//making sure valid location value
 	if(loc >= 0 && loc <= size_)
	{
		//insert into empty list
		if(size_ == 0)
		{
			Item* temp = new Item;
			head_ = temp;
			tail_ = temp;
			temp->val = val;	
			temp->next = NULL;
			temp->prev = NULL;
			size_++;			
		}
		//insert into front of list
		else if(loc==0)
		{
			Item* temp = new Item;
			temp->prev = NULL;
			temp->next = head_;
			head_->prev = temp;
			head_ = temp;
			temp->val = val;
			size_++;
		}
		//insert into back of list
		else if(loc == size_)
		{
			Item* temp = new Item;
			tail_->next = temp;
			temp->next = NULL;
			temp->val = val;
			temp->prev = tail_;
			tail_ = temp;
			size_++;
		}
		//insert middle of list
		else
		{
			Item* temp = new Item;
			Item* currptr = getNodeAt(loc);
			temp->prev = currptr->prev;
			temp->prev->next = temp;
			currptr->prev = temp;
			temp->next = currptr;
			temp->val = val;
			size_++;			
		}
	}
	else
	{
		return;
	}
			
}

/**
 * Complete the following function
 */
void LListInt::remove(int loc)
{
	//check to see if list is empty before removing
	if(size_ != 0)
	{	
		//making sure valid location value
		if(loc >= 0 && loc <= size_ -1)
		{
			//removing from beginning of list
			if(loc == 0)
			{
				delete head_;
				head_ = head_->next;
				size_--;
			}
			//removing from end of list
			else if(loc == size_-1)
			{
				delete tail_;
				tail_ = tail_->prev;
				size_--;
			}
			//removing from middle of list
			else
			{
				Item* temp1;
				Item* temp2;
				Item* currptr = getNodeAt(loc);
				temp1 = currptr->prev;
				temp1->next = currptr->next;
				temp2 = currptr->next;
				temp2->prev = temp1;
				delete currptr;
				size_--;
			}
		}
		else
		{
			return;
		}
	}
	else
	{
		return;	
	}
}



void LListInt::push_back(const int&val)
{
	Item* temp = new Item;

	//check to see if we push_back into empty list
	if(head_ == NULL)
	{
		temp->next = NULL;
		temp->prev = NULL;
		head_ = temp;
		tail_ = temp;
		temp->val = val;
		size_++;
	}
	else
	{
		tail_->next = temp;
		temp->next = NULL;
		temp->prev = tail_;
		tail_ = temp;
		temp->val = val;
		size_++;
	}
}

LListInt::LListInt(const LListInt& other)
{
	Item* temp = new Item;
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;

	temp = other.head_;

	while(temp->next!=NULL)
	{
		push_back(temp->val);
	}
	
}

LListInt& LListInt::operator=(const LListInt& other)
{
	//check to see if self-assignment or not
	if(this != &other)
	{
		Item* temp = new Item;
		//check to see if necessary to clear depending if list is empty or not
		if(size_!=0)
		{
			this->clear();
		}
		temp = other.head_;
		while(temp->next!=NULL)
		{
			push_back(temp->val);
		}
	}
	return *this;
}
	
 
void LListInt::set(int loc, const double& val)
{
  Item *temp = getNodeAt(loc);
  temp->val = val;
}

int& LListInt::get(int loc)
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

int const & LListInt::get(int loc) const
{
  Item *temp = getNodeAt(loc);
  return temp->val;
}

void LListInt::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


LListInt::Item* LListInt::getNodeAt(int loc) const
{
  Item *temp = head_;
  if(loc >= 0 && loc < size_){
    while(temp != NULL && loc > 0){
      temp = temp->next;
      loc--;
    }
    return temp;
  }
  else {
    //throw std::invalid_argument("bad location");
    return NULL;
  }
}
