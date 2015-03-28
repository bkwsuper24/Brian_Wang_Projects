#include <sstream>
#include <iomanip>
#include "product.h"
#include <string>

Product::Product(const std::string category, const std::string name, double price, int qty) : 
  name_(name),
  price_(price),
  qty_(qty),
  category_(category)
{

}

Product::~Product()
{
  /*//Deallocation
  map<std::string, std::set<Product*> > iterator it = ProductMap.begin();
  while(it !=ProductMap.end())
  {
    ProductMap.erase(it++);
  }

  map<std::string, std::vector<Product*> > iterator it = cartVector.begin();
  while(it !=cartVector.end())
  {
    cartVector.erase(it++);
  }
  */
}


double Product::getPrice() const
{
  return price_;
}

std::string Product::getName() const
{
  return name_;
}

void Product::subtractQty(int num)
{
  qty_ -= num;
}

int Product::getQty() const
{
  return qty_;
}




/**
 * default implementation...can be overriden in a future
 * assignment
 */ 
bool Product::isMatch(std::vector<std::string>& searchTerms) const
{
  return false;
}

void Product::dump(std::ostream& os) const
{
  os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n";
}

std::string Product::displayString() const
{
  std::stringstream ss;
  std::stringstream nn;

  std::string str_price;
  std::string str_qty;

  ss << qty_;
  str_qty = ss.str();

  nn << price_;
  str_price = nn.str();

  std::string display = name_ + " " + str_price + " " + str_qty;
  return display;


}



