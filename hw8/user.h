#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>

/**
 * Implements User functionality and information storage
 *  You should not need to derive anything from User at this time
 */
class User{
 public:
  User();
  User(std::string name, int age, double balance, int type, long long pwordHash);
  virtual ~User();

  int getAge() const;
  long long getPasswordHash() const;
  double getBalance() const;
  std::string getName() const;
  void deductAmount(double amt);
  virtual void dump(std::ostream& os);

 private:
  std::string name_;
  int age_;
  double balance_;
  int type_;
  long long pwordHash_;
};
#endif
