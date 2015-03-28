#include <iostream>
#include "datastore.h"
#include "util.h"
#include <string>
#include <vector>

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

void DStore::addReview(Review* r)
{
	ReviewVector.push_back(r);

	string prodName1 = r->prodName;

	std::map<std::string, std::vector<Review*> >::iterator it = reviewMap.find(prodName1);

	//Review does not exist
	if(it == reviewMap.end())
	{
		std::vector<Review*> temp;
		temp.push_back(r);
		reviewMap.insert(make_pair(prodName1, temp));
	}
	else
	{
		it->second.push_back(r);
	}
}
	


vector<Product*> DStore::search(vector<string>& terms, int type)
{
	//vector used to return hits
	std::vector<Product*> results;

	//initialize keyword set with first term in set of map
	std::set<Product*> keyword = ProductMap.find(terms[0])->second;

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
	ofile <<"<reviews>" << endl;

	for(unsigned int i=0; i<ReviewVector.size(); i++)
	{
		ofile << ReviewVector[i]->prodName << "\n" << ReviewVector[i]->rating << " " << ReviewVector[i]->date << 
		" " << ReviewVector[i]->reviewText << "\n";  
	}

	ofile << "</reviews>" << endl;
}


void DStore::addCart(string username, Product *p)
{
	if(cartMap.find(username) != cartMap.end())
	{
		cartMap.find(username)->second.push_back(p);
	}
	//create new cart
	else
	{
		vector<Product*> temp;
		temp.push_back(p);
		cartMap.insert(make_pair(username, temp));
	}
}

std::vector<Product*> DStore::viewCart(string username)
{
	std::vector<Product*> temp;
	//username exists in vector
	if(cartMap.find(username) != cartMap.end())
	{
		temp = cartMap.find(username)->second;

		for(unsigned int i=0; i < temp.size(); i++)
		{
			std::cout<<"Item "<< i+1 << endl;
			std::cout<< temp[i]->displayString() << endl;
		}
	}

	return temp;

}

void DStore::removeCart(std::string name, int index)
{
	std::vector<Product*> tempVec1;
	std::vector<Product*> tempVec2;

	tempVec1 = cartMap.find(name)->second;

	for(unsigned int i=0; i<tempVec1.size(); i++)
	{
		if(i!=index)
		{
			tempVec2.push_back(tempVec1[i]);
		}
	}

	cartMap[name] = tempVec2;


}

void DStore::buyCart(string shopper)
{
	int counter = 0;

	//Looping through user vector to find if person exists
	for(unsigned int i=0; i<UserVector.size();i++)
	{
		if(UserVector[i]->getName() == shopper)
		{
			if(cartMap.find(shopper) != cartMap.end())
			{
				vector<Product*> samplecart = cartMap.find(shopper)->second;

				//loop once for the samplecart of one person
				for(unsigned int j=0; j<samplecart.size(); j++)
				{
					//check to see if you have sufficent funds
					if(samplecart[j]->getQty()>0 && (UserVector[i]->getBalance() - samplecart[j]->getPrice()>=0))
					{
						UserVector[i]->deductAmount(samplecart[j]->getPrice());
						samplecart[j]->subtractQty(1);
						if(samplecart[j]->getQty()==0)
						{
							//samplecart.erase(samplecart.begin()+j);
							cartMap.find(shopper)->second.erase(cartMap.find(shopper)->second.begin()+j);
						}
					}
					else
					{
						cout << "You don't have enough money/There is nothing in your cart!" << endl;
					}
				}
			}
			else
			{
				cout << "User has not added anything to cart before buying!" << endl;
			}
			counter++;
		}
	}
	
	if(counter == 0)
	{
		cout << "User does not exist" << endl;
	}
}

std::vector<User*> DStore::getUserVector()
{
	return UserVector;
}

std::vector<Product*> DStore::getProductVector()
{
	return ProductVector;
}

std::vector<double> DStore::getRating()
{
	return RatingVector;
}

std::map<std::string, std::vector<Review*> > DStore::getReviewMap()
{
	return reviewMap;
}

std::map<std::string, std::vector<Product*> > DStore::getCartMap()
{
	return cartMap;
}


	

	

