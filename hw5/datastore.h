#ifndef DATASTORE_H
#define DATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "product.h"
#include "user.h"
#include "review.h"
#include <map>

/** 
 * DataStore Interface needed for parsing and instantiating products and users
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 */
class DataStore {
 public:
  virtual ~DataStore() { }

  /**
   * Adds a product to the data store
   */
  virtual void addProduct(Product* p) = 0;
 
  /**
   * Adds a user to the data store
   */
  virtual void addUser(User* u) = 0;

  /**
   * Adds a review
   */
  virtual void addReview(Review* r) = 0;

  /**
   * Performs a search of products whose keywords match the given "terms"
   *  type 0 = AND search (intersection of results for each term) while
   *  type 1 = OR search (union of results for each term)
   */
  virtual std::vector<Product*> search(std::vector<std::string>& terms, int type) = 0;

  /**
   * Reproduce the database file from the current Products and User values
   */
  virtual void dump(std::ostream& ofile) = 0;


};

class DStore: public DataStore
{
  public:

    DStore();
    virtual ~DStore();
    void addProduct(Product* p);
    void addUser(User* u);
    void addReview(Review* r);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    //extra functions
    void addCart(std::string username, Product* p);
    std::vector<Product*> viewCart(std::string username);
    void buyCart(std::string shopper);
    void removeCart(std::string name, int index);

    std::vector<User*> getUserVector();
    std::vector<Product*> getProductVector();
    std::vector<double> getRating();
    std::map<std::string, std::vector<Review*> > getReviewMap();
    std::map<std::string, std::vector<Product*> > getCartMap();
    std::vector<User*> UserVector;
    double avgRating();
  private:

    std::vector<Product*> ProductVector;
    std::vector<Review*> ReviewVector;
    std::vector<double> RatingVector;

    std::map<std::string, std::set<Product*> > ProductMap;
    std::map<std::string, std::vector<Product*> > cartMap;
    std::map<std::string, std::vector<Review*> > reviewMap;
};

#endif
