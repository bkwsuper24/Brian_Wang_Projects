#include <iostream>
#include <iomanip>
#include "product.h"
#include "util.h"
#include <string>
#include <sstream>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand):

	Product(category, name, price, qty),
	size_(size),
	brand_(brand)
{

}

Clothing::~Clothing()
{


}

string Clothing::getSize() const
{
	return size_;
}

string Clothing::getBrand() const
{
	return brand_;
}

set<string> Clothing::keywords() const
{
	string keyword = category_ + " " + name_ + " " + size_ + " " + brand_;

	return (parseStringToWords(keyword)); 
}

string Clothing::displayString() const
{
	stringstream ss;
	stringstream nn;

	string str_price;
	string str_qty;

	ss << qty_;
	str_qty = ss.str();

	nn << price_;
	str_price = nn.str();

	string display = name_ + "\n" + "Size: " + size_ + " " + "Brand: " + brand_ + "\n" + str_price + " " + str_qty + " left.";
	return display;
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
