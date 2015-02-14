#include "llistint.h"
#include <iostream>

using namespace std;

int main()
{
	LListInt* list = new LListInt();

	if(list->empty())
	{
		cout << "SUCCESS: List is initially empty." << endl;
	}
	else
	{
		cout << "FAIL: List is not empty when it should be." << endl;
	}

	 //insert into empty list
        list->insert(0,2);
        if(!list->empty())
        {
                cout << "SUCCESS: List is not empty after one insertion." << endl;
        }
        else
        {
        cout << "FAIL: List is empty after one insertion." << endl;
        }

        //checking size of list
        if (list->size() == 1)
        {
                cout << "SUCCESS: List has size 1 after one insertion." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size();
                cout << " after one insertion.";
                cout << endl;
        }

        //checking value at index
        if (list->get(0) == 2)
        {
                cout << "SUCCESS: 2 is at the 0th index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 2 is not at the 0th index of the list, " << list->get(0);
	}
//inserting at head again 
        list->insert(0,3);

        if(list->get(0) == 3)
        {
                cout << "SUCCESS: 3 is now at the 0th index of the list." << endl;
        }
        else
        {
                cout <<"FAIL: 3 is not at the 0th index of the list, " << list->get(0);
                cout << " is instead." << endl;
        }

        if(list->size() == 2)
        {
                cout << "SUCCESS: List has size 2 after two insertion." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after two insertion.";
	}
 //checking to see if index moved correctly
        if (list->get(1) == 2)
        {
                cout << "SUCCESS: 2 has moved to the 1st index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 2 has not moved." << endl;
        }

        //insert in middle
        list->insert(1,9);
        if(list->size() == 3)
        {
                cout << "SUCCESS: List has size 3 after three insertion." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after three insertion.";
                cout << endl;                                                  
  	}

        if(list->get(1) == 9)
        {
                 cout << "SUCCESS: 9 is at the 1st index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 9 is not at the 1st index of the list, " << list->get(0);
                cout << " is instead." << endl;
        }
        if(list->get(2) == 2)
        {
                cout << "SUCCESS: 2 has moved to 2nd index of list." << endl;
        }
        else
        {
                cout << "FAIL: 2 has not moved." << endl;
        }

        list->insert(3,4);
        if(list->size() == 4)
        {
                cout << "SUCCESS: List has size 4 after four insertion." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after four insertion.";
                cout << endl;
        }
        if (list->get(3) == 4)
        {
                cout << "SUCCESS: 4 is at the 3rd index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 4 is not at the 3rd index of the list, " << list->get(3);
                cout << " is instead." << endl;
	}
        list->remove(3);

        if (list->size() == 3)
        {
                cout << "SUCCESS: List has size 3 after one removal." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after one removal.";
                cout << endl;
        }

        if (list->get(2) == 2)
        {
                cout << "SUCCESS: 2 is at the 2nd index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 2 is not at the 2nd index of the list, " << list->get(2);
                cout << " is instead." << endl;

 	}

        list->remove(1);
        if (list->size() == 2)
        {
                cout << "SUCCESS: List has size 2 after two removal." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after two removal.";
                cout << endl;
        }
        if (list->get(1) == 2)
        {
                cout << "SUCCESS: 2 is at the 1st index of the list." << endl;
        }
        else
        {
                cout << "FAIL: 2 is not at the 1st index of the list, " << list->get(0);
                cout << " is instead." << endl;
        }

	list->remove(0);
        if (list->size() == 1)
        {
                cout << "SUCCESS: List has size 1 after three removal." << endl;
        }
        else
        {
                cout << "FAIL: List has size " << list->size() << " after three removal.";
                cout << endl;
        }

        if(list->get(0) == 2)
        {
                cout << "SUCCESS: 2 is at the 0th index of the list." << endl;
        }
        else
        {
		cout << "FAIL: 2 is not at the 0th index of the list, " << list->get(0);
                cout << " is instead." << endl;
        }

        list->remove(0);
        if (list->empty())
        {
                cout << "SUCCESS: List is empty after four removal." << endl;
        }
        else
        {
                cout << "FAIL: List is not empty after four removal when it should be." << endl;
        }
        delete list;
}

