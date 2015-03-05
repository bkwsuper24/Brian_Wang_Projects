#ifndef MOVIE_H
#define MOVIE_H
#include "product.h"
#include <string>

class Movie: public Product
{
public:
	Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
	~Movie();
	std::set<std::string> keywords() const;
	std::string displayString() const;
	void dump(std::ostream& os) const;

	//possible get functions
	std::string getGenre() const;
	std::string getRating() const;

private:
	const std::string genre_;
	const std::string rating_;

};
#endif