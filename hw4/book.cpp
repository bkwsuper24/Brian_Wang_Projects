#include <iostream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author):

	Product(category, name, price, qty),
	isbn_(isbn),
	author_(author)
{

}

Book::~Book()
{


}

string Book::getIsbn() const
{
	return isbn_;
}

string Book::getAuthor() const
{
	return author_;
}

set<string> Book::keywords() const
{
	string keyword = category_ + " " + author_ + " " + name_ + " ";

	set<string> myset;
	myset = parseStringToWords(keyword);
	myset.insert(isbn_);

	return myset; 
}

string Book::displayString() const
{
	stringstream ss;
	stringstream nn;

	string str_price;
	string str_qty;

	ss << qty_;
	str_qty = ss.str();

	nn << price_;
	str_price = nn.str();

	string display = name_ + "\n" + "Author: " + author_ + " " + "ISBN: " + isbn_ + "\n" + str_price + " " + str_qty + " left.";
	return display;
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

