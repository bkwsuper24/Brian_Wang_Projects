#include "user.h"
using namespace std;

User::User() : name_("unknown"), age_(0), balance_(0.0), type_(0), pwordHash_(0)
{

}
User::User(std::string name, int age, double balance, int type, long long pwordHash) : 
  name_(name), age_(age), balance_(balance), type_(type), pwordHash_(pwordHash)
{

}

User::~User()
{

}


int User::getAge() const
{
  return age_;
}

long long User::getPasswordHash() const
{
	return pwordHash_;
}

std::string User::getName() const
{
  return name_;
}

double User::getBalance() const
{
  return balance_;
}

void User::deductAmount(double amt)
{
  balance_ -= amt;
}

void User::dump(std::ostream& os)
{
  os << name_ << " " << age_ << " " << balance_ << " " << type_ << " " << pwordHash_ << endl;
}
