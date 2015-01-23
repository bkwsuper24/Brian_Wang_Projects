#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

struct Item
{
	Item(int v, Item* n)
	{
		val = v;
		next = n;
	}
	int val;
	Item* next;
};

void readLists(Item*& head1, Item*& head2, char* fname)
{
	Item* curr;

	ifstream inputfile (fname);

	if(inputfile.fail())
	{
		cout << "Error! Cannot read file!" << endl;
		return;
	}

	for(int i=0; i<2; i++)
	{
		string line;
		//reading in first line to a temporary string
		getline(inputfile, line);	
		stringstream ss;
		ss << line;
		//this loop is to check that ss isn't at end, and string contains something
		while(!ss.eof() && line.size() > 0)
		{
			int ssline;
			//ssline contains first number only
			ss >> ssline;
			
			if(i==0)
			{     
				if(head1 == NULL)//create head1
				{
					head1 = new Item(ssline, NULL);
					curr = head1;
				}
				
				else if(head1 != NULL)//updating curr when head1 is created
				{
					curr -> next = new Item(ssline, NULL);
					curr = curr -> next;
				}
			}
			else if (i==1)
			{
				if(head2 == NULL)//create head2
                               	{
                                       	head2 = new Item(ssline, NULL);
                                       	curr = head2;
                               	}

                               	else if(head2 != NULL)//updating curr when head2 is created
                               	{
                                       	curr -> next = new Item(ssline, NULL);
                                       	curr = curr -> next;
                               	}
                       	}
		}
	}
return;
}


	
//Copying and concatenating two lists into one
Item* concatenate(Item* head1, Item* head2)
{
	if(head1 == NULL)
	{
		if(head2 == NULL)
		{
			return NULL;
		}
	
		else
		{
			return new Item(head2->val, concatenate(head2->next, head1));
		}
	}

	else
	{
		return new Item(head1->val, concatenate(head1->next, head2));
	}

}




void removeEvens(Item*& head)
{	
	//Starts and checks for first item in list to see if even
	if(head->val %2 == 0)
	{
		Item* temp;
		temp = head;
		head = head->next;
		removeEvens(head);
		delete temp;
	}
	//Ends function once we are done reading through list	
	if(head->next == NULL)
	{
		return;
	}
	else
	{
		if(head->next->val %2 != 0)
		{
			//Call function again and move pointer to next if not even
			removeEvens(head->next);
		}
		else
		{
			//Skipping evens
			Item* temp2;
			temp2 = head->next;
			head->next = head->next->next;
			removeEvens(head);
			delete temp2;
		}
	}
}





/*
double findAverage(Item* head);
{

}
*/

//Outputting function to file
void printList(ostream& ofile, Item* head)
{
	 if(head == NULL)
	 {
		 ofile << endl;
	 }
 	 else
	 {
   		 ofile << head->val << " ";
   		 printList(ofile, head->next);
 	 }
}


int main(int argc, char* argv[])
{
	//Creating heads
	Item* head1 = NULL; 
	Item* head2 = NULL; 
	Item* head3 = NULL;

	//Calling function that reads input
	readLists(head1, head2, argv[1]);
	
	//Calling function that writes output
	ofstream ofile(argv[2]);
	
	//Calling function prototype of concatenate and printing
	head3 = concatenate(head1, head2);
	printList(ofile, head3);
	
	//Calling function prototype of removeEvens and printing
	removeEvens(head3);
	printList(ofile, head3);

	//cout << findAverage(head3) << endl;

	//Deleting memory used up by head1
	while (head1!=NULL)
        {
                Item* temp1;
                temp1 = head1;
                head1 = head1->next;
                delete temp1;
        }

	//Deleting memory used up by head2
	while (head2!=NULL)
        {
                Item* temp2;
                temp2 = head2;
                head2 = head2->next;
                delete temp2;
        }

	//Deleting memory used by head3
	while (head3!=NULL)
	{
		Item* temp3;
		temp3 = head3;
		head3 = head3->next;
		delete temp3;
	}
		
}
