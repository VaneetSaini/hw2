#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, std::string genre, std::string rating) :
	Product(category, name, price, qty)
	
{
	name_ = name;
	price_ = price;
	genre_ = genre;
	rating_ = rating;
	qty_ = qty;

}

Movie::~Movie()
{
	
}

std::set<std::string> Movie::keywords() const
{
	std::set<std::string> result;
	std::set<std::string> keyName;
	std::set<std::string> keyGenre;

	keyName = parseStringToWords(name_);
	keyGenre = parseStringToWords(genre_);
	result = setUnion(keyName, keyGenre);

	return result;
}

std::string Movie::displayString() const
{
	return name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}

