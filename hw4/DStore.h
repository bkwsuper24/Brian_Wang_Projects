#ifndef DSTORE_H
#define DSTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include <map>

class DStore: public DataStore
{
  public:

    DStore();
    virtual ~DStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    //extra functions
    void addCart(std::string username, Product* p);
    void viewCart(std::string username);
    void buyCart(std::string shopper);

    vector<Product*> getProd

  private:

    std::vector<Product*> ProductVector;
    std::vector<User*> UserVector;

    std::map<std::string, std::set<Product*> > ProductMap;
    std::map<std::string, std::vector<Product*> > cartVector;
};

#endif