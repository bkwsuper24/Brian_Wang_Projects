#include <iostream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):

	Product(category, name, price, qty),
	genre_(genre),
	rating_(rating)
{

}

Movie::~Movie()
{


}

string Movie::getGenre() const
{
	return genre_;
}

string Movie::getRating() const
{
	return rating_;
}

set<string> Movie::keywords() const
{
	string keyword = category_ + " " + name_ + " " + genre_ + " ";

	set<string> myset;

	myset = parseStringToWords(keyword);
	myset.insert(rating_);

	return myset; 
}

string Movie::displayString() const
{
	stringstream ss;
	stringstream nn;

	string str_price;
	string str_qty;

	ss << qty_;
	str_qty = ss.str();

	nn << price_;
	str_price = nn.str();

	string display = name_ + "\n" + "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n" + str_price + " " + str_qty + " left.";
	return display;
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}
