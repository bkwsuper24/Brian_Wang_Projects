#include <iostream>
#include "datastore.h"
#include "util.h"
#include <string>

using namespace std;

DStore::DStore()
{



}

DStore::~DStore()
{



}


void DStore::addProduct(Product* p)
{
	ProductVector.push_back(p);

	std::set<std::string> keyword = p->keywords();
	std::set<std::string>::iterator it;

	for(it=keyword.begin(); it!=keyword.end(); ++it)
	{
		//Product keyword does not exist
		if(ProductMap.find(*it) == ProductMap.end())
		{
			std::set<Product*> temp;
			temp.insert(p);
			ProductMap.insert(make_pair(*it, temp));
		}
		else
		{
			ProductMap.find(*it)->second.insert(p);
		}
	}
}

void DStore::addUser(User* u)
{
	bool isFound = false;
	if(UserVector.size()>0)
	{
		for(unsigned int i=0; i<UserVector.size(); i++)
		{
			if((UserVector[i]->getName() == u->getName()))
			{
				cout << "User exists already!" << endl;
				isFound = true;
			}
		}
		if (isFound == false)
		{
			UserVector.push_back(u);
		}			
	}
	else if(UserVector.size()==0)
	{
		UserVector.push_back(u);
	}
}

vector<Product*> DStore::search(vector<string>& terms, int type)
{
	//vector used to return hits
	std::vector<Product*> results;

	//initialize keyword set with first term in set of map
	std::set<Product*> keyword = ProductMap.find(terms[0])->second;
	if(keyword.size()!=0)
	{
	//iterator for vector
		std::vector<std::string>::iterator it1;
		if(type == 0)
		{
			for(it1 = terms.begin(); it1!=terms.end(); ++it1)
			{
				std::map<std::string, std::set<Product*> >::iterator key = ProductMap.find((*it1));
				std::set<Product*> keyword2 = key->second;
				keyword = setIntersection(keyword, keyword2);
			}
		}

		std::vector<std::string>::iterator it2;
		if(type == 1)
		{
			for(it2 = terms.begin(); it2!=terms.end(); ++it2)
			{
				std::map<std::string, std::set<Product*> >::iterator key = ProductMap.find((*it2));
				std::set<Product*> keyword2 = key->second;
				keyword = setUnion(keyword, keyword2);
			}
		}
	}

	if(keyword.size() == 0)
	{
		return results;
	}


	std::set<Product*>::iterator iter;
	for(iter = keyword.begin(); iter!=keyword.end(); ++iter)
	{
		results.push_back((*iter));
	}

	return results;
}

void DStore::dump(std::ostream& ofile)
{
	ofile << "<products>" << endl;

	for(unsigned int i=0; i<ProductVector.size(); i++)
	{
		ProductVector[i]->dump(ofile);
	}
	
	ofile << "</products>" << endl;
	ofile << "<users>" << endl;

	for(unsigned int i=0; i<UserVector.size(); i++)
	{
		UserVector[i]->dump(ofile);
	}
	ofile <<"</users>" << endl;
}


void DStore::addCart(string username, Product *p)
{
	std::vector<Product*> product = cartVector.find(username)->second; 

	if(product != cartVector.end()->second)
	{
		cout << "Enters loop" << endl;
		product.push_back(p);
	}
	//create new cart
	else
	{
		//temporary vector to add cart
		vector<Product*> temp;
		temp.push_back(p);
		cartVector.insert(make_pair(username, temp));
	}
}

void DStore::viewCart(string username)
{
	//username exists in vector
	if(cartVector.find(username) != cartVector.end())
	{
		std::vector<Product*> temp = cartVector.find(username)->second;

		//temp.size()
		for(unsigned int i=0; i < temp.size(); i++)
		{
			std::cout<<"Item "<< i+1 << endl;
			std::cout<< temp[i]->displayString() << endl;
		}
	}
	else
	{
		cout << "User could not be found!";
		return;
	}

}

void DStore::buyCart(string shopper)
{
	std::vector<User*>sampleuser;

	int counter = 0;
	//Looping through user vector to find if person exists
	for(unsigned int i=0; i<UserVector.size();i++)
	{
		if(UserVector.getName() == shopper)
		{
			counter = 1;
			sampleuser = UserVector[i];
		}
		else
		{
			cout << "You don't exist!";
		}
	}


	if(counter == 1)
	{
		vector<Product*> samplecart = cartVector.find(buyer)->second

		//loop once for the samplecart of one person
		for(unsigned int i=0; i<samplecart.size(); i++)
		{
			//check to see if you have sufficent funds
			if(samplecart[i]->getQty()>0 && (sampleuser->getBalance() - samplecart[i]->getPrice()>=0)
			{
				sampleuser->deductAmount(samplecart[i]->getPrice());
				samplecart[i]->subtractQty(0);
			}
			else
			{
				cout << "You don't have enought money!" << endl;
			}

		}
	}
	else
	{
		return;
	}
}


	




	
	


}
	

